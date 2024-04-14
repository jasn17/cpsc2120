#include <iostream>
#include <string>

using namespace std;

int main(void) {
	string arr[5] = {"2", "4", "6", "8", "+"};

	if (isalnum(arr[4][0])) {
		cout << "Is a fucking number" << endl;
	}	

	return 0;
}
