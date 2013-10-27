#include "../include/bitsetFunctions.h"

/* ****** Functions that modify the bitset ****** */

Fingerprint mirror(Fingerprint fingerprint)
{
	Fingerprint result;
	for (int i=0;i<FING_SIZE;i++)
		result[i]=fingerprint[FING_SIZE-1-i];
	return result;
}

Fingerprint flipAll(Fingerprint fingerprint)
{
	return fingerprint.flip();
}

Fingerprint rotate(Fingerprint fingerprint,int round=1)
{
	//rotate to the right

	Fingerprint result;
	if(round>=0)
	{
		int shift=round%FING_SIZE;
		for(int i=0;i<(FING_SIZE-shift);i++)
			result[i]=fingerprint[i+shift];
		for(int i=0; i<shift;i++)
			result[FING_SIZE-shift+i]=fingerprint[i];
	}
	else
	{
		//cout<<"ERROR: function rotate"<<endl;
		result = fingerprint;
	}
	return result;
}

/* ****** Functions that truncate the bitset ****** */

Password keepLeft(Fingerprint fingerprint)
{
	/* keeps the MSB part */

	Password result;	
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[PASS_SIZE+i];
	return result;}

Password keepRight(Fingerprint fingerprint)
{
	/* keeps the LSB part */
	
	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[i];
	return result;
}

Password hopOne(Fingerprint fingerprint)
{
	/* keeps one bit, discards one bit */

	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[2*i];
	return result;
}

Password hopTwo(Fingerprint fingerprint)
{
	/* keeps two bits, discards two bits */

	Password result;
	for (int i=0;i<PASS_SIZE;i++)
	{
		if(i%2==0) //if even
			result[i]=fingerprint[2*i];
		else //if odd
			result[i]=fingerprint[2*i-1];
	}
	return result;
}

Password sumTwo(Fingerprint fingerprint)
{
	/* sums two bits and adds the result  */
	
	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[2*i] xor fingerprint[2*i+1]; 
		//alternative notation : a xor b <=> a^b
	return result;
}

