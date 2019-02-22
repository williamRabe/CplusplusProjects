/*
Program name	: Binary
Author			: Wm. Rabe
Date created	: 12.10.2018
Description		: This program reads in a user entered binary string (ex: 00101001)
and determines if it is divisible by 7.
*/

#include <iostream>
#include <string>
#include <exception> // for exception class access

#define TEST false // bool for testing/debugging

using namespace std;

// classes
class NonBinaryException : public exception{ // user defined exception class inherted from exception class
	public :
		virtual const char* what() {
			return "User input is NOT a binary string.";
		}

};



// function prototypes
string getInput(void);
string checkInput(void);
unsigned int stringToBase10( string );
bool divisibleBySeven( int );

//main
int main(int argc, char const *argv[]) {
	bool keepGoing = true;

	string userStr = checkInput();

	do{

		int userBaseTenNum = stringToBase10( userStr );

		bool yes = divisibleBySeven(userBaseTenNum);

		cout << endl <<  userStr;
		cout << " " << userBaseTenNum;
		(yes) ? cout << " Divisible by 7." << endl : cout << " Not divisible by 7." << endl;

		userStr = checkInput();

		if(userStr.at(0) == 'x' || userStr.at(0) == 'X') { keepGoing = false;}

	} while(keepGoing);

	return 0;
} // end main

// functions
string getInput(void){
	string input;

	cout << "Please enter a binary string or exit by typing \"x\": ";
	cin >> input;

	if (TEST){ cout << "getInput: tested" << endl; } // gives me an idea where the program is incase of failures
	return input;
} // end getInput

string checkInput(void){
	bool tryAgain = true;
	int size;
	char ch;
	string input;


	while(tryAgain){
		tryAgain = false;
		input = getInput();

			if(input.at(0) == 'x' || input.at(0) == 'X'){ // exit program condition.
			return input;
		}

		for (auto a = input.begin(); a != input.end(); a++) {
			try{

				if(*a != '1' && *a != '0'){
					throw NonBinaryException();
				}
			} catch(NonBinaryException& e){
				cout << e.what() << endl;
				tryAgain = true;
				break;
			}
		}
	}
	if (TEST){ cout << "checkInput: tested" << endl; }
	return input;
} // end checkInput

unsigned int stringToBase10(string n){

	unsigned int result = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
      result <<= 1;
      if (*it == '1') result |= 1;
  }

	if (TEST){ cout << "stringToBase10: tested" << endl; }

	  return result;
} // end stringToBase10

bool divisibleBySeven(int value){
	bool success = false;
	(value % 7 == 0) ? success = true : success = false;

	if(value == 0){ success = false;}

	return success;
} // end divisibleBySeven
