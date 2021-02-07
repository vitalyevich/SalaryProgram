#pragma once

#include <iostream>
using namespace std;

const int LEFT_RANGE_OF_MARK = 1;
const int RIGHT_RANGE_OF_MARK = 10;

const int LEFT_RANGE_OF_NUMBER = 100000;
const int RIGHT_RANGE_OF_NUMBER = 999999;

const int LEFT_RANGE_OF_YEAR = 1950;
const int RIGHT_RANGE_OF_YEAR = 2020;

int inputNumber(int left_range, int right_range);
bool isNumberNumeric();
bool isNumberRangeCorrect(int number, int left_range, int right_range);
