#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{

//	TestReductionFunctions::comparisonReductionFunctions();
	Fingerprint fingerprint(string("101010101010101010101010"));
	//Fingerprint fingerprint(string("000010110001010100011100"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);

	return 0;
}
