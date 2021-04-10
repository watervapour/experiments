#include <iostream>

#include "TestClass.h"

using namespace std;

int main(int argv, char** argc) {

	TestClass test;
	TestClass test2(4, 69);
	B();

	B* bee = new B();

	TestClass test3(bee);

	cout << test.abc() << endl;
	return 0;
}
