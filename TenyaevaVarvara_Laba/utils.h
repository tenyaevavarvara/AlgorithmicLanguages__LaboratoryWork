#pragma once
#include <iostream>
#include "logger.h"

#define INPUT_LINE(in, str) getline(in>>std::ws, str); logValue(str);

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()	// check type
		|| std::cin.peek() != '\n'	// is buffer empty (int/float check)
		|| x < min || x > max)		// check range
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type number (" << min << "-" << max << "):";
	}
	logValue(x);
	return x;
}