#ifndef ContactBST_H
#define ContactBST_H

#include <iostream>
#include "contact.h"
#include "myvector.h"
#include <fstream>
#include <sstream>
using namespace std;

// reference lab9
//  declaration and definition of the Node function
class Node
{
private:
	string key;
	MyVector<Contact> *contactVector;
	Node *left;
	Node *right;

public:
	Node(string key, MyVector<Contact> *contactVector);
	~Node();
	string getKey() { return this->key; }
	MyVector<Contact> *getData() { return this->contactVector; }
	friend class ContactBST;
};
Node::Node(string key, MyVector<Contact> *contactVector) // non-default constructor
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->contactVector = contactVector;
}
Node::~Node() // destructor
{
	cout << "deleted.." << this->key << endl;
}
//=============================================================================
// declaring and defining the ContactBST function
class ContactBST
{
private:
	Node *root;

public:
	ContactBST();												// constructor
	~ContactBST();												// destructor
	Node *getRoot();											// returns the root of the Tree
	Node *add(Node *ptr, string key, Contact *data);			// add key into tree/subtree with root ptr
	Node *update(Node *ptr, string key);						// Edit the node with key
	Node *del(Node *ptr, string key);							// Delete a node with key from the tree/subtree with root
	Node *search(Node *ptr, string key);						// Find and returns the node with key
	bool markFav(Node *ptr, string key);						// Mark a contact as favorite
	bool unmarkFav(Node *ptr, string key);						// Unmark a contact as favorite
	void printASC(Node *ptr);									// Print the data at nodes in an ascending order
	void printDES(Node *ptr);									// Print the data at nodes in a descending order
	void printFav(Node *ptr);									// Print the favorite data at nodes in an ascending order
	int importCSV(Node *ptr, string path);						// Load all the contacts from the CSV file to the BST
	int exportCSV(Node *ptr, string path);						// Export all the contacts from the BST to a CSV file in an ascending order
	void printNode(Node *ptr);									// prints the details of a given node
	void printNodeFile(Node *ptr, ofstream &myfile);			// prints the details of a given node into a csv file
	void printASCfile(Node *ptr, ofstream &myfile, int &count); // helper function to print in ascending order in a csv file
	Node *findMin(Node *ptr);									// finds the minimum node with root ptr

public:											   // helper methods
	void insert_helper(string key, Contact *data); // Helper method for insert method
	void remove_helper(string key);				   // Helper method for remove method
};

ContactBST::ContactBST() // default constructor of the bst tree
{
	this->root = nullptr;
}
ContactBST::~ContactBST() // destructor of the bst tree
{
	while (root)
	{
		root = del(root, root->key); // calls delete repeatedly until root becomes null
	}
}

Node *ContactBST::getRoot() // function to get root
{
	return root; // returns root
}

void ContactBST::insert_helper(string key, Contact *data) // function to help insert into the tree
{
	root = add(root, key, data); // calls the add method
	cout << "The contact has been added successfully" << endl;
}

void ContactBST::remove_helper(string key) // function to help remove from the tree
{
	root = del(root, key); // calls the del method
	cout << "The contact has been removed successfully" << endl;
}

// iterative search through a binary tree
Node *ContactBST::search(Node *ptr, string key) // reference - https://www.geeksforgeeks.org/iterative-searching-binary-search-tree/
{												// studied the approach from this site and implemented

	Node *temp = ptr; // creates a temp node equal to root
	while (temp != nullptr)
	{
		// moves along the right side
		if (key > temp->key)
		{
			temp = temp->right;
		}

		// moves along the left side
		else if (key < temp->key)
		{
			temp = temp->left;
		}
		else
		{
			return temp; // returns temp if node is found
		}
	}
	return nullptr; // returns nullptr if node is not found
}

Node *ContactBST::add(Node *ptr, string key, Contact *data) // used to add node into the tree
{

	Node *found = search(ptr, key); // checks if node with the key is already present

	if (found != nullptr) // if node was found
	{
		found->contactVector->push_back(*data); // the contact object is pushed into the existing contact vector in the corredponding node
		return ptr;
	}

	else // if node doesn't exist - recursively moves till the end of the tree and creates a node
	{

		if (ptr == nullptr) // base case
		{

			MyVector<Contact> *temp = new MyVector<Contact>(); // creates new vector
			temp->push_back(*data);							   // stores the contact object in the contact vector of the new node
			Node *curr = new Node(key, temp);				   // creates new node with the value

			return curr; // returns new node to insert
		}
		else if (key < ptr->key)
		{
			ptr->left = add(ptr->left, key, data); // recursively traverse the left of the tree
		}
		else if (key > ptr->key)
		{
			ptr->right = add(ptr->right, key, data); // recursively traverse the right of the tree
		}
		return ptr;
	}
}

