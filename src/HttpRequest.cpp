/**
 * @file HttpRequest.cpp
 * @author Josef Aschwanden
 * @brief 
 * @version 0.1
 * @date 2023-06-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

#include "HttpRequest.hpp"


HttpParseError::HttpParseError(const std::string& message) : message(message){}

const char* HttpParseError::what() const noexcept {
    return message.c_str();
}

HttpRequest::HttpRequest(const std::string& requestRaw){
    std::istringstream iss(requestRaw);
    std::string line;
    std::getline(iss, line);
    std::istringstream requestLineStream(line);
    requestLineStream >> method;

    if (allowedMethods.find(method) == allowedMethods.end()){
        throw HttpParseError("Invalid Method");
    }
    requestLineStream >> url;
    requestLineStream >> httpVersion;
    if (httpVersion != "HTTP/1.1"){
        throw HttpParseError("Invalid HTTP Version, use HTTP/1.1");
    }

    uint8_t lineWithoutContent = 0;
    while(std::getline(iss,line)){
        if (line != "\r" && line != ""){    // accept both \r\n and \n
            // headers
        }
        else{
            break;
        }
    }

    while(std::getline(iss, line)){
        body += line+"\n";
    }
}

const std::string& HttpRequest::getMethod() const{
    return method;
}
const std::string& HttpRequest::getUrl() const{
    return url;
}

const std::vector<std::string> HttpRequest::getUrlSegments() const {
    std::vector<std::string> segments;
    std::string segment;
    std::stringstream ss(getUrl());

    if (getUrl()[0] == '/'){
        std::getline(ss, segment, '/');
    }

    while(std::getline(ss, segment, '/')){
        if (segment == ""){
            throw std::runtime_error("Invalid url string");
        }
        segments.push_back(segment);
    }
    return segments;
}

const std::string& HttpRequest::getHeader(const std::string& headerName) const{
    return headers.at(headerName);
}
const std::map<std::string, std::string>& HttpRequest::getHeaders() const{
    return headers;
}
const std::string& HttpRequest::getBody() const{
    return body;
}