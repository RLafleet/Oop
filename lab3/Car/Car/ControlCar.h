#pragma once
#include "Car.h"
#include <string>

class ControlCar
{
public:
	explicit ControlCar(Car& car);
	bool ControlCommand(const std::string& commandLine);

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool CarInfo();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	[[nodiscard]] std::string DirectionToString(const Direction& direction) const;

private:
	Car& m_car;
};