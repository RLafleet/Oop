#pragma once
#include <iostream>
#include <vector>
#include <set>

const int UPPER_BOUND = 100000000;
const int LOWER_BOUND = 1;

std::set<int> GeneratePrimeNumbersSet(int n);
void WriteNumberPrimeNumbersSet(const std::set<int>& set);