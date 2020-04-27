//
// Created by ce.a.sun on 2019/12/18.
//

#include <Client/CClient/CClient.hpp>
#include <Common/CLog/CLog.hpp>

int main(){

    using namespace GameClient;

    APP_LOG_INFO("Game Start");
    CClient& client = CClient::intance();
    client.run();
    APP_LOG_INFO("Game End");
    return 0;
}