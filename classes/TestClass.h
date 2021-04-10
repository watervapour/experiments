#pragma once
#include <iostream>
class B {
public:
	B();

	int x;
	B(int);
};

class TestClass{


public:

	TestClass();
	TestClass(int, int);
	TestClass(B*);

	int abc();


};

