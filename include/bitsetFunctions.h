#ifndef __BITSETFUNCTIONS_H
#define __BITSETFUNCTIONS_H

#include "RainbowAttack.h"

/* Functions that modify the bitset */

Fingerprint mirror(Fingerprint fingerprint);
Fingerprint flipAll(Fingerprint fingerprint);
Fingerprint rotate(Fingerprint fingerprint,int round);

/* Functions that truncate the bitset */

Password keepLeft(Fingerprint fingerprint);
Password keepRight(Fingerprint fingerprint);
Password hopOne(Fingerprint fingerprint);
Password hopTwo(Fingerprint fingerprint);
Password sumTwo(Fingerprint fingerprint);

#endif
