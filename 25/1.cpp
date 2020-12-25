#include <iostream>
#include <cstdio>

int loopSize(int subjectNumber, int publicKey)
{
    long long n = 1;
    int loopSize = 0;
    while(n != publicKey)
    {
        n = n * subjectNumber % 20201227;
        loopSize++;
    }

    return loopSize;
}

long long encKey(int loopSize, int subjectNumber)
{
   long long n = 1;
   for(int i = 0; i < loopSize; ++i)
   {
       n = n * subjectNumber % 20201227;
   }
   return n;
}

int main()
{
    int a;
    int b;
    scanf("%d\n%d", &a, &b);

    std::cout << encKey(loopSize(7, a), b);

    return 0;
}
