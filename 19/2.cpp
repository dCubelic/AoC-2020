#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <regex>

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

std::variant<std::vector<std::vector<int>>, std::string> parseRules(std::string const & s)
{
    std::vector<std::vector<int>> parsedRules;
    std::vector<std::string> rules = split(s, "|");

    for(auto const & rule: rules)
    {
        std::vector<int> parsedRule;
        std::vector<std::string> r = split(rule, " ");
        for(auto & str: r)
        {
            try
            {
                parsedRule.push_back(std::stoi(str));
            }
            catch(std::exception & e)
            {
                str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
                return str;
            }
        }
        parsedRules.push_back(parsedRule);
    }

    return parsedRules;
}

std::unordered_map<int, std::string> M;

std::string getRegex(std::unordered_map<int, std::variant<std::vector<std::vector<int>>, std::string>> & rules, int index)
{
    if(M.find(index) != M.end())
    {
        return M[index];
    }
    std::string regex;

    if(index == 8)
    {
        return getRegex(rules, 42) + "+";
    }
    if(index == 11)
    {
        regex = "(";
        for(int i = 1; i < 10; ++i)
        {
            regex += "(" + getRegex(rules, 42) + "{" + std::to_string(i) + "}" + getRegex(rules, 31) + "{" + std::to_string(i) + "})";
            if(i != 9)
            {
                regex += "|";
            }
        }

        return regex + ")";
    }

    auto rule = rules[index];

    try
    {
        regex = std::get<std::string>(rule);
    }
    catch(std::bad_variant_access &e)
    {
        regex = "(";
        auto parts = std::get<std::vector<std::vector<int>>>(rule);
        for(int i = 0; i < (int) parts.size(); ++i)
        {
            auto part = parts[i];
            for(int ruleIndex : part)
            {
                 regex += getRegex(rules, ruleIndex);
            }
            if(i != (int) parts.size() - 1)
            {
                regex += "|";
            }
        }
        regex += ")";
    }

    M[index] = regex;
    return regex;
}

int main()
{
    std::string input;

    std::unordered_map<int, std::variant<std::vector<std::vector<int>>, std::string>> rules;

    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty()) { break; }

        std::vector<std::string> parts = split(input, ":");
        rules[std::stoi(parts[0])] = parseRules(parts[1]);
    }

    std::string r = "^" + getRegex(rules, 0) + "$";
    std::regex reg(r);

    int count = 0;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.eof()) { break; }

        if(std::regex_match(input, reg))
        {
            count++;
        }
    }

    std::cout << count;

    return 0;
}

