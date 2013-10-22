#include <iostream>
#include <bitset>
#include <math.h>
#include "src/RainbowAttack.cpp"

using namespace std;

int main()
{
    bitset<FING_NBR_BITS> fingerprint(string("010100010000"));
    RainbowAttack* Rainbow = new RainbowAttack();
    Rainbow->findPassword(fingerprint);

    return 0;
}
