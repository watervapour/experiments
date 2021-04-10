#include <iostream>

int A = 111;
int B = 222;
int C = 3300;

int* varFetcher(int);
using namespace std;
int main(){
	cout << varFetcher(1) << endl;
	cout << *varFetcher(2) << endl;

	*varFetcher(3) = 456;
	cout << C;	
	return 0;
}

int* varFetcher(int index){
	if(index == 1){
		return &A;
	} else if (index == 2){
		return &B;
	} else {
		return &C;
	}

}
