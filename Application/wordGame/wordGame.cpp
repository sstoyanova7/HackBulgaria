#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream input("input.txt", ios::in);

    int capacity = 10, rows = 0;
    string word;
    string* table = new string[capacity];

    input >> word;

    while(!input.eof())
    {
        if(rows == capacity)
        {
            capacity += 10;
            string* tmp = new string[capacity];
            for(int i = 0; i < rows; i++)
                tmp[i] = table[i];
            delete []table;
            table = tmp;
        }
        input >> table[rows++];
    }

    input.close();
    int wordSize = word.size(),
        columns = table[0].size(),
        counter = 0;
    bool flag = 1;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            if(word[0] == table[i][j])
            {
                if(wordSize <= i+1) //up
                {
                    int m = i;
                    for(int k = 0; k < wordSize && flag; k++, m--)
                        if(word[k] != table[m][j])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= rows - i) //down
                {
                    int m = i;
                    for(int k = 0; k < wordSize && flag; k++, m++)
                        if(word[k] != table[m][j])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= j+1) //left
                {
                    int n = j;
                    for(int k = 0; k < wordSize && flag; k++, n--)
                        if(word[k] != table[i][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= columns - j) //right
                {
                    int n = j;
                    for(int k = 0; k < wordSize && flag; k++, n++)
                        if(word[k] != table[i][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= i+1 && wordSize <= j+1) //up&left
                {
                    int m = i, n = j;
                    for(int k = 0; k < wordSize && flag; k++, m--, n--)
                        if(word[k] != table[m][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= i+1 && wordSize <= columns -j) //up&rigjt
                {
                    int m = i, n = j;
                    for(int k = 0; k < wordSize && flag; k++, m--, n++)
                        if(word[k] != table[m][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= rows - i && wordSize <= j+1) //down&left
                {
                    int m = i, n = j;
                    for(int k = 0; k < wordSize && flag; k++, m++, n--)
                        if(word[k] != table[m][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }

                if(wordSize <= rows - i && wordSize <= columns -j) //down&rigjt
                {
                    int m = i, n = j;
                    for(int k = 0; k < wordSize && flag; k++, m++, n++)
                        if(word[k] != table[m][n])
                            flag = 0;
                    if(flag)
                        counter++;
                    flag = 1;
                }
            }
        }
    cout << counter;

    delete []table;
    return 0;
}
