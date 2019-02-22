/*
Program name	: Program08LinkedList
Author			: Wm. Rabe
Date Created	: 11/6/2018
Description		: This program implements a list of nodes containing a string
				  value. The student will add code to place the nodes into
				  the linked list in alphabetical order and then print the
				  list forwards. For extra credit, the student will change the
				  list to a double linked list so that it has a head node and
				  a tail node and will add a method to print the list in
				  reverse.
*/

// includes
#include <iostream>
#include <cstdlib>
#include <string>

// using
using namespace std;

class StringNode
{
	// prototypes for class methods
public:
	StringNode(string dataInit = "", StringNode* nextLoc = nullptr);
	void InsertAfter(StringNode* nodePtr);
	StringNode* GetNext();
	string GetDataVal();

	// class attributes (also called properties or class variables)
private:
	string dataVal;
	StringNode* nextNodePtr;
};

// Class Constructor
StringNode::StringNode(string dataInit, StringNode* nextLoc)
{
	this->dataVal = dataInit;
	this->nextNodePtr = nextLoc;
}

/* Insert node after this node.
 * Before: this -- next
 * After:  this -- node -- next
 */
void StringNode::InsertAfter(StringNode* nodePtr)
{
	StringNode* tempNextPtr = nullptr;

	tempNextPtr = this->nextNodePtr;    // Remember next
	this->nextNodePtr = nodePtr;       // this -- node -- ?
	nodePtr->nextNodePtr = tempNextPtr; // this -- node -- next

}

// get the pointer to the next node
StringNode* StringNode::GetNext()
{
	return this->nextNodePtr;
}


string StringNode::GetDataVal()
{
	return this->dataVal;
}


StringNode * findInsertionPtr (StringNode * headPtr, string myValue){
	StringNode * cur = headPtr;
	StringNode * next = headPtr->GetNext();

	while(next != nullptr && next->GetDataVal() < myValue){
		cur = next;
		next = next->GetNext();
	}

	return cur;
}

void printListForward(StringNode * headPtr)
{

	StringNode * currPtr = headPtr->GetNext();
	while (currPtr != nullptr)
	{
		// print a comma and space unless this is the first one
		if (currPtr != headPtr->GetNext())
			cout << ", ";

		// print the data value
		cout << currPtr->GetDataVal();

		// assign the next pointer to the current one
		currPtr = currPtr->GetNext();
	}
	cout << endl;
}


int main()
{
	StringNode* headPtr = nullptr; // Create intNode objects
	StringNode* currPtr = nullptr;
	StringNode* prevPtr = nullptr;
	string fname;

	// in this linked list, the head node will be an empty dummy
	// (dataVal will always be the empty string)

	// Head is the front of the nodes list
	headPtr = new StringNode();
	prevPtr = headPtr;

	// get the input from the user and insert into the list
	cout << "Please enter a first name (enter EXIT to quit): ";
	cin >> fname;
	while (fname != "EXIT")
	{
		currPtr = new StringNode(fname);

		prevPtr = findInsertionPtr(headPtr, fname);
		prevPtr->InsertAfter(currPtr); // Append curr

		cout << "Please enter a first name (enter EXIT to quit): ";
		cin >> fname;
	}

	// Print the list forwards
	printListForward(headPtr);

	return 0;
}
