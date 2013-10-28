#ifndef RAINBOWATTACK_H
#define RAINBOWATTACK_H

#include <iostream>
#include <bitset>
#include <math.h>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"
using namespace std;

#define PASS_SIZE 12
#define FING_SIZE 24

typedef bitset<12> Password;
typedef bitset<24> Fingerprint;
const byte MESSAGE[] = {0x43,0x41,0x43,0x41,0x43,0x41,0x43,0x41};

class RainbowAttack
{
public:
	RainbowAttack();
	~RainbowAttack();
	void findPassword(Fingerprint fingerprint);
	int getFoundNum() {return m_foundNum;}
	int getTableSize() {return m_tablesLength;}
private:
	Fingerprint hashDES(Password reducedPass);
	Password reductionFunction(int number, Fingerprint fingerprint);
	Password blue(Fingerprint fingerprint);
	Password green(Fingerprint fingerprint);
	Password yellow(Fingerprint fingerprint);
	Password red(Fingerprint fingerprint);

	void tablesCreation();
	int inTable(Fingerprint fingerprint);
	void insertionSort();

	Password m_dictionary[4096]; //table with passwords
	Fingerprint m_tables[4096]; //table with their rainbow fingerprint
	int m_tablesLength;
	int m_foundNum;
};

#endif
