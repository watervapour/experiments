#include <iostream>

uint8_t A = 1;
uint8_t B = 3;

uint16_t regReturn(uint8_t var){

	return (var << 4);
}

using namespace std;
int  main(){
	cout << regReturn(A) << endl;
	cout << regReturn(B) << endl;

	return 0;
}
