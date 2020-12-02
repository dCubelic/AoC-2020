#include <cstdio>
#include <iostream>
#include <regex>
#include <string>

std::tuple<int, int, std::string, std::string> parse_input(std::string const & input)
{
    std::regex regex("^(.*)-(.*) ([a-z]): (.*)$");
    std::smatch m;
    std::regex_match(input, m ,regex);
    std::cout << m[1] << " " << m[2] << " " << m[3] << " " << m[4] << std::endl;
    return {std::stoi(m[1]), std::stoi(m[2]), m[3], m[4]};
}

int main()
{
    std::string input;
    int invalid = 0;
    int total = 0;
    while(std::cin)
    {
        std::getline(std::cin, input);
        if(input.empty()) break;
        total++;
        auto [min, max, c, str] = parse_input(input);
        int count = 0;
        for(auto ch: str)
        {
            if(ch == c[0])
            {
                if(++count > max)
                {
                    invalid++;
                    break;
                }
            }
        }
        if(count < min) invalid++;
    }
    printf("%d", total-invalid);

}
