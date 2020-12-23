#include <vector>
#include <iostream>
#include <string>

void print(std::vector<int> & l)
{
    for(auto n: l)
    {
        std::cout << n << " ";
    }
    std::cout << '\n';
}

void doMove(std::vector<int> & l, int curCup)
{
    int sp = std::find(std::begin(l), std::end(l), curCup) - std::begin(l);
    std::vector<int> e;
    for(int i = 0; i < 3; ++i)
    {
        if(sp + 1 >= (int) l.size())
        {
            sp = -1;
        }
        e.push_back(l[sp+1]);
        l.erase(l.begin() + sp + 1);
    }

    auto val = curCup-1;
    while(std::find(std::begin(l), std::end(l), val) == l.end())
    {
        val--;
        if(val < 1)
        {
            val = 9;
        }
    }

    auto index = std::find(std::begin(l), std::end(l), val) - std::begin(l);

    for(int i = 0; i < 3; ++i)
    {
        l.insert(std::begin(l)+index+1, e[2-i]);
    }

}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    std::vector<int> l;
    for(auto c: input)
    {
       l.push_back(c - '0');
    }

    auto curCup = l[0];
    for(int i = 0; i < 100; ++i)
    {
        doMove(l, curCup);
        auto curCupIndex = std::find(std::begin(l), std::end(l), curCup) + 1;
        if(curCupIndex >= std::end(l))
        {
            curCupIndex = std::begin(l);
        }
        curCup = *curCupIndex;
    }

    auto index = std::find(std::begin(l), std::end(l), 1) - std::begin(l) + 1;
    for(int i = 0; i < l.size() - 1; ++i)
    {
        std::cout << l[(index+i) % l.size()];
    }

    return 0;
}
