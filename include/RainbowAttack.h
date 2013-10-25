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
        bitset<PASS_NBR_BITS> blue(bitset<FING_NBR_BITS> fingerprint);
        bitset<PASS_NBR_BITS> green(bitset<FING_NBR_BITS> fingerprint);
        bitset<PASS_NBR_BITS> yellow(bitset<FING_NBR_BITS> fingerprint);
        bitset<PASS_NBR_BITS> red(bitset<FING_NBR_BITS> fingerprint);
     	bitset<PASS_NBR_BITS> reductionFunction(int number, bitset<FING_NBR_BITS> fingerprint);

        bitset<FING_NBR_BITS> hashDES(bitset<PASS_NBR_BITS> reducedPass);
        ~RainbowAttack();
    protected:
    private:
        void tablesCreation();
        int intoTables(bitset<FING_NBR_BITS> fingerprint);
        void insertionSort();

        bitset<PASS_NBR_BITS> m_dictionary[4096];
        bitset<FING_NBR_BITS> m_tables[4096];
        int m_tablesLength;
};

#endif // RAINBOWATTACK_H
