#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <algorithm>
#include <string>
#include <memory.h>
using namespace std;

class BigInt
{
    public:
        BigInt();
        BigInt(string num);
         ~BigInt();

        void setValue(string num);
        string getValue();
        //string getRemainder();

        BigInt add(BigInt num);
        BigInt minus(BigInt num);
        BigInt multi(BigInt num);
        BigInt divide(BigInt num);
        BigInt mod(BigInt num);

        //BigInt modPow(BigInt exponent, BigInt num);//Only for positive integer
    protected:

    private:
        string value;
        int compare(string op1, string op2);//Only for positive integer
        //string remainder;
};

#endif // BIGINT_H
