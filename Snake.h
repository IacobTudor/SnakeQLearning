#ifndef SNAKEQLEARNING_SNAKE_H
#define SNAKEQLEARNING_SNAKE_H

#include<vector>

class Snake {
private:
    std::vector<std::pair<int,int>>body;
public:
    Snake(int pi,int pj);
    std::pair<int,int>HeadP();
    void Move(int o);
    void Eat(std::pair<int,int>p);
    bool ValidMove(int o,int N,int M) const;
    bool HasValid(int N,int M) const;
    int GetState(int N,int M) const;
    std::vector<std::pair<int,int>>AllBody() const;
};


#endif //SNAKEQLEARNING_SNAKE_H