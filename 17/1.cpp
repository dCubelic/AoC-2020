#include <iostream>
#include <string>
#include <vector>

using Map = std::vector<std::vector<std::vector<char>>>;

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
                map[i][j].push_back('.');
            }
        }
    }
    return map;
}

const std::vector<std::tuple<int, int, int>> deltas = {{-1, -1, -1}, {-1, -1, 0}, {-1, -1, 1}, {-1, 0, -1}, {-1 ,0, 0}, {-1, 0, 1}, {-1, 1, -1}, {-1, 1, 0}, {-1, 1, 1}, {0, -1, -1}, {0, -1, 0}, {0, -1, 1}, {0, 0, -1}, {0, 0, 1}, {0, 1, -1}, {0, 1, 0}, {0, 1, 1}, {1, -1, -1}, {1, -1, 0}, {1, -1, 1}, {1, 0, -1}, {1, 0, 0}, {1, 0, 1}, {1, 1, -1}, {1, 1, 0}, {1, 1, 1}};

int countActiveNeighbours(Map const & m, int i, int j, int k, int max)
{
    int count = 0;

    for(auto t: deltas)
    {
        int x = std::get<0>(t);
        int y = std::get<1>(t);
        int z = std::get<2>(t);

        if(i+z >= 0 && i+z < max && j+y >= 0 && j+y < max && k+x >= 0 && k+x < max && m[i+z][j+y][k+x] == '#') { count++; }
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
               if(map[i][j][k] == '#') count++;
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
            map[d][row][i+d] = input[i];
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
                    int c = countActiveNeighbours(map, i, j, k, d*2 + size);
                    if(map[i][j][k] == '#' && (c == 2 || c == 3))
                    {
                        newMap[i][j][k] = '#';
                    }
                    else if(map[i][j][k] == '.' && c == 3)
                    {
                        newMap[i][j][k] = '#';
                    }
                    else
                    {
                        newMap[i][j][k] = '.';
                    }
                }
            }
        }
        map = newMap;
    }

    std::cout << countActive(map, d*2+size);
}