bool cont() // function to check if the user wants to continue
{
	char a;
	do
	{
		cout << "Do you want to continue[y/n]" << endl;
		cin >> a;
	} while (tolower(a) != 'y' and tolower(a) != 'n');
	return (tolower(a) == 'y');
}

Node *ContactBST::update(Node *ptr, string key) // update function - to edit contacts
{
	Node *found = search(ptr, key); // finds the contact
	if (found != nullptr)			// if contact is found
	{
		printNode(found); // print details of the node
		int n;
		do
		{
			cout << "\n Please select the record you want to edit: " << endl;
			cin >> n;
		} while (n < 0 or n > found->contactVector->size()); // checks constraints for input

		char o;
		bool flag = true; // to check if user wants to continue
		while (flag)
		{
			// provide the user with available options
			cout << "Which field do you want to edit? \n1. First Name \n2. Last Name \n3. Email \n4. Phone \n5. City \n6. Country" << endl;
			cin >> o;
			switch (o)
			{

			case ('1'):
			{
				string tempFN;
				cout << "Please enter the new first name" << endl;
				cin >> tempFN;
				Contact tempC = found->contactVector->at(n - 1);
				// creates new contact object pointer based on the new first name
				Contact *tempCptr = new Contact(tempFN, tempC.lname, tempC.email, tempC.primaryPhone, tempC.city, tempC.country, tempC.isFav);
				string tempKey = (tempFN + " " + tempC.lname);

				// if the contact vector has more records then the contact is just removed from the contactvector
				if (found->contactVector->size() > 1)
				{
					found->contactVector->erase(n - 1);
				}
				else // if the contact vector has only one entry then the entire node is deleted
				{
					remove_helper(found->key);
				}
				insert_helper(tempKey, tempCptr); // the updated node is then inserted again into the tree
				flag = false;					  // doesn't allow the user to continue as the entire node is changed
				break;
			}
			case ('2'):
			{
				// proceeds in exact same way as the above function
				string tempLN;
				cout << "Please enter the new last name" << endl;
				cin >> tempLN;
				Contact tempC = found->contactVector->at(n - 1);
				Contact *tempCptr = new Contact(tempC.fname, tempLN, tempC.email, tempC.primaryPhone, tempC.city, tempC.country, tempC.isFav);
				string tempKey = (tempC.fname + " " + tempLN);
				if (found->contactVector->size() == 1)
				{
					remove_helper(found->key);
				}
				else
				{
					found->contactVector->erase(n - 1);
				}
				insert_helper(tempKey, tempCptr);
				flag = false; // doesn't allow the user to continue as the entire node is changed

				break;
			}
			case ('3'):
			{
				string tempEM;
				cout << "Please enter the new email" << endl;
				cin >> tempEM;
				found->contactVector->at(n - 1).email = tempEM; // assigns the new email id
				flag = cont();									// asks user if they want to continue updating
				break;
			}
			case ('4'):
			{
				string tempP;
				cout << "Please enter the new phone number" << endl;
				cin >> tempP;
				found->contactVector->at(n - 1).primaryPhone = tempP; // assigns the new phone number
				flag = cont();										  // asks user if they want to continue updating
				break;
			}
			case ('5'):
			{
				string tempCity;
				cout << "Please enter the new city" << endl;
				cin >> tempCity;
				found->contactVector->at(n - 1).city = tempCity; // updates the city
				flag = cont();
				break;
			}
			case ('6'):
			{
				string tempCountry;
				cout << "Please enter the new city" << endl;
				cin >> tempCountry;
				found->contactVector->at(n - 1).country = tempCountry; // updates the country
				flag = cont();
				break;
			}

			default: // throws an error for invalid input and asks user to provide an input again
			{
				cout << "Error! Please enter a valid input" << endl;
				break;
			}
			}
		}
	}
	else // if the given record is not found
	{
		cout << "Record Not Found" << endl;
		return nullptr;
	}
}

bool ContactBST::markFav(Node *ptr, string key) // to mark a contact as fav
{
	Node *found = search(ptr, key); // searches for the contact
	if (found == nullptr)			// if contact is not found
	{
		cout << "No Records Found" << endl;
		return false; // returns that option couldn't be completed
	}
	// if the node is found
	printNode(found); // prints the details of the node found
	int n;
	do
	{
		cout << "\n Please select the record you want to edit: " << endl;
		cin >> n;										 // asks user to input the serial number of the record to be updated
	} while (n < 0 or n > found->contactVector->size()); // input constraints

	found->contactVector->at(n - 1).setFav(); // sets the contact record as favorite
	cout << found->key << " (" << found->contactVector->at(n - 1).email << ") "
		 << "has been successfully set as favorite." << endl;
	return true; // returns true to denote that the operation was successful
}

