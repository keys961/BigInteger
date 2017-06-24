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

        //Operations without changing neither operands
        BigInt add(BigInt num);
        BigInt minus(BigInt num);
        BigInt multi(BigInt num);
        BigInt divide(BigInt num);


        BigInt mod(BigInt num);//Just handle 2 positive

        //Only for positive integer
        //return this^exponent mod num
        BigInt modPow(BigInt exponent, BigInt num);

    protected:

    private:
        string value;
        int compare(string op1, string op2);//Only for positive integer
        bool isOdd();

};

#endif // BIGINT_H
