#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

double getMantissa(string man_string)
{
	double mantisssa = 0.0;
	int j = -1;
	for (unsigned i = 0; i < man_string.length(); i++)
	{
		if (man_string[i] == '1')
			mantisssa += pow(2, j);
		j--;
	}
	return 1.0 + mantisssa;
}

double getExponent(string exp_string)
{
	int n = exp_string.length();
	double bias = pow(2, n - 1) - 1;
	double exp = 0.0;
	int j = 0;
	for (int i = exp_string.length() - 1; i > -1; i--)
	{
		if (exp_string[i] == '1')
			exp += pow(2, j);
		j++;
	}
	return exp - bias;
}

string getBitString(int exp_bits, int man_bits)
{
	string bit_str;
	unsigned totalBits = exp_bits + man_bits + 1;
	cout << "Enter bit string: ";
	cin >> bit_str;
	while (bit_str.length() != totalBits)
	{
		cout << "Wrong number of bits.\n";
		cout << "Enter bit string: ";
		cin >> bit_str;
	}
	return bit_str;
}

int main(int argc, char *argv[])
{
	int man_bits = 0, exp_bits = 0;
	string sect1, sect2, sect3, sect4, sect5,
		 bit_string, man_string, exp_string;
	char sign = '0';
	ifstream file_read;
	file_read.open(argv[1], ios::in);
	file_read >> sect1 >> sect2 >> sect3 >> sect4 >> sect5;
	file_read.close();

	// Get order of file
	// Get number of bits
	if (sect1[0] == 's' && sect2[0] == 'e' && sect4[0] == 'm')
	{
		// Sign - Exp - Man
		exp_bits = stoi(sect3);
		man_bits = stoi(sect5);
		bit_string = getBitString(exp_bits, man_bits);
		sign = bit_string[0];
		exp_string = bit_string.substr(1, exp_bits);
		man_string = bit_string.substr(exp_bits + 1, man_bits);
	}
	else if (sect1[0] == 's' && sect2[0] == 'm' && sect4[0] == 'e')
	{
		// Sign - Man - Exp
		man_bits = stoi(sect3);
		exp_bits = stoi(sect5);
		bit_string = getBitString(exp_bits, man_bits);
		sign = bit_string[0];
		man_string = bit_string.substr(1, man_bits);
		exp_string = bit_string.substr(man_bits + 1, man_bits);
	}
	else if (sect1[0] == 'e' && sect3[0] == 's' && sect4[0] == 'm')
	{
		//Exp - Sign - Man
		exp_bits = stoi(sect2);
		man_bits = stoi(sect5);
		bit_string = getBitString(exp_bits, man_bits);
		exp_string = bit_string.substr(0, exp_bits);
		sign = bit_string[exp_bits];
		man_string = bit_string.substr(exp_bits + 1, man_bits);
	}
	else if (sect1[0] == 'e' && sect3[0] == 'm' && sect5[0] == 's')
	{
		//Exp - Man - Sign
		exp_bits = stoi(sect2);
		man_bits = stoi(sect4);
		bit_string = getBitString(exp_bits, man_bits);
		exp_string = bit_string.substr(0, exp_bits);
		man_string = bit_string.substr(exp_bits, man_bits);
		sign = bit_string[bit_string.length() - 1];
	}
	else if (sect1[0] == 'm' && sect3[0] == 's' && sect4[0] == 'e')
	{
		// Man - Sign - Exponent
		man_bits = stoi(sect2);
		exp_bits = stoi(sect5);
		bit_string = getBitString(exp_bits, man_bits);
		man_string = bit_string.substr(0, man_bits);
		sign = bit_string[man_bits];
		exp_string = bit_string.substr(man_bits + 1, exp_bits);
	}
	else if (sect1[0] == 'm' && sect3[0] == 'e' && sect5[0] == 's')
	{
		// Man - Exponent - Sign
		man_bits = stoi(sect2);
		exp_bits = stoi(sect4);
		bit_string = getBitString(exp_bits, man_bits);
		man_string = bit_string.substr(0, man_bits);
		exp_string = bit_string.substr(man_bits, exp_bits);
		sign = bit_string[bit_string.length() - 1];
	}
	double man_dec = 0.0, exp_dec = 0.0;
	man_dec = getMantissa(man_string);
	exp_dec = getExponent(exp_string);
	if (sign == '1')
		cout << "Value: " << man_dec * pow(2, exp_dec) * -1 << "\n";
	else
		cout << "Value: " << man_dec * pow(2, exp_dec) << "\n";
}