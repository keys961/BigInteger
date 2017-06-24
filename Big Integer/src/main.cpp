#include <iostream>
#include "BigInt.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("output.txt");
    string numA, numB;
    cout << "Please input number A:" ;
    cin >> numA;
    cout << "Please input number B:";
    cin >> numB;

    BigInt A(numA), B(numB);

    out << "A = " << numA << endl;
    cout << "A = " << numA << endl;

    out << "B = " << numB << endl;
    cout << "B = " << numB << endl;

    out << "A + B = " << A.add(B).getValue() << endl;
    cout << "A + B = " << A.add(B).getValue() << endl;

    out << "A - B = " << A.minus(B).getValue() << endl;
    cout << "A - B = " << A.minus(B).getValue() << endl;

    out << "A * B = " << A.multi(B).getValue() << endl;
    cout << "A * B = " << A.multi(B).getValue() << endl;

    out << "A / B = " << A.divide(B).getValue() << endl;
    cout << "A / B = " << A.divide(B).getValue() << endl;

    out << "A % B = " << A.mod(B).getValue() << endl;
    cout << "A % B = " << A.mod(B).getValue() << endl;

    return 0;
}
