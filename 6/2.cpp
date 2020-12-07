#include <iostream>
#include <string>
#include <set>
#include <map>

int main()
{
    std::string input;
    std::map<char, int> m;
    int sum = 0;
    int pc = 0;
    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty())
        {
            for(auto it: m)
            {
                if(it.second == pc)
                {
                    sum++;
                }
            }
            if(std::cin.eof()) break;
            pc = 0;
            m.clear();
        }
        else
        {
            pc++;
            for(auto c: input)
            {
                auto s = m.find(c);
                if(s != m.end())
                {
                    s->second++;
                }
                else
                {
                    m.insert({c, 1});
                }
            }
        }
    }

    std::cout << sum;

    return 0;
}

