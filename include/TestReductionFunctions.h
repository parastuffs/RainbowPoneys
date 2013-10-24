#ifndef TESTREDUCTIONFUNCTIONS_H
#define TESTREDUCTIONFUNCTIONS_H
#include "../include/RainbowAttack.h"

class TestReductionFunctions
{
    public:
        TestReductionFunctions();
        void comparisonReductionFunctions();
        virtual ~TestReductionFunctions();
    protected:
        int numberOfCollisions(RainbowAttack* Rainbow, int reductionFunction);
        int intoTables(bitset<PASS_NBR_BITS> word, int tablesLength, bitset<PASS_NBR_BITS> tables[]);
    private:
};

#endif // TESTREDUCTIONFUNCTIONS_H
