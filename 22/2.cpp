#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <set>

unsigned long sum;

int playGame(std::queue<int> p1, std::queue<int> p2, int s1, int s2)
{
    std::set<std::pair<std::queue<int>, std::queue<int>>> s;
    std::queue<int> p1c;
    std::queue<int> p2c;
    for(int i = 0; i < s1; ++i)
    {
        p1c.push(p1.front());
        p1.pop();
    }
    for(int i = 0; i < s2; ++i)
    {
        p2c.push(p2.front());
        p2.pop();
    }

    while(!p1c.empty() && !p2c.empty())
    {
        if(s.find({p1c, p2c}) != s.end())
        {
            return 0;
        }
        s.insert({p1c, p2c});

        auto c1 = p1c.front();
        p1c.pop();
        auto c2 = p2c.front();
        p2c.pop();

        if((int) p1c.size() >= c1 && (int) p2c.size() >= c2)
        {
            int winner = playGame(p1c, p2c, c1, c2);
            if(winner == 0)
            {
                p1c.push(c1);
                p1c.push(c2);
            }
            else
            {
                p2c.push(c2);
                p2c.push(c1);
            }
        }
        else
        {
            if(c1 > c2)
            {
                p1c.push(c1);
                p1c.push(c2);
            }
            else
            {
                p2c.push(c2);
                p2c.push(c1);
            }
        }
    }

    sum = 0;
    int winner = p1c.empty() ? 1 : 0;
    while(!p1c.empty())
    {
        sum += p1c.size() * p1c.front();
        p1c.pop();
    }
    while(!p2c.empty())
    {
        sum += p2c.size() * p2c.front();
        p2c.pop();
    }

    return winner;
}

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

    playGame(p1, p2, p1.size(), p2.size());

    std::cout << sum;

    return 0;
}

