#include "../include/RainbowAttack.h"
#include "../include/bitsetFunctions.h"

RainbowAttack::RainbowAttack()
{
	m_tablesLength=0;
	m_foundNum = 0;
	this->tablesCreation();
}

RainbowAttack::~RainbowAttack() {}

void RainbowAttack::tablesCreation()
{
	//We list all the existing words
	int j, limit;
	limit = pow(2, PASS_SIZE);
	Password pass, tmpPass;
	Fingerprint fingPrint;
	Fingerprint previousFingPrint;

	for(int i=0; i < limit ; i++)
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

	for(int i=0;i<m_tablesLength; i++) {
		cout << hashDES(m_dictionary[i]);
		if(i<m_tablesLength-1)
			cout << endl;
	}

	//Sort the table
	insertionSort();

	//Delete the duplicate fingerprints
	j=1;
	for(int i=1; i < m_tablesLength; i++) {
		if(m_tables[i-1] != m_tables[i]) {
			m_tables[j] = m_tables[i];
			m_dictionary[j] = m_dictionary[i];
			j++;
		}
	}
	m_tablesLength = j;

	//cout<<"Length of the Rainbow Table: "<<m_tablesLength<<endl;
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
	fingerprint=rotate(fingerprint,1);
	return keepLeft(fingerprint);
}

Password RainbowAttack::green(Fingerprint fingerprint)
{
	// Second reduction function
	fingerprint=rotate(fingerprint,2);
	return keepLeft(fingerprint);
}

Password RainbowAttack::yellow(Fingerprint fingerprint)
{
	// Third reduction function
	fingerprint=rotate(fingerprint,3);
	return keepLeft(fingerprint);
}

Password RainbowAttack::red(Fingerprint fingerprint)
{
	// Fourth reduction function
	fingerprint=rotate(fingerprint,4);
	return keepLeft(fingerprint);
}

void RainbowAttack::findPassword(Fingerprint fingerprint)
{
    int id;
    Password pass;
    Fingerprint originalFingerprint;
    originalFingerprint = fingerprint;
	bool found=false;
	
    //Look if the fingerprint is into the tables, and give its corresponding ID
    for(int i=0 ; i < 4 && !found; i++)
    {
        id=this->inTable(fingerprint);

        if(id >= 0)
        {//We try to have the password corresponding to the current step
			pass = m_dictionary[id].to_ulong();

            Fingerprint tempFing;
			for(int j=0; j < 4 && !found; j++) {
				tempFing = this->hashDES(pass);
				if(tempFing == originalFingerprint) {
					found = true;
				}
				if(!found) {
					pass = this->reductionFunction(j, tempFing);
					//pass = this->reductionFunction(j, tempFing);
				}
			}
        }
		if(!found)
        {//fingerprint not found
			for(int j=3-i; j < 4; j++) {
            	pass = this->reductionFunction(j, fingerprint);
            	//pass = this->reductionFunction(j, fingerprint);
            	fingerprint = this->hashDES(pass);
			}
        }
    }

    if(found)
    {
        cout << "Password found. It is: " << pass << endl;

        //Vérification (pour déboguage de l'implémentation de l'algorithme)...
        fingerprint = this->hashDES(pass);
        if(fingerprint != originalFingerprint) {
            cout << "Something is wrong" << endl;
		}
        else {
			m_foundNum++;
            cout << "Mot de passe vraiment trouve :D!";
		}

        //Useful for the presentation
        cout << "Original fingerprint: " << originalFingerprint << endl;
        cout << "Found fingerprint: "<< fingerprint << endl;
    }
    else
    {
        cout << "Rainbow table incomplete." << endl;
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
	byte key[8] = {0,0,0,0,0,0,0,0};

	//Since we won't check them, the value of the parity bits doesn't matter.
	//The next few lines will shift the last 12 bits of the 64 bits key
	//so that the last bit of each byte can hold a parity byte.
	bitset<8> temp = (reducedPass << 1).to_ulong();
	key[7] = temp.to_ulong();
	temp = (reducedPass >> 7).to_ulong();
	temp.set(7,0);
	key[6] = temp.to_ulong();

	byte cipher[CryptoPP::DES::BLOCKSIZE];
	CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption e;
	e.SetKey(key,sizeof(key));
	e.ProcessData(cipher,MESSAGE,sizeof(MESSAGE));

	//Keeping only the last 24 bits of the cipher.
	bitset<8> temp1 = cipher[CryptoPP::DES::BLOCKSIZE-2];
	bitset<8> temp2 = cipher[CryptoPP::DES::BLOCKSIZE-1];
	bitset<8> temp3 = cipher[CryptoPP::DES::BLOCKSIZE];

	Fingerprint fingerprint(string(temp1.to_string()+temp2.to_string()
												+temp3.to_string()));
	return fingerprint;
}
