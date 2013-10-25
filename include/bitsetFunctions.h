#ifndef __BITSETFUNCTIONS_H
#define __BITSETFUNCTIONS_H

#include "RainbowAttack.h"

/* Functions that modify the bitset */

bitset<FING_NBR_BITS> mirror(bitset<FING_NBR_BITS> fingerprint);
bitset<FING_NBR_BITS> flipAll(bitset<FING_NBR_BITS> fingerprint);
bitset<FING_NBR_BITS> rotate(bitset<FING_NBR_BITS> fingerprint,int round);

/* Functions that truncate the bitset */

bitset<PASS_NBR_BITS> keepLeft(bitset<FING_NBR_BITS> fingerprint);
bitset<PASS_NBR_BITS> keepRight(bitset<FING_NBR_BITS> fingerprint);
bitset<PASS_NBR_BITS> hopOne(bitset<FING_NBR_BITS> fingerprint);
bitset<PASS_NBR_BITS> hopTwo(bitset<FING_NBR_BITS> fingerprint);
bitset<PASS_NBR_BITS> sumTwo(bitset<FING_NBR_BITS> fingerprint);

#endif
