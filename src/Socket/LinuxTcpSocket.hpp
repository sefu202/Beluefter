/**
 * @file LinuxTcpSocket.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Linux Tcp socket abstraction
 * @version 0.1
 * @date 2023-01-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LINUX_TCP_SOCKET
#define LINUX_TCP_SOCKET 1

#include "ITcpSocket.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

/**
 * @class LinuxTcpSocket
 * @brief Tcp Socket class for linux
 * 
 */
class LinuxTcpSocket {
public:
    enum EDomain{
        eDomain_Local = 0,
        eDomain_IPv4,
        eDomain_IPv6,
    };

    using ipAddress = uint32_t;
    static const uint32_t inaddr_any = 0;

    LinuxTcpSocket(EDomain domain);

    void bindSocket(uint16_t port, ipAddress interface = inaddr_any);

    void listenSocket(uint16_t backlogSize = 1);

    LinuxTcpSocket acceptConnection();

    size_t readData(uint8_t *buffer, size_t maxBufferSize);

    void sendData(const uint8_t *buffer, size_t bufferSize);

    void closeSocket();

protected:
    void openSocket();

    /**
     * @brief Create child (communication) socket
     * 
     * @param parent parent socket
     * @param port partner port
     * @param ipAddr partner ip
     * @param socket socket id
     */
    LinuxTcpSocket(const LinuxTcpSocket& parent, uint16_t port, ipAddress ipAddr, int socket);

    EDomain m_domain;                               /**< Domain of the Socket (IPv4/IPv6/Local) */
    bool m_isOpen = false;                          /**< Flag to indicate if the socket is open */
    int m_socket = 0;                               /**< Socket handle from linux */
    const LinuxTcpSocket *m_parentSocket = nullptr; /**< Parent socket */
    ipAddress m_connectedAddress = uint32_t(0);     /**< IP Address of the other endpoint */
    uint16_t m_connectedPort = 0;                   /**< Port of the other endpoint */
};


#endif  /* LINUX_TCP_SOCKET */