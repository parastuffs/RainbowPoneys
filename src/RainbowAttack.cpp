#include "../include/RainbowAttack.h"
#include "../include/bitsetFunctions.h"

//Useful : http://www.cplusplus.com/reference/bitset/bitset/

RainbowAttack::RainbowAttack()
{
    m_tablesLength=0;
    this->tablesCreation();

}

RainbowAttack::~RainbowAttack()
{
    //dtor
}

void RainbowAttack::tablesCreation()
{
    //We list all the existing words
    int i, j, limit;
    limit = pow(2, PASS_NBR_BITS);
    bitset<PASS_NBR_BITS> pass;
    bitset<PASS_NBR_BITS> word;
    bitset<FING_NBR_BITS> fingPrint;

    for(i=0; i < limit ; i++)
    {
        //we copy the word (automatic conversion from int to bitset)
        word = pass = i;

        //We apply 4 reduction functions
        for(j=0; j < 4; j++)
        {
            fingPrint = this->hashDES(word);

            //We apply the reduction function
            word = this->reductionFunction(j, fingPrint);
        }

        //We have to hash one more time
        fingPrint = this->hashDES(word);

        //We watch if the hashed word already exists in the tables, if it does,
        //we go to the next word without saving the current
        if(this->intoTables(fingPrint) >= 0)
            continue;

        //We save the final word
        for(j=0; j < FING_NBR_BITS; j++)
        	m_tables[m_tablesLength].set(j,fingPrint[j]);
        for(j=0;j<PASS_NBR_BITS;j++)
            m_dictionary[m_tablesLength].set(j,pass[j]);
        m_tablesLength++;
    }

    cout << "Table Length: " << m_tablesLength << endl;
    //Done :D!
}


bitset<PASS_NBR_BITS> RainbowAttack::reductionFunction(int number,
		bitset<FING_NBR_BITS> fingerprint)
{
    if(number == 0) {
		return blue(fingerprint);
    }
    else if(number == 1) {
        return green(fingerprint);
    }
    else if(number == 2) {
		return yellow(fingerprint);
    }
    else if(number == 3) {
		return red(fingerprint);
    }
	else
		return 0;
}

bitset<PASS_NBR_BITS> RainbowAttack::blue(bitset<FING_NBR_BITS> fingerprint)
{
	fingerprint=mirror(fingerprint);
	return hopOne(fingerprint);
}

bitset<PASS_NBR_BITS> RainbowAttack::green(bitset<FING_NBR_BITS> fingerprint)
{
	fingerprint=flipAll(fingerprint);
	return keepRight(fingerprint);
}

bitset<PASS_NBR_BITS> RainbowAttack::yellow(bitset<FING_NBR_BITS> fingerprint)
{
	fingerprint=mirror(fingerprint);
	fingerprint=rotate(fingerprint,18);
	fingerprint=flipAll(fingerprint);
	return hopTwo(fingerprint);
}

bitset<PASS_NBR_BITS> RainbowAttack::red(bitset<FING_NBR_BITS> fingerprint)
{
	fingerprint=rotate(fingerprint, 7);
	fingerprint=mirror(fingerprint);
	return sumTwo(fingerprint);
}

void RainbowAttack::findPassword(bitset<FING_NBR_BITS> fingerprint)
{
    int id=-1, i, j;
    bitset<PASS_NBR_BITS> pass;
    bitset<FING_NBR_BITS> originalFingerprint;
    originalFingerprint = fingerprint;

    //Look if the fingerprint is into the tables, and give its corresponding ID
    for(i=0 ; i < 4; i++)
    {
        id=this->intoTables(fingerprint);

        if(id < 0)
        {//fingerprint not found
            pass = this->reductionFunction(3-i, fingerprint);
            fingerprint = this->hashDES(pass);
        }
        else
        {//We try to have the password corresponding to the current step

            //We take the password corresponding to the actual fingerprint
            //(but it's not the true password because there were 4 reductions
            //and 5 hashes), whatever the value of i
            for(j=0; j < PASS_NBR_BITS; j++)
                pass.set(j,m_tables[id][j]);

            //We make the intermediate steps to find the true password
            //(if i=3 the for() is useless)

            //I add this temp, but we have to find a workaround
            bitset<FING_NBR_BITS> tempFing;
            for(j=0; j < 3-i; j++)
            {
                tempFing = this->hashDES(pass);
                pass = this->reductionFunction(j, tempFing);
            }

            break;//Mauvaise pratique
        }
    }

    if(id >= 0)
    {
        cout << "Password found. It is: ";
        for(i=0; i < PASS_NBR_BITS; i++)
            cout << pass[i];
        cout << endl;

        //Vérification (pour déboguage de l'implémentation de l'algorithme)...
        fingerprint = this->hashDES(pass);
        if(fingerprint != originalFingerprint)
            cout << "Mouais il y a un probleme dans l implementation de l algorithme..." << endl;
        else
            cout << "Mot de passe vraiment trouve :D!";

        //Useful for the presentation
        cout << "Original fingerprint:";
        for(i=0; i < FING_NBR_BITS; i++)
            cout << originalFingerprint[i];
        cout << endl << "Found fingerprint:";
        for(i=0; i < FING_NBR_BITS; i++)
            cout << fingerprint[i];
    }
    else
    {
        cout << "Nothing found...";
    }
}

int RainbowAttack::intoTables(bitset<FING_NBR_BITS> fingerprint)
{
    int i, j;
    bool ok=false;
    int id=-1;

    //We check every fingerprint
    for(i=0; i < m_tablesLength && id < 0; i++)
    {
        //We check every bit
		//Highly unefficient way to check.
		//We should sort the table first, then either
		//do a dichotomic search or some sort of dictionary
		//search. Not check every bit of every word.
        ok=true;
        for(j=0; j < FING_NBR_BITS; j++)
            if(m_tables[i][j] != fingerprint[j])
                ok=false;
        if(ok == true)
            id = i;
    }

    return id;
}

bitset<FING_NBR_BITS> RainbowAttack::hashDES(bitset<PASS_NBR_BITS> reducedPass)
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
	e.ProcessData(cipher,message,sizeof(message));

	//Not very nice way to do it.
	bitset<8> temp1 = cipher[CryptoPP::DES::BLOCKSIZE-2];
	bitset<8> temp2 = cipher[CryptoPP::DES::BLOCKSIZE-1];
	bitset<8> temp3 = cipher[CryptoPP::DES::BLOCKSIZE];

	bitset<FING_NBR_BITS> fingerprint(string(temp1.to_string()+temp2.to_string()
												+temp3.to_string()));

	//cout << "fingerprint: '" << fingerprint << "'" << endl;

	return fingerprint;
}
