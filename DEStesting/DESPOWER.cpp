#include <iostream>
#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"

#include <iomanip>
#include <cstdio>

using namespace std;

const int PASS_NBR_BITS = 12;

int main(int argc, char* argv[])
{
	 
	//Code from codeproject
	byte plainText[] = {'H','E','L','L','O',' ','W','O','R','L','D',
		0x0,0x0,0x0,0x0,0x0};
	byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
	::memset(key,0x01,CryptoPP::DES::DEFAULT_KEYLENGTH);
	
	byte cbCypheredText[CryptoPP::DES::BLOCKSIZE];
	byte cbRecoveredText[CryptoPP::DES::BLOCKSIZE];
	
	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption Encryptor;
	Encryptor.SetKey(key,sizeof(key));
	Encryptor.ProcessData(cbCypheredText,plainText,sizeof(plainText));
	
	CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption Decryptor;
	Decryptor.SetKey(key,sizeof(key));
	Decryptor.ProcessData(cbRecoveredText,cbCypheredText,sizeof(cbCypheredText));

	cout << "Default key length: " << Encryptor.DefaultKeyLength() << endl;
	cout << "Block size: " << Encryptor.MandatoryBlockSize() << endl;
	cout << "Algorithm: " << Encryptor.AlgorithmName() << endl;
	cout << "Plain text(" << sizeof(plainText) << " bytes): ";
	cout << "'" << plainText << "'" << endl;
	cout << "Cypher text(" << sizeof(cbCypheredText) << " bytes)" << endl;
	cout << "Recovered text(" << sizeof(cbRecoveredText) << " bytes): ";
	cout << "'" << cbRecoveredText << "'" << endl;

	//Code from the cryptoPP's wiki
/*
	CryptoPP::AutoSeededRandomPool prng;
	byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key,sizeof(key));

	string plain = "ECB Mode Test";
	string cipher, encoded;

	encoded.clear();
	CryptoPP::StringSource(key,sizeof(key),true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "key: " << encoded << endl;
	
	cout << "Plain text: " << plain << endl;

	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e;
	e.SetKey(key,sizeof(key));

	CryptoPP::StringSource(plain,true,
		new CryptoPP::StreamTransformationFilter(e,
			new CryptoPP::StringSink(cipher)
		)
	);

	encoded.clear();
	CryptoPP::StringSource(cipher,true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "Cipher Text: " << encoded << endl;
*/


	return 0;
}
