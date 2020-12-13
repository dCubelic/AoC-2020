#include <cstdio>
#include <iostream>
#include <vector>

int wew = 10;
int wns = 1;
int ew = 0;
int ns = 0;

void move(int v)
{
    ew += v * wew;
    ns += v * wns;
}

void moveWaypoint(char d, int v)
{
    if(d == 'N')
    {
        wns += v;
    }
    else if(d== 'S')
    {
        wns -= v;
    }
    else if(d == 'E')
    {
        wew += v;
    }
    else if(d == 'W')
    {
        wew -= v;
    }
}

void rotate(char d, int v)
{
    if(d == 'R')
    {
        while(v > 0)
        {
            int newwns = -wew;
            int newwew = wns;
            wew = newwew;
            wns = newwns;
            v -= 90;
        }
    }
    else if(d == 'L')
    {
        rotate('R', 360 - v);
    }
}

int main()
{
    char c;
    int v;
    while(int r = scanf("%c%d ", &c, &v) > 0)
    {
       if(c == 'E' || c == 'W' || c == 'N' || c == 'S')
       {
           moveWaypoint(c, v);
       }
       else if(c == 'R' || c == 'L')
       {
          rotate(c, v);
       }
       else if(c == 'F')
       {
           move(v);
       }
    }

    std::cout << std::abs(ew) + std::abs(ns);

    return 0;
}

