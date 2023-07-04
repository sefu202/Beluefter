/**
 * @file ITcpSocket.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Tcp socket interface
 * @version 0.1
 * @date 2023-01-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <cstdint>
#include <list>

class ITcpSocket{
public:
    enum EDomain{
        eDomain_Local = 0,
        eDomain_IPv4,
        eDomain_IPv6,
    };

    using ipAddress = uint32_t;
    static const uint32_t inaddr_any = 0;

    ITcpSocket(EDomain domain); // only ipv4 yet

    virtual ~ITcpSocket() = default;

    virtual void bind(uint16_t port, ipAddress interface = inaddr_any) = 0;

    virtual void listen(uint16_t backlogSize = 1) = 0;

    virtual ITcpSocket& accept() = 0;

    virtual size_t read(uint8_t *buffer, size_t maxBufferSize) = 0;

    virtual void send(uint8_t *buffer, size_t bufferSize) = 0;

    virtual void close() = 0;

protected:

    ITcpSocket(const ITcpSocket& other);

    EDomain m_domain;
    bool m_isOpen = false;
    int m_socket = 0;
    const ITcpSocket *m_parentSocket = nullptr;
    ipAddress m_connectedAddress = uint32_t(0);
    uint16_t m_connectedPort = 0;
};