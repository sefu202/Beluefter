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
#include "_HmiButton.hpp"

#include "HttpRequest.hpp"
#include "Heubelueftung.hpp"
#include "libraries/json.hpp"


int main() {
    using nlohmann::json;
    
    LinuxTcpSocket tcpSocket(LinuxTcpSocket::eDomain_IPv4);
    tcpSocket.bindSocket(64969);
    tcpSocket.listenSocket();

    json heubelueftungCfg;
    json heubelueftungCfgProperties;
    heubelueftungCfgProperties["tachometer"] = true;
    heubelueftungCfgProperties["control-types"] = std::array<std::string,2>({"local", "remote"});
    heubelueftungCfgProperties["control-modes"] = std::array<std::string,2>({"manual", "auto"});

    heubelueftungCfg["properties"] = heubelueftungCfgProperties;

    Heubelueftung heubelueftung();

    /*HmiButton btnRcOn;
    HmiButton btnAuto;
    HmiButton btnOn;

    btnRcOn.setDisabled(true);
    btnRcOn.setState(true);
    btnRcOn.setErrorOnClick("This button only displays status");*/

    while(1){
        auto conSocket = tcpSocket.acceptConnection();
        uint8_t buffer[1024];
        size_t buflen = conSocket.readData(buffer, sizeof(buffer));

        auto request = std::string();

        for (unsigned int i = 0; i < buflen; i++){
            request.push_back(buffer[i]);
        }
        HttpRequest httpRequest(request);

        
        std::string response;

        //const auto response = heubelueftung.handleWebRequest(httpRequest.getUrl(),httpRequest.getBody());
        /*if (httpRequest.getUrl().find("btnRcOn") != std::string::npos){
            response = btnRcOn.handleWebRequest(httpRequest);
        }
        if (httpRequest.getUrl().find("btnAuto") != std::string::npos){
            response = btnAuto.handleWebRequest(httpRequest);
        }
        if (httpRequest.getUrl().find("btnOn") != std::string::npos){
            response = btnOn.handleWebRequest(httpRequest);
        }

        btnOn.setDisabled(btnAuto.isOn() || !btnRcOn.isOn());
        btnAuto.setDisabled(!btnRcOn.isOn());

        if (!btnRcOn.isOn()){
            btnOn.setErrorOnClick("Remote control not enabled");
        }
        if (btnAuto.isOn()){
            btnOn.setErrorOnClick("Automatic control enabled");
        }*/
        

        std::string sendbuffer = "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
        sendbuffer += response + "\r\n\r\n";

        conSocket.sendData((uint8_t *)sendbuffer.data(), sendbuffer.size());
        conSocket.closeSocket();
    }
    tcpSocket.closeSocket();

    return 0;
}