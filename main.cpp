#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{
	//TestReductionFunctions::comparisonReductionFunctions();
	//Fingerprint fingerprint(string("101010101010101010101010"));
	Fingerprint fingerprint(string("101000101011011000001010"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);
	
	return 0;
}
