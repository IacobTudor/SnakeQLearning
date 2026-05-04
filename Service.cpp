#include "Service.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>

Service::Service(const int N,const int M) {
    this->N = N;
    this->M = M;
    Fi = rand()%N + 1;
    Fj = rand()%M + 1;
    this->qt = new QTable();
    this->s = new Snake(1,1);
}

Service::~Service() {
    delete this->qt;
    delete this->s;
}

int Service::GetState() {
    bool FoodUp = this->s->HeadP().first < Fi;
    bool FoodRight = this->s->HeadP().second < Fj;
    return this->s->GetState(N,M)*4 + 2*FoodUp + FoodRight;
}

bool In(std::pair<int,int>p,std::vector<std::pair<int,int>>Body) {
    for (int i=0;i<Body.size();i++) {
        if (p==Body[i])return true;
    }
    return false;
}

double Service::MakeMove(int o) {
    int dx[]{0,-1,0,1};
    int dy[]{1,0,-1,0};
    if (!this->s->ValidMove(o,this->N,this->M)) {
        return -1.0;
    }
    if (Fi == this->s->HeadP().first + dx[o] && Fj == this->s->HeadP().second + dy[o]) {
        this->s->Eat({Fi,Fj});
        Fi = rand()%N + 1;
        Fj = rand()%M + 1;
        while (In({Fi,Fj},this->s->AllBody())) {
            Fi = rand()%N + 1;
            Fj = rand()%M + 1;
        }
        return 1.0;
    }
    int d1(abs(Fi - this->s->HeadP().first)+abs(Fj - this->s->HeadP().second));
    this->s->Move(o);
    int d2(abs(Fi - this->s->HeadP().first)+abs(Fj - this->s->HeadP().second));
    return (d1-d2)*0.05-0.01;
}

void RenderGrid(sf::RenderWindow& window,const std::vector<std::vector<char>>& a,int N, int M){
    const int cellSize = 80;
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            char c = a[i][j];
            cell.setPosition(sf::Vector2f((j - 1) * cellSize,(i - 1) * cellSize));
            if (c == '.')cell.setFillColor(sf::Color(30, 30, 30));
            else if (c == '#')cell.setFillColor(sf::Color::Green);
            else if (c == 'H')cell.setFillColor(sf::Color::Yellow);
            else if (c == '*')cell.setFillColor(sf::Color::Red);
            window.draw(cell);
        }
    }
}

void Service::Simulate(bool print) {
    delete this->s;
    this->s = new Snake(1,1);
    int turns(0);

    if (print) {

        sf::RenderWindow window(sf::VideoMode(sf::Vector2u(M * 80, N * 80)), "Snake");
        sf::Clock clock;

        while (this->s->HasValid(this->N,this->M) && turns <= 1000) {
            int state = this->GetState();
            int mv = this->qt->ChooseMove(state);
            double r = MakeMove(mv);
            this->qt->Update(state, this->GetState(), mv, r);
            turns++;

            while (auto event = window.pollEvent()){
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
            if (!window.isOpen()) break;

            std::vector<std::vector<char>> a(N + 1, std::vector<char>(M + 1, '.'));
            std::vector<std::pair<int,int>>Body(this->s->AllBody());
            for (int i=1;i<Body.size();i++)a[Body[i].first][Body[i].second]='#';
            a[Body[0].first][Body[0].second]='H';
            a[Fi][Fj]='*';

            window.clear();
            RenderGrid(window, a, N, M);
            window.display();

            while (clock.getElapsedTime().asSeconds() < 0.33f) {
                while (auto event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                        window.close();
                }
                if (!window.isOpen()) break;
            }
            clock.restart();
        }
    } else {
        while (this->s->HasValid(this->N,this->M) && turns <= 1000) {
            int state = this->GetState();
            int mv = this->qt->ChooseMove(state);
            double r = MakeMove(mv);
            this->qt->Update(state, this->GetState(), mv, r);
            turns++;
        }
    }
}

void Service::train(int iter) {
    for (int i = 0 ; i < iter ; i++) {
        Simulate(i==iter-1);
        this->qt->Iter();
    }
}