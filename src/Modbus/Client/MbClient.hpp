/**
 * @file MbClient.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Modbus TCP Client
 * @version 0.1
 * @date 2023-07-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <iostream>
#include <fstream>
#include <arpa/inet.h>

#include "Socket/LinuxTcpSocket.hpp"
#include "Modbus/Data/Protocol.hpp"
#include "Data/ServerException.hpp"

namespace Modbus{

/**
 * @class MbClient
 * @brief 
 */
class MbClient {
public:
    MbClient(const char *url, uint16_t port);
    MbClient(uint32_t ipAddr, uint16_t port);

    /**
     * @brief Connects to the Server
     */
    void connect();

    /**
     * @brief Checks if the server is connected
     */
    bool isConnected();

    /**
     * @brief Closes the connection
     */
    void close();

    /**
     * @brief Reads a single coil (modbus function 1)
     * 
     * @param coilAddress Address of the coil
     * @return coilValue
     */
    bool readCoil(uint16_t coilAddress);

    /**
     * @brief Reads multiple coils (modbus function 1)
     * 
     * @param coilAddress Address of the first coil
     * @param numCoils number of coils to read
     * @return std::vector<bool> coil values
     */
    std::vector<bool> readCoils(uint16_t coilAddress, uint16_t numCoils);

    /**
     * @brief Reads single discrete input (modbus function 2)
     * 
     * @param inputAddress Address of the input 
     * @return input value
     */
    bool readDiscreteInput(uint16_t inputAddress);

    /**
     * @brief Reads multiple discrete inputs (modbus function 2)
     * 
     * @param inputAddress Address of the first Input
     * @param numInputs numer of inputs to read 
     * @return std::vector<bool> input values
     */
    std::vector<bool> readDiscreteInputs(uint16_t inputAddress, uint16_t numInputs);

    /**
     * @brief Writes single coil (modbus function 5)
     * 
     * @param coilAddress Address of the coil to write
     * @param coilValue value to write
     */
    void writeCoil(uint16_t coilAddress, bool coilValue);

    /**
     * @brief Reads input registers (modbus function 4)
     * 
     * @param inputRegisterAddress address of first input register
     * @param numInputRegisters number of input registers to read (max 125 simultaniously)
     * @return std::vector<uint16_t> input register values
     */
    std::vector<uint16_t> readInputRegisters(uint16_t inputRegisterAddress, uint16_t numInputRegisters);
    
    /**
     * @brief Reads holding registers (modbus function 3)
     * 
     * @param holdingRegisterAddress address of first holding register
     * @param numHoldingRegisters number of holding registers to read (max 125 simultaniously)
     * @return std::vector<uint16_t> holding register values
     */
    std::vector<uint16_t> readHoldingRegisters(uint16_t holdingRegisterAddress, uint16_t numHoldingRegisters);

private:

    /**
     * @brief Implements modbus function 1 and 2
     * 
     * @param function Function to execute (1 for read coils, 2 for read discrete inputs)
     * @param bitAddress address of the first bit to read
     * @param numBits number of bits to read
     * @return std::vector<bool> bit values
     */
    std::vector<bool> readBits(uint8_t function, uint16_t bitAddress, uint16_t numBits);

    /**
     * @brief Implements modbus function 3 and 4
     * 
     * @param function Function to execute (3 for read holding registers, 4 for read input registers)
     * @param registerAddress address of the first register to read
     * @param numRegisters number of registers to read
     * @return std::vector<uint16_t> register values
     */
    std::vector<uint16_t> readRegisters(uint8_t function, uint16_t registerAddress, uint16_t numRegisters);

    /**
     * @brief Create a Header
     * 
     * @param function function to create the header for
     * @return Modbus::Protocol::Header new header
     */
    Modbus::Protocol::Header createHeader(uint8_t function);

    /**
     * @brief Receives Modbus Protocol Header
     * 
     * @param function function code to check (0 = don't care)
     * @return Modbus::Protocol::Header 
     */
    Modbus::Protocol::Header receiveHeader(uint8_t function);

    /**
     * @brief Receives Modbus exception code
    */
    ExceptionCode receiveException();

    LinuxTcpSocket m_socket;
    uint32_t m_ipAddr; 
    uint16_t m_port;
    uint16_t m_transactionId = 0;

    uint8_t m_unitId = 255;
    
};


}