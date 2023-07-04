/**
 * @file HmiButton.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Button for HMI
 * @version 0.1 Created class
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <string>
#include "HttpRequest.hpp"
#include "Subsystem.hpp"
#include "libraries/json.hpp"

class Widget : public Subsystem {

};

/**
 * @class HmiButton 
 * @brief Button for HMI visu
 */
class HmiButton : public Widget {
public:
    using json = nlohmann::json;
    /**
     * @brief Handles Web Request
     * @param request received request
     * @return json reply
     */
    json handleWebRequest(const HttpRequest& request);

    /**
     * @brief Set the State of the button
     * @param isOn true = on 
     */
    void setState(bool isOn);

    /**
     * @brief Disable / enable button
     * @param isDisabled true = disable button
     */
    void setDisabled(bool isDisabled);

    /**
     * @brief Make the button visible / invisible
     * @param isVisible true = set button visible
     */
    void setVisible(bool isVisible);

    /**
     * @brief Set error message for disabled button
     * @param errorOnClick message to show when the button is clicked illegalley
     */
    void setErrorOnClick(const std::string errorOnClick);

    /**
     * @brief check if the button is on
     * @return true = button is on
     */
    bool isOn() const;

    /**
     * @brief Check if the button is disabled
     * @return true = button is disabled
     */
    bool isDisabled() const;

    /**
     * @brief Check if the button is visible
     * @return true = button is visible
     */
    bool isVisible() const;

private:
    bool m_isOn = false;            // State of the button
    bool m_isDisabled = false;      // Button disabled
    bool m_isVisible = true;        // button visible
    std::string m_errorOnClick;     // error message when button is clicked while disabled
};