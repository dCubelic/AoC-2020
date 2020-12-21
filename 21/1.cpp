#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

std::vector<std::string> split(std::string const & s, std::string const & delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0;
    size_t pos = 0;
    do
    {
        pos = s.find(delim, prev);
        if (pos == std::string::npos) { pos = s.length(); }
        std::string token = s.substr(prev, pos-prev);
        if (!token.empty()) { tokens.push_back(token); }
        prev = pos + delim.length();
    }
    while (pos < s.length() && prev < s.length());
    return tokens;
}

int main()
{
    std::map<std::string, std::set<std::string>> m;
    std::map<std::string, int> ingredCount;

    std::string input;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.eof()) { break; }

        input.erase(std::remove(input.begin(), input.end(), ')'), input.end());
        auto pos = input.find('(');
        std::vector<std::string> ingredients = split(input.substr(0, pos), " ");
        std::vector<std::string> alergens = split(input.substr(pos + 9, input.size() - pos - 9), ",");

        std::set<std::string> s;
        for(auto const & ingred: ingredients)
        {
            s.insert(ingred);
            ingredCount[ingred]++;
        }
        for(auto const & alergen: alergens)
        {
            auto a = alergen;
            a.erase(std::remove(a.begin(), a.end(), ' '), a.end());
            if(m.find(a) == m.end())
            {
                m[a] = s;
            }
            else
            {
                std::set<std::string> intersection;
                std::set_intersection(m[a].begin(), m[a].end(), s.begin(), s.end(), std::inserter(intersection, intersection.begin()));
                m[a] = intersection;
            }
        }
    }

    std::set<std::string> def;
    for(auto const & d: m)
    {
        def.insert(d.second.begin(), d.second.end());
    }

    int sum = 0;
    for(auto const & ingred: ingredCount)
    {
        if(def.find(ingred.first) == def.end())
        {
            sum += ingred.second;
        }
    }

    std::cout << sum;

    return 0;
}

