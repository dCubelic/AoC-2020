#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>

int main()
{
    const int d = 25;
    int a;
    std::vector<int> inputs;
    int p = 0;
    std::multiset<int> lastSums;
    while(int r = scanf("%d", &a))
    {
        inputs.push_back(a);
        if(inputs.size() == d)
        {
            for(int i = 0; i < (int) inputs.size(); ++i)
            {
                for(int j = 0; j < (int) inputs.size(); ++j)
                {
                    if(i == j) { continue; }
                    lastSums.insert(inputs[i] + inputs[j]);
                }
            }
        }
        else if(inputs.size() > d)
        {
            if(lastSums.count(a) == 0) { break; }
            for(int i = p+1; i < p + d; ++i)
            {
                auto itr = lastSums.find(inputs[p] + inputs[i]);
                if(itr != lastSums.end()){
                    lastSums.erase(itr);
                }
            }
            p++;
            for(int i = p; i < p + d - 1; ++i)
            {
                lastSums.insert(a+inputs[i]);
            }
        }
    }

    std::cout << a << '\n';
    std::queue<int> q;
    int qSum = 0;
    for(int & input : inputs)
    {
        while(qSum + input > a)
        {
            qSum -= q.front();
            if(!q.empty())
            {
                q.pop();
            }
        }
        if(qSum + input < a)
        {
            q.push(input);
            qSum += input;
        }
        else if(qSum + input == a)
        {
            q.push(input);
            break;
        }
    }

    int min = 99999999;
    int max = 0;
    while(!q.empty())
    {
       if(q.front() < min)
       {
           min = q.front();
       }
       if(q.front() > max)
       {
           max = q.front();
       }
       q.pop();
    }

    std::cout << min + max;

    return 0;
}
