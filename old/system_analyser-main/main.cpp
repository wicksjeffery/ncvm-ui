// c++ main.cpp SystemAnalyser.cpp -o main -std=c++20 -fmodules-ts

#include <iostream>
#include <memory>
#include "SystemAnalyser.h"

int main()
{
	std::cout << "Hello World" << std::endl;
	auto system = std::make_unique<SystemAnalyser>();
// 	system->RunCommand("ls -la");
	system->RunCommand("asdf");
	system->DisplayOutput();

	return 0;
}