bool ContactBST::unmarkFav(Node *ptr, string key)
{
	// proceeds exactly like the above function
	Node *found = search(ptr, key);
	if (found == nullptr)
	{
		return false;
	}
	printNode(found);
	int n;
	do
	{
		cout << "\n Please select the record you want to edit: " << endl;
		cin >> n;
	} while (n < 0 or n > found->contactVector->size());

	found->contactVector->at(n - 1).removeFav(); // removes the contact from fav
	found->contactVector->at(n - 1).setFav();	 // sets the contact record as favorite
	cout << found->key << " (" << found->contactVector->at(n - 1).email << ") "
		 << "has been successfully removed from favorites." << endl;
	return true;
}

int ContactBST::importCSV(Node *ptr, string path) // imports details from file
{
	ifstream myfile(path, ios::in); // opens file
	if (myfile.fail())
	{
		cout << "File failed to open" << endl;
		return -1;
	}
	int count(0);				 // stores the number of records to be imported
	Contact *temp = new Contact; // creates new contact object
	string line, word;			 // line keeps each word with comma and word keeps each word with the comma removed
	bool fav;
	int i = 0;

	// reference - assignment2
	while (!myfile.eof()) // traverses to the end of the file
	{
		word = ""; // initializes word as empty string

		myfile >> line; // takes a word from the file till we encounter a space

		if (i != 6) // the last value(fav) doesn't end with a comma
		{
			for (int j = 0; j < line.length() - 1; j++)
			{
				word += line[j]; // copies everything except the comma
			}
		}
		else
		{
			word = line;
		}

		// switch case to set each parameter of the contact object
		switch (i)
		{
		case 0:
		{
			temp->fname = word;
			i++;
			break;
		}
		case 1:
		{
			temp->lname = word;
			i++;
			break;
		}
		case 2:
		{
			temp->email = word;
			i++;
			break;
		}
		case 3:
		{
			temp->primaryPhone = word;
			i++;
			break;
		}
		case 4:
		{
			temp->city = word;
			i++;
			break;
		}
		case 5:
		{
			temp->country = word;
			i++;
			break;
		}
		case 6:
		{
			if (word == "0")
			{
				temp->isFav = false;
			}
			else
			{
				temp->isFav = true;
			}
			i = 0;
			insert_helper((temp->fname + " " + temp->lname), temp); // inserts the contact object created
			count++;												// keeps incrementing the number of records imported successfully
			break;
		}

		default:
		{
			break;
		}
		}
	}

	return count; // returns the final count of the contacts imported
}

