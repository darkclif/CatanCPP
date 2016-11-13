#include "Debug.h"

void Debug::printMessage(string s) {
#ifdef _DEBUG
	cout << s << endl;
#endif // _DEBUG
}

void Debug::printMessage(double d) {
#ifdef _DEBUG
	cout << d << endl;
#endif // _DEBUG
}

void Debug::printMessage(float f) {
#ifdef _DEBUG
	cout << f << endl;
#endif // _DEBUG
}

void Debug::printMessage(int i) {
#ifdef _DEBUG
	cout << i << endl;
#endif // _DEBUG
}

void Debug::printMessage(bool b) {
#ifdef _DEBUG
	if (b == true) {
		cout << "true" << endl;
	} else {
		cout << "false" << endl;
	}
#endif // _DEBUG
}

void Debug::printMessage(char c) {
#ifdef _DEBUG
	cout << c << endl;
#endif // _DEBUG
}

void Debug::printMessage(long l) {
#ifdef _DEBUG
	cout << l << endl;
#endif // _DEBUG
}
