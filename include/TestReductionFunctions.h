#ifndef TESTREDUCTIONFUNCTIONS_H
#define TESTREDUCTIONFUNCTIONS_H
#include "../include/RainbowAttack.h"

class TestReductionFunctions
{
    public:
        TestReductionFunctions();
        static void comparisonReductionFunctions();
        ~TestReductionFunctions();
    private:
        static int numberOfCollisions(RainbowAttack* Rainbow, int reductionFunction);
        static int intoTables(bitset<PASS_NBR_BITS> word, int tablesLength, bitset<PASS_NBR_BITS> tables[]);
};

#endif // TESTREDUCTIONFUNCTIONS_H
