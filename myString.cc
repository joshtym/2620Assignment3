//********************************************************************
// Course: CPSC2620 Fall 2013
// Name: Josh Tymburski
// Assignment #3
// Class Implementation
// Professor: Howard Cheng
// Program: myString.cc
// Purpose: Takes the header file and defines all the elements of it
// Programming Partner: Anthony Tymburski
// Software Used: Geany
//********************************************************************
#include<iostream>
#include<cassert>
#include<cctype>
#include"myString.h"
using namespace std;

//********************************************************************
// Default Constructor
// Post-Condition -- The character array will be set to size 0 as
//                   defined by the nullpointer whilst the length will
//                   be set to 0 as well
//********************************************************************
myString::myString()
{
	str = nullptr;
	len = 0;
	capacity = len;
}

//********************************************************************
// Constructor to set the character array at 1
// Post-Condition -- The character array will be set to size 1 and
//                   contain the given char entered by the user. The
//                   length will also be set to 1.
//********************************************************************
myString::myString(char c)
{
	str = new char[1];
	str[0] = c;
	len = 1;
	capacity = len;
}

//********************************************************************
// Constructor to set the character array greater than 1
// Post-Condition -- The character array will be set to the length
//                   of the given array. The length will also be set to
//                   this value.
//********************************************************************
myString::myString(const char *c)
{
	str = nullptr;
	len = 0;
	int charNum = 0;
	
	while (c[charNum] != '\0')
		charNum++;
	
	len = charNum;
	capacity = len;
	str = new char[charNum];
	
	for (int i = 0; i < charNum; i++)
		str[i] = c[i];
}

//********************************************************************
// Constructor that copies another object.
// Post-Condition -- The contents of object 1, in this case, s, are 
//                   copied entirely into a new object by performing 
//                   a deep copy.
//********************************************************************
myString::myString(const myString& s)
{
	len = s.len;
	capacity = len;
	delete[] str;
	str = new char[len];
	for (int i = 0; i < len; i++)
		str[i] = s.str[i];
}

//********************************************************************
// Destructor 
// Post-Condition -- Deallocates all memory used in the constructor.
//                   Essentially resets the myString.
//********************************************************************
myString::~myString()
{
	delete[] str;
	str = nullptr;
	len = 0;
	capacity = len;
}

//********************************************************************
// Assignment Operator Overload
// Post-Condition -- The assignment operater is overloaded to ensure
//                   that any assignment makes a deep copy.
//********************************************************************
myString& myString::operator=(const myString& s)
{
	if (this != &s)
	{
		delete[] str;
		str = nullptr;
		
		len = s.length();
		capacity = s.capacity;
		str = new char[len];
		
		for (int i = 0; i < len; i++)
		{
			str[i] = s.str[i];
		}
	}
	
	return *this;
}

//********************************************************************
// [] Operator Overload
// Post-Condition -- The [] operator is overloaded to allow for the use
//                   with the myString within the program
//********************************************************************
char& myString::operator[](int i)
{
	assert(0 <= i && i < len);
	return str[i];
}

//********************************************************************
// [] const Operator Overload
// Post-Condition -- The [] operator is overloaded in the same way as
//                   the above one, however, this one allows use for
//                   const objects
//********************************************************************
const char& myString::operator[](int i) const
{
	assert(0 <= i && i < len);
	return str[i];
}

//********************************************************************
// += Operator Overload
// Post-Condition -- The += operator is overloaded to allow for its
//                   functionality in the main program. Allows a user
//                   to directly modify a string and add on a given
//                   input
//********************************************************************
myString& myString::operator+=(const myString& s)
{
	for (int i = 0; i < s.len; ++i)
	{
		resize();
		str[len - 1] = s.str[i];
	}
	return *this;
}

//********************************************************************
// Addition Operator Overload
// Post-Condition -- The + operator is overloaded to allow for its
//                   functionality in the main program. Allows a user
//                   to create a new string that is equal to the
//                   current string with the user given string added on
//********************************************************************
myString myString::operator+(const myString& s)
{
	myString newString{*this};
	
	newString += s;
	
	return newString;
}

//********************************************************************
// Is Equal Operator Overload
// Post-Condition -- The == operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks if two strings are exactly the same
//********************************************************************
bool myString::operator==(const myString& s) const
{
	bool isEqual = true;
	
	if (len != s.len)
		return false;
	
	for (int i = 0; i < len; ++i)
	{
		if (str[i] != s.str[i])
			isEqual = false;
	}
	return isEqual;	
}

//********************************************************************
// Less Than Operator Overload
// Post-Condition -- The < operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks to see if the current string is
//                   lexographically smaller than the user given string
//                   I.E. Does it appear in the dictionary before the
//                        other string?
//********************************************************************
bool myString::operator<(const myString& s) const
{
	for (int i = 0; i < len; ++i)
	{
		if (str[i] < s.str[i])
			return true;
		else if (str[i] > s.str[i])
			return false;
	}
	
	if(len < s.len)
		return true;
		
	return false;
}

//********************************************************************
// Does Not Equal Operator Overload
// Post-Condition -- The != operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks to see if the current string does
//                   not equal the user given string
//********************************************************************
bool myString::operator!=(const myString& s) const
{
	return (!(*this == s));
}

//********************************************************************
// Less Than or Equal To Operator Overload
// Post-Condition -- The <= operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks to see if the current string is
//                   lexographically smaller than OR equal to the user
//                   given string.
//********************************************************************
bool myString::operator<=(const myString& s) const
{
	return	(*this == s || *this < s);
}

