#include <iostream>
#include <string>
#include <map>
#include <set>
#include <regex>

int numOfBags(std::string const & s, std::map<std::string, std::set<std::pair<std::string, int>>> const & m)
{
    auto mv = m.find(s);
    int sum = 0;
    for(auto b: mv->second)
    {
       sum += b.second + b.second * numOfBags(b.first, m);
    }
    return sum;
}

void parseInput(std::map<std::string, std::set<std::pair<std::string, int>>> & m, std::string const & input)
{
    std::string inp = input;

    std::regex regex("(.*) bags contain");
    std::smatch sm;
    std::regex_search(inp, sm, regex);
    std::string bag = sm[1];

    regex = "( ([0-9]) (.*?) bag[s]?[,.])";
    std::set<std::pair<std::string, int>> s;
    while(std::regex_search(inp, sm, regex))
    {
        s.insert({sm[3], std::stoi(sm[2])});
        inp = sm.suffix();
    }
    m.insert({bag, s});
}

int main()
{
    std::map<std::string, std::set<std::pair<std::string, int>>> m;
    std::string input;

    while(true)
    {
        std::getline(std::cin, input);
        parseInput(m, input);
        if(std::cin.eof()) break;
    }

    std::cout << numOfBags("shiny gold", m);

    return 0;
}
