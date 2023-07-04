/**
 * @file HttpRequest.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>
#include <map>
#include <set>

class HttpParseError : public std::exception{
public:
    HttpParseError(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};

class HttpRequest{
public:
    HttpRequest(const std::string& requestRaw);

    const std::string& getMethod() const;
    const std::string& getUrl() const;
    const std::string& getHeader(const std::string& headerName) const;
    const std::map<std::string, std::string>& getHeaders() const;
    const std::string& getBody() const;

private:
    std::string method;
    std::string url;
    std::map<std::string, std::string> headers;
    std::string body;
    std::string httpVersion;
    const std::set<std::string> allowedMethods = {"GET", "POST"};
};