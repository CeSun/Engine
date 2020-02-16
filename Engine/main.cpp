//
// Created by ce.a.sun on 2019/12/18.
//
#include <iostream>
#include "CEngine/CEngine.hpp"


int main(){
    using namespace std;
    using namespace GameClient;

    cout << "Game Start" << endl;
    CEngine engine;
    engine.run();

    cout << "Game End" << endl;
    return 0;
}