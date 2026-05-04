#ifndef SNAKEQLEARNING_SERVICE_H
#define SNAKEQLEARNING_SERVICE_H

#include "QTable.h"
#include "Snake.h"

#include <cstdlib>
#include <ctime>

class Service {
private:
    QTable* qt;
    Snake* s;
    int N,M,Fi,Fj;
public:
    Service(int N,int M);
    void train(int iter);
    void Simulate(bool print);
    int GetState();
    double MakeMove(int o);
    ~Service();
};


#endif //SNAKEQLEARNING_SERVICE_H