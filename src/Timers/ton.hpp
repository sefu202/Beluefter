/**
 * @file ton.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief TON Timer
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 * /

#pragma once
#include <chrono>

struct TON{
public:
    bool operator() ();
    bool operator() (std::chrono::milliseconds pt_in, bool in_in);

    bool in;
    std::chrono::milliseconds pt;
    std::chrono::milliseconds et;
    bool Q;

private:
    void update();

    std::chrono::time_point<std::chrono::system_clock> start;
    bool M;

}; */