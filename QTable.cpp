#include "QTable.h"

#include <algorithm>

QTable::QTable() {
    for (int i=0;i<64;i++) {
        for (int j=0;j<4;j++) {
            this->Q[i][j]=0.0;
        }
    }
    this->alpha=0.005;
    this->gama=0.95;
    this->epsilon=1;
    this->epsilon_decay=0.995;
    this->epsilon_min=0.05;
}

int QTable::ChooseMove(int state) {
    if ((double)(rand()%1000)/1000.0 <= this->epsilon) {
        return rand()%4;
    }
    double Mx(-1e9);
    for (int i=0;i<4;i++) {
        Mx=std::max(Mx,this->Q[state][i]);
    }
    for (int i=0;i<4;i++) {
        if (this->Q[state][i]==Mx)return i;
    }
}

void QTable::Update(int oldState,int newState,int mv,double r) {
    double Mx=-1e9;
    for (int i=0;i<4;i++) {
        Mx=std::max(Mx,this->Q[newState][i]);
    }
    this->Q[oldState][mv]+=this->alpha*(r+this->gama*Mx-Q[oldState][mv]);
}

void QTable::Iter() {
    this->epsilon*=this->epsilon_decay;
    this->epsilon = std::max(this->epsilon,this->epsilon_min);
}