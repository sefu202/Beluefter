/**
 * @file ServerException.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ServerException.hpp"

namespace Modbus{

ServerException::ServerException(ExceptionCode exceptionCode) : m_msg(ExceptionCodeToString(exceptionCode)){
    
}

ServerException::ServerException(const char* message) : m_msg(message){

}


const char* ServerException::what() const noexcept {
    return m_msg.c_str();
}

}