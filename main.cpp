#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{

//	TestReductionFunctions::comparisonReductionFunctions();
	Fingerprint fingerprint(string("111111001111001000001011"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);

	return 0;
}
