#include <iostream>
#include <cstdio>
#include <string>
#include <queue>

int main()
{
    std::queue<int> p1;
    std::queue<int> p2;
    std::string input;
    std::getline(std::cin, input);
    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty()) { break; }

        p1.push(std::stoi(input));
    }

    std::getline(std::cin, input);
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.eof()) { break; }

        p2.push(std::stoi(input));
    }

    while(!p1.empty() && !p2.empty())
    {
        auto c1 = p1.front();
        p1.pop();
        auto c2 = p2.front();
        p2.pop();

        if(c1 > c2)
        {
            p1.push(c1);
            p1.push(c2);
        }
        else
        {
            p2.push(c2);
            p2.push(c1);
        }
    }

    unsigned long sum = 0;
    while(!p1.empty())
    {
        sum += p1.size() * p1.front();
        p1.pop();
    }
    while(!p2.empty())
    {
        sum += p2.size() * p2.front();
        p2.pop();
    }

    std::cout << sum;

    return 0;
}
