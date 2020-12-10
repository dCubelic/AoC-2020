#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

std::map<std::vector<int>::iterator, long long> m;

long long count(std::vector<int>::iterator b, std::vector<int>::iterator e)
{
    if(b+1 == e) return 1;
    if(m.find(b) != m.end()) return m[b];

    long long val;
    if(b+3 < e && *(b+3) - *b <= 3)
    {
        val = count(b+3, e) + count(b+2, e) + count(b+1, e);
    }
    else if(b+2 < e && *(b+2) - *b <= 3)
    {
        val = count(b+2, e) + count(b+1, e);
    }
    else
    {
        val = count(b+1, e);
    }
    m[b] = val;
    return val;
}

int main()
{
    int a;
    std::vector<int> inputs;
    while(int r = scanf("%d", &a) > 0)
    {
        inputs.push_back(a);
    }
    inputs.push_back(0);

    std::sort(inputs.begin(), inputs.end());

    printf("%lld", count(inputs.begin(), inputs.end()));

    return 0;
}
