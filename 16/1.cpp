#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <regex>

using Rule = std::vector<std::pair<int, int>>;



std::pair<std::string, Rule> parseRule(std::string s)
{
    std::regex regex("^(.*): (.*)-(.*) or (.*)-(.*)$");
    std::smatch m;
    std::regex_match(s, m, regex);

    std::vector<std::pair<int, int>> ranges;

    ranges.emplace_back(std::stoi(m[2]), std::stoi(m[3]));
    ranges.emplace_back(std::stoi(m[4]), std::stoi(m[5]));

    return {m[1], ranges};
}

std::vector<int> parseTicket(std::string s)
{
    std::vector<int> ticket;
    std::string token;
    size_t pos = 0;
    while((pos = s.find(',')) != std::string::npos)
    {
        token = s.substr(0, pos);
        try
        {
            ticket.push_back(std::stoi(token));
        }
        catch(std::exception &e) { }
        s.erase(0, pos + 1);
    }
    try
    {
        ticket.push_back(std::stoi(s));
    }
    catch(std::exception &e) { }

    return ticket;
}

bool checkRanges(std::map<std::string, Rule> rules, int t)
{
    for(auto r: rules)
    {
        if ((t >= r.second[0].first && t <= r.second[0].second) || (t >= r.second[1].first && t <= r.second[1].second))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::string input;
    std::map<std::string, Rule> rules;
    std::vector<int> myTicket;
    std::vector<std::vector<int>> tickets;

    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty()) break;

        auto r = parseRule(input);
        rules[r.first] = r.second;
    }

    std::getline(std::cin, input);
    std::getline(std::cin, input);
    myTicket = parseTicket(input);

    std::getline(std::cin, input);
    std::getline(std::cin, input);

    while(true)
    {
        std::getline(std::cin, input);
        tickets.push_back(parseTicket(input));

        if(std::cin.eof()) break;
    }

    int count = 0;
    for(auto ticket: tickets)
    {
        for(auto t: ticket)
        {
            if(!checkRanges(rules, t))
            {
                count += t;
            }
        }
    }

    std::cout << count;

    return 0;
}
