#include "../include/bitsetFunctions.h"
/*int main()
{
	cout<<"Hello Meust"<<endl;
	bitset<FING_NBR_BITS> test(string("010101111001111010011000"));
	cout<<"fingerprint="<<test<<endl;
	bitset<PASS_NBR_BITS> tronc;
	
	tronc=keepLeft(test);
	cout<<"fingerprint="<<test<<endl;
	cout<<"KEEPLEFT___="<<tronc<<endl<<endl;
	
	tronc=keepRight(test);
	cout<<"fingerprint="<<test<<endl;
	cout<<"KEEPRIGHT__="<<tronc<<endl<<endl;
	
	tronc=hopOne(test);
	cout<<"fingerprint="<<test<<endl;
	cout<<"HOP ONE____="<<tronc<<endl<<endl;
	
	tronc=hopTwo(test);
	cout<<"fingerprint="<<test<<endl;
	cout<<"HOP TWO____="<<tronc<<endl<<endl;
	
	tronc=sumTwo(test);
	cout<<"fingerprint="<<test<<endl;
	cout<<"SUM TWO____="<<tronc<<endl<<endl;
	
	return 0;
}*/

/* ****** Functions that modify the bitset ****** */

bitset<FING_NBR_BITS> mirror(bitset<FING_NBR_BITS> fingerprint)
{
	bitset<FING_NBR_BITS> result;
	for (int i=0;i<FING_NBR_BITS;i++)
		result[i]=fingerprint[FING_NBR_BITS-1-i];
	return result;
}

bitset<FING_NBR_BITS> flipAll(bitset<FING_NBR_BITS> fingerprint)
{
	return fingerprint.flip();
}

bitset<FING_NBR_BITS> rotate(bitset<FING_NBR_BITS> fingerprint,int round=1)
{
	//rotate to the right

	bitset<FING_NBR_BITS> result;
	if(round>=0)
	{
		int shift=round%FING_NBR_BITS;
		for(int i=0;i<(FING_NBR_BITS-shift);i++)
			result[i]=fingerprint[i+shift];
		for(int i=0; i<shift;i++)
			result[FING_NBR_BITS-shift+i]=fingerprint[i];
	}
	else
	{
		//cout<<"ERROR: function rotate"<<endl;
		result = fingerprint;
	}
	return result;
}

/* ****** Functions that truncate the bitset ****** */

bitset<PASS_NBR_BITS> keepLeft(bitset<FING_NBR_BITS> fingerprint)
{
	/* keeps the MSB part */
	
	bitset<PASS_NBR_BITS> result;
	for (int i=0;i<PASS_NBR_BITS;i++)
		result[i]=fingerprint[PASS_NBR_BITS+i];
	return result;}

bitset<PASS_NBR_BITS> keepRight(bitset<FING_NBR_BITS> fingerprint)
{
	/* keeps the LSB part */
	
	bitset<PASS_NBR_BITS> result;
	for (int i=0;i<PASS_NBR_BITS;i++)
		result[i]=fingerprint[i];
	return result;
}

bitset<PASS_NBR_BITS> hopOne(bitset<FING_NBR_BITS> fingerprint)
{
	/* keeps one bit, discards one bit */
	
	bitset<PASS_NBR_BITS> result;
	for (int i=0;i<PASS_NBR_BITS;i++)
		result[i]=fingerprint[2*i];
	return result;
}

bitset<PASS_NBR_BITS> hopTwo(bitset<FING_NBR_BITS> fingerprint)
{
	/* keeps two bits, discards two bits */
	
	bitset<PASS_NBR_BITS> result;
	for (int i=0;i<PASS_NBR_BITS;i++)
	{
		if(i%2==0) //if even
			result[i]=fingerprint[2*i];
		else //if odd
			result[i]=fingerprint[2*i-1];
	}
	return result;
}

bitset<PASS_NBR_BITS> sumTwo(bitset<FING_NBR_BITS> fingerprint)
{
	/* sums two bits and adds the result  */
	
	bitset<PASS_NBR_BITS> result;
	for (int i=0;i<PASS_NBR_BITS;i++)
		result[i]=fingerprint[2*i] xor fingerprint[2*i+1]; 
		//alternative notation : a xor b <=> a^b
	return result;
}

