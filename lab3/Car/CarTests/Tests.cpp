#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Car/ControlCar.h"
#include "../Car/Car.h"

TEST_CASE("Car control tests")
{
    Car car;
    ControlCar control(car);
    std::string commandLine;
    SECTION("Engine On") 
    {
        commandLine = "EngineOn";
        REQUIRE(control.ControlCommand(commandLine) == true);
    }
    SECTION("Engine Off")
    {
        commandLine = "EngineOff";
        REQUIRE(control.ControlCommand(commandLine) == true);
    }
    SECTION("Car Info")
    {
        commandLine = "Info";
        REQUIRE(control.ControlCommand(commandLine) == true);
    }
    SECTION("Car Info")
    {
        commandLine = "SetSpeed 100";
        REQUIRE(control.ControlCommand(commandLine) == true);
    }
    SECTION("Car Info")
    {
        commandLine = "SetGear 2";
        REQUIRE(control.ControlCommand(commandLine) == true);
    }
}

TEST_CASE("Full car tests")
{
    Car car;
    ControlCar control(car);
    std::string commandLine;
    SECTION("Reach speed 150 and engine off")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(30) == true);
        REQUIRE(control.SetGear(3) == true);
        REQUIRE(control.SetSpeed(50) == true);
        REQUIRE(control.SetGear(5) == true);
        REQUIRE(control.SetSpeed(150) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 150);
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Reach speed -20 and engine off")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(-1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 20);
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Check forward direction")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Forward");
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Check stand direction")
    {
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Stand");
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Stand");
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Check back direction")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(-1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Back");
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Check changing direction")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Stand");
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Forward");
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.SetGear(-1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Back");
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(control.TurnOffEngine() == true);
    }

    SECTION("Check changing speed")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(car.ReturnCurrentSpeed() == 0);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 20);
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 0);
        REQUIRE(control.SetGear(-1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 20);
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.SetSpeed(0) == true);
        REQUIRE(car.ReturnCurrentSpeed() == 0);
        REQUIRE(control.TurnOffEngine() == true);
    }

}

TEST_CASE("Invalid Car control tests")
{
    Car car;
    ControlCar control(car);
    std::string commandLine;

    SECTION("Invalid Engine Command")
    {
        commandLine = "InvalidCommand";
        REQUIRE(control.ControlCommand(commandLine) == false);
    }

    SECTION("Invalid Set Speed Command")
    {
        REQUIRE(control.SetSpeed(10) == false);
    }

    SECTION("Invalid Set Gear Command")
    {
        commandLine = "SetGear 10"; 
        REQUIRE(control.SetGear(10) == false);
    }

    SECTION("Engine Off While Moving")  
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.TurnOffEngine() == false);
    }

    SECTION("Set to zero gear on direction back")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(-1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Back");
        REQUIRE(control.SetGear(0) == true);
        REQUIRE(control.DirectionToString(car.ReturnCurrentDirection()) == "Back");

    }

    SECTION("Invalid speed on 2 gear")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.SetGear(2) == true);
        REQUIRE(control.SetSpeed(51) == false);
    }

    SECTION("Invalid speed on 3 gear")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(30) == true);
        REQUIRE(control.SetGear(3) == true);
        REQUIRE(control.SetSpeed(61) == false);
    }

    SECTION("Invalid speed on 4 gear")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.SetGear(2) == true);
        REQUIRE(control.SetSpeed(50) == true);
        REQUIRE(control.SetGear(4) == true);
        REQUIRE(control.SetSpeed(91) == false);
    }

    SECTION("Invalid speed on 5 gear")
    {
        REQUIRE(control.TurnOnEngine() == true);
        REQUIRE(control.SetGear(1) == true);
        REQUIRE(control.SetSpeed(20) == true);
        REQUIRE(control.SetGear(2) == true);
        REQUIRE(control.SetSpeed(50) == true);
        REQUIRE(control.SetGear(5) == true);
        REQUIRE(control.SetSpeed(151) == false);
        REQUIRE(control.SetSpeed(49) == false);
    }

    SECTION("Set Speed Before Setting Gear")
    {
        REQUIRE(control.SetSpeed(30) == false);
    }

    SECTION("Set Gear Without Turning On Engine")
    {
        REQUIRE(control.SetGear(1) == false);
    }
}