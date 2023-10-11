/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <string>

#include "Socket/LinuxTcpSocket.hpp"
#include "HmiButton.hpp"

#include "HttpRequest.hpp"
#include "Heubelueftung.hpp"
#include "libraries/json.hpp"

void printTree(std::string path, Subsystem& subsystem){
    std::cout << path << std::endl;
    if (!subsystem.getAllChildren().empty()){
        /*for (auto& [childId, child] : subsystem.getAllChildren()){
            printTree(path + "/"+ childId, child);
        }*/
    }
}


int main() {
    using nlohmann::json;
    
    LinuxTcpSocket tcpSocket(LinuxTcpSocket::eDomain_IPv4);
    tcpSocket.bindSocket(64969);
    tcpSocket.listenSocket();

    Heubelueftung heubelueftung;

    while(1){
        auto conSocket = tcpSocket.acceptConnection();
        uint8_t buffer[1024];
        size_t buflen = conSocket.readData(buffer, sizeof(buffer));

        auto request = std::string();

        for (unsigned int i = 0; i < buflen; i++){
            request.push_back(buffer[i]);
        }
        HttpRequest httpRequest(request);

        /*std::cout << "URL: " << httpRequest.getUrl() << std::endl;
        for (auto& segment : httpRequest.getUrlSegments()){
            std::cout << "/"<< segment;
        }
        std::cout << std::endl;*/

        try{
            json req = nullptr;
            if (httpRequest.getMethod() == "POST"){
                req = json::parse(httpRequest.getBody());
            }

            std::string sendbuffer = "HTTP/1.0 200 OK\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
            sendbuffer += heubelueftung.handleWebRequest(req).dump(4) + "\r\n\r\n";
            conSocket.sendData((uint8_t *)sendbuffer.data(), sendbuffer.size());
        }
        catch(...){

        }

        conSocket.closeSocket();
    }
    tcpSocket.closeSocket();

    return 0;
}