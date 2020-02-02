//
// Created by ce.a.sun on 2019/12/18.
//
#include <iostream>
#include "CEngine/CEngine.h"


int main(){

    using namespace std;
    cout<< "Hello Engine" << endl;
    using namespace GameClient;
    CEngine engine;
    engine.run();

    cout << "Game End" << endl;
    return 0;
}