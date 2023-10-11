/**
 * @file Protocol.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Modbus Protocol container
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Protocol.hpp"

namespace Modbus{

Protocol::Header::Header(
    uint16_t transactionId,
    uint16_t protocolId,
    uint16_t length,
    uint8_t  unitId,
    uint8_t  functionCode
) 
: transactionId(transactionId)
, protocolId(protocolId)
, length(length)
, unitId(unitId)
, functionCode(functionCode){
}

std::array<uint8_t, 8> Protocol::Header::serialize() const {
    std::array<uint8_t, 8> binaryHeader;

    binaryHeader[0] = static_cast<uint8_t>(transactionId >> 8);
    binaryHeader[1] = static_cast<uint8_t>(transactionId);
    binaryHeader[2] = static_cast<uint8_t>(protocolId >> 8);
    binaryHeader[3] = static_cast<uint8_t>(protocolId);
    binaryHeader[4] = static_cast<uint8_t>(length >> 8);
    binaryHeader[5] = static_cast<uint8_t>(length);
    binaryHeader[6] = unitId;
    binaryHeader[7] = functionCode;

    return binaryHeader;
}

Protocol::Header::Header(const std::array<uint8_t, 8> &binaryHeader){
    transactionId   = static_cast<uint16_t>(binaryHeader[0]) << 8 | binaryHeader[1];
    protocolId      = static_cast<uint16_t>(binaryHeader[2]) << 8 | binaryHeader[3];
    length          = static_cast<uint16_t>(binaryHeader[4]) << 8 | binaryHeader[5];
    unitId          = binaryHeader[6];
    functionCode    = binaryHeader[7];
}

void Protocol::setHeader(Header setheader){
    header = setheader;
}

const Protocol::Header& Protocol::getHeader() const {
    return header;
}

void Protocol::setPayload(const std::vector<uint8_t>& iPayload){
    header.length = iPayload.size() + Header::offsetLengthPayloadLength;
    payload = iPayload;
}

void Protocol::setPayload(std::vector<uint8_t> &&iPayload){
    header.length = iPayload.size() + Header::offsetLengthPayloadLength;
    payload = std::move(iPayload);
}

const std::vector<uint8_t> &Protocol::getPayload() const{
    return payload;
}

uint16_t Protocol::getPayloadLength() const {
    return header.length - Header::offsetLengthPayloadLength;
}

std::vector<uint8_t> Protocol::serialize() const
{
    std::vector<uint8_t> ret;
    Header headerCopy = header;
    headerCopy.length = payload.size() + Header::offsetLengthPayloadLength;
    const auto serializedHeader = headerCopy.serialize();

    ret.insert(ret.end(), serializedHeader.begin(), serializedHeader.end());
    ret.insert(ret.end(), payload.begin(), payload.end());

    return ret;
}
}