#include "Snake.h"

#include <iostream>
#include <ostream>

Snake::Snake(int pi,int pj) {
    this->body.push_back({pi,pj});
}

std::pair<int,int>Snake::HeadP() {
    return this->body[0];
}

void Snake::Eat(std::pair<int,int>p) {
    this->body.insert(this->body.begin(),p);
}

int dx[]{0,-1,0,1};
int dy[]{1,0,-1,0};

void Snake::Move(int o) {
    for (int i=this->body.size()-1;i>0;i--) {
        this->body[i]=this->body[i-1];
    }
    this->body[0]={this->body[0].first+dx[o],this->body[0].second+dy[o]};
}

bool Snake::ValidMove(int o,int N,int M) const {
    std::vector<std::pair<int,int>>body2=this->body;
    for (int i=body2.size()-1;i>0;i--) body2[i]=body2[i-1];
    body2[0]={body2[0].first+dx[o],body2[0].second+dy[o]};
    for (int i=0;i<body2.size();i++) {
        if (this->body[i]==body2[0])return false;
        if (body2[i].first<1||body2[i].first>N||body2[i].second<1||body2[i].second>M)return false;
    }
    return true;
}

bool Snake::HasValid(int N, int M) const {
    for (int i=0;i<4;i++) {
        if (ValidMove(i,N,M))return true;
    }
    return false;
}

int Snake::GetState(int N,int M) const {
    int s(0);
    for (int i=0;i<4;i++) {
        s*=2,s+=ValidMove(i,N,M);
    }
    return s;
}

std::vector<std::pair<int,int>>Snake::AllBody() const {
    return this->body;
}