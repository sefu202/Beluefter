/**
 * @file ExceptionCodes.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Modbus Exception codes
 * @version 0.1
 * @date 2023-01-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <string>

namespace Modbus{
    enum class ExceptionCode {
        eIllegalFunction = 1,           /**< Function code received in the query is not recognized or allowed by server */
        eIllegalDataAddress = 2,        /**< Data address of some or all the required entities are not allowed or do not exist in server */
        eIllegalDataValue = 3,          /**< Value is not accepted by server */
        eServerDeviceFailure = 4,       /**< Unrecoverable error occurred while server was attempting to perform requested action */
        eAck = 5,                       /**< Server has accepted request and is processing it, but a long duration of time is required. This response is returned to prevent a timeout error from occurring in the client. client can next issue a Poll Program Complete message to determine whether processing is completed */
        eServerBusy = 6,                /**< Server is engaged in processing a long-duration command; client should retry later */
	    eNack = 7,                      /**< Server cannot perform the programming functions; client should request diagnostic or error information from server */
        eMemoryParityError = 8,         /**< Server detected a parity error in memory; client can retry the request */
        eGatewayPathUnavailable = 10,   /**< Specialized for Modbus gateways: indicates a misconfigured gateway */
        eGatewayTargetNoResponse = 11   /**< Specialized for Modbus gateways: sent when server fails to respond */
    };

    inline std::string ExceptionCodeToString(ExceptionCode exeptionCode){
        switch (exeptionCode) {
            case ExceptionCode::eIllegalFunction:
                return "eIllegalFunction";
                break;
            case ExceptionCode::eIllegalDataAddress:
                return "eIllegalDataAddress";
                break;
            case ExceptionCode::eIllegalDataValue:
                return "eIllegalDataValue";
                break;
            case ExceptionCode::eServerDeviceFailure:
                return "eServerDeviceFailure";
                break;
            case ExceptionCode::eAck:
                return "eAck";
                break;
            case ExceptionCode::eServerBusy:
                return "eServerBusy";
                break;
            case ExceptionCode::eNack:
                return "eNack";
                break;
            case ExceptionCode::eMemoryParityError:
                return "eMemoryParityError";
                break;
            case ExceptionCode::eGatewayPathUnavailable:
                return "eGatewayPathUnavailable";
                break;
            case ExceptionCode::eGatewayTargetNoResponse:
                return "eGatewayTargetNoResponse";
                break;
        }
        return "Invalid exception code";
    }
}
