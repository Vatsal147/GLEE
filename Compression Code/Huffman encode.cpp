#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<iterator>

using namespace std;


int main(){
string z;
char y;    

//open the input file to be encoded
ifstream input("Huffman code Test_file_2.txt");
if (input.fail())
{
    cout<<"Error while opening file";
    return 1;
}
//read data from the input file
while(!input.eof())
{
    input.get(y);
    z = z + y;
}
input.close();
//declared map to store the frequency of characters in input file
map <string, int> fqtable;
map <string, int>::iterator itr;
int c0 = 0;

//calculate the fq of characters in input
for (int i = 0, n = z.size(); i < n; i++)
{
    c0 = 0;
    for (itr = fqtable.begin(); itr != fqtable.end(); itr++)
    {
        if ((z.substr(i,1).compare(itr->first)) == 0)
        {
            itr->second++;
            c0++;
            break;
        }
    }
    if (c0 == 0)
    {
        fqtable.insert(pair<string, int>(z.substr(i,1),1));
    }
}


int c1=0, a, b, counter = 0, temp_fq, c2 = 0;
string prsnt, temp_var1, temp_var2;

//declare a map to store the assigned binary codes of characters
map <char, vector<bool>>bncode;
map <char, vector<bool>>::iterator p;

while (fqtable.size() > 0)
{
    c1=0;
    //finding the character with min fq
    for (itr = fqtable.begin(); itr != fqtable.end(); itr++)
    {
        a = itr->second;
        if (c1 == 0)
        {
            b = a;
            prsnt = itr->first;
            c1++;
        }
        if (a < b)
        {
            b = a;
            prsnt = itr->first;
        }
    }
    //run a loop to assign characters their binary codes
    for (int i = 0, n = prsnt.size(); i < n; i++)
    {
        //assigning to those characters which have previously occured
        for (p = bncode.begin(); p != bncode.end(); p++)
        {
            if (prsnt[i] == p->first)
            {
                //check if its the one with min fq
                if (counter % 2 == 0)
                {
                    //assign node a left value
                    bncode[p->first].push_back(false);
                    if (i == n - 1)
                    {
                        //stores the left's variable and fq in temporary variables
                        temp_fq = b;
                        temp_var1 = prsnt;
                        fqtable.erase(prsnt);
                    }
                    else
                    {
                        counter++;
                    }
                    c2++;
                    break;
                }
                //it goes here if its the one with next min fq
                else
                {
                    //assign node a right value
                    bncode[p->first].push_back(true);
                    if (i == n - 1)
                    {
                        //updating the first map with new fq and variable
                        fqtable.erase(prsnt);
                        fqtable.insert(pair<string, int>(temp_var1 + prsnt, b + temp_fq));
                    }
                    else
                    {
                        counter++;
                    }
                    c2++;
                    break;
                }
            }
        }
        //assigning binary code to those characters which have occured for the first time
        if (c2 == 0)
        {
            bncode.insert(pair<char, vector<bool>>(prsnt[i], vector<bool>()));

            if (counter % 2 == 0)
            {
                //assign node a left value
                bncode[prsnt[i]].push_back(false);
                temp_var1 = prsnt[i];
                temp_fq = b;
                fqtable.erase(temp_var1);
            }
            else
            {
                //assign node a right value
                bncode[prsnt[i]].push_back(true);
                temp_var2 = prsnt[i];
                fqtable.erase(temp_var2);
                //adding the new variable into second map
                fqtable.insert(pair<string, int>(temp_var1 + temp_var2, b + temp_fq));
            }
        }
        counter++;
        c2 = 0;
    }
}
//deleting the last bool value from each character as it's extra
for (p = bncode.begin(); p != bncode.end(); p++)
{
    p->second.pop_back();
}
int len;
bool temp_code;
//reversing the order of binary codes to make it in correct order
for (p = bncode.begin(); p != bncode.end(); p++)
{
    len = p->second.size() / 2;
    for (int i = 0; i < len; i++)
    {
        temp_code = p->second[i];
        p->second[i] = p->second[p->second.size() - 1 - i];
        p->second[p->second.size() - 1 - i] = temp_code;
    }
}
//binary file to store ouput
ofstream output("Encoded file_2.dat", ios::binary);
int c3 = 0, byte = 0;

for(unsigned int i = 0; i < z.size(); i++)
{
    for (p = bncode.begin(); p != bncode.end(); p++)
    {
        if (z[i] == p->first)
        {
            for (unsigned int j = 0; j < p->second.size(); j++)
            {
                //grouping bits in chunk of 8 and writing them in binary file
                byte = byte << 1;
                c3++;
                if (bncode[z[i]][j] == 1)
                {
                    byte++;
                }
                if (c3 == 8)
                {
                    c3 = 0;
                    output.write((char*)&byte, sizeof(byte) - 3);
                    byte = 0;
                }
            }
            break;
        }
    }
}
//adding those last left bytes which can't form 8 bits group
if ( c3 != 0)
{
    int tarr = 8 - c3;
    byte = byte << tarr;
    output.write((char*)&byte, sizeof(byte) - 3);
}
output.close();
}

