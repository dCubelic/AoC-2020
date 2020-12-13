#include <cstdio>
#include <iostream>
#include <vector>

int ew = 0;
int ns = 0;
char direction = 'E';

std::vector<char> dirs = {'E', 'S', 'W', 'N'};

void moveInDirection(char d, int v)
{
   if(d == 'E')
   {
       ew += v;
   }
   else if(d == 'W')
   {
       ew -= v;
   }
   else if(d == 'N')
   {
       ns += v;
   }
   else if(d == 'S')
   {
       ns -= v;
   }
}

void rotate(char d, int v)
{
    int index = std::find(dirs.begin(), dirs.end(), direction) - dirs.begin();
    if(d == 'R')
    {
        index = (index + v/90) % 4;
    }
    else if(d == 'L')
    {
        index = (index + (360-v)/90) % 4;
    }
    direction = dirs[index];
}

int main()
{
    char c;
    int v;
    while(int r = scanf("%c%d ", &c, &v) > 0)
    {
       if(c == 'E' || c == 'W' || c == 'N' || c == 'S')
       {
           moveInDirection(c, v);
       }
       else if(c == 'R' || c == 'L')
       {
          rotate(c, v);
       }
       else if(c == 'F')
       {
           moveInDirection(direction, v);
       }
    }

    std::cout << std::abs(ew) + std::abs(ns);

    return 0;
}
