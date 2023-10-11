#include "Subsystem.hpp"
/**
 * @file Subsystem.cpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief Subsystem base Class
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Subsystem.hpp"

Subsystem::Subsystem() {
    m_parent = this;
}

Subsystem::Subsystem(Subsystem *parent) : m_parent(parent) {

}

void Subsystem::registerChild(std::string childId, Subsystem& childNode){
    m_children[childId] = &childNode;
    childNode.m_id = childId;
    childNode.setParent(*this);
}

bool Subsystem::isRoot() const {
    return this == m_parent;
}

void Subsystem::setParent(Subsystem& parentNode){
    m_parent = &parentNode;
}

Subsystem& Subsystem::getParent() {
    if (isRoot()){
        throw std::runtime_error("Tried to get Parent of Root node!");
    }
    return *m_parent;
}


nlohmann::json Subsystem::handleWebRequest(const json& request) {
    json ret;
    ret["error"] = "No WebRequest Handler created for this subsystem";
    // TODO LOG
    return ret;
}


bool Subsystem::childExists(std::string childId) const {
    return m_children.find(childId) != m_children.end();
}

Subsystem& Subsystem::getChild(std::string childId){
    if (childExists(childId)){
        return *(m_children.at(childId));
    }
    else{
        throw std::runtime_error("Children does not exist");
    }
}

std::map<std::string, Subsystem*>& Subsystem::getAllChildren(){
    return m_children;
}

std::string Subsystem::getOwnId() const {
    return m_id;
}
