#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
	RainbowAttack *Rainbow = new RainbowAttack();
	int i=0;
	string line;
	ifstream file("FP");
	if(file.is_open()) {
		while(getline(file,line)) {
			Fingerprint fingerprint(line);
			Rainbow->findPassword(fingerprint);
			i++;
		}
	}
	file.close();

	cout << "Number of passwords found: " << Rainbow->getFoundNum();
	cout << " out of "<< i <<endl;

	return 0;
}
