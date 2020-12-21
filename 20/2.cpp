#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

using Tile = std::vector<std::string>;

Tile rotate(Tile const & tile)
{
    Tile newTile;

    for(int i = 0; i < (int) tile.size(); ++i)
    {
        newTile.push_back(std::string(tile[i].size(), '.'));
        for(int j = 0; j < (int) tile[i].size(); ++j)
        {
            newTile[i][j] = tile[tile.size() - 1 - j][i];
        }
    }

    return newTile;
}

Tile flipH(Tile const & tile)
{
    Tile newTile;

    for(int i = 0; i < (int) tile.size(); ++i)
    {
        newTile.push_back(std::string(tile[i].size(), '.'));
        for(int j = 0; j < (int) tile[i].size(); ++j)
        {
            newTile[i][j] = tile[i][tile[i].size()-1-j];
        }
    }

    return newTile;
}

Tile flipV(Tile const & tile)
{
    Tile newTile;

    for(int i = 0; i < (int) tile.size(); ++i)
    {
        newTile.push_back(std::string(tile[i].size(), '.'));
        for(int j = 0; j < (int) tile[i].size(); ++j)
        {
            newTile[i][j] = tile[tile.size()-1-i][j];
        }
    }

    return newTile;
}

std::string getRow(Tile const & tile, int row)
{
    return tile[row];
}

std::string getColumn(Tile const & tile, int column)
{
    std::string c;

    for(auto const & row: tile)
    {
        c += row[column];
    }

    return c;
}

void print(Tile const & tile)
{
    for(const auto & i : tile)
    {
        std::cout << i << '\n';
    }
    std::cout << '\n';
}

std::set<std::string> getEdges(Tile const & tile)
{
    std::set<std::string> edges;

    std::string row0 = getRow(tile, 0);
    std::string row9 = getRow(tile, 9);
    std::string column0 = getColumn(tile, 0);
    std::string column9 = getColumn(tile, 9);

    edges.insert(row0);
    std::reverse(row0.begin(), row0.end());
    edges.insert(row0);
    edges.insert(row9);
    std::reverse(row9.begin(), row9.end());
    edges.insert(row9);
    edges.insert(column0);
    std::reverse(column0.begin(), column0.end());
    edges.insert(column0);
    edges.insert(column9);
    std::reverse(column9.begin(), column9.end());
    edges.insert(column9);

    return edges;
}

bool canMatch(Tile const & tile1, Tile const & tile2)
{
    auto edges1 = getEdges(tile1);
    auto edges1fh = getEdges(flipH(tile1));
    auto edges1fv = getEdges(flipV(tile1));
    edges1.insert(edges1fh.begin(), edges1fh.end());
    edges1.insert(edges1fv.begin(), edges1fv.end());
    auto edges2 = getEdges(tile2);
    auto edges2fh = getEdges(flipH(tile2));
    auto edges2fv = getEdges(flipV(tile2));
    edges2.insert(edges2fh.begin(), edges2fh.end());
    edges2.insert(edges2fv.begin(), edges2fv.end());

    std::set<std::string> intersection;
    std::set_intersection(edges1.begin(), edges1.end(), edges2.begin(), edges2.end(), std::inserter(intersection, intersection.begin()));

    return !intersection.empty();
}

bool canMatchRight(Tile const & tile1, Tile const & tile2)
{
    std::set<std::string> edges1;
    edges1.insert(getColumn(tile1, 9));
    auto edges2 = getEdges(tile2);
    auto edges2fh = getEdges(flipH(tile2));
    auto edges2fv = getEdges(flipV(tile2));
    edges2.insert(edges2fh.begin(), edges2fh.end());
    edges2.insert(edges2fv.begin(), edges2fv.end());

    std::set<std::string> intersection;
    std::set_intersection(edges1.begin(), edges1.end(), edges2.begin(), edges2.end(), std::inserter(intersection, intersection.begin()));

    return !intersection.empty();
}

bool canMatchBottom(Tile const & tile1, Tile const & tile2)
{
    std::set<std::string> edges1;
    edges1.insert(getRow(tile1, 9));
    auto edges2 = getEdges(tile2);
    auto edges2fh = getEdges(flipH(tile2));
    auto edges2fv = getEdges(flipV(tile2));
    edges2.insert(edges2fh.begin(), edges2fh.end());
    edges2.insert(edges2fv.begin(), edges2fv.end());

    std::set<std::string> intersection;
    std::set_intersection(edges1.begin(), edges1.end(), edges2.begin(), edges2.end(), std::inserter(intersection, intersection.begin()));

    return !intersection.empty();
}

Tile matchRight(Tile const & tile1, Tile const & tile2)
{
    Tile tile = tile2;
    for(int i = 0; i < 4; ++i)
    {
        if(getColumn(tile1, 9) == getColumn(tile, 0)) { return tile; }
        tile = rotate(tile);
    }

    tile = flipH(tile2);
    for(int i = 0; i < 4; ++i)
    {
        if(getColumn(tile1, 9) == getColumn(tile, 0)) { return tile; }
        tile = rotate(tile);
    }

    tile = flipV(tile2);
    for(int i = 0; i < 4; ++i)
    {
        if(getColumn(tile1, 9) == getColumn(tile, 0)) { return tile; }
        tile = rotate(tile);
    }

    tile = flipV(tile2);
    tile = flipH(tile);
    for(int i = 0; i < 4; ++i)
    {
        if(getColumn(tile1, 9) == getColumn(tile, 0)) { return tile; }
        tile = rotate(tile);
    }
}

