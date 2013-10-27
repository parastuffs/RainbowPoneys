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
        static int inTable(Password word, int tablesLength, Password tables[]);
};

#endif // TESTREDUCTIONFUNCTIONS_H
