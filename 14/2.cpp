#include <iostream>
#include <string>
#include <cstdio>
#include <map>
#include <bitset>

void writeToMaskedAddress(int start_index, std::string const & mask, unsigned long long pos, unsigned long long val, std::map<unsigned long long, unsigned long long> & m)
{
    std::bitset<36> p(pos);

    for(int i = start_index; i < 36; ++i)
    {
        if(mask[35-i] == '1')
        {
            p.set(i);
        }
        else if(mask[35-i] == 'X')
        {
            p.reset(i);
            writeToMaskedAddress(i+1, mask, p.to_ullong(), val, m);
            p.set(i);
            writeToMaskedAddress(i+1, mask, p.to_ullong(), val, m);
            return;
        }
    }

    m[p.to_ullong()] = val;
}

int main()
{
    std::string input;
    std::string mask;
    std::map<unsigned long long int, unsigned long long> m;

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
            unsigned long long val = std::stoi(input.substr(input.find('=') + 2));

            writeToMaskedAddress(0, mask, pos, val, m);
        }

        if(std::cin.eof()) { break; }
    }

    unsigned long long sum = 0;
    for(auto e: m)
    {
        sum += e.second;
    }

    std::cout << sum;

    return 0;
}

