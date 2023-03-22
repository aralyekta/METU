#include "the8.h"

#include <fstream>
//DO NOT ADD OTHER LIBRARIES

/* Öğrendiklerim:
    1- Hashing yaparken unsigned int kullan
    2- Hashing yaparken power'dan başlayıp x'e böle böle inmek yerine tam tersini yap
        Çünkü overflowdan başlayıp aşağı inemezsin, ama 1'den başlayıp overflowa çıkabilirsin
        0 -> 0 -> 0 -> 0 -> 0                           1 -> 10 -> 100 -> 1000 -> 0
    3- Hashingde overflow olması sıkıntı değil, hatta iyi bir şey. Otomatik olarak mod implement etmiş oluyorsun.
    4- Farklı keylerin aynı yere hashlenmesi durumunu çözmen lazım. "Amaan olmaz zaten" diyemezsin, olur.
    5- Update hashing yaparken bölmek yerine çarp. Bölerken fraksiyonları integer yuvarlamasına kaybedersin.
        Çarpımda da overflow olarak kaybedersin, ama bunun np olduğunu söylemiştim.
    6- Unsigned - int implicit castinglerine dikkat et, sıkıntı yaşıyor olabilirsin orada.
*/

using namespace std;

unsigned int myHash(string::const_iterator strItr, unsigned int modF, int x, int M, unsigned int power)
{
    unsigned int result = 0;
    unsigned int factor = 1;
    strItr += (M - 1);
    for (int i = 0; i < M; ++i, factor *= x, --strItr)
    {
        result += (*strItr) * factor;
    }
    return result % modF;
}

unsigned int updateHash(char cold, char cnew, unsigned int hashVal, unsigned int modF, int n, int x, unsigned int power)
{
    // cout << "Will update hash from " << hashVal << "\n";
    hashVal -= cold * power;
    // while (hashVal < 0)
    // {
    //     hashVal += modF;
    // }

    hashVal *= 10;
    hashVal += cnew;
    return hashVal % modF;
}

bool matchPattern(string::const_iterator textItr, string pattern, int M)
{
    for (int i = 0; i < M; ++i, ++textItr)
    {
        if (pattern[i] != *textItr)
        {
            return false;
        }
    }
    return true;
}

// int newHash(string::const_iterator strItr, int modF, int M)
// {
//     unsigned long hash = 5381;
//     int c;
//     for (int i = 0; i < M; ++i, ++strItr)
//     {
//         c = *strItr;
//         hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//     }
//     return hash % modF;
// }

vector<int> the8(const string &text, const vector<string> &patterns)
{
    std::ofstream myfile;
    myfile.open("test.txt");
    int modF = 32768;
    int x = 10;
    int M = patterns[0].length();
    vector<int> *hashTable = new vector<int>[modF](); // This part
    int N = text.length();
    int K = 0;
    unsigned int power = pow(x, M - 1);
    vector<int> shifts; //DO NOT CHANGE THIS
    myfile << "modF: " << modF << " and power: " << power << "\n";
    vector<string>::const_iterator patItr = patterns.begin();
    // Create the mapping from hash values to pattern numbers, note that numbers begin from 1
    for (int i = 1; patItr != patterns.end(); ++patItr, ++K, ++i)
    {
        unsigned int hashVal = myHash(patItr->begin(), modF, x, M, power);
        // int hashVal = newHash(patItr->begin(), modF, M);
        // cout << hashVal << "\n";
        hashTable[hashVal].push_back(i); // This part
        myfile << "wrote " << i << " on the index " << hashVal << " and it is for the pattern " << (*patItr) << "\n";
    }

    int index = 1;
    string *numToPat = new string[K + 1];
    // Create the mapping from pattern numbers fo patterns themselves
    for (patItr = patterns.begin(); patItr != patterns.end(); ++patItr, ++index)
    {
        numToPat[index] = *patItr;
    }

    // Do the actual pattern matching across the text
    string::const_iterator textItr = text.begin();
    unsigned int hashVal = myHash(textItr, modF, x, M, power); // The hash value of the first M characters of the text
    // int hashVal = newHash(textItr, modF, M); // The hash value of the first M characters of the text
    int leftIndex = 0;
    int rightIndex = M - 1;
    do
    {
        vector<int>::const_iterator itr = hashTable[hashVal].begin();
        for (; itr != hashTable[hashVal].end(); ++itr)
        {
            int numOfPat = *itr; // This part
            if (numOfPat >= 1)
            {
                string hashMatchedPat = numToPat[numOfPat];
                myfile << "Hash val matched for index " << leftIndex << " for hash val: " << hashVal << "\n";
                bool result = matchPattern(textItr, hashMatchedPat, M);
                myfile << "pattern match result is: " << result << "\n";
                if (result)
                {
                    shifts.push_back(leftIndex);
                    break;
                }
            }
        }

        char cold = text[leftIndex];
        ++leftIndex;
        ++rightIndex;
        char cnew = text[rightIndex];
        hashVal = updateHash(cold, cnew, hashVal, modF, M, x, power);

        ++textItr;
        // hashVal = newHash(textItr, modF, M);
    } while (rightIndex < N - 1);

    vector<int>::const_iterator itr = hashTable[hashVal].begin();
    for (; itr != hashTable[hashVal].end(); ++itr)
    {
        int numOfPat = *itr; // This part
        if (numOfPat >= 1)
        {
            string hashMatchedPat = numToPat[numOfPat];
            myfile << "Hash val matched for index " << leftIndex << " for hash val: " << hashVal << "\n";
            bool result = matchPattern(textItr, hashMatchedPat, M);
            myfile << "pattern match result is: " << result << "\n";
            if (result)
            {
                shifts.push_back(leftIndex);
                break;
            }
        }
    }

    myfile.close();
    delete[] hashTable;
    delete[] numToPat;
    return shifts; //DO NOT CHANGE THIS
}

int main()
{
    // string text = "abcde";
    // const vector<string> patterns = {"ab", "ed"};

    // string text = "abcdefgijbcde";
    // const vector<string> patterns = {"bcde", "defg", "qwer", "uutz"};

    ifstream readText;
    readText.open("text_big");
    string text;
    readText >> text;
    readText.close();

    vector<string> patterns;
    for (int i = 0; i < 1000; i++)
    {
        char curStr[1001];
        scanf("%1000s ", curStr);
        string str = curStr;
        patterns.push_back(str);
    }
    // string::const_iterator itr = text.begin();
    // itr += 394000;
    // cout << "Will do\n";
    // for (int i = 0; i < 1000; i++, itr++)
    // {
    //     cout << *itr;
    // }
    // cout << "\n";

    // string testStr = "lsuultrumkslpnssrpuksunlnonsnrtlkuomskmmmlnsomsmurnssrtknnurutsusnmrnrtssnpnrmppktmssmkmplkputrtltss";
    // string testPtr = "gbbddacajebdegjdejghdbddeihciggghhjcjccagdeajffghbdafgfjgfdebjaiiacaeeaajecacjgjbjjihhjfcdjdecddefdi";
    // unsigned int power = pow(10, 99);
    // cout << " first hash: " << myHash(testStr.begin(), 32768, 10, 100, power) << "\n";
    // cout << " second hash: " << myHash(testPtr.begin(), 32768, 10, 100, power) << "\n";
    vector<int> shifts = the8(text, patterns);
    ofstream writeMatched;
    writeMatched.open("my_output_big");
    vector<int>::iterator itr = shifts.begin();
    for (; itr != shifts.end(); ++itr)
    {
        writeMatched << *itr << "\n";
    }
    writeMatched.close();
    return 0;
}