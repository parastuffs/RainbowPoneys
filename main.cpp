#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{

//	TestReductionFunctions::comparisonReductionFunctions();
	Fingerprint fingerprint(string("000101010011100101001000"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);

	return 0;
}
