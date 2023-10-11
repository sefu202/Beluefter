/**
 * @file ServerException.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Server Exception class
 * @version 0.1
 * @date 2023-07-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <exception>
#include <string>
#include "ExceptionCodes.hpp"

namespace Modbus{

class ServerException : public std::exception {
public:
    explicit ServerException(ExceptionCode exceptionCode);

    explicit ServerException(const char* message);

    virtual ~ServerException() noexcept = default;

    virtual const char* what() const noexcept;

protected:
    std::string m_msg;
};

}