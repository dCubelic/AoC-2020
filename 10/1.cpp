#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

int main()
{
    int a;
    std::vector<int> inputs;
    while(int r = scanf("%d", &a) > 0)
    {
        inputs.push_back(a);
    }

    std::cout << "out\n";

    std::sort(inputs.begin(), inputs.end());

    int cur_jolt = 0;
    std::map<int, int> m;
    for(auto jolt: inputs)
    {
        m[jolt - cur_jolt]++;
        cur_jolt = jolt;
    }

    std::cout << m[1] * (m[3] + 1);

    return 0;
}
