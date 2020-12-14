#include <iostream>
#include <string>
#include <cstdio>
#include <map>
#include <bitset>

unsigned long long calculateMaskedVal(std::string const & mask, long long val)
{
    std::bitset<36> v(val);
    for(int i = 0; i < 36; ++i)
    {
        if(mask[35-i] == '1') v.set(i);
        else if(mask[35-i] == '0') v.reset(i);
    }

    return v.to_ullong();
}

int main()
{
    std::string input;
    std::string mask;
    std::map<int, long long> m;

    while(true)
    {
        std::getline(std::cin, input);
        if(input.find("mask") == 0)
        {
            mask = input.substr(7);
        }
        else if(input.find("mem") == 0)
        {
            int pos = std::stoi(input.substr(4, input.find(']') - input.find('[') - 1));
            long long val = std::stoi(input.substr(input.find('=') + 2));

            m[pos] = calculateMaskedVal(mask, val);
        }

        if(std::cin.eof()) { break; }
    }

    long long sum = 0;
    for(auto e: m)
    {
        sum += e.second;
    }

    std::cout << sum;

    return 0;
}
