#pragma once
#include <iostream>
#include <string>

using namespace std;

class Debug {

public:
	static void printMessage(string s);
	static void printMessage(double d);
	static void printMessage(float f);
	static void printMessage(int i);
	static void printMessage(bool b);
	static void printMessage(char c);
	static void printMessage(long l);
};
