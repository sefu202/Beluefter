/**
 * @file MbClient.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Modbus TCP Client implementation
 * @version 0.1
 * @date 2023-07-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "MbClient.hpp"

namespace Modbus{

MbClient::MbClient(const char *url, uint16_t port) 
:   m_socket(LinuxTcpSocket::eDomain_IPv4), 
    m_port(port) 
{
    m_ipAddr = ntohl(inet_addr(url));
}

MbClient::MbClient(uint32_t ipAddr, uint16_t port) 
:   m_socket(LinuxTcpSocket::eDomain_IPv4),  
    m_ipAddr(ipAddr), m_port(port)
{

}

void MbClient::connect(){
    std::cout << "Connect\n";
    m_socket.connectSocket(m_ipAddr, m_port);
}

bool MbClient::isConnected(){
    return m_socket.isConnected();
}

void MbClient::close(){
    m_socket.closeSocket();
}

bool MbClient::readCoil(uint16_t coilAddress){
    return readCoils(coilAddress, 1)[0];
}


std::vector<bool> MbClient::readCoils(uint16_t coilAddress, uint16_t numCoils){
    return readBits(1, coilAddress, numCoils);
}


bool MbClient::readDiscreteInput(uint16_t inputAddress){
    return readCoils(inputAddress, 1)[0];
}


std::vector<bool> MbClient::readDiscreteInputs(uint16_t inputAddress, uint16_t numInputs){
    return readBits(2, inputAddress, numInputs);
}

void MbClient::writeCoil(uint16_t coilAddress, bool coilValue){
    // *** Transmit ***
    const uint8_t function = 5;
    Modbus::Protocol protocol;
    protocol.setHeader(createHeader(function));

    std::vector<uint8_t> payload;

    // Coil Address
    payload.push_back(coilAddress >> 8);
    payload.push_back(coilAddress & 0xff);

    // Coil value: Set = 0xFF00, Reset = 0x0000
    payload.push_back(coilValue ? 0xFF : 0);
    payload.push_back(0);

    protocol.setPayload(payload);
    m_socket.sendData(protocol.serialize().data(), protocol.serialize().size());

    
    // *** Receive ***
    const uint8_t rxPayloadLength = 4;
    Modbus::Protocol rxProtocol;
    rxProtocol.setHeader(receiveHeader(function));

    std::vector<uint8_t> rxBuffer;
    rxBuffer.resize(rxProtocol.getPayloadLength());
    uint16_t numRead = m_socket.readData(rxBuffer.data(), rxBuffer.size());
    rxProtocol.setPayload(std::move(rxBuffer));


    // *** Error Checking ***
    if (rxProtocol.getPayloadLength() != rxPayloadLength && numRead != rxProtocol.getPayloadLength()){
        throw std::runtime_error("Incorrect payload length");
    }

    uint16_t coilAddressReceived = rxProtocol.getPayload()[0] << 8 | rxProtocol.getPayload()[1];
    uint16_t coilValueReceived = rxProtocol.getPayload()[2] << 8 | rxProtocol.getPayload()[3];

    if (coilAddressReceived != coilAddress){
        throw std::runtime_error("Wrong coil address in Modbus function 5 reply, server error");
    }

    if ((coilValueReceived != 0xff00) && coilValue || (coilValueReceived != 0x0000) && !coilValue){
        throw std::runtime_error("Wrong coil value in Modbus function 5 reply, server error");
    }
}

std::vector<uint16_t> MbClient::readInputRegisters(uint16_t inputRegisterAddress, uint16_t numInputRegisters){
    return readRegisters(4, inputRegisterAddress, numInputRegisters);
}

std::vector<uint16_t> MbClient::readHoldingRegisters(uint16_t holdingRegisterAddress, uint16_t numHoldingRegisters){
    return readRegisters(3, holdingRegisterAddress, numHoldingRegisters);
}

std::vector<bool> MbClient::readBits(uint8_t function, uint16_t bitAddress, uint16_t numBits){

    // TODO: Check numBits for max 2008
    
    // *** Transmit ***
    Modbus::Protocol protocol;
    protocol.setHeader(createHeader(function));

    std::vector<uint8_t> payload;

    // Byte Address
    payload.push_back(bitAddress >> 8);
    payload.push_back(bitAddress & 0xff);

    // Number of Bytes
    payload.push_back(numBits >> 8);
    payload.push_back(numBits & 0xff);

    protocol.setPayload(payload);
    m_socket.sendData(protocol.serialize().data(), protocol.serialize().size());


    // *** Receive ***
    Modbus::Protocol rxProtocol;
    rxProtocol.setHeader(receiveHeader(function));

    std::vector<uint8_t> rxBuffer;
    rxBuffer.resize(rxProtocol.getPayloadLength());
    uint16_t numRead = m_socket.readData(rxBuffer.data(), rxBuffer.size()); // todo check num read

    rxProtocol.setPayload(std::move(rxBuffer));
    
    uint8_t numInputBytes = rxProtocol.getPayload()[0];

    if (numInputBytes < numBits / 8){
        throw std::runtime_error("Not enough Input bytes");
    }

    std::vector<bool> ret;

    for (uint16_t i = 0; i < numBits; i++){
        uint8_t bitNum = i % 8;
        ret.push_back((rxProtocol.getPayload()[1+i/8] >> bitNum) & 0x1);    // extract every bit beginning at Byte 1.0
    }

    return ret;
}

std::vector<uint16_t> MbClient::readRegisters(uint8_t function, uint16_t registerAddress, uint16_t numRegisters){
    // *** Transmit ***
    Modbus::Protocol protocol;
    protocol.setHeader(createHeader(function));

    std::vector<uint8_t> payload;

    // Byte Address
    payload.push_back(registerAddress >> 8);
    payload.push_back(registerAddress & 0xff);

    // Number of Bytes
    payload.push_back(numRegisters >> 8);
    payload.push_back(numRegisters & 0xff);

    protocol.setPayload(payload);
    m_socket.sendData(protocol.serialize().data(), protocol.serialize().size());


    // *** Receive ***
    Modbus::Protocol rxProtocol;
    rxProtocol.setHeader(receiveHeader(function));

    std::vector<uint8_t> rxBuffer;
    rxBuffer.resize(rxProtocol.getPayloadLength());
    uint16_t numRead = m_socket.readData(rxBuffer.data(), rxBuffer.size()); // todo check num read

    rxProtocol.setPayload(std::move(rxBuffer));
    
    uint8_t numRegisterBytes = rxProtocol.getPayload()[0];

    if (numRegisterBytes < numRegisters / 8){
        throw std::runtime_error("Not enough input bytes");
    }

    std::vector<uint16_t> ret;

    for (uint16_t i = 0; i < numRegisters; i++){
        ret.push_back(rxProtocol.getPayload()[1+i*2]<<8 | rxProtocol.getPayload()[1+i*2+1]);
    }

    return ret;

}

Modbus::Protocol::Header MbClient::createHeader(uint8_t function)
{
    Modbus::Protocol::Header header;

    header.transactionId = ++m_transactionId;
    header.protocolId = 0;
    header.unitId = m_unitId;
    header.functionCode = function;
    return header;
}

Modbus::Protocol::Header MbClient::receiveHeader(uint8_t function)
{
    std::array<uint8_t, 8> headerBuffer;
    uint16_t numRead = m_socket.readData(headerBuffer.data(),headerBuffer.size());

    Modbus::Protocol::Header rxHeader(headerBuffer);

    // Header validation
    if (
        numRead != 8 ||
        rxHeader.functionCode != function && function != 0 ||   // function code 0 = don't care
        rxHeader.protocolId != 0 ||
        rxHeader.transactionId != m_transactionId
    )
    {
        if (rxHeader.functionCode == function+128){
            throw ServerException(receiveException());
        }
        else{
            throw std::runtime_error("Invalid header received");
        }
    }

    return rxHeader;
}


ExceptionCode MbClient::receiveException(){
    uint8_t exceptionCode;
    uint16_t numRead = m_socket.readData(&exceptionCode, 1);

    if (numRead != 1){
        throw std::runtime_error("Wrong number of payload bytes received");    
    }

    return ExceptionCode(exceptionCode);
}

}