#include <cstdio>
#include <iostream>
#include <regex>
#include <string>

std::tuple<int, int, std::string, std::string> parse_input(std::string const & input)
{
    std::regex regex("^(.*)-(.*) ([a-z]): (.*)$");
    std::smatch m;
    std::regex_match(input, m ,regex);
    return {std::stoi(m[1]), std::stoi(m[2]), m[3], m[4]};
}

int main()
{
    std::string input;
    //int invalid = 0;
    int total = 0;
    int valid = 0;
    while(std::cin)
    {
        std::getline(std::cin, input);
        if(input.empty()) break;
        total++;
        auto [min, max, c, str] = parse_input(input);
        if(str[min-1] == c[0] && str[max-1] != c[0]) valid++;
        else if(str[min-1] != c[0] && str[max-1] == c[0]) valid++;
        else
        {
            std::cout << min << " " << max << " " << c << " " << str << std::endl;
        }
    }
    printf("%d", valid);

}
