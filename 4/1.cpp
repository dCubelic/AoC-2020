#include <iostream>
#include <string>
#include <vector>
#include <regex>

const std::vector<std::string> list = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};


int countEntry(std::string entry)
{
    for(auto item: list)
    {
        if(entry.find(item) == std::string::npos) {
           return 0;
        }
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
