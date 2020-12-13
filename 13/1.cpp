#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

std::vector<int> split(std::string & s)
{
    std::vector<int> values;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(',')) != std::string::npos) {
        token = s.substr(0, pos);
        try
        {
            values.push_back(std::stoi(token));
        }
        catch(std::exception &e) { }
        s.erase(0, pos + 1);
    }
    try
    {
        values.push_back(std::stoi(token));
    }
    catch(std::exception &e) { }

    return values;
}

int main()
{
    int t;
    std::string input;
    scanf("%d\n", &t);
    std::getline(std::cin, input);
    std::vector<int> values = split(input);

    int min = values[0] - t % values[0];
    int argmin = 0;
    for(auto v: values)
    {
        if(v - t % v < min)
        {
            min = v - t % v;
            argmin = v;
        }
    }

    std::cout << min*argmin;

    return 0;
}
