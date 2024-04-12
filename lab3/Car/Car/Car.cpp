#include "Car.h"

const std::pair<int, int> REVERSE_SPEED_RANGE = { -20, 0 };
const std::pair<int, int> NEUTRAL_SPEED_RANGE = { -20, 150 };
const std::pair<int, int> FIRST_SPEED_RANGE = { 0, 30 };
const std::pair<int, int> SECOND_SPEED_RANGE = { 20, 50 };
const std::pair<int, int> THIRD_SPEED_RANGE = { 30, 60 };
const std::pair<int, int> FOURTH_SPEED_RANGE = { 40, 90 };
const std::pair<int, int> FIFTH_SPEED_RANGE = { 50, 150 };
const int MAX_SPEED = 150;

bool Car::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
		return true;
	}
	return false;
}
bool Car::TurnOffEngine()
{
	if (m_isEngineOn && m_gear == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}
	return false;
}

bool Car::CorrectGearShift(int gear) const
{
	if (gear == -1 && m_speed <= 0) 
	{
		return true;
	}

	if (gear == 1 && m_speed >= 0) 
	{
		return true;
	}

	// Фигурные скобки по феншую. Исправлено
	if (gear > 1 && m_speed >= 0) 
	{
		return true;
	}

	if (gear == 0) {
		return true;
	}

	return false;
}

bool Car::SetGear(int gear)
{
	if (!m_isEngineOn && gear != 0)
	{
		return false;
	}
	if (!CurrentSpeedInGearSpeedRange(m_speed, gear))
	{
		return false;
	}
	if (!CorrectGearShift(gear))
	{
		return false;
	}
	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (m_gear == 0 && abs(speed) > abs(m_speed))
	{
		return false;
	}

	if (!CurrentSpeedInGearSpeedRange(speed, m_gear))
	{
		return false;
	}
	m_speed = (m_gear == -1) ? -speed : speed;

	return true;
}

bool Car::ReturnEngineOn() const
{
	return m_isEngineOn;
}

int Car::ReturnCurrentGear() const
{
	return m_gear;
}

int Car::ReturnCurrentSpeed() const
{
	// Возвращает пусть всегда положительная
	return abs(m_speed);
}

//Неправильно определяется направленме при нейтрале назад
Direction Car::ReturnCurrentDirection() const
{
	if (m_speed == 0)
	{
		return Direction::Stand;
	}
	else if (m_speed < 0)
	{
		return Direction::Back;
	}

	return Direction::Forward;

}

//метод статический. Исправлено
bool Car::IsSpeedInRange(const std::pair<int, int>& speedRange, int speed)
{
	int minSpeed = speedRange.first;
	int maxSpeed = speedRange.second;

	return speed >= minSpeed && speed <= maxSpeed;
}

bool Car::CurrentSpeedInGearSpeedRange(int speed, int gear) const
{
	// Цикл
	switch (gear) {
	case -1:
		return IsSpeedInRange(REVERSE_SPEED_RANGE, speed);
	case 0:
		return IsSpeedInRange(NEUTRAL_SPEED_RANGE, speed);
	case 1:
		return IsSpeedInRange(FIRST_SPEED_RANGE, speed);
	case 2:
		return IsSpeedInRange(SECOND_SPEED_RANGE, speed);
	case 3:
		return IsSpeedInRange(THIRD_SPEED_RANGE, speed);
	case 4:
		return IsSpeedInRange(FOURTH_SPEED_RANGE, speed);
	case 5:
		return IsSpeedInRange(FIFTH_SPEED_RANGE, speed);
	default:
		return false;
	}
}