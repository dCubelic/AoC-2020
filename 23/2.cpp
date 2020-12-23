#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <set>

struct Node
{
    int val;
    Node *next;
    explicit Node(int val)
        : val(val), next(nullptr) { }
};

std::map<int, Node*> m;

int main()
{
    std::string input;
    std::getline(std::cin, input);

    Node *head = new Node(input[0] - '0');
    m[input[0] - '0'] = head;
    Node *last = head;
    for(auto i = 1U; i < input.size(); ++i)
    {
        Node *n = new Node(input[i] - '0');
        m[input[i] - '0'] = n;
        last->next = n;
        last = n;
    }

    int n = 10;
    while(n <= 1000000)
    {
        Node *node = new Node(n);
        m[n] = node;
        last->next = node;
        last = node;
        n++;
    }
    last->next = head;

    Node *cur = head;
    std::set<int> removed;
    for(int i = 0; i < 10000000; ++i)
    {
        Node *fot = cur->next;
        Node *lot = fot->next->next;
        removed.clear();
        removed.insert(fot->val);
        removed.insert(fot->next->val);
        removed.insert(lot->val);
        auto val = cur->val-1;
        while(removed.find(val) != removed.end())
        {
           val--;
           if(val <= 0)
           {
               val = 1000000;
           }
        }
        if(val == 0) { val = 1000000; }
        cur->next = lot->next;
        Node *in = m[val];
        lot->next = in->next;
        in->next = fot;
        cur = cur->next;
    }

    std::cout << static_cast<unsigned long>(m[1]->next->val) * static_cast<unsigned long>(m[1]->next->next->val);

    return 0;
}
