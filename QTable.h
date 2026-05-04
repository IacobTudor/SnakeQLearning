#ifndef SNAKEQLEARNING_QTABLE_H
#define SNAKEQLEARNING_QTABLE_H

#include <cstdlib>
#include <ctime>

class QTable {
private:
    double Q[64][4];
    double alpha,gama,epsilon,epsilon_min,epsilon_decay;
public:
    QTable();
    int ChooseMove(int state);
    void Update(int oldState,int newState, int mv, double r);
    void Iter();
};


#endif //SNAKEQLEARNING_QTABLE_H