/**
 * @file Subsystem.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Subsystem base Class
 * @version 0.1
 * @date 2023-07-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "HttpRequest.hpp"
#include "libraries/json.hpp"
#include <string>

class Subsystem{
public:
    using json = nlohmann::json;

    /**
     * @brief Constructor for Root Subsystems
     */
    Subsystem();

    /**
     * @brief Constructor
     * @param parent pointer to parent subsystem
     */
    Subsystem(Subsystem* parent);

    /**
     * @brief Registers a child subsystem with its id
     * @param childId child id string, unique per parent subsystem
     * @param childNode the node
     */
    void registerChild(std::string childId, Subsystem& childNode);

    /**
     * @brief Check if the subsystem is root
     * @return true subsystem is root
     */
    bool isRoot() const;

    /**
     * @brief Set the Parent subsystem
     * @param parentNode parent subsystem
     */
    void setParent(Subsystem& parentNode);

    /**
     * @brief Get the Parent subsystem
     * @return Subsystem& parent subsystem reference
     */
    Subsystem& getParent();

    /**
     * @brief Process web request
     * @param request HTTP Request
     * @return json reply
     */
    virtual json handleWebRequest(const json& request);

    /**
     * @brief Check if a specific child exists
     * @param childId child id to check
     * @return true = child exists
     */
    bool childExists(std::string childId) const;

    /**
     * @brief Get a child by id
     * @param childId child to get
     * @return Subsystem& child reference
     */
    Subsystem& getChild(std::string childId);

    /**
     * @brief Get the All Children subsystems
     * 
     * @return std::map<std::string, Subsystem>& map of all subsystems, key = subsystem id
     */
    std::map<std::string, Subsystem*>& getAllChildren();

    /**
     * @brief Get the Own Id
     * 
     * @return std::string id
     */
    std::string getOwnId() const;

private:

    Subsystem* m_parent = nullptr;  // Pointer to the parent subsystem
    std::map<std::string, Subsystem*> m_children;    // children map
    std::string m_id;
};