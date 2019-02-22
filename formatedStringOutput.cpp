/*
Program name	: File I/O
Author			: Wm. Rabe
Date Created	: 11/6/2018
Description		: This program reads data in from a formated file and uses that
data to fill a vector of objects, then prints the data in a formated output.
String, vector, class, and output manipulation was used to acheive this.
*/

// includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// classes
class Person{
	private:
		string FirstName;
		string LastName;
		int Age;

 		public:

			void setFirstName( string z){
				FirstName = z;
			}
			void setLastName( string x){
				LastName = x;
			}
			void setAge( int x){
				Age = x;
			}

			const string getFirstName(){
				return FirstName;
			}
			const string getLastName(){
				return LastName;
			}
			const int getAge(){
				return Age;
			}

			const printPerson(){
				cout << setw(12) << left <<getLastName();
				cout << setw(12) << left <<getFirstName();
				cout << setw(4) << right << getAge() << endl;
			}
		// constructors
			// basic constuctor
			Person(){
				setFirstName("");
				setLastName("");
				setAge(0);
			}
			// overloaded constructor
			Person(string x, string y, int z){
				setFirstName(x);
				setLastName(y);
				setAge(z);
			}
}; // end Person class

// functions
void filtered_print_and_delete(vector<Person>);
bool sort_obj(const Person , const Person );

int main(int argc, char const *argv[]) {
	string line;
	string fname;
	string lname;
	string age;
	int pos;
	ifstream file (argv[1]); // using argv for flexability.
	vector<Person> list;

	if(file.is_open()){ // checks if file exists and can open.
		while(getline( file , line )){
			pos = line.find(" ");
			lname = (line.substr(0,pos));
			line.erase(0,pos+1);
			pos = line.find(" ");
			fname = (line.substr(0,pos));
			line.erase(0,pos+1);
			age = line;
			list.push_back(Person(fname, lname, stoi(age))); // inserts new Person obj at end of list
		}

		file.close(); // closes file
	} else cout << "Unable to open file: " << argv[1] << endl; // if specified file can't open

	auto sortLambda = [] (Person &a, Person &b) -> bool{
		return a.getLastName() < b.getLastName();
	};

	sort(list.begin(), list.end(), sortLambda);

	filtered_print_and_delete(list);

	return 0;
}// end main

// prints vectors based on specified age, deleting each element after being handled.
void filtered_print_and_delete(vector<Person> v){
	Person * ptr;
	while(! v.empty()){
		ptr = &v.at(0);
		if(ptr->getAge() >= 40){
			ptr->printPerson();
		}
		v.erase(v.begin());
	}

} //end print_list
