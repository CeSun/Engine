//
// Created by ce.a.sun on 2019/12/18.
//
#include <iostream>
#include "src/Client/CClient/CClient.hpp"


int main(){
    using namespace std;
    using namespace GameClient;

    cout << "Game Start" << endl;
    CClient& client = CClient::getIntance();
    client.run();
    cout << "Game End" << endl;
    return 0;
}