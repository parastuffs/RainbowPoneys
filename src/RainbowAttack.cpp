#include "../include/RainbowAttack.h"
#include "../include/bitsetFunctions.h"

//Useful : http://www.cplusplus.com/reference/bitset/bitset/

RainbowAttack::RainbowAttack()
{
	m_tablesLength=0;
	this->tablesCreation();
}

RainbowAttack::~RainbowAttack() {}

void RainbowAttack::tablesCreation()
{
	//We list all the existing words
	int i, j, limit;
	limit = pow(2, PASS_SIZE);
	Password pass, tmpPass;
	Fingerprint fingPrint;
	Fingerprint previousFingPrint;

	cout<<"Rainbow table : \n"<<endl;
	for(i=0; i < limit ; i++) //limit = 4096
	{
		// Conversion from int to bitset
		pass=i;
		tmpPass = pass;

		// We apply 4 successive hashes/reductions
		for(j=0; j < 4; j++)
		{
			fingPrint = this->hashDES(tmpPass);
			tmpPass = this->reductionFunction(j, fingPrint);
		}
		// We have to hash one last time
		fingPrint = this->hashDES(tmpPass);

		//We save the password and the fingerprint directly
		m_dictionary[m_tablesLength] = pass;
		m_tables[m_tablesLength] = fingPrint;

		m_tablesLength++;
	}

	//We sort the table
	insertionSort();

	//Delete the duplicate fingerprints
	previousFingPrint=m_tables[0];
	j=1;
	for(i=1; i < m_tablesLength; i++) {
		if(previousFingPrint != m_tables[i]) {
			m_tables[j] = m_tables[i];
			m_dictionary[j] = m_dictionary[i];
			j++;
		}
		previousFingPrint = m_tables[i];
	}

	m_tablesLength = j;

/*	for(int i=0;i<m_tablesLength;i++) {
		cout<<"Pass="<<m_dictionary[i];
		cout<<" -> Fingerprint="<<m_tables[i]<<endl;
	}
*/
	cout<<"Length of the Rainbow Table: "<<m_tablesLength<<endl;
}

Password RainbowAttack::reductionFunction(int number, 
		Fingerprint fingerprint)
{
	// 4 different reduction "rainbow" functions
	if(number == 0)
		return blue(fingerprint);
	else if(number == 1)
		return green(fingerprint);
	else if(number == 2)
		return yellow(fingerprint);
	else if(number == 3)
		return red(fingerprint);
	else
	{
		cout<<"ERROR: in reductionFunction"<<endl;
		return 0;
	}
}

Password RainbowAttack::blue(Fingerprint fingerprint)
{
	// First reduction function
	//fingerprint=mirror(fingerprint);
	//fingerprint=rotate(fingerprint,2);
	//return hopOne(fingerprint);
	//return keepRight(fingerprint);
	//return keepLeft(fingerprint);
	//return hopTwo(fingerprint);
	return sumTwo(fingerprint);
}

Password RainbowAttack::green(Fingerprint fingerprint)
{
	// Second reduction function
	fingerprint=flipAll(fingerprint);
	//fingerprint=rotate(fingerprint,5);
	//return hopOne(fingerprint);
	//return keepRight(fingerprint);
	//return keepLeft(fingerprint);
	//return hopTwo(fingerprint);
	return sumTwo(fingerprint);
}

Password RainbowAttack::yellow(Fingerprint fingerprint)
{
	// Third reduction function
	fingerprint=mirror(fingerprint);
	//fingerprint=rotate(fingerprint,9);
	//fingerprint=flipAll(fingerprint);
	//return hopOne(fingerprint);
	//return keepRight(fingerprint);
	//return keepLeft(fingerprint);
	//return hopTwo(fingerprint);
	return sumTwo(fingerprint);
}

Password RainbowAttack::red(Fingerprint fingerprint)
{
	// Fourth reduction function
	fingerprint=rotate(fingerprint, 7);
	fingerprint=mirror(fingerprint);
	//return hopOne(fingerprint);
	//return keepRight(fingerprint);
	//return keepLeft(fingerprint);
	//return hopTwo(fingerprint);
	return sumTwo(fingerprint);
}

