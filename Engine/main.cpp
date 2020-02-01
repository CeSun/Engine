//
// Created by ce.a.sun on 2019/12/18.
//
#include <iostream>
#include "CEngine/CEngine.h"


int main(){
    std::cout<< "Hello Engine" << std::endl;
    using namespace GameClient;
    CEngine engine;
    engine.run();
    return 0;
}