#include <iostream>
using namespace std;

int main()
{
    double x, y;
    bool flag = 0;
    string directions;

    cout << "Starting point: ";
    cin >> x >> y;

    cout << "Type string: ";
    cin >> directions;

    for(int i = 0; i < directions.size(); i++)
    {
        switch (directions[i])
        {
            case '~': flag = !flag; break;
            case '>': if(flag) x--; else x++; break;
            case '<': if(flag) x++; else x--; break;
            case 'v': if(flag) y--; else y++; break;
            case '^': if(flag) y++; else y--; break;
        }
    }

   cout << "(" << x << ", " << y << ")";








    return 0;
}
