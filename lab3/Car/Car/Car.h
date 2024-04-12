#pragma once
#include <utility>
#include <cmath>

enum class Direction
{
	Forward,
	Stand,
	Back
};

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	//Get
	[[nodiscard]] bool ReturnEngineOn() const;

	bool SetGear(int gear);
	[[nodiscard]] int ReturnCurrentGear() const;

	bool SetSpeed(int speed);
	[[nodiscard]] int ReturnCurrentSpeed() const ;

	[[nodiscard]] Direction ReturnCurrentDirection() const;

private:
	//Is correct
	[[nodiscard]] bool CorrectGearShift(int gear) const;
	//Name
	[[nodiscard]] bool CurrentSpeedInGearSpeedRange(int speed, int gear) const;
	//Поменять параметры местами
	//Struct > pair
	[[nodiscard]] static bool IsSpeedInRange(const std::pair<int, int>& speedRange, int speed);

	bool m_isEngineOn = false;
	// скорость но со знаком. Направление убрать.
	int m_speed = 0;
	int m_gear = 0;
};