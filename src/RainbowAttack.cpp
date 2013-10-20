#include "../include/RainbowAttack.h"

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
            //We hash the actual word and receive the first HASH_NBR_BITS bits 
	    //(!! HASH_NBR_BITS >= FING_NBR_BITS)
	    //Question: do we recieve to LSB or MSB?
	    //There is another problem: we should give DES the plain text,
	    //that is a 12 bits word.
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

    //Done :D!
}

bitset<PASS_NBR_BITS> RainbowAttack::reductionFunction(int number, 
		bitset<FING_NBR_BITS> fingerprint)
{
    int i;
    //This is wrong, to reduction function reduces the fingerprint
    //to a word the same length as the password, 12 bits.
    bitset<FING_NBR_BITS> word;

    if(number == 0)
    {
        for(i=0; i < FING_NBR_BITS ; i++)
            word.set(i, fingerprint[i]);
    }
    else if(number == 1)
    {
        for(i=0; i < FING_NBR_BITS ; i++)
            word.set(i, fingerprint[(FING_NBR_BITS-i)]);
    }
    else if(number == 2)
    {
        for(i=0; i < FING_NBR_BITS ; i +=2)
        {
            word.set(i, fingerprint[(i+1)]);
            word.set(i+1, fingerprint[i]);
        }
    }
    else if(number == 3)
    {
        for(i=0; i < FING_NBR_BITS ; i++)
            word.set(i, fingerprint[(FING_NBR_BITS-i)]);
        for(i=0; i < FING_NBR_BITS ; i +=2)
        {
            word.set(i, word[(i+1)]);
            word.set(i+1, word[i]);
        }
    }

    return 0;//TO CHANGE, don't have the time right now.
}

void RainbowAttack::findPassword(bitset<FING_NBR_BITS> fingerprint)
{

    //ATTENTION : Méthode seulement valable pour les 2 étapes sur les 
    //3 principales! C'est-à-dire fonctionne
    //si Fs trouvé dans la table, ainsi que si c'est F', F'', F''' et 
    //F'''' mais ça ne fonctionne pas pour aller
    //plus loin que ça avec l'histoire de la queue car je ne vois pas 
    //comment retrouver le pass dans ce cas-là, même avec l'idée de Brian...

    int id=-1, i, j;
    bitset<PASS_NBR_BITS> pass;// (and not <PASS_NBR_BITS> !) => Why not ? It has to have to same length as a password, not a hash.
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
	    //(if i=3 the for() is useless, it's normal according to what 
	    //I understood.)

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
    for(i=0; i < m_tablesLength; i++)
    {
        //We check every bit
        ok=true;
        for(j=0; j < PASS_NBR_BITS; j++)
            if(m_tables[i][j] != fingerprint[j])
                ok=false;
        if(ok == true)
        {
            id = i;
            break;//Mauvaise pratique
        }
    }

    return id;
}

bitset<FING_NBR_BITS> RainbowAttack::hashDES(bitset<PASS_NBR_BITS> reducedPass)
{
    //TO DO
    return 0;
}
