#include <iostream>
#include <cstdio>
#include <unordered_map>

int main()
{
    int a;
    int counter = 1;
    std::unordered_map<int, int> m;
    std::unordered_map<int, int> m2;
    while(int r = scanf("%d,", &a) > 0)
    {
        m[a] = counter++;
    }

    while(counter < 30000001)
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
