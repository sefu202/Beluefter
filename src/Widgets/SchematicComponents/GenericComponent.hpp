/**
 * @file GenericComponent.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Generisches Schemabauelement
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <string>
#include "Widgets/Widget.hpp"

class GenericComponent : public Widget{
public:
    using json = nlohmann::json;
    
    GenericComponent();
    GenericComponent(std::string color, std::string bmk, std::string name, bool blink);

    /**
     * @brief Handles Web Request
     * @param request received request
     * @return json reply
     */
    virtual json handleWebRequest(const json& request) override;

    void setColor(std::string color);

    void setBmk(std::string bmk);
    void setName(std::string name);
    void setBlink(bool blink);

private:
    std::string m_color = "";
    std::string m_bmk = "";
    std::string m_name = "";
    bool m_blink = false;
};