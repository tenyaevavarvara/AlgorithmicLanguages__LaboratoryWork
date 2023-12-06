#pragma once
#include <iostream>

#define INPUT_LINE(in, str) getline(in>>std::ws, str);

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};



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
	//std::cerr << x << std::endl;
	return x;
}
