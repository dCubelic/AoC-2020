#include <iostream>
#include <string>
#include <vector>
#include <regex>

const std::vector<std::string> list = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

bool checkRange(std::string e, int lower, int upper)
{
    return std::stoi(e) >= lower && std::stoi(e) <= upper;
}

bool checkRegex(std::string e, std::string r)
{
    return std::regex_match(e, std::regex(r));
}

int countEntry(std::string entry)
{
    for(auto item: list)
    {
        if(entry.find(item) == std::string::npos) {
           return 0;
        }

        std::regex regex(".*" + item + ":(.*?) .*$");
        std::smatch m;
        std::regex_match(entry, m, regex);

        if(item == "byr") if(!checkRange(m[1], 1920, 2002)) return 0;
        if(item == "iyr") if(!checkRange(m[1], 2010, 2020)) return 0;
        if(item == "eyr") if(!checkRange(m[1], 2020, 2030)) return 0;
        if(item == "hgt") if(!checkRegex(m[1], "(1[5-8][0-9]cm|19[0-3]cm|59in|6[0-9]in|7[0-6]in)")) return 0;
        if(item == "hcl") if(!checkRegex(m[1], "#[0-9a-f]{6}")) return 0;
        if(item == "ecl") if(!checkRegex(m[1], "(amb|blu|brn|gry|grn|hzl|oth)")) return 0;
        if(item == "pid") if(!checkRegex(m[1], "[0-9]{9}")) return 0;
    }

    return 1;
}

int main()
{
    std::string entry;
    std::string input;
    int count = 0;

    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty())
        {
            count += countEntry(entry);
            entry = "";
            if(std::cin.eof()) break;
        }
        else
        {
            entry += " " + input + " ";
        }
    }

    std::cout << count;

    return 0;
}
