#include <iostream>
#include <string>
#include <set>

int main()
{
    std::string input;
    std::set<char> s;
    int sum = 0;
    while(true)
    {
        std::getline(std::cin, input);
        if(input.empty())
        {
            sum += s.size();
            s.clear();
            if(std::cin.eof()) break;
        }
        else
        {
            for(auto c: input)
            {
                s.insert(c);
            }
        }
    }

    std::cout << sum;

    return 0;
}
