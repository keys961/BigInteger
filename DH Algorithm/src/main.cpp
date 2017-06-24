#include <fstream>
#include <iostream>
#include "BigInt.h"
#include <string>
#include <time.h>

using namespace std;

string generateKey(int i);

int main()
{
	/*BigInt a1("123456789098765432123456789909876544322131284737856189576458923465986243598642359827654985629856243798562895629387195623984632984761298462138946123984761298356");
	BigInt b1("12348912756914387659813475619837462398146538975613489576187953612489613258934765193845619384751832746982134692835631489576348957637894619328576918");

	cout << a1.add(b1).getValue() << endl;
	cout << a1.minus(b1).getValue() << endl;
	cout << a1.multi(b1).getValue() << endl;
	cout << a1.divide(b1).getValue() << endl;
	cout << a1.mod(b1).getValue() << endl;*/

	string primitiveRoot, prime;
	string privateKeya, privateKeyb;
	cout << "Input g(primitive root) and p(big prime):" << endl;
	cin >> primitiveRoot >> prime;
	/*cout << "Input private key a of UserA:" << endl;
	cin >> privateKeya;
	cout << "Input private key b of UserB:" << endl;
	cin >> privateKeyb;*/

	privateKeya = generateKey(0);
	_sleep((unsigned)1000);
	privateKeyb = generateKey(1);


	BigInt g(primitiveRoot), p(prime), a(privateKeya), b(privateKeyb);
	BigInt A, B, KA, KB; //Public key A, Public key B, Session key K

	cout << "Private key a: " << privateKeya << endl;
	cout << "Private key b: " << privateKeyb << endl;

	cout << "Generating public key A of userA..." << endl;
	A = g.modPow(a, p);
	cout << "A: " << A.getValue() << endl;

	cout << "Generating public key B of userB..." << endl;
	B = g.modPow(b, p);
	cout << "B: " << B.getValue() << endl;

	cout << "Generating session key K for userA..." << endl;
	KA = B.modPow(a, p);
	cout << "K: " << KA.getValue() << endl;

	cout << "Generating session key K for userB..." << endl;
	KB = A.modPow(b, p);
	cout << "K: " << KB.getValue() << endl;

	/*BigInt exponent("123456789098765432123456789909876544322131284737856189576458923465986243598642359827654985629856243798562895629387195623984632984761298462138946123984761298356");
	BigInt num("12348912756914387659813475619837462398146538975613489576187953612489613258934765193845619384751832746982134692835631489576348957637894619328576918");
	BigInt a("3");
	cout << exponent.add(num).getValue() << endl;
	cout << exponent.minus(num).getValue() << endl;
	cout << exponent.multi(num).getValue() << endl;
	cout << exponent.divide(num).getValue() << endl;
	cout << exponent.mod(num).getValue() << endl;
	cout << a.modPow(exponent, num).getValue() << endl;*/
	system("pause");

	ofstream out("output.txt");
	out << "p: " << p.getValue() << endl;
	out << "g: " << g.getValue() << endl;
	out << "Private key a: " << a.getValue() << endl;
	out << "Public key A: " << A.getValue() << endl;
	out << "Private key b: " << b.getValue() << endl;
	out << "Public key B: " << B.getValue() << endl;
	out << "Session key K of userA: " << KA.getValue() << endl;
	out << "Session key K of userB: " << KB.getValue() << endl;
	system("pause");
	return 0;
}

string generateKey(int i)
{ //Generate 100-digit key
	string key;
	srand((unsigned)time(NULL));
	if (i == 0)
		cout << "Generating private key a of UserA.." << endl;
	else
		cout << "Generating private key b of UserB.." << endl;
	char c = rand() % 9 + '1';
	key = key + c;

	for (int i = 0; i < 99; i++)
	{
		c = rand() % 10 + '0';
		key = key + c;
	}

	return key;
}
