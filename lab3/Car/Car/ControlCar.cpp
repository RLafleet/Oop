#include "ControlCar.h"
#include <iostream>
#include <sstream>

ControlCar::ControlCar(Car& car)
    : m_car(car)
{
}

bool ControlCar::ControlCommand(const std::string& commandLine)
{
    std::stringstream ss(commandLine);
    std::string action;
    ss >> action;
    if (action == "EngineOn")
    {
        TurnOnEngine();
    }
    else if (action == "EngineOff")
    {
        TurnOffEngine();
    }
    else if (action == "SetGear")
    {
        int gear;
        ss >> gear;
        SetGear(gear);
    }
    else if (action == "SetSpeed")
    {
        int speed;
        ss >> speed;
        SetSpeed(speed);
    }
    else if (action == "Info")
    {
        CarInfo();
    }
    else
    {
        return false;
    }
    return true;
}

bool ControlCar::TurnOnEngine()
{
    if (m_car.TurnOnEngine())
    {
        std::cout << "Engine turned on" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Engine not turned on" << std::endl;
        return false;
    }
}

bool ControlCar::TurnOffEngine()
{
    if (m_car.TurnOffEngine())
    {
        std::cout << "Engine turned off" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Engine was not turned off" << std::endl;
        return false;
    }
}

std::string ControlCar::DirectionToString(const Direction& direction) const
{
    if (direction == Direction::Stand)
    {
        return "Stand";
    }
    else if (direction == Direction::Back)
    {
        return "Back";
    }
    else if (direction == Direction::Forward)
    {
        return "Forward";
    }
    return "Wrong direction";
}

bool ControlCar::CarInfo()
{
    if (m_car.ReturnEngineOn())
    {
        std::cout << "Engine is on." << std::endl;
    }
    else
    {
        std::cout << "Engine is off" << std::endl;
    }
    std::cout << "Gear: " << m_car.ReturnCurrentGear() << std::endl;
    std::cout << "Speed: " << m_car.ReturnCurrentSpeed() << std::endl;
    std::cout << "Direction: " << DirectionToString(m_car.ReturnCurrentDirection()) << std::endl;
    return true;
}

bool ControlCar::SetGear(int gear)
{
    if (m_car.SetGear(gear))
    {
        std::cout << "Gear set." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed to set gear." << std::endl;
        return false;
    }
}

bool ControlCar::SetSpeed(int speed)
{
    if (m_car.SetSpeed(speed))
    {
        std::cout << "Desired speed reached." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Desired speed cannot be reached." << std::endl;
        return false;
    }
}
