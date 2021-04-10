#include "TestClass.h"
B::B() {
	std::cout << "Bee" << std::endl;
}

B::B(int num) {
	x = num;
}

TestClass::TestClass() {
	std::cout << "UWU" << std::endl;
}

TestClass::TestClass(int x, int y) {
	std::cout << x << y << std::endl;
}

TestClass::TestClass(B* abc) {
	std::cout << abc->x << std::endl;
}

int TestClass::abc() {
	return 6;
}