//********************************************************************
// Greater Than Operator Overload
// Post-Condition -- The > operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks to see if the current string is
//                   lexographically greater than the user given string
//********************************************************************
bool myString::operator>(const myString& s) const
{
	return !(*this <= s);
}

//********************************************************************
// Greater Than or Equal To Operator Overload
// Post-Condition -- The >= operator is overloaded so that a user may
//                   use this operator in correlation with the myString
//                   objects. Checks to see if the current string is
//                   lexographically greater than OR equal to the user
//                   given string.
//********************************************************************
bool myString::operator>=(const myString& s) const
{
	return !(*this < s);
}

//********************************************************************
// Function returns the value of the length of the string as defined
// in the constructor
//********************************************************************
int myString::length() const
{
	return len;
}

//********************************************************************
// Function receives an index at which the user would like to view and
// returns the contents of that index
//********************************************************************

char& myString::at(int i)
{
	assert(0 <= i && i < len);
	return str[i];
}

//********************************************************************
// Function receives an index at which the user would like to view and
// returns the contents of that index. However, this version ensures
// that the character is kept constant
//********************************************************************
const char& myString::at(int i) const
{
	assert(0 <= i && i < len);
	return str[i];
}

//********************************************************************
// Function receives a position and length of a substring within the
// current object and constructs a new object with that new string and
// returns it.
//********************************************************************
myString myString::substr(int k, int n) const
{
	assert(k + n <= len && k >= 0);
	
	myString subString;

	for (int i = 0; i < n; i++)
	{
		subString.resize();
		
		subString.str[i] = str[i + k];
	}
	
	return subString;
}

//********************************************************************
// Function takes in the string and indexes to where the user would
// like the string to be removed. It takes the starting point and
// the length from that point to be removed and removes them
//********************************************************************
myString& myString::erase(int k, int n)
{
	assert(k + n <= len && k >= 0);
	
	myString tempString{*this};
	int stringSize = len;
	
	delete[] str;
	str = nullptr;
	len = 0;
	capacity = len;
	
	for (int i = 0; i < k; i++)
	{	
		resize();
		
		str[i] = tempString.str[i];
	}
	
	for (int i = (k + n); i < stringSize; i++)
	{	
		resize();
		
		str[len - 1] = tempString.str[i];
	}
	
	return* this;
}

//********************************************************************
// Function takes in an index and a myString. It then inserts the 
// given myString at the index inputted from the user
//********************************************************************
myString& myString::insert(int k, const myString& s)
{
	assert(k >= 0 && k <= len);
	myString temp{*this};
	int size = len;
	
	if (!str)
		delete[] str;
	len = 0;
	capacity = len;
	
	for (int i = 0; i < k; i++)
	{
		resize();
		
		str[i] = temp.str[i];
	}
	
	for (int i = 0; i < s.length(); i++)
	{
		resize();
		
		str[i + k] = s.str[i];
	}
	
	for (int i = k; i < size; i++)
	{
		resize();
		
		str[i + s.length()] = temp.str[i];
	}
	
	return *this;
}

//********************************************************************
// Function takes in a string from the user and attempts to locate that
// string. If found, it returns the position of the start of that
// string. If not found, it returns an invalid position, IE, -1.
//********************************************************************
int myString::find(const myString &s) const
{
  for (int i = 0; i <= len - s.len; i++)
  {
    int match = 0;     
    while (match < s.len && str[i+match] == s.str[match]) 
    {
      match++;
    }

    if (match == s.len) 
    {
      return i;
    }
  }

  return npos;
}

//********************************************************************
// Function allows use of the getline function in correlation with the
// myString objects within the main program.
//********************************************************************
istream& getline(istream& is, myString& s)
{
	s.str = nullptr;
	s.len = 0;
	s.capacity = s.len;
	
	char c;
	
	cin.get(c);
	
	while (c != '\n')
	{
		s.resize();
		
		s.str[s.length()-1] = c;
		
		cin.get(c);
	}
	
	return is;
}

//********************************************************************
// Function allows use of the >> operator in correlation with the
// myString objects within the main program
//********************************************************************
istream& operator>>(istream& is, myString& s)
{
	myString temp;
	char c;
	
	cin >> c;
	
	while(isspace(c))
	{
		cin >> c;
	}
	
	while(c != '\n' && !(isspace(c)))
	{
		
		temp.resize();
		
		temp.str[temp.length() - 1] = c;
		
		cin.get(c);
	}
	
	//delete[] s.str;
	s = temp;
	return is;
}

//********************************************************************
// Function allows use of the << operator in correlation with the
// myString objects within the main program
//********************************************************************
ostream& operator<<(ostream& os, const myString& s)
{
	for (int i = 0; i < s.length(); ++i)
		cout << s.str[i];
		
	return os;
}

//********************************************************************
// Function checks to see if the array has reached it's maximum holding
// value. If it has, it calls the function to expand it. If not, it 
// increases the length of the string inside by one.
//********************************************************************
void myString::resize()
{
	if (len == capacity)
	{
		expandSize();
	}
	
	len++;
}

//********************************************************************
// Function takes a character array and resizes it dynmically to allow
// for more room in the array
//********************************************************************
void myString::expandSize()
{
	char *temp;
	temp = new char[len];
	
	for (int i = 0; i < len; i++)
	{
		temp[i] = str[i];
	}
	
	//if (str != nullptr)
	delete[] str;
	
	str = new char[len + 50];
	
	
	for (int i = 0; i < len; i++)
	{
		str[i] = temp[i];
	}
	
	capacity = len + 50;
	
	//if (temp != nullptr)
	delete[] temp;
		
	temp = nullptr;
}
	
	
	
	



