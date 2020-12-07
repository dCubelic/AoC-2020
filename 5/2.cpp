#include <iostream>
#include <cstdio>
#include <string>
#include <set>

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
   std::set<int> s;
   for(int i = 0; i < 1024; ++i)
   {
      s.insert(i);
   }
   while(true)
   {
       std::string input;
       std::getline(std::cin, input);
       if(std::cin.eof()) break;
       int id = calculateSeatID(input);
       s.erase(id);
       if(id > maxID) maxID = id;
   }
   for(int a: s)
   {
       if(s.find(a+1) == s.end() && s.find(a-1) == s.end())
       {
            std::cout << a;
            break;
       }
   }
   return 0;
}
