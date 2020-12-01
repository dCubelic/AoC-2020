#include <cstdio>
#include <set>
#include <utility>
#include <vector>
#include <optional>

std::optional<std::pair<int, int>> numsThatSumTo(std::vector<int> const & nums, int sum)
{
  std::set<int> a;

  for(int n: nums)
  {
    if(a.find(n) != a.end())
    {
      return {{n, sum - n}};
    }
    a.insert(sum-n);
  }
  return {};
}

int main()
{
  std::vector<int> nums;
  int n;

  while(int r = scanf("%d", &n) > 0)
  {
    nums.push_back(n);
  }

  for(int n: nums)
  {
    if(auto pair = numsThatSumTo(nums, 2020 - n))
    {
     auto [a, b] = *pair;
     printf("%d * %d * %d = %d", n, a,b , n * a * b);
     break;
    }
  }
  return 0;
}

