#include "../include/bitsetFunctions.h"

/* ****** Functions that modify the bitset ****** */

Fingerprint mirror(Fingerprint fingerprint)
{ 
	//for a bitset 'abcdef', returns 'fedcba'
	
	Fingerprint result;
	for (int i=0;i<FING_SIZE;i++)
		result[i]=fingerprint[FING_SIZE-1-i];
	return result;
}

Fingerprint flipAll(Fingerprint fingerprint)
{
	//invert 1's and 0's
	
	return fingerprint.flip();
}

Fingerprint rotate(Fingerprint fingerprint,int round=1)
{
	//rotates the fingerprint bitset to the right by 'round' bits
	//e.g. a bitset 'abcdef', rotated by 2 bits to the right
	//would become 'efabcd'

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
		result = fingerprint; //no rotation in case of wrong parameter
	return result;
}

/* ****** Functions that truncate the bitset ****** */

Password keepLeft(Fingerprint fingerprint)
{
	/* password = the MSB part of the fingerprint */
	//N.B. MSB = Most Significant Bit
	
	Password result;	
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[PASS_SIZE+i];
	return result;}

Password keepRight(Fingerprint fingerprint)
{
	/* password = the LSB part of fingerprint */
	//N.B. LSB = Least Significant Bit
	
	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[i];
	return result;
}

Password hopOne(Fingerprint fingerprint)
{
	/* uses one bit of fingerprint to make the password,
	skips the next bit, and so on */
	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[2*i];
	return result;
}

Password hopTwo(Fingerprint fingerprint)
{
	/* uses two bits of fingerprint to make the password,
	skips the next two bits, and so on */

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
	/* sums bits of fingerprint by groups of two, and the resulting bit
	is concatenated with the other results to form the password */
	
	Password result;
	for (int i=0;i<PASS_SIZE;i++)
		result[i]=fingerprint[2*i] xor fingerprint[2*i+1]; 
	return result;
}

