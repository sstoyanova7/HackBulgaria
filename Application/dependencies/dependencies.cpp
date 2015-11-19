#include <iostream>
#include <windows.h>
#include <io.h>
#include <fstream>
using namespace std;

bool helper(string a) //if returned 1 -> can not be installed
{
    if(access (("installed_modules/" + a).c_str(), 0) == 0)
    {
        cout << a << " is already installed.\n";
        return 0;
    }
    bool flag;
    string packages;
    ifstream inputPackages("all_packages.json", ios::in);
    do
    {
        flag = !inputPackages.eof();
        getline(inputPackages, packages);
        int foundQuote = 0;
        for(; foundQuote != packages.size(); foundQuote++)
            if(packages[foundQuote] == '"')
                break;
        if(packages.find(a) == foundQuote + 1)
            break;
    }while(flag);

    inputPackages.close();

    if(!flag)
    {
        cout << '"' << a << "\" was not found.\n";
        return 1;
    }
    int size = 0, capacity = 2;
    string* dependencies = new string[capacity];
    for(int i = packages.find('['); packages[i] != ']'; i++)
    {
        if(packages[i] == '"')
        {
            string tmp;
            i++;
            for(;packages[i] != '"'; i++)
                tmp.push_back(packages[i]);
            if(size == capacity)
            {
                capacity +=2;
                string* tmp2 = new string[capacity];
                for(int j = 0; j < size; j++)
                    tmp2[j] = dependencies[j];
                delete []dependencies;
                dependencies = tmp2;
            }
            dependencies[size++] = tmp;
        }
    }
    cout << "Installing " << a << ".\n";
    if(size == 0)
    {
        CreateDirectory ( ( "installed_modules//" + a ).c_str(), NULL );
        delete []dependencies;
        return 0;
    }

    cout << "In order to install " << a << ", we need ";
    for(int i = 0; i < size; i++)
    {
        if(i < size - 2)
            cout << dependencies[i] << ",";
        else if(i == size - 2)
            cout << dependencies[i] << " and ";
        else if(i == size - 1)
            cout << dependencies[i] << ".\n";
    }
    flag = 0;
    for(int i = 0; i < size && !flag; i++)
    {
        flag = helper(dependencies[i]);
    }
    if(flag)
    {
        cout << '"' << a << "\" cannot be installed.\n";
        delete [] dependencies;
        return 1;
    }
    CreateDirectory ( ( "installed_modules//" + a ).c_str(), NULL );
    return 0;
}


int main()
{

    string installed = "installed_modules",
           dependencies;
    if(access (installed.c_str(), 0) != 0)
        CreateDirectory(installed.c_str(), NULL);

    ifstream inputDependencies("dependencies.json", ios::in);
    //get(inputDependencies, dependencies, '}');
    bool flag;
    do
    {
        getline(inputDependencies, dependencies);
        flag = !inputDependencies.eof();
        if(dependencies.find("dependencies") != string::npos)
            break;
    }while (flag);
    inputDependencies.close();

    int found = dependencies.find("dependencies");
    flag = 0;
    for(int i = found + 15; dependencies[i] != ']' && !flag; i++)
        if(dependencies[i] == '"')
        {
            string tmp;
            i++;
            for(;dependencies[i] != '"'; i++)
                tmp.push_back(dependencies[i]);
            flag = helper(tmp);
        }
    if(flag)
        cout << "Not all packages were installed.\n";
    else
        cout << "All done.\n";
    return 0;
}
