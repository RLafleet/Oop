#pragma once
enum class Direction
{
	Forward,
	Stand,
	Back
};

class DataCar
{
public:
	virtual ~DataCar() = default;

	// Убрать наследование
	virtual bool TurnOnEngine() = 0;
	virtual bool TurnOffEngine() = 0;
	[[nodiscard]] virtual bool ReturnEngineOn() const = 0;

	virtual bool SetGear(int gear) = 0;
	[[nodiscard]] virtual int ReturnCurrentGear() const = 0;

	virtual bool SetSpeed(int speed) = 0;
	[[nodiscard]] virtual int  ReturnCurrentSpeed() const = 0;

	[[nodiscard]] virtual Direction ReturnCurrentDirection() const = 0;
};