/**
 * @file Protocol.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Modbus protocol container
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H 1

#include <vector>
#include <array>

/**
 * @namespace Modbus
 * @brief Modbus Namespace
 */
namespace Modbus{

/**
 * @class Protocol
 * @brief Modbus protocol container
 */
class Protocol{
public:
    /**
     * @struct Header
     * @brief struct representing a modbus TCP header
     */
    struct Header{

        /**
         * @brief Empty initialisation
         * 
         */
        Header() = default;

        /**
         * @brief Binary value initialisation
         * 
         * @param binaryHeader header as received on tcp
         */
        Header(const std::array<uint8_t, 8> &binaryHeader);

        /**
         * @brief Value initialisation
         */
        Header(uint16_t transactionId, uint16_t protocolId, uint16_t length, uint8_t  unitId, uint8_t  functionCode);

        /**
         * @brief serializes the header
         * 
         * @return std::array<uint8_t, 8> header as sent on tcp
         */
        std::array<uint8_t, 8> serialize() const;

        uint16_t    transactionId = 0;  /**< transaction id */
        uint16_t    protocolId = 0;     /**< protocol id */
        uint16_t    length = 0;         /**< length of the payload + unitId + functionCode */
        uint8_t     unitId = 0;         /**< unit id */
        uint8_t     functionCode = 0;   /**< functionCode */

        static constexpr uint16_t offsetLengthPayloadLength = 2;   /**< How much lenght is bigger than the actual payload length */
    };

    /**
     * @brief Set the Header
     * @param header Header struct
     */
    void setHeader(Header header);

    /**
     * @brief Get the Header
     * 
     * @return Header struct reference
     */
    const Header& getHeader() const;
    
    /**
     * @brief Set the Payload
     * 
     * @note overrides header payload if it differs from the actual payload size
     * @param iPayload protocol payload input
     */
    void setPayload(const std::vector<uint8_t>& iPayload);

    /**
     * @brief Set the Payload with move
     * 
     * @note overrides header payload if it differs from the actual payload size
     * @param iPayload protocol payload input
     */
    void setPayload(std::vector<uint8_t>&& iPayload);

    /**
     * @brief Get the Payload object
     * 
     * @return const std::vector<uint8_t> reference to payload
     */
    const std::vector<uint8_t>& getPayload() const;

    /**
     * @brief Get the Payload Length
     * 
     * @return uint16_t payload length in bytes
     */
    uint16_t getPayloadLength() const;

    /**
     * @brief Serializes the protocol
     * @return std::vector<uint8_t> serialized protocol
     */
    std::vector<uint8_t> serialize() const;

private:
    Header header;                  /**< Protocol Header */
    std::vector<uint8_t> payload;   /**< Protocol Payload */
};

}

#endif /*PROTOCOL_H*/