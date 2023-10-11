/**
 * @file LinuxTcpSocket.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Linux tcp socket implementation
 * @version 0.1
 * @date 2023-01-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "LinuxTcpSocket.hpp"

LinuxTcpSocket::LinuxTcpSocket(EDomain domain) : m_domain(domain){
    openSocket();
}

LinuxTcpSocket::LinuxTcpSocket(const LinuxTcpSocket& parent, uint16_t port, ipAddress ipAddr, int socket) 
: m_parentSocket(&parent) 
, m_connectedPort(port)
, m_connectedAddress(ipAddr)
, m_socket(socket)
, m_isOpen(true) {

}

void LinuxTcpSocket::bindSocket(uint16_t port, ipAddress interface){
    int opt = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE | SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        throw std::runtime_error(std::string("LinuxTcpSocket::bindSocket(): setsockopt(SOL_SOCKET, SO_KEEPALIVE | SO_REUSEADDR | SO_REUSEPORT) failed, reason: ") + strerror(errno));
    }

    int domain = m_domain == eDomain_Local ? AF_LOCAL : m_domain == eDomain_IPv4 ? AF_INET : AF_INET6;
    struct sockaddr_in address;
    address.sin_family = domain;
    address.sin_addr.s_addr = htonl(interface);
    address.sin_port = htons(port);
    if (bind(m_socket, (struct sockaddr*) &address, sizeof(address)) < 0) {
        throw std::runtime_error(std::string("LinuxTcpSocket::bindSocket(): bind() failed, reason: ") + strerror(errno));
    }
}

void LinuxTcpSocket::listenSocket(uint16_t backlogSize) {
    if (listen(m_socket, backlogSize) < 0){
        throw std::runtime_error(std::string("LinuxTcpSocket::listenSocket(): listen() failed, reason: ") + strerror(errno));
    }
}

LinuxTcpSocket LinuxTcpSocket::acceptConnection() {
    struct sockaddr_in address;
    size_t addrlen = sizeof(address);
    int newSocket = accept(m_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    if (newSocket < 0){
        throw std::runtime_error(std::string("LinuxTcpSocket::acceptConnection(): accept() failed, reason: ") + strerror(errno));
    }

    LinuxTcpSocket newTcpSocket(*this, ntohs(address.sin_port), /*ntohl(address.sin_addr)*/ 0, newSocket);

    return newTcpSocket;
}

void LinuxTcpSocket::connectSocket(ipAddress ipAddr, uint16_t port){
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(ipAddr);
    servaddr.sin_port = htons(port);

    if (connect(m_socket, (struct sockaddr*)&servaddr, sizeof(servaddr))  != 0){
        throw std::runtime_error(std::string("LinuxTcpSocket::connectSocket(): connect() failed, reason: ") + strerror(errno));
    }
    m_isConnected = true;
}

size_t LinuxTcpSocket::readData(uint8_t *buffer, size_t maxBufferSize) {
    ssize_t readRes = read(m_socket, buffer, maxBufferSize);
    if (readRes < 0) {
        throw std::runtime_error(std::string("LinuxTcpSocket::read(): failed, reason: ") + strerror(errno));
    }
    return size_t(readRes);
}

void LinuxTcpSocket::sendData(const uint8_t *buffer, size_t bufferSize) {
    ssize_t sendRes = send(m_socket, buffer, bufferSize, 0);
    if (sendRes < 0) {
        throw std::runtime_error(std::string("LinuxTcpSocket::send(): failed, reason: ") + strerror(errno));
    }
}

void LinuxTcpSocket::closeSocket() {
    close(m_socket);
}


void LinuxTcpSocket::openSocket() {
    int domain = m_domain == eDomain_Local ? AF_LOCAL : m_domain == eDomain_IPv4 ? AF_INET : AF_INET6;
    m_socket = socket(domain, SOCK_STREAM, 0);

    if (m_socket < 0){
        throw std::runtime_error("LinuxTcpSocket::openSocket(): Failed to create socket");
    }

    m_isOpen = true;
}


bool LinuxTcpSocket::isConnected() const {
    return m_isConnected;
}