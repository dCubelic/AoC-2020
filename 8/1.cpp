#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <string>

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

    int acc = 0;
    for(int i = 0; i < (int) instrs.size(); ++i)
    {
        if(visited.count(i) == 1) { break; }
        visited.insert(i);
        if(instrs[i].first == "acc")
        {
           acc += instrs[i].second;
        }
        else if(instrs[i].first == "jmp")
        {
            i += instrs[i].second - 1;
        }
    }

    std::cout << acc;

    return 0;
}
