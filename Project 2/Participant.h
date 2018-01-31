#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <iostream>
#include <string>
using namespace std;
class Participant
{
private:
	string name;
	int power;

public:
	Participant();
	void setName(const string);
	void setPower(int);
	const string getName() const;
	int getPower() const;
	friend istream& operator >> (istream&, Participant&);
	friend ostream& operator << (ostream&, Participant&);
	bool operator==(Participant&);
};

Participant::Participant():name("empty"),power(-1){}

void Participant::setName(const string n)
{
	name = n;
}

void Participant::setPower(int pow)
{
	power = pow;
}

const string Participant::getName() const
{
	return name;
}

int Participant::getPower() const
{
	return power;
}

istream& operator >> (istream& in, Participant& other)
{
	string str;
	getline(in, str);

	int len = str.length();
	int indexOfLastDelimeter = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] == ' ' || str[i] == '	' )
		{
			indexOfLastDelimeter = i;
			break;
		}
	}
	if (str != "")
	{
		string n;
		n = str.substr(0, indexOfLastDelimeter);
		string p;
		p = str.substr(indexOfLastDelimeter + 1, len);
		int pow = stoi(p);

		other.setName(n);
		other.setPower(pow);
	}
	return in;
}

ostream& operator << (ostream& out, Participant& other)
{
	out << other.name << " " << other.power;
	return out;
}

bool Participant::operator==(Participant& other)
{
	return name == other.name && power == other.power;
}


#endif