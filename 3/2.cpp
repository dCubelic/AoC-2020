#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

int countTrees(std::vector<std::string> map, int dx, int dy)
{
    int x = 0;
    int y = 0;
    int count = 0;
    while(y < (int) map.size())
    {
        x = (x + dx) % map[0].size();
        y += dy;
       if (map[y][x] == '#')
       {
           count++;
       }
    }
    return count;
}

int main()
{
    std::vector<std::string> map;
    std::string str;
    while(std::cin)
    {
        std::getline(std::cin, str);
        map.push_back(str);
    }

    std::vector<int> dx = {1, 3, 5, 7, 1};
    std::vector<int> dy = {1, 1, 1, 1, 2};
    unsigned long long count = 1;
    for(int i = 0; (int) i < dx.size(); ++i)
    {
        count *= countTrees(map, dx[i], dy[i]);
    }
    printf("%lld", count);

    return 0;
}
