/**
 * @file Simens3Rw40.hpp
 * @author Josef Aschwanden (aschwandenjosef@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string>

namespace Motorstarter{
class Siemens3Rw40{
    enum EFaultIndicator{
        eNoFault = 0,
        eNoStartCommand = 1,
        eInhibit = 2,
        eMotorStarterFailure = 3
    };

    std::string getFaultIndicator() const;
    EFaultIndicator getEFaultIndicator() const;

private:
    EFaultIndicator m_faultIndicator;  // Fault Indicator
    bool m_fault;       // Overload / Fault
    bool m_bypassed;    // Bypass Mode Active
    bool m_onRun;       // On / Run
};
}