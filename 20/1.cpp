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

    long long factor = 1;
    for(auto const & kv: m)
    {
        if(kv.second == 2)
        {
            factor *= kv.first;
        }
    }

    std::cout << factor;

    return 0;
}
