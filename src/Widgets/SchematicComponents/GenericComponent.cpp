/**
 * @file GenericComponent.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Generic Schematic compenent Implementation
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "GenericComponent.hpp"

GenericComponent::GenericComponent(){}

GenericComponent::GenericComponent(std::string color, std::string bmk, std::string name, bool blink){
    m_color = color;
    m_bmk = bmk;
    m_name = name;
    m_blink = blink;
}

nlohmann::json GenericComponent::handleWebRequest(const json &request)
{
    json j;
    j["color"] = m_color;
    j["bmk"] = m_bmk;
    j["name"] = m_name;
    j["blink"] = m_blink;

    return j;
}

void GenericComponent::setColor(std::string color)
{
    m_color = color;
}
void GenericComponent::setBmk(std::string bmk){
    m_bmk = bmk;
}
void GenericComponent::setName(std::string name){
    m_name = name;
}
void GenericComponent::setBlink(bool blink){
    m_blink = blink;
}
