#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <set>

std::vector<std::pair<int, int>> deltas = {{0, 2}, {0, -2}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

int count(std::set<std::pair<int, int>> const & blacks, int x, int y)
{
    auto count = 0;
    for(auto const & d: deltas)
    {
        if(blacks.find({x+d.first, y+d.second}) != blacks.end())
        {
            count++;
        }
    }
    return count;
}

std::set<std::pair<int, int>> neighbours(std::set<std::pair<int, int>> const & blacks)
{
    std::set<std::pair<int, int>> n;

    for(auto const & b: blacks)
    {
        for(auto const & d: deltas)
        {
            n.insert({b.first+d.first, b.second+d.second});
        }
    }

    return n;
}

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

    std::set<std::pair<int, int>> blacks;
    for(auto const & kv: m)
    {
        if(kv.second)
        {
            blacks.insert({kv.first.first, kv.first.second});
        }
    }

    for(int i = 0; i < 100; ++i)
    {
        auto oldBlacks = blacks;
        std::set<std::pair<int, int>> neighs = neighbours(blacks);
        for(auto const & b: oldBlacks)
        {
           auto c = count(oldBlacks, b.first, b.second);
           if(c == 0 || c > 2)
           {
               blacks.erase(b);
           }
        }
        for(auto const & n: neighs)
        {
            auto c = count(oldBlacks, n.first, n.second);
            if(c == 2)
            {
                blacks.insert(n);
            }
        }
    }

    std::cout << blacks.size() << "\n";

    return 0;
}

