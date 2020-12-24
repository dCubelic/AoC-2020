#include <iostream>
#include <string>
#include <regex>
#include <map>

int main()
{
    std::string input;
    std::map<std::pair<int, int>, bool> m;

    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.eof()) { break; }
        input = std::regex_replace(input, std::regex("se"), "a");
        input = std::regex_replace(input, std::regex("sw"), "b");
        input = std::regex_replace(input, std::regex("ne"), "c");
        input = std::regex_replace(input, std::regex("nw"), "d");

        int x = 0;
        int y = 0;
        for(auto & c: input)
        {
            if(c == 'e')
            {
                y -= 2;
            }
            else if(c == 'w')
            {
                y += 2;
            }
            else if(c == 'a')
            {
                x += 1;
                y -= 1;
            }
            else if(c == 'b')
            {
                x += 1;
                y += 1;
            }
            else if(c == 'c')
            {
                x -= 1;
                y -= 1;
            }
            else if(c == 'd')
            {
                y += 1;
                x -= 1;
            }
        }
        m[{x, y}] = !m[{x, y}];
    }

    int count = 0;
    for(auto const & kv: m)
    {
        if(kv.second)
        {
            count++;
        }
    }

    std::cout << count;

    return 0;
}
