#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{

//	TestReductionFunctions::comparisonReductionFunctions();
	Fingerprint fingerprint(string("010100010000"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);

	return 0;
}
