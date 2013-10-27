#ifndef RAINBOWATTACK_H
#define RAINBOWATTACK_H

#include <iostream>
#include <bitset>
#include <math.h>
//#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"
#include <iomanip> //utile...?
#include <cstdio> //utile...?
using namespace std;

#define PASS_SIZE 12
#define FING_SIZE 24

typedef bitset<12> Password;
typedef bitset<24> Fingerprint;
const byte MESSAGE[] = {0,0,0,0,0,0,0,0}; //64 bits

class RainbowAttack
{
	public:
		RainbowAttack();
		~RainbowAttack();
		void findPassword(Fingerprint fingerprint);
		Fingerprint hashDES(Password reducedPass);
		Password blue(Fingerprint fingerprint);
		Password green(Fingerprint fingerprint);
		Password yellow(Fingerprint fingerprint);
		Password red(Fingerprint fingerprint);
		Password reductionFunction(int number, Fingerprint fingerprint);
		
	private:
		void tablesCreation();
		int inTable(Fingerprint fingerprint);
		void insertionSort();

		Password m_dictionary[4096]; //table with passwords
		Fingerprint m_tables[4096]; //table with their rainbow fingerprint
		int m_tablesLength;
};

#endif // RAINBOWATTACK_H
