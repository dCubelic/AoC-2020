#include <cstdio>
#include <set>

int main()
{
  std::set<int> a;

  while(true)
  {
    int n;
    scanf("%d", &n);
    if(a.find(n) != a.end())
    {
      printf("%d * %d = %d", n, (2020 - n), n * (2020 - n));
      break;
    }
    a.insert(2020-n);
  }

  return 0;
}