void RainbowAttack::findPassword(Fingerprint fingerprint)
{
	int id=-1, i, j;
	Password pass;
	Fingerprint originalFingerprint;
	originalFingerprint = fingerprint;

	//Look if the fingerprint is into the tables, and give its corresponding ID
	for(i=0 ; i < 4; i++)
	{
		id=this->inTable(fingerprint);

		if(id < 0)
		{	//fingerprint not found
			pass = this->reductionFunction(3-i, fingerprint);
			fingerprint = this->hashDES(pass);
		}
		else
		{	//We try to have the password corresponding to the current step

			//We take the password corresponding to the actual fingerprint
			//(but it's not the true password because there were 4 reductions
			//and 5 hashes), whatever the value of i
			pass = m_dictionary[id].to_ulong();
			cout << "We may have found in the dico: " << pass << endl;
			cout << "ID in the table: " << id << endl;

			//We make the intermediate steps to find the true password
			//(if i=3 the for() is useless)

			//I add this temp, but we have to find a workaround
			Fingerprint tempFing;
			for(j=0; j < 4-i; j++)
			{
				tempFing = this->hashDES(pass);
				pass = this->reductionFunction(j, tempFing);
			}

			break;//Mauvaise pratique
		}
	}

	if(id >= 0)
	{
		cout << "Password found. It is: " << pass << endl;

		//Vérification (pour déboguage de l'implémentation de l'algorithme)...
		fingerprint = this->hashDES(pass);
		if(fingerprint != originalFingerprint)
			cout << "Something is wrong" << endl;
		else
			cout << "Mot de passe vraiment trouve :D!";

		//Useful for the presentation
		cout << "Original fingerprint: " << originalFingerprint << endl;
		cout << endl << "Found fingerprint: "<< fingerprint << endl;
	}
	else
	{
		cout << "Nothing found...";
	}
}

void RainbowAttack::insertionSort()
{	//sort the rainbow table according to the fingerprint.
	int i, j;
	Password tempDic;
	Fingerprint temp;

	for(i=1; i < m_tablesLength; i++)
	{
		temp = m_tables[i];
		tempDic = m_dictionary[i];
		for(j = i-1; j>= 0 && m_tables[j].to_ulong() > temp.to_ulong(); j--)
		{
			m_tables[j+1] = m_tables[j];
			m_dictionary[j+1] = m_dictionary[j];
		}

		m_tables[j+1] = temp;
		m_dictionary[j+1] = tempDic;
	}

}

int RainbowAttack::inTable(Fingerprint toFind)
{
	// Dichotomic search which says if we find the fingerprint 
	// (toFind variable) in m_tables and its position
	int low=0;
	int middle;
	int high=m_tablesLength-1;

	do
	{
		middle=(low+high)/2;
		if(m_tables[middle].to_ulong() < toFind.to_ulong())
			low = middle+1;
		else
			high = middle-1;
	}
	while(toFind != m_tables[middle] && low <= high);

	if(toFind == m_tables[middle])
		return middle;
	else
		return -1;
}

Fingerprint RainbowAttack::hashDES(Password reducedPass)
{

	//Beware, the message encoded with DES is constant!
	//The only thing that changes from one iteration to the other
	//is the key, which is extended to 64 bits.
	byte key[8] = {0,0,0,0,0,0,0,0};
	//On a le bit de parité en fin de chaque byte. Les 6 premiers bytes seront à 0.
	//Ensuite, Le 1er bit du 8e byte est le bit de parité. On le met à 0, osef.
	//Ensuite on doit décaler les 8 bit utiles d'une place vers la gauche (on multiplie
	//par 2). Le 8e sera donc renvoyé vers le  7e byte. Attention, il sera envoyé à la
	//deuxième position du 7e byte puisque la première est occupée par le bit de parité.
	//On aura donc quelque chose qui ressemble à :
	//| 0 0 b12 b11 b10 b9 b8 p7 | b7 b6 b5 b4 b3 b2 b1 p8 |
	//où pi est le bit de parité du byte i.
	bitset<8> temp = (reducedPass << 1).to_ulong();//On garde bits 7 à 1
	key[7] = temp.to_ulong();
	temp = (reducedPass >> 7).to_ulong();//On garde bits 12 à 8
	temp.set(7,0);//bit de parité, on s'en fout, en soit.
	key[6] = temp.to_ulong();

	byte cipher[CryptoPP::DES::BLOCKSIZE];
	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e;
	e.SetKey(key,sizeof(key));
	e.ProcessData(cipher,MESSAGE,sizeof(MESSAGE));

	//Not very nice way to do it.
	bitset<8> temp1 = cipher[CryptoPP::DES::BLOCKSIZE-2];
	bitset<8> temp2 = cipher[CryptoPP::DES::BLOCKSIZE-1];
	bitset<8> temp3 = cipher[CryptoPP::DES::BLOCKSIZE];

	Fingerprint fingerprint(string(temp1.to_string()+temp2.to_string()
												+temp3.to_string()));

	//cout << "fingerprint: '" << fingerprint << "'" << endl;

	return fingerprint;
}
