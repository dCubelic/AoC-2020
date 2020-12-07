#include <iostream>
#include <string>
#include <map>
#include <set>
#include <regex>

bool canContainShiny(std::string const & s, std::map<std::string, std::set<std::string>> const & m)
{
    auto mv = m.find(s);
    if(mv->second.find("shiny gold") != mv->second.end())
    {
       //std::cout << mv -> first << '\n';
       return true;
    }
    else
    {
        for(auto b: mv->second)
        {
            auto z = canContainShiny(b, m);
            if(z) return true;
        }
    }

    return false;
}

void parseInput(std::map<std::string, std::set<std::string>> & m, std::string const & input)
{
    std::string inp = input;

    std::regex regex("(.*) bags contain");
    std::smatch sm;
    std::regex_search(inp, sm, regex);
    std::string bag = sm[1];

    regex = "( ([0-9]) (.*?) bag[s]?[,.])";
    std::set<std::string> s;
    while(std::regex_search(inp, sm, regex))
    {
        s.insert(sm[3]);
        inp = sm.suffix();
    }
    m.insert({bag, s});
}

int main()
{
    std::map<std::string, std::set<std::string>> m;
    std::string input;

    while(true)
    {
        std::getline(std::cin, input);
        parseInput(m, input);
        if(std::cin.eof()) break;
    }

    int sum = 0;
    for(auto it: m)
    {
        if(canContainShiny(it.first, m)) sum++;
    }

    std::cout << sum;
    return 0;
}
