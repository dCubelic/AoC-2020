#include <iostream>
#include <string>
#include <vector>

using Map = std::vector<std::vector<std::vector<std::vector<char>>>>;

Map initMap(int n)
{
    Map map;

    for(int i = 0; i < n; ++i)
    {
        map.push_back({});
        for(int j = 0; j < n; ++j)
        {
            map[i].push_back({});
            for(int k = 0; k < n; ++k)
            {
                map[i][j].push_back({});
                for(int l = 0; l < n; ++l)
                {
                    map[i][j][k].push_back('.');
                }
            }
        }
    }
    return map;
}

std::vector<std::tuple<int, int, int, int>> getDeltas()
{
    std::vector<std::tuple<int, int, int, int>> deltas;
    for(int i = -1; i < 2; ++i)
    {
        for(int j = -1; j < 2; ++j)
        {
            for(int k = -1; k < 2; ++k)
            {
                for(int l = -1; l < 2; ++l)
                {
                    if(i == 0 && j == 0 && k == 0 && l == 0) continue;
                    deltas.emplace_back(i, j, k, l);
                }
            }
        }
    }
    return deltas;
}

int countActiveNeighbours(Map const & m, int i, int j, int k, int l, int max)
{
    int count = 0;

    for(auto t: getDeltas())
    {
        int x = std::get<0>(t);
        int y = std::get<1>(t);
        int z = std::get<2>(t);
        int w = std::get<3>(t);

        if(i+w >= 0 && i+w < max && j+z >= 0 && j+z < max && k+y >= 0 && k+y < max && l+x >= 0 && l+x < max && m[i+w][j+z][k+y][l+x] == '#') { count++; }
    }

    return count;
}

int countActive(Map const & map, int max)
{
    int count = 0;
    for(int i = 0; i < max; ++i)
    {
       for(int j = 0; j < max; ++j)
       {
           for(int k = 0; k < max; ++k)
           {
               for(int l = 0; l < max; ++l)
               {
                   if(map[i][j][k][l] == '#') count++;
               }
           }
       }
    }
    return count;
}

int main()
{
    int d = 6;
    int size = 8;

    std::string input;
    Map map = initMap(d*2 + size);

    int row = d;
    while(true)
    {
        std::getline(std::cin, input);

        for(int i = 0; i < (int) input.size(); ++i)
        {
            map[d][d][row][i+d] = input[i];
        }

        row++;
        if(std::cin.eof()) { break; }
    }

    for(int it = 0; it < d; ++it)
    {
        Map newMap = map;
        for(int i = 0; i < d*2 + size; ++i)
        {
            for(int j = 0; j < d*2 + size; ++j)
            {
                for(int k = 0; k < d*2 + size; ++k)
                {
                    for(int l = 0; l < d*2 + size; ++l)
                    {
                        int c = countActiveNeighbours(map, i, j, k, l, d*2 + size);
                        if(map[i][j][k][l] == '#' && (c == 2 || c == 3))
                        {
                            newMap[i][j][k][l] = '#';
                        }
                        else if(map[i][j][k][l] == '.' && c == 3)
                        {
                            newMap[i][j][k][l] = '#';
                        }
                        else
                        {
                            newMap[i][j][k][l] = '.';
                        }
                    }
                }
            }
        }
        map = newMap;
    }

    std::cout << countActive(map, d*2+size);
}
