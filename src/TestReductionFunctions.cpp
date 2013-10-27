#include "../include/TestReductionFunctions.h"

TestReductionFunctions::TestReductionFunctions()
{
    //ctor
}

//Print the number of collisions of each reduction function
void TestReductionFunctions::comparisonReductionFunctions()
{
    int numberOfReductionFunctions = 4, i, result=0;
    RainbowAttack* Rainbow = new RainbowAttack();

    //There is no many reduction functions that we have to test, so we don't need to automatically find the 4 best reduction functions, we decide to just print them and let the programmer find the 4 reduction functions that lead to the lowest number of collisions.
    for(i=0; i < numberOfReductionFunctions; i++)
    {
        result = numberOfCollisions(Rainbow, i);
        cout << "Reduction function " << i << " gives " << result << " collision(s)." << endl;
    }

    cout << endl << "Take the four reduction functions that lead to the lowest number of collisions.";
}

//Create the rainbow table with only reduction function and return the number of collisions with de 2^12 passwords
//The methods used in this method should be private. The return statement should
//be based on a getTableLength.
int TestReductionFunctions::numberOfCollisions(RainbowAttack* Rainbow, int reductionFunction)
{
    int i, j, limit, tablesLength=0;
    limit = pow(2, PASS_SIZE);
    Password pass;
    Password word;
    Fingerprint fingPrint;
    Password tables[4096];//We don't need Fingerprint here because we won't save the fingerprints, it will be the fingerprint after the reduction function

    for(i=0; i < limit ; i++)
    {
        //we copy the word (automatic conversion from int to bitset)
        word = pass = i;

        //We hash the password
        fingPrint = Rainbow->hashDES(word);

        //We apply 1 reduction functions
        word = Rainbow->reductionFunction(reductionFunction, fingPrint);

        //We don't have to hash one more time, it's useless for this test
        //We watch if the password already exists in the tables, if it does,
        //we go to the next word without saving the current
        if(inTable(word, tablesLength, tables) >= 0)
            continue;

        //We save the final word
        for(j=0; j < PASS_SIZE; j++)
        	tables[tablesLength].set(j,word[j]);
        //useless to save the password into the dictionnary
        tablesLength++;
    }

    return 4096 - tablesLength;
}

int TestReductionFunctions::inTable(Password word, int tablesLength, Password tables[])
{
    int i, j;
    int id=-1;

    //We check every word
    for(i=0; i < tablesLength && id >= 0; i++)
        if(tables[i] != word)
            id = i;

    return id;
}

TestReductionFunctions::~TestReductionFunctions()
{
    //dtor
}
