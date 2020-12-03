#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> map;
    std::string str;
    while(std::cin)
    {
        std::getline(std::cin, str);
        map.push_back(str);
    }

    int x = 0;
    int y = 0;
    int count = 0;
    while(y < (int) map.size())
    {
        x = (x + 3) % map[0].size();
        y += 1;
       if (map[y][x] == '#')
       {
           count++;
       }
    }

    printf("%d", count);

    return 0;
}
