#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<int, int>> split(std::string & s)
{
    std::vector<std::pair<int, int>> values;

    size_t pos = 0;
    std::string token;
    int index = 0;
    while ((pos = s.find(',')) != std::string::npos) {
        token = s.substr(0, pos);
        try
        {
            values.emplace_back(std::stoi(token), index);
        }
        catch(std::exception &e) { }
        s.erase(0, pos + 1);
        index++;
    }
    try
    {
        values.emplace_back(std::stoi(s), index);
    }
    catch(std::exception &e) { }

    return values;
}

int main()
{
    long long t;
    std::string input;
    scanf("%lld\n", &t);
    std::getline(std::cin, input);
    std::vector<std::pair<int, int>> values = split(input);

    t = 0;
    long long step = values[0].first;
    while(true)
    {
        bool flag = true;
        for(auto p: values)
        {
            if((t + p.second) % p.first != 0) {
                flag = false;
                break;
            }
            else
            {
                if(step % p.first != 0)
                {
                    step *= p.first;
                }
            }
        }
        if(flag)
        {
            std::cout << t;
            break;
        }
        t += step;
    }

    return 0;
}