Tile matchBottom(Tile const & tile1, Tile const & tile2)
{
    Tile tile = tile2;
    for(int i = 0; i < 4; ++i)
    {
        if(getRow(tile1, 9) == getRow(tile, 0)) { return tile; }
        tile = rotate(tile);
    }

    tile = flipH(tile2);
    for(int i = 0; i < 4; ++i)
    {
        if(getRow(tile1, 9) == getRow(tile, 0)) { return tile; }
        tile = rotate(tile);
    }
    tile = flipV(tile2);
    for(int i = 0; i < 4; ++i)
    {
        if(getRow(tile1, 9) == getRow(tile, 0)) { return tile; }
        tile = rotate(tile);
    }

    tile = flipV(tile2);
    tile = flipH(tile);
    for(int i = 0; i < 4; ++i)
    {
        if(getRow(tile1, 9) == getRow(tile, 0)) { return tile; }
        tile = rotate(tile);
    }
}

std::pair<int, Tile> tileForIndex(int index, std::vector<std::pair<int, Tile>> const & tiles)
{
    return *std::find_if(tiles.begin(), tiles.end(), [index](auto &x){ return x.first == index; });
}

int countMonsters(Tile const & tile)
{
    int count = 0;
    for(int i = 0; i < (int) tile.size() - 3; ++i)
    {
        for(int j = 0; j < (int) tile[i].size() - 20; ++j)
        {
            if(tile[i][j+18] == '#' && tile[i+1][j] == '#' && tile[i+1][j+5] == '#' && tile[i+1][j+6] == '#' && tile[i+1][j+11] == '#' && tile[i+1][j+12] == '#' && tile[i+1][j+17] == '#' && tile[i+1][j+18] == '#' && tile[i+1][j+19] == '#' && tile[i+2][j+1] == '#' && tile[i+2][j+4] == '#' && tile[i+2][j+7] == '#' && tile[i+2][j+10] == '#' && tile[i+2][j+13] == '#' && tile[i+2][j+16] == '#')
            {
                count++;
}
        }
    }
    return count;
}

int main()
{
    std::vector<std::pair<int, Tile>> tiles;
    char input[11];
    int a;
    while(true)
    {
        if(int r = scanf("Tile %d:", &a) <= 0) { break; }
        std::vector<std::string> tile;
        for(int i = 0; i < 10; ++i)
        {
            scanf("%s\n", input);
            tile.emplace_back(input);
        }
        tiles.emplace_back(a, tile);

        scanf("\n");
    }

    std::map<int, int> m;

    for(int i = 0; i < (int) tiles.size(); ++i)
    {
       Tile tile = tiles[i].second;
       for(int j = i+1; j < (int) tiles.size(); ++j)
       {
           if(i == j) continue;
           Tile tile2 = tiles[j].second;

           if(canMatch(tile, tile2))
           {
               m[tiles[i].first]++;
               m[tiles[j].first]++;
           }
       }
    }

    std::pair<int, Tile> firstTile;
    for(auto const & kv: m)
    {
        if(kv.second == 2)
        {
            firstTile = tileForIndex(kv.first, tiles);
            break;
        }
    }

    tiles.erase(std::remove(tiles.begin(), tiles.end(), firstTile), tiles.end());

    std::vector<std::vector<Tile>> map;
    auto lastTile = firstTile;
    lastTile.second = rotate(rotate(lastTile.second));
    for(int i = 0; i < 12; ++i)
    {
        std::vector<Tile> row;
        row.push_back(lastTile.second);
        for(int j = 1; j < 12; ++j)
        {
           for(auto const & t: tiles)
           {
                if(canMatchRight(lastTile.second, t.second))
                {
                    auto matchedTile = matchRight(lastTile.second, t.second);
                    row.push_back(matchedTile);
                    lastTile = t;
                    lastTile.second = matchedTile;
                    tiles.erase(std::remove(tiles.begin(), tiles.end(), t), tiles.end());
                    break;
                }
           }
        }
        map.push_back(row);

        if(i < 11)
        {
            for(auto const & t: tiles)
            {
                if(canMatchBottom(row[0], t.second))
                {
                    auto matchedTile = matchBottom(row[0], t.second);
                    lastTile = t;
                    lastTile.second = matchedTile;
                    tiles.erase(std::remove(tiles.begin(), tiles.end(), t), tiles.end());
                    break;
                }
            }
        }
    }

    std::vector<std::string> strmap;

    for(int i = 0; i < (int) map.size(); ++i)
    {
        for(int j = 1; j < 9; ++j)
        {
            std::string strrow;
            for(int k = 0; k < (int) map[i].size(); ++k)
            {
               strrow += map[i][k][j].substr(1, 8);
            }
            strmap.push_back(strrow);
        }
    }

    int count = 0;
    for(int i = 0; i < strmap.size(); ++i)
    {
        for(int j = 0; j < strmap[i].size(); ++j)
        {
            if(strmap[i][j] == '#')
            {
                count++;
            }
        }
    }

    while(countMonsters(strmap) == 0)
    {
        strmap = rotate(strmap);
    }

    std::cout << count - 15*countMonsters(strmap);

    return 0;
}
