#include<iostream>
#include "Service.h"
using namespace std;
int main() {
    srand(time(nullptr));
    Service sv(6,10);
    sv.train(10000);
    return 0;
}