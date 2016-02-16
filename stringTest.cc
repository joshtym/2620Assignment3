//
// CS 2620 Assignment 3
//
// Howard Cheng
// Oct 4, 2013
//
// This program tests various functionalities of the myString class.
//
// Note: this is not an exhaustive test!  You may wish to test your routines
// some more.  In particular, memory problems may not be detected with this
// program.
//

#include "myString.h"
#include <iostream>
#include <cassert>

using namespace std;

void printString(const myString& s, const char* prompt);

int main(void)
{
  myString s1;
  myString s2("abcdefg");
  myString s3('X');
  myString s4(s2);
  const myString s5 = "this is a constant string.";

  // test constructors
  assert(s1 == "");
  assert(s2 == "abcdefg");
  assert(s3 == "X");
  assert(s4 == s2);
  
  //Test find
  cout << "bcde loc in s2 is: " << s2.find("bcde") << endl;

  // test output and lengths
  printString(s1, "s1");
  cout << "Length = " << s1.length() << endl;
  printString(s2, "s2");
  cout << "Length = " << s2.length() << endl;
  printString(s3, "s3");
  cout << "Length = " << s3.length() << endl; 
  printString(s4, "s4");
  cout << "Length = " << s4.length() << endl;
  printString(s5, "s5");
  cout << "Length = " << s5.length() << endl;

  // test input
  cout << endl;
  cout << "enter s1, s2, s3, s4 separated by whitespaces, terminated by a newline:" << endl;
  cin >> s1;
  cin.ignore();          // eat a new line
  printString(s1, "s1");
  printString(s2, "s2");
  printString(s3, "s3");
  printString(s4, "s4");

  cout << endl;
  cout << "get a line of text into s1:" << endl;
  getline(cin, s1);
  printString(s1, "s1");

  cout << (cin.good() ? "good" : "not good") << endl;
  cout << (cin.eof() ? "eof": "not eof") << endl;

  // test []
  cout << "printing every second letter of s1: " << endl;
  for (int i = 0; i < s1.length(); i += 2) {
    cout << s1[i];
  }
  cout << endl;

  cout << "printing every second letter of s5: " << endl;
  for (int i = 0; i < s5.length(); i += 2) {
    cout << s5[i];
  }
  cout << endl;

  // test substring
  cout << endl;
  cout << "Substring test:" << endl;
  printString(s2.substr(2, 4), "s2.substr(2, 4)"); 
  printString(s2.substr(0, s2.length()), "s2.substr(0, s2.length())"); 
  printString(s5.substr(2, 5), "s5.substr(2, 5)");

  // test erase
  cout << endl;
  cout << "Erase test:" << endl;
  s2.erase(2, 4);
  printString(s2, "s2.erase(2, 4)");
  s1.erase(0, s1.length());
  printString(s1, "s1.erase(0, s1.length())");

  // test insertion
  cout << endl;
  cout << "Insert test:" << endl;
  s1.insert(0, "hello world!");
  printString(s1, "s1.insert(0, \"hello world!\")");
  s1.insert(5, " cruel");
  printString(s1, "s1.insert(5, \" cruel\")");
  s1.erase(0, 5);
  s1.insert(0, "goodbye");
  printString(s1, "s1");

  // test concatenation
  cout << endl;
  cout << "Concatentation test:" << endl;
  s2 += "this is the end.";
  printString(s2, "s2 += \"this is the end.\"");
  
  printString(s1 + "  Bye!", "s1 + \"  Bye!\"");

  printString(s1 + "", "s1 + \"\"");
  printString(s1 + " " + "hello again!", "s1 + \" \" + \"hello again!\"");

  // test comparisons
  s1 = "abc";
  s2 = s1;
  s3 = s1 + "a";
  s4 = "x";
  
  assert(s1 == s2 || s1 <= s2 || s2 <= s1);
  assert(!(s1 > s2 || s2 > s1 || s1 != s2));
  assert(s1 < s3 && s1 <= s3 && s1 != s3);
  assert(!(s1 >= s3 || s1 > s3 || s1 == s3));
  assert(s1 != s4);
  assert(s4 > s1);
  assert(s4 >= s1);
  assert(s1 != s4 && s4 > s1 && s4 >= s1);
  assert(!(s1 == s4 || (s4 <= s1 && s4 < s1)));

  cout << endl;
  cout << "Comparison tests passed." << endl;

  // the following should not compile
  /*
  s5.erase(2,4);
  s5.insert(4, "hello");
  */
  return 0;
}

void printString(const myString& s, const char* prompt)
{
  cout << prompt << " = \"" << s << "\"" << endl;
}
