#include <iostream>
using namespace std;

class testClass
{
public:
	testClass();

	void funcA();
	void funcB();
	void callArrayFunc(int);
	
	void (testClass::*classArr[2])() = {&testClass::funcA, &testClass::funcB};
//	void (testClass::*arr[2])()={&testClass::funcA};
//	void (testClass::*functionPointer)() = &testClass::funcB;
private:
	//void (testClass::funcArray[2])() = {funcA, funcB};
	//void (*funcArray[2])(); 
};

testClass::testClass(){
	//void (testClass::*classArr[2])() = {&testClass::funcA, &testClass::funcB};
}

void testClass::funcA(){
	cout << "func A" << endl;
}

void testClass::funcB(){
	cout << "func B" << endl;
}

void testClass::callArrayFunc(int func){
	//(this.*classArr[0])();
	(this->*classArr[0])();
	//*(classArr[1])();
}

int main(){
	void (testClass::*mainArr[2])() = {&testClass::funcA, &testClass::funcB};
	testClass mtc;
	(mtc.*mainArr[0])();
	(mtc.*mainArr[1])();
	(mtc.*mainArr[1])();
	(mtc.*mainArr[0])();

	mtc.callArrayFunc(0);
//	(mtc.*arr[1])();
	
	return 0;
}
