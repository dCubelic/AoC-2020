#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <string>

bool infiniteLoop(std::vector<std::pair<std::string, int>> const & instrs, int index)
{
    std::set<int> visited;
    for(int i = 0; i < (int) instrs.size(); ++i)
    {
        if(visited.count(i) == 1) { return true; }
        visited.insert(i);
        if(i == index && instrs[i].first == "jmp") { continue; }
        if((i == index && instrs[i].first == "nop") || (instrs[i].first == "jmp"))
        {
            i += instrs[i].second - 1;
        }
    }

    return false;
}

int run(std::vector<std::pair<std::string, int>> const & instrs)
{
    int acc = 0;
    for(int i = 0; i < (int) instrs.size(); ++i)
    {
        if(instrs[i].first == "acc")
        {
           acc += instrs[i].second;
        }
        else if(instrs[i].first == "jmp")
        {
            i += instrs[i].second - 1;
        }
    }

    return acc;
}

int main()
{
    char ins[10];
    std::string instruction;
    int value;

    std::set<int> visited;
    std::vector<std::pair<std::string, int>> instrs;

    while(int r = scanf("%s %d", ins, &value) > 0)
    {
        instruction = ins;
        instrs.emplace_back(instruction, value);
    }

    for(int i = 0; i < (int) instrs.size(); ++i)
    {
        if(!infiniteLoop(instrs, i))
        {
            instrs[i].first = instrs[i].first == "jmp" ? "nop" : "jmp";
            std::cout << run(instrs);
            break;
        }
    }

    return 0;
}
