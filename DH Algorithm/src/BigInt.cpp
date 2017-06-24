#include "BigInt.h"

const BigInt TWO("2");
const BigInt ONE("1");

BigInt::BigInt()
{
	this->value = "0";
	//this->remainder = "0";
}

BigInt::BigInt(string num)
{
	this->value = num;
	//this->remainder = "0";
}

BigInt::~BigInt()
{
	//dtor
}

bool BigInt::isOdd()
{
	int lastDigit = value[value.size() - 1] - '0';
	if (lastDigit % 2)
		return true;
	else
		return false;
}

int BigInt::compare(string op1, string op2)
{ //Compare 2 positive number
	while (op1.size() > 1 && op1[0] == '0')
		op1.erase(0, 1);
	while (op2.size() > 1 && op2[0] == '0')
		op2.erase(0, 1);
	int len1 = op1.size();
	int len2 = op2.size();
	if (len1 > len2)
		return 1;
	else if (len1 < len2)
		return -1;
	else
		return op1.compare(op2);
}

void BigInt::setValue(string num)
{
	this->value = num;
}

string BigInt::getValue()
{
	return this->value;
}

BigInt BigInt::add(BigInt num)
{
	string tempOperand;
	BigInt temp;

	string result;
	BigInt res; //Result

	int flag = 0;
	if (this->value[0] == '-' && num.getValue().at(0) != '-')
	{ //Op1 is negative while Op2 is positive
		tempOperand = this->getValue();
		tempOperand.erase(0, 1);
		temp.setValue(tempOperand);
		return num.minus(temp); //Return Op2 - Op1
	}
	else if (this->value[0] != '-' && num.getValue().at(0) == '-')
	{//Op2 is negative while Op1 is positive
		tempOperand = num.getValue();
		tempOperand.erase(0, 1);
		temp.setValue(tempOperand);
		return this->minus(temp);//Return Op1 - Op2
	}
	else if (this->value[0] == '-' && num.getValue().at(0) == '-')
		flag = 1; //Both negative, set flag
				  //Handle double positive/negative
	int ptrA = this->value.size() - 1;
	int ptrB = num.value.size() - 1;
	int sum = 0, carry = 0;
	while (ptrA >= 0 && this->getValue().at(ptrA) != '-'
		&& ptrB >= 0 && num.getValue().at(ptrB) != '-')//Perform ADD
	{ //From LSB to MSB digit by digit
		sum = this->getValue().at(ptrA) - '0' +
			num.getValue().at(ptrB) - '0' + carry;
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else
			carry = 0;

		result.insert(0, 1, sum + '0');
		ptrA--; ptrB--;
	}

	while (ptrA >= 0 && this->getValue().at(ptrA) != '-')
	{ //If A is longer
		sum = this->getValue().at(ptrA) - '0' + carry;
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else
			carry = 0;
		result.insert(0, 1, sum + '0');
		ptrA--;
	}

	while (ptrB >= 0 && num.getValue().at(ptrB) != '-')
	{ //If B is longer
		sum = num.getValue().at(ptrB) - '0' + carry;
		if (sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else
			carry = 0;
		result.insert(0, 1, sum + '0');
		ptrB--;
	}
	if (carry)
		result.insert(0, 1, '1');
	if (flag) //If it is negative, add -
		result.insert(0, 1, '-');
	res.setValue(result);
	return res;//Return result
}

BigInt BigInt::minus(BigInt num)
{
	BigInt res, tempOperand, tempOperand2;
	string result, op1, op2;
	int len1, len2, i;
	int comp = 0;
	int flag = 1; //1 all positive, -1 all negative

	op1 = this->getValue(); op2 = num.getValue();
	if (op1[0] == '-' && op2[0] != '-')
	{ //If op1 is negative, op1 + (-op2)
		op2.insert(0, 1, '-');
		tempOperand.setValue(op2);
		return this->add(tempOperand);
	}
	else if (op1[0] != '-' && op2[0] == '-')
	{ //If op2 is negative
		op2.erase(0, 1);
		tempOperand.setValue(op2);
		return this->add(tempOperand);
	}
	else if (op1[0] == '-' && op2[0] == '-')
		flag = -1;
	//Handle 2 positive/negative
	comp = compare(op1, op2);
	if (comp == 0) //Equal
		return res;

	if (flag == 1)//2 positive
	{

		if (comp < 0) //Op1 < Op2
		{
			tempOperand.setValue(op1);
			res = num.minus(op1);//Get oppo
			res.setValue(res.getValue().insert(0, 1, '-'));//Add '-'
			return res;
		}
		else //Op1 > Op2
		{
			reverse(op1.begin(), op1.end());//Reverse to calc easier
			reverse(op2.begin(), op2.end());

			len1 = op1.size(); len2 = op2.size();
			char* digits = (char*)malloc(sizeof(char) * (len1 + 1));//Store digits
			memset(digits, 0, sizeof(char) * (len1 + 1));
			for (i = 0; i < len1 && i < len2; i++)
			{//From LSB to MSB
				digits[i] = (int)( op1[i] - op2[i]);
				//result = result + c;
			}
			while (i < len1)//Len2 <= Len1
			{
				digits[i] = op1[i] - '0';
				i++;
			}

			//Calc carry
			int carry = 0;
			for (i = 0; i < len1; i++)
			{
				if (digits[i] + carry < 0)
				{
					digits[i] = digits[i] + 10 + carry + '0';
					carry = -1; //If digit < 0, borrow
				}
				else
				{
					digits[i] = digits[i] + carry + '0';
					carry = 0;
				}
			}
			//Get substring
			for (i = len1 - 1; i >= 0; i--)
				if (digits[i] != '0')
				{
					digits[i + 1] = 0;
					break;
				}
			//for (; i >= 0; i--)
				//result = result + (char)(digits[i] + 48);
			//reverse(result.begin(), result.end());//Get true result
			result = digits;
			reverse(result.begin(), result.end());
			res.setValue(result);
			delete[] digits;
			return res;
		}
	}
	else //2 negative
	{
		op1.erase(0, 1); op2.erase(0, 1);
		tempOperand.setValue(op1); tempOperand2.setValue(op2);
		res = tempOperand2.minus(tempOperand);//Convert to 2 positive
		return res;
	}

}

BigInt BigInt::multi(BigInt num)
{
	int i, j;
	string result;//Result string
	BigInt res, temp1, temp2;
	string op1 = this->getValue();//Operand1
	string op2 = num.getValue();//Operand2

	if(op1.compare("0") == 0 || op2.compare("0") == 0)
        return res;

	if (op1[0] == '-' && op2[0] == '-')
	{
		op1.erase(0, 1); op2.erase(0, 1);
	}
	else if ((op1[0] == '-' && op2[0] != '-') ||
		(op1[0] != '-' && op2[0] == '-'))
	{ //Result is negative
		if (op1[0] == '-')//Erase '-'
			op1.erase(0, 1);
		else
			op2.erase(0, 1);
		temp1.setValue(op1); temp2.setValue(op2);
		res = temp1.multi(temp2);
		res.setValue(res.getValue().insert(0, 1, '-'));//Add '-'
		return res;
	}
	reverse(op1.begin(), op1.end()); //Make it easier
	reverse(op2.begin(), op2.end());
	int len1 = op1.size(); int len2 = op2.size();
	//Store digits and clear to 0
	int* digits = (int*)malloc(sizeof(int)*(len1 + len2));
	memset(digits, 0, sizeof(int)*(len1 + len2));
	//Start calc, from lsb to msb
	for (i = 0; i < len1; i++)//From lsb to msb
		for (j = 0; j < len2; j++)
			digits[i + j] += (op1[i] - '0') * (op2[j] - '0');
	//calc carry
	int carry = 0, digit = 0;
	for (i = 0; i < len1 + len2; i++)
	{
		digit = digits[i] + carry;
		digits[i] = digit % 10;
		carry = digit / 10;
	}
	for (i = len1 + len2 - 1; i >= 0; i--)//From MSB
		if (digits[i])
			break;
	while (i >= 0)//from MSB to LSB
	{
		char c = (char)digits[i] + '0';
		result = result + c;
		i--;
	}
	delete[] digits;
	res.setValue(result);
	return res;
}

BigInt BigInt::divide(BigInt num)
{
	BigInt res, temp1, temp2;
	string result, op1, op2, tempstr;
	int len1, len2, i, lastPos;
	op1 = this->getValue(); op2 = num.getValue();
	if (op1[0] == '-' && op2[0] == '-')
	{
		op1.erase(0, 1); op2.erase(0, 1);
	}
	else if ((op1[0] == '-' && op2[0] != '-') ||
		(op1[0] != '-' && op2[0] == '-'))
	{ //Result is negative
		if (op1[0] == '-')//Erase '-'
			op1.erase(0, 1);
		else
			op2.erase(0, 1);
		temp1.setValue(op1); temp2.setValue(op2);
		res = temp1.divide(temp2);//ABS Division
		if (res.getValue().compare("0"))
			res.setValue(res.getValue().insert(0, 1, '-'));//Add '-' if res isn't 0
		return res;
	}
	//Handle all positive
	if (op2.compare("0") == 0)
	{  //Return ERROR message if divisor is 0
		cout << "ERROR: Divisor cannot be 0!" << endl;
		res.setValue("ERROR");
		return res;
	}

	if (compare(op1, op2) < 0) //Return 0
		return res;

	len1 = op1.size(); len2 = op2.size();
	int quotient = 0;
	lastPos = len2 - 1; tempstr = op1.substr(0, len2);//Prepare 1st division
	while (lastPos <= len1 - 1)
	{
		quotient = 0;
		temp1.setValue(tempstr); temp2.setValue(op2);
		while (compare(temp1.getValue(), op2)
			>= 0)
		{//Get one digit, 0 <= quotient <= 9
			quotient++; //Loop minus
			temp1 = temp1.minus(temp2);
		}
		//set digit
		result = result + (char)(quotient + '0');
		if (++lastPos <= len1 - 1)//Move to next lower digit
			tempstr = temp1.getValue() + op1[lastPos];
	}
	//Eliminate 0s
	for (i = 0; i < (int)result.size(); i++)
		if (result[i] != '0')
			break;
	result = result.substr(i, result.size());

	res.setValue(result);
	return res;
}

BigInt BigInt::mod(BigInt num)
{
	BigInt res, temp1, temp2;
	string result, op1, op2, tempstr;
	int len1, len2, lastPos;
	op1 = this->getValue(); op2 = num.getValue();
	//Handle all positive
	if (op2.compare("0") == 0)
	{  //Return ERROR message if divisor is 0
		cout << "ERROR: Divisor cannot be 0!" << endl;
		res.setValue("ERROR");
		return res;
	}

	if (compare(op1, op2) < 0) //Return 0
	{
		res.setValue(op1);
		return res;
	}

	len1 = op1.size(); len2 = op2.size();
	//int quotient = 0;
	lastPos = len2 - 1; tempstr = op1.substr(0, len2);//Prepare 1st division
	while (lastPos <= len1 - 1)
	{
		//quotient = 0;
		temp1.setValue(tempstr); temp2.setValue(op2);
		while (compare(temp1.getValue(), op2)
			>= 0)
		{//Get one digit, 0 <= quotient <= 9
		 //quotient++; //Loop minus
			temp1 = temp1.minus(temp2);
		}
		//set digit
		//result = result + (char)(quotient + '0');
		if (++lastPos <= len1 - 1)//Move to next lower digit
			tempstr = temp1.getValue() + op1[lastPos];
		else
			tempstr = temp1.getValue();
	}
	result = tempstr;
	//Eliminate 0s
	while (result[0] == '0' && result.size() > 1)
		result.erase(0, 1);
	//result = result.substr(i, result.size());

	res.setValue(result);
	return res;
}

BigInt BigInt::modPow(BigInt exponent, BigInt num)
{ //Return this^exponent mod num
	//ORIGIN = ((this^2)^(exponent/2)) mod num
	//or in odd ((this^2)^(exponent/2) * this) mod num
	//Do it iteratively
	BigInt origin = *this;
	BigInt result = ONE;
	while (exponent.getValue().compare("0") != 0)//While exp > 0
	{
		if (exponent.isOdd())//If odd, need to multiply to res
			result = result.multi(origin).mod(num);
		origin = origin.multi(origin).mod(num); //Ori = Ori ^ 2 mod num
		exponent = exponent.divide(TWO);//Exp /= 2
	}
	return result;
}

