#include <iostream>
#include <string>
#include "crypto++/des.h"
#include "crypto++/modes.h"
#include "crypto++/filters.h"
#include "crypto++/osrng.h"
#include "crypto++/hex.h"

#include <iomanip>
#include <cstdio>
#include <bitset>

using namespace std;

const int PASS_NBR_BITS = 12;

typedef bitset<12> Password;
typedef bitset<24> Fingerprint;
const byte MESSAGE[] = {0x43,0x41,0x43,0x41,0x43,0x41,0x43,0x41};

Fingerprint hashDES(Password reducedPass);

int main(int argc, char* argv[])
{

	Password pass(string("011111101111"));
	Fingerprint fingerprint = hashDES(pass);
	cout << "pass: " << pass << endl;
	cout << "hash (24 bits): " << fingerprint << endl;
	Password passA(string("111111111111"));
	fingerprint = hashDES(passA);
	cout << "passA: " << passA << endl;
	cout << "hash (24 bits): " << fingerprint << endl;

/*
	bitset<64> message(string("0100000101000010010000110100010001000101010001100100011101001000"));
	cout << "Plain message: '" << message << "'" << endl;
	bitset<8>test;
	cout << "sizeof(test): " << sizeof(test) << endl;
	cout << test.size() << endl;

	byte plainText[8] = {0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41};
	cout << "plainText before initialization: '" << plainText << "'" << endl;
	for(int i=0;i<8;i++) {
		cout << "i: " << i << endl;
		cout << "sizeof(temp): " << sizeof((message >> (i*8)).to_ulong()) << endl;
		bitset<8> temp(string((message << i*8).to_string()));
		cout << "sizeof(temp) bis: " << sizeof(temp) << endl; 
		cout << "temp(string): '" << temp << "'" << endl;
		cout << "temp(ulong): '" << temp.to_ulong() << "'" << endl;
		plainText[i] = temp.to_ulong();
	}
	cout << "sizeof(plainText): " << sizeof(plainText) << endl;
	cout << "caca" << endl;
	cout << "plainText after: '" << plainText << "'" << endl;
	string out;
	out.clear();
	CryptoPP::StringSource(plainText,sizeof(plainText),true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(out)
		)
	);
	cout << out << endl;
*/
//	bitset<12> pass(string("101001100001"));
//	int n = 64/8;
//	byte key[] = {0,0,0,0,0,0,0,0};
//	//On a le bit de parité en fin de chaque byte. Les 6 premiers bytes seront à 0.
//	//Ensuite, Le 1er bit du 8e byte est le bit de parité. On le met à 0, osef.
//	//Ensuite on doit décaler les 8 bit utiles d'une place vers la gauche (on multiplie
//	//par 2). Le 8e sera donc renvoyé vers le  7e byte. Attention, il sera envoyé à la
//	//deuxième position du 7e byte puisque la première est occupée par le bit de parité.
//	//On aura donc quelque chose qui ressemble à :
//	//| 0 0 b12 b11 b10 b9 b8 p7 | b7 b6 b5 b4 b3 b2 b1 p8 |
//	//où pi est le bit de parité du byte i.
//	bitset<8> temp = (pass << 1).to_ulong();//On garde bits 7 à 1
//	key[7] = temp.to_ulong();
//	temp = (pass >> 7).to_ulong();//On garde bits 12 à 8
//	temp.set(7,0);//bit de parité, on s'en fout, en soit.
//	key[6] = temp.to_ulong();
// 
//	//Code from codeproject
//	//byte plainText[] = {'H','E','L','L','O',' ','W','O','R','L','D',
//	//	0x0,0x0,0x0,0x0,0x0};
//	
//	//Il se peut que j'aie un probleme avec le fait que byte n'est pas un tableau
//	//de bytes (de 8 bits). Il faudrait alors que je me démerde pour parcourir le
//	//bitset et le couper en paquets de 8 bits. Utiliser sizeof(bitset) ?
//	//bitset<12> password(string("101010101010"));
//	//bitset<16> extendedPass(string("0100000101000010"));//Test with "0000" concatenated with password.to_string
//	//bitset<8> passA(string("01000001"));
//	//bitset<8> passB(string("01000010"));
//	//byte plainText[] = {passA.to_ulong(),passB.to_ulong()};
//	//byte plainText[] = {passA.to_ulong()};
//
//	//
//	//Trying to convert 56btits long bitset into a table of bytes
//	//
//	//bitset<56> extPass
//
//
//	//byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
//	//::memset(key,0x01,CryptoPP::DES::DEFAULT_KEYLENGTH);
//	
//	byte cbCypheredText[CryptoPP::DES::BLOCKSIZE];
//	byte cbRecoveredText[CryptoPP::DES::BLOCKSIZE];
//	
//	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption Encryptor;
//	Encryptor.SetKey(key,sizeof(key));
//	Encryptor.ProcessData(cbCypheredText,plainText,sizeof(plainText));
//	
//	CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption Decryptor;
//	Decryptor.SetKey(key,sizeof(key));
//	Decryptor.ProcessData(cbRecoveredText,cbCypheredText,sizeof(cbCypheredText));
//
//	cout << "Default key length: " << Encryptor.DefaultKeyLength() << endl;
//	cout << "Block size: " << Encryptor.MandatoryBlockSize() << endl;
//	cout << "Algorithm: " << Encryptor.AlgorithmName() << endl;
//	cout << "Plain text(" << sizeof(plainText) << " bytes): ";
//	cout << "'" << plainText << "'" << endl;
//	cout << "Cypher text(" << sizeof(cbCypheredText) << " bytes)" << endl;
//	cout << "Recovered text(" << sizeof(cbRecoveredText) << " bytes): ";
//	cout << "'" << cbRecoveredText << "'" << endl;
//
//	cout << "### Passing a BITESET to a BYTE" << endl;
//
//	bitset<8> word(string("01000001"));//A
//	byte wordByte = word.to_ulong();
//	cout << "word: '" << word << "'" << endl;
//	cout << "wordByte: '" << wordByte << "'" << endl;
//
//	cout << "### Trying to pass a BYTE to a BITSET" << endl;
//	byte secondWord = 'B';
//	bitset<8> secondBitset = secondWord;
//	cout << "secondWord: '" << secondWord << "'" << endl;
//	cout << "secondBitset: '" << secondBitset << "'" << endl;



	/*
	bitset<8> temp = (bsW << 8).to_ulong();
	cout << temp << endl;
	cout << "bit: " << bsW[11] << endl;
	*/

/*
	//Code from the cryptoPP's wiki

	CryptoPP::AutoSeededRandomPool prng;
	byte key[CryptoPP::DES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key,sizeof(key));

	string plain = "ECB Mode Test";
	string cipher, encoded;
	string decoded;

	//Conversion du plaintext en hex
	CryptoPP::StringSource(plain,true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "Plain Text Hex Style: " << encoded << endl;


	encoded.clear();
	//conversion de la clé en hexadécimal
	CryptoPP::StringSource(key,sizeof(key),true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "key: " << encoded << endl;
	
	cout << "Plain text: " << plain << endl;

	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e;
	e.SetKey(key,sizeof(key));

	//Chiffrement du plaintext
	CryptoPP::StringSource(plain,true,
		new CryptoPP::StreamTransformationFilter(e,
			new CryptoPP::StringSink(cipher)
		)
	);

	encoded.clear();
	//Conversion du texte chiffré en hexadécimal
	CryptoPP::StringSource(cipher,true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "Cipher Text: " << encoded << endl;
	
	CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption d;
	d.SetKey(key,sizeof(key));
	decoded.clear();
	CryptoPP::StringSource(cipher,true,
		new CryptoPP::StreamTransformationFilter(d,
			new CryptoPP::StringSink(decoded)
		)
	);

	encoded.clear();
	CryptoPP::StringSource(decoded,true,
		new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(encoded)
		)
	);
	cout << "Decoded Text: " << encoded << endl;
*/


	return 0;
}

Fingerprint hashDES(Password reducedPass)
{
	byte key[8] = {0,0,0,0,0,0,0,0};
	bitset<8> temp = (reducedPass << 1).to_ulong();//On garde bits 7 à 1
	key[7] = temp.to_ulong();
	temp = (reducedPass >> 7).to_ulong();//On garde bits 12 à 8
	temp.set(7,0);//bit de parité, on s'en fout, en soit.
	key[6] = temp.to_ulong();

	byte cipher[CryptoPP::DES::BLOCKSIZE];
	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e;
	e.SetKey(key,sizeof(key));
	e.ProcessData(cipher,MESSAGE,sizeof(MESSAGE));

	bitset<8> temp1 = cipher[CryptoPP::DES::BLOCKSIZE-2];
	bitset<8> temp2 = cipher[CryptoPP::DES::BLOCKSIZE-1];
	bitset<8> temp3 = cipher[CryptoPP::DES::BLOCKSIZE];

	Fingerprint fingerprint(string(temp1.to_string()+temp2.to_string()+temp3.to_string()));

	return fingerprint;
}
