#include <iostream>
#include <cstdio>
#include <string>

int calculateSeatID(std::string s)
{
    int lower = 0;
    int upper = 127;
    int row = 0;
    for(int i = 0; i < 7; ++i)
    {
        if(s[i] == 'F')
        {
            upper -= (upper - lower + 1) / 2;
        }
        else {
            lower += (upper - lower + 1) / 2;
        }
    }
    row = lower;
    lower = 0;
    upper = 7;
    int column = 0;
    for(int i = 7; i < 10; ++i)
    {
        if(s[i] == 'L')
        {
            upper -= (upper - lower + 1) / 2;
        }
        else
        {
            lower += (upper - lower + 1) / 2;
        }
    }
    column = lower;
    return row * 8 + column;
}

int main()
{
   int maxID = 0;

   while(true)
   {
       std::string input;
       std::getline(std::cin, input);
       if(std::cin.eof()) break;
       int id = calculateSeatID(input);
       if(id > maxID) maxID = id;

   }
   std::cout << maxID;
   return 0;
}
