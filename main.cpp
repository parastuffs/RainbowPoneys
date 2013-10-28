#include "include/RainbowAttack.h"
#include "include/TestReductionFunctions.h"

int main()
{

//	TestReductionFunctions::comparisonReductionFunctions();
	//Fingerprint fingerprint(string("101010101010101010101010"));
	Fingerprint fingerprint(string("111110100101011100010111"));
	Fingerprint fingerprint1(string("111101101001011100011011"));
	Fingerprint fingerprint2(string("011011010100001000000000"));
	Fingerprint fingerprint3(string("000011010110001000000000"));
	Fingerprint fingerprint4(string("110011100101001000000000"));
	Fingerprint fingerprint5(string("001111100101111000001111"));
	Fingerprint fingerprint6(string("000000000001101000010000"));
	Fingerprint fingerprint7(string("001111000010010100010011"));
	Fingerprint fingerprint8(string("010101011000000000010101"));
	Fingerprint fingerprint9(string("100101010111110000010110"));
	Fingerprint fingerprint10(string("101010010111111100011001"));
	//Fingerprint fingerprint(string("000010110001010100011100"));
	RainbowAttack *Rainbow = new RainbowAttack();
	Rainbow->findPassword(fingerprint);
	Rainbow->findPassword(fingerprint1);
	Rainbow->findPassword(fingerprint2);
	Rainbow->findPassword(fingerprint3);
	Rainbow->findPassword(fingerprint4);
	Rainbow->findPassword(fingerprint5);
	Rainbow->findPassword(fingerprint6);
	Rainbow->findPassword(fingerprint7);
	Rainbow->findPassword(fingerprint8);
	Rainbow->findPassword(fingerprint9);
	Rainbow->findPassword(fingerprint10);

	return 0;
}
