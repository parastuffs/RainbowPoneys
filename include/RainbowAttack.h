#ifndef RAINBOWATTACK_H
#define RAINBOWATTACK_H
#include <iostream>
#include <bitset>
#include <math.h>

using namespace std;

int const PASS_NBR_BITS = 12;
int const HASH_NBR_BITS = 24;
int const FING_NBR_BITS = 24;

class RainbowAttack
{
    public:
        RainbowAttack();
        void findPassword(bitset<HASH_NBR_BITS> fingerprint);
        virtual ~RainbowAttack();
    protected:
    private:
        void tablesCreation();
        bitset<HASH_NBR_BITS> reductionFunction(int number, bitset<HASH_NBR_BITS> fingerprint);
        bitset<HASH_NBR_BITS> hashDES(bitset<HASH_NBR_BITS> reducedPass);
        int intoTables(bitset<HASH_NBR_BITS> fingerprint);

         //I can't know the length of the rainbow table before I create it... I should use a list but I'm not used to. TO CHANGE
        bitset<PASS_NBR_BITS> m_dictionary[4096];//Dans les crochets : pow(2,PASS_NBR_BITS)
        bitset<FING_NBR_BITS> m_tables[4096];//Dans les crochets : pow(2,PASS_NBR_BITS)
        int m_tablesLength;
};

#endif // RAINBOWATTACK_H
