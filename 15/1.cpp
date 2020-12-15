#include <iostream>
#include <cstdio>
#include <map>

int main()
{
    int a;
    int counter = 1;
    std::map<int, int> m;
    std::map<int, int> m2;
    while(int r = scanf("%d,", &a) > 0)
    {
        m[a] = counter++;
    }

    while(counter < 2021)
    {
        if(m2.find(a) != m2.end())
        {
            a = m2[a];
        }
        else
        {
            a = 0;
        }
        if(m.find(a) != m.end())
        {
            m2[a] = counter - m[a];
        }
        m[a] = counter;
        counter++;
    }

    std::cout << a;

    return 0;
}
