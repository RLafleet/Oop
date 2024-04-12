#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"
#include "DivideVector.h" 

SCENARIO("ProcessVector function tests", "[ResponceVector]") {
    GIVEN("An empty vector") {
        std::vector<double> startVector = {};

        WHEN("Calling ResponceVector function") {
            startVector = ResponceVector(startVector);

            THEN("Vector size should remain unchanged") {
                REQUIRE(startVector.size() == 0);
            }
        }
    }

    GIVEN("A vector with max element being zero") {
        std::vector<double> startVector = { 0, -2, -1 };
        std::vector<double> resultVector = { 0, -2, -1 };

        WHEN("Calling ResponceVector function") {
            startVector = ResponceVector(startVector);

            THEN("Vector should remain unchanged") {
                REQUIRE(startVector == resultVector);
            }
        }
    }

    GIVEN("A vector with max element") {
        WHEN("Max element is the last") {
            std::vector<double> startVector = { 1, 2, 3, 5 };
            std::vector<double> resultVector = { 0.400, 0.800, 1.200, 2.000 };

            WHEN("Calling ResponceVector function") {
                startVector = ResponceVector(startVector);

                THEN("Vector elements should be divided by half of max element") {
                    REQUIRE(startVector == resultVector);
                }
            }
        }

        WHEN("Max element is the first") {
            std::vector<double> startVector = { 5, 2, 3, 1 };
            std::vector<double> resultVector = { 2.000, 0.800, 1.200, 0.400 };

            WHEN("Calling ResponceVector function") {
                startVector = ResponceVector(startVector);

                THEN("Vector elements should be divided by half of max element") {
                    REQUIRE(startVector == resultVector);
                }
            }
        }

        WHEN("Max element is in the middle") {
            std::vector<double> startVector = { 0, 2, 3, 5 };
            std::vector<double> resultVector = { 0.000, 0.800, 1.200, 2.000 };

            WHEN("Calling ResponceVector function") {
                startVector = ResponceVector(startVector);

                THEN("Vector elements should be divided by half of max element") {
                    REQUIRE(startVector == resultVector);
                }
            }
        }
    }
}