#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

const std::vector<std::pair<int, int>> d = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

int countAdjacent(std::vector<std::string> const & seats, int oi, int oj, char x)
{
    int count = 0;
    int i;
    int j;
    for(auto p: d)
    {
        i = oi;
        j = oj;
        while(i+p.first >= 0 && i+p.first < (int) seats.size() && j+p.second >= 0 && j+p.second < (int) seats[0].size())
        {
            if(seats[i+p.first][j+p.second] == x)
            {
                count++;
            }
            if(seats[i+p.first][j+p.second] != '.') { break; }
            i += p.first;
            j += p.second;
        }
    }
    return count;
}

int performRound(std::vector<std::string> & seats)
{
    int count = 0;
    std::vector<std::string> newSeats = seats;

    for(int i = 0; i < (int) seats.size(); ++i)
    {
        std::string row = seats[i];
        for(int j = 0; j < (int) row.size(); ++j)
        {
            char seat = row[j];
            if(seat == 'L' && countAdjacent(seats, i, j, '#') == 0)
            {
                newSeats[i][j] = '#';
                count++;
            }
            else if(seat == '#' && countAdjacent(seats, i, j, '#') >= 5)
            {
                newSeats[i][j] = 'L';
                count++;
            }
            else
            {
                newSeats[i][j] = seat;
            }
        }
    }
    seats = newSeats;
    return count;
}

int countAllOcupied(std::vector<std::string> & seats)
{
    int count = 0;
    for(const auto& l: seats)
    {
        for(auto c: l)
        {
            if(c == '#') { count++; }
        }
    }
    return count;
}

void printSeats(std::vector<std::string> const & seats)
{
    for(auto row: seats)
    {
        std::cout << row << '\n';
    }
}

int main()
{
    std::string line;
    std::vector<std::string> seats;

    while(true)
    {
        std::getline(std::cin, line);
        seats.push_back(line);
        if(std::cin.eof()) { break; }
    }

    while(performRound(seats) > 0) {
    }

    std::cout << countAllOcupied(seats);

    return 0;
}
