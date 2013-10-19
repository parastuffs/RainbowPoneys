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
    bitset<HASH_NBR_BITS> word;

    for(i=0; i < limit ; i++)
    {
        //we copy the word (automatic conversion from int to bitset)
        word = i;

        //We apply 4 reductions functions
        for(j=0; j < 4; j++)
        {
            //We hash the actual word and receive the first HASH_NBR_BITS bits (!! HASH_NBR_BITS >= FING_NBR_BITS)
            word = this->hashDES(word);

            //We apply the reduction function
            word = this->reductionFunction(j, word);
        }

        //We have to hash one more time
        word = this->hashDES(word);

        //We watch if the hashed word already exist into the tables, if yes, we go to the next word without saving the actual
        if(this->intoTables(word) >= 0)
            continue;

        //We save the final word
        for(j=0; j < FING_NBR_BITS; j++)
            m_tables[m_tablesLength].set(j,word[j]);
        m_tablesLength++;
    }

    //Done :D!
}

bitset<HASH_NBR_BITS> RainbowAttack::reductionFunction(int number, bitset<HASH_NBR_BITS> fingerprint)
{
    int i;
    bitset<HASH_NBR_BITS> word;

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

    return word;
}

void RainbowAttack::findPassword(bitset<HASH_NBR_BITS> fingerprint)
{

    //ATTENTION : M�thode seulement valable pour les 2 �tapes sur les 3 principales! C'est-�-dire fonctionne
    //si Fs trouv� dans la table, ainsi que si c'est F', F'', F''' et F'''' mais �a ne fonctionne pas pour aller
    //plus loin que �a avec l'histoire de la queue car je ne vois pas comment retrouver le pass dans ce cas-l�, m�me avec l'id�e de Brian...

    int id=-1, i, j;
    bitset<HASH_NBR_BITS> pass;// (and not <PASS_NBR_BITS> !)
    bitset<HASH_NBR_BITS> originalFingerprint;
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
        {//We try to have the password corresponding to the actual step

            //We take the password corresponding to the actual fingerprint (but it's not the true password because there were 4 reductions and 5 hashes), whatever the value of i
            for(j=0; j < PASS_NBR_BITS; j++)
                pass.set(j,m_tables[id][j]);

            //We make the intermediate steps to find the true password (if i=3 the for() is useless, it's normal according to what I understood.)
            for(j=0; j < 3-i; j++)
            {
                pass = this->hashDES(pass);
                pass = this->reductionFunction(j, pass);
            }

            break;
        }
    }

    if(id >= 0)
    {
        cout << "Password found. It is: ";
        for(i=0; i < PASS_NBR_BITS; i++)
            cout << pass[i];
        cout << endl;

        //V�rification (pour d�boguage de l'impl�mentation de l'algorithme)...
        fingerprint = this->hashDES(pass);
        if(fingerprint != originalFingerprint)
            cout << "Mouais il y a un probleme dans l implementation de l algorithme..." << endl;
        else
            cout << "Mot de passe vraiment trouve :D!";

        //Useful for the presentation
        cout << "Original fingerprint:";
        for(i=0; i < HASH_NBR_BITS; i++)
            cout << originalFingerprint[i];
        cout << endl << "Found fingerprint:";
        for(i=0; i < HASH_NBR_BITS; i++)
            cout << fingerprint[i];
    }
    else
    {
        cout << "Nothing found...";
    }
}

int RainbowAttack::intoTables(bitset<HASH_NBR_BITS> fingerprint)
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
            break;
        }
    }

    return id;
}

bitset<HASH_NBR_BITS> RainbowAttack::hashDES(bitset<HASH_NBR_BITS> reducedPass)
{
    //TO DO
    return 0;
}
