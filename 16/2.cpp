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

bool checkRange(Rule r, int t)
{
    return ((t >= r[0].first && t <= r[0].second) || (t >= r[1].first && t <= r[1].second));
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
        if(std::cin.eof()) break;

        tickets.push_back(parseTicket(input));
    }

    // remove invalid tickets
    for(int i = 0; i < (int) tickets.size(); ++i)
    {
        for(auto t: tickets[i])
        {
            if(!checkRanges(rules, t))
            {
                tickets.erase(tickets.begin() + i);
                i--;
                break;
            }
        }
    }

    // find all valid fields
    std::map<int, std::vector<std::string>> fields;
    for(const auto& r: rules)
    {
        for(int i = 0; i < (int) myTicket.size(); ++i)
        {
            bool valid = true;
            for(auto t: tickets)
            {
                if(!checkRange(r.second, t[i]))
                {
                    valid = false;
                    break;
                }
            }


            if(valid)
            {
                fields[i].push_back(r.first);
            }
        }
    }

    // map fields to indices
    std::map<int, std::string> trueFields;
    auto s = fields.size();
    while(trueFields.size() < s)
    {
       std::string elementToRemove;
       for(auto f: fields)
       {
           if(f.second.size() == 1)
           {
               elementToRemove = f.second[0];
               trueFields[f.first] = f.second[0];
               break;
           }
       }


       for(auto &f: fields)
       {
           auto index = std::find(f.second.begin(), f.second.end(), elementToRemove);
           if(index != f.second.end())
           {
               f.second.erase(index);
           }
       }
    }

    // calculate factor
    long long factor = 1;
    for(const auto& f: trueFields)
    {
       if(f.second.find("departure") == 0)
       {
          factor *= myTicket[f.first];
       }
    }

    std::cout << factor;

    return 0;
}