void ContactBST::printNode(Node *ptr) // method to print the details of a node
{
	MyVector<Contact> *temp = ptr->getData(); // stores the contactvector
	for (int j = 0; j < temp->size(); j++)	  // loops through each index of the contactvector and prints the details
	{
		cout << j + 1 << ". "; // gives the corresponding serial number within a node
		for (int i = 0; i < 6; i++)
		{
			switch (i)
			{
			case 0:
			{
				cout << ptr->key << ", ";
				break;
			}
			case 1:
			{
				cout << temp->at(j).email << ", ";
				break;
			}
			case 2:
			{
				cout << temp->at(j).primaryPhone << ", ";
				break;
			}
			case 3:
			{
				cout << temp->at(j).city << ", ";
				break;
			}
			case 4:
			{
				cout << temp->at(j).country << ", ";
				break;
			}
			case 5:
			{
				cout << temp->at(j).isFav << endl;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void ContactBST::printASC(Node *ptr) // inorder traversing gives ascending order
{

	if (ptr == nullptr) // base case
	{
		return;
	}
	printASC(ptr->left);  // print the left side
	printNode(ptr);		  // print the root of the correspinding tree
	printASC(ptr->right); // print the right side
}

void ContactBST::printDES(Node *ptr) // reversing the inorder traversing function
{
	if (ptr == nullptr) // base case
	{
		return;
	}
	printDES(ptr->right); // print the right side
	printNode(ptr);		  // print the root of the correspinding tree
	printDES(ptr->left);  // print the left side
}

void ContactBST::printFav(Node *ptr) // method the print all the favorite contacts - inorder traversing while checking if the contact is fav or not
{
	if (ptr == nullptr) // base case
	{
		return;
	}
	printFav(ptr->left);					  // traverses the left of the tree
	MyVector<Contact> *temp = ptr->getData(); // checks through the contact vector of the corresponding node
	for (int j = 0; j < temp->size(); j++)
	{
		if (temp->at(j).isFav) // if the contact in the node is favorite then the details are printed
		{					   // can't use printNode function here as it will print the details of all the contacts in the node
			for (int i = 0; i < 6; i++)
			{
				switch (i)
				{
				case 0:
				{
					cout << ptr->key << ",";
					break;
				}
				case 1:
				{
					cout << temp->at(j).email << ",";
					break;
				}
				case 2:
				{
					cout << temp->at(j).primaryPhone << ",";
					break;
				}
				case 3:
				{
					cout << temp->at(j).city << ",";
					break;
				}
				case 4:
				{
					cout << temp->at(j).country << ",";
					break;
				}
				case 5:
				{
					cout << temp->at(j).isFav << endl;
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
	}
	printFav(ptr->right); // traverses the right of the tree
}

void ContactBST::printNodeFile(Node *ptr, ofstream &myfile) // prints the details of a node into the file
{
	MyVector<Contact> *temp = ptr->getData(); // gets the contact vector associated with the node
	for (int j = 0; j < temp->size(); j++)
	{
		for (int i = 0; i < 6; i++)
		{
			switch (i)
			{
			case 0:
			{
				myfile << ptr->key << ", ";
				break;
			}
			case 1:
			{
				myfile << temp->at(j).email << ", ";
				break;
			}
			case 2:
			{
				myfile << temp->at(j).primaryPhone << ", ";
				break;
			}
			case 3:
			{
				myfile << temp->at(j).city << ", ";
				break;
			}
			case 4:
			{
				myfile << temp->at(j).country << ", ";
				break;
			}
			case 5:
			{
				myfile << temp->at(j).isFav << endl;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}
void ContactBST::printASCfile(Node *ptr, ofstream &myfile, int &count) // helper function to print everything in ascending order into the file - inorder traversing
{
	if (ptr == nullptr) // base case
	{
		return;
	}
	printASCfile(ptr->left, myfile, count);	 // print the left side of the tree
	printNodeFile(ptr, myfile);				 // call the printNodeFile function to print the corresponding node
	count++;								 // increment the count of the files exported
	printASCfile(ptr->right, myfile, count); // print the right side of the tree
}

int ContactBST::exportCSV(Node *ptr, string path) // exports the contacts into a file
{
	ofstream myfile;
	myfile.open(path, ios::out);
	if (myfile.fail())
	{
		return -1;
	}
	int count(0);
	printASCfile(ptr, myfile, count); // calls the helper function
	myfile.close();
	return count;
}

Node *ContactBST::findMin(Node *ptr) // finds out the node with the min value in the tree rooted at ptr
{
	if (ptr == nullptr) // base case
	{
		return nullptr;
	}

	Node *temp = ptr;

	while (temp->left != nullptr)
	{
		temp = temp->left; // traversing till the left end (charateristic of binary tree - minimum is at the extreme left)
	}

	return temp;
}

Node *ContactBST::del(Node *ptr, string key) // function to remove a ptr
{
	Node *temp = ptr; // temporarily stores ptr in a node

	if (temp == nullptr) // if we reach traverse till the end of the tree without encountering the node means the node is not found
	{
		cout << "Record not found" << endl;
		return nullptr;
	}
	else if (key < temp->key)
	{
		ptr->left = del(temp->left, key); // recursively traversing through the left of the tree
	}
	else if (key > temp->key)
	{
		ptr->right = del(temp->right, key); // recursively traversing through the right of the tree
	}

	else // if the node is found
	{
		int size = temp->contactVector->size();
		if (size == 1) // if there is only one contact in the contact vector
		{
			if (temp->right == nullptr and temp->left == nullptr) // case 1 - where the node is a leaf node
			{
				ptr = nullptr;
				delete temp; // delete the node
			}

			else if (temp->right != nullptr and temp->left != nullptr) // case 2 - where the node has two children
			{
				Node *min = findMin(ptr->right);		// find the minimum among the children towards the right
				swap(min->key, ptr->key);				// built in function - swaps the min and the current ptr
				ptr->right = del(ptr->right, min->key); // recursively traverses through the right of the tree till the node to be removed is at the end
			}

			else // case 3 - where the node has any one children
			{
				if (temp->left == nullptr) // swap with the right if the left is null
				{
					ptr = ptr->right;
					delete temp;
				}

				else // swap with the left if the right is null
				{
					ptr = ptr->left;
					delete temp;
				}
			}
		}

		else // if there are more than one entries in the contactvector
		{
			printNode(temp); // print the details of the node
			int n;
			do
			{
				cout << "\n Please select the record you want to edit: " << endl;
				cin >> n;
			} while (n < 0 or n > temp->contactVector->size()); // constraints on the input

			temp->contactVector->erase(n - 1); // remove the corresponding contact from the vector
		}
	}
	return ptr;
}

#endif