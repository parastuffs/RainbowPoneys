#ifndef RAINBOWATTACK_H
#define RAINBOWATTACK_H

#include <iostream>
#include <bitset>
#include <math.h>
#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"

#include <iomanip>
#include <cstdio>

using namespace std;

int const PASS_NBR_BITS = 12;
int const HASH_NBR_BITS = 64;
int const FING_NBR_BITS = 24;
byte const message[] = {0,0,0,0,0,0,0,0};//64 bits

class RainbowAttack
{
    public:
        RainbowAttack();
        void findPassword(bitset<FING_NBR_BITS> fingerprint);
        virtual ~RainbowAttack();
    protected:
    private:
        void tablesCreation();
        bitset<PASS_NBR_BITS> reductionFunction(int number, 
			bitset<FING_NBR_BITS> fingerprint);
        bitset<FING_NBR_BITS> hashDES(bitset<PASS_NBR_BITS> reducedPass);
        int intoTables(bitset<FING_NBR_BITS> fingerprint);

         //I can't know the length of the rainbow table before I create it... 
	 //I should use a list but I'm not used to. TO CHANGE
	//Dans les crochets : pow(2,PASS_NBR_BITS)
	bitset<PASS_NBR_BITS> m_dictionary[4096];
	//Dans les crochets : pow(2,PASS_NBR_BITS)
        bitset<FING_NBR_BITS> m_tables[4096];
        int m_tablesLength;
};

#endif // RAINBOWATTACK_H
