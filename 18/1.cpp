#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cctype>

long long parseMathExpr(std::string const & s)
{
    std::queue<std::string> q;
    std::stack<std::string> st;

    std::string num;
    for(int i = 0; i < (int) s.size(); ++i)
    {
       auto c = s[i];
       if(c == ' ')
       {
           if(!num.empty())
           {
               q.push(num);
               num = "";
           }
           continue;
       }

       if(isdigit(c) != 0)
       {
           num += c;
           if(i == (int) s.size() - 1)
           {
               q.push(num);
               num = "";
           }
       }
       else {
           if(!num.empty())
           {
               q.push(num);
               num = "";
           }

           if(c == '(')
           {
               st.push("(");
           }
           else if(c == ')')
           {
               while(!st.empty() && st.top() != "(")
               {
                   q.push(st.top());
                   st.pop();
               }
               st.pop();
           }
           else // operator
           {
               while(!st.empty() && (st.top() == "+" || st.top() == "*"))
               {
                   q.push(st.top());
                   st.pop();
               }
               std::string str(1, c);
               st.push(str);
           }
       }
    }

    while(!st.empty())
    {
        q.push(st.top());
        st.pop();
    }

    while(!q.empty())
    {
        std::string t = q.front();
        q.pop();
        if(!(t == "+" || t == "*" || t == "(" || t == ")"))
        {
            st.push(t);
        }
        else if(t == "+" || t == "*")
        {
            long long first = std::stoll(st.top());
            st.pop();
            long long second = std::stoll(st.top());
            st.pop();

            long long res = t == "+" ? first + second : first * second;

            st.push(std::to_string(res));
        }
    }

    return std::stoll(st.top());
}

int main()
{
    std::string input;

    long long sum = 0;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.eof()) { break; }

        sum += parseMathExpr(input);
    }

    std::cout << sum;

    return 0;
}
