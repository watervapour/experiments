#include <iostream>
using namespace std;

void funcD();

void funcA(){
	cout << "funcA called!" << endl;
}

void funcB(){
	cout << "funcB called!" << endl;
}

void funcC(){
	cout << "funcC called!" << endl;
}




int main(int argc, char** argv){
	void (*funcArray[4])()={funcA,funcB,funcD, funcC};
	funcArray[1]();
	funcArray[2]();
	funcArray[0]();
	funcArray[1]();
	funcArray[3]();
	return 0;
}

void funcD(){
	cout << "Func D!!!" << endl;
}

