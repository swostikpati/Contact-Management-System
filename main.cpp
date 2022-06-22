//=================================================================================
// Name         : DS Assignment#3
// Author       : Swostik Pati
// Version      : 1.0
// Date Created : 10-03-2022
// Date Modified:
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include <iostream>
#include <cstdlib>
#include <sstream>

#include "contact.h"
#include "contactbst.h"
#include "myvector.h"
using namespace std;

//==========================================================
void listCommands() // reference lab9 - code to print menu
{
	cout << "----------------------------------" << endl;
	cout << "import <path>      :Import contacts from a CSV file" << endl
		 << "export <path>      :Export contacts to a CSV file" << endl
		 << "add                :Add a new contact" << endl
		 << "edit <key>         :Update a contact's details" << endl
		 << "del <key>          :Delete a contact" << endl
		 << "searchFor <key>    :Search for a contact" << endl
		 << "markfv <key>       :Mark as favourite" << endl
		 << "umarkfv <key>      :Unmark as favourite" << endl
		 << "printASC           :Print contacts in ascending order" << endl
		 << "printDES           :Print contacts in descending order" << endl
		 << "printfv            :Print all favourite contacts" << endl
		 << "help               :Display the available commands" << endl
		 << "exit               :Exit the program" << endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
	ContactBST myContactBST;		 // initiated the binary search tree
	string user_input, command, key; // variables to store user input

	while (true)
	{
		listCommands();
		cout << ">";
		getline(cin, user_input);

		// parse userinput into command and key
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, key);
		Node *root = myContactBST.getRoot(); // getting the root of the binary search tree
		cout << "----------------------------------" << endl;

		if (command == "import") // checks if import function has to be called
		{
			int temp = myContactBST.importCSV(root, key); // calls the importCSV function to take input from the files
			if (temp == -1)
			{
				cout << "No records could be imported" << endl;
			}
			else
			{
				cout << "The number of records imported are: " << temp << endl; // prints the total number of records imported
			}
		}

		else if (command == "export") // checks if the export function has to be called
		{
			int temp = myContactBST.exportCSV(root, key); // calls the exportCSV function to save the data into the files
			if (temp == -1)
			{
				cout << "No records could be imported" << endl;
			}
			else
			{
				cout << "The number of records exported are: " << temp << endl; // prints the total number of records exported
			}
		}

		else if (command == "add") // checks if a record has to be added
		{
			cout << "Please enter the details of the contact:" << endl; // takes the details as input from the user
			string fn, ln, em, pp, city, country;
			bool fav;
			cout << "First Name: ";
			cin >> fn;
			cout << "\nLast Name: ";
			cin >> ln;
			cout << "\nEmail: ";
			cin >> em;
			cout << "\nPhone Number: ";
			cin >> pp;
			cout << "\nCity: ";
			cin >> city;
			cout << "\nCountry: ";
			cin >> country;
			char c;
			do
			{
				cout << "\nDo you want to add the contact in your favorites?[y/n]" << endl; // asks user if they want to set the contact as favorite
				cin >> c;
			} while (tolower(c) != 'y' and tolower(c) != 'n'); // verifies the input

			if (tolower(c) == 'n')
			{
				fav = false;
			}
			else
			{
				fav = true;
			}

			Contact *temp = new Contact(fn, ln, em, pp, city, country, fav); // creates a contact object in the dynamic memory
			string k = (fn + " " + ln);										 // stores the key
			myContactBST.insert_helper(k, temp);							 // calls the insert_helper function to insert the object into the tree
		}

		else if (command == "edit") // checks if the user edit contact details
		{
			Node *temp = myContactBST.update(root, key); // calls the update function
		}

		else if (command == "del") // checks if the user wants to delete a contact
		{
			myContactBST.remove_helper(key); // calls the remove_helper function
		}

		else if (command == "searchFor") // checks if the user wants to search a contact
		{
			Node *temp = myContactBST.search(root, key); // calls the search function to find if the node exists
			if (temp != nullptr)
			{
				cout << "Records Found:" << endl;
				myContactBST.printNode(temp); // calls the printNode function to print the details of the node
			}
			else
			{
				cout << "No records Found" << endl; // if the node is not found
			}
		}
		else if (command == "markfv") // checks if the user wants to mark a contact as fav
		{
			bool temp = myContactBST.markFav(root, key); // calls the markFav function
			if (temp)
			{
				cout << "The contact is marked as favorite succesfully." << endl;
			}
		}
		else if (command == "umarkfv") // checks if the user wants to unmark a fav contact
		{
			bool temp = myContactBST.unmarkFav(root, key); // calls the unmarkfv function
			if (temp)
			{
				cout << "The contact is unmarked as favority succesfully." << endl;
			}
		}
		else if (command == "printASC") // checks if the user wants to print the records in ascending order
		{
			if (root == nullptr) // checks if there are no contacts in the tree
			{
				cout << "No Records Found" << endl;
			}

			myContactBST.printASC(root); // calls the printASC function
		}
		else if (command == "printDES") // checks if the user wants to print the records in descending order
		{
			if (root == nullptr) // checks if there are no contacts in the tree
			{
				cout << "No Records Found" << endl;
			}
			myContactBST.printDES(root); // calls the printDES function
		}
		else if (command == "printfv") // checks if the user wants to  print all the fav contacts
		{
			myContactBST.printFav(root); // calls the printFav function
		}
		else if (command == "help") // checks if the user wants to view the menu again
		{
			listCommands(); // calls the function to list all the commands again
		}
		else if (command == "exit") // checks if the user wants to exit from this function
		{
			cout << "Thank you Exited!" << endl;
			return 0;
		}
		else
		{
			cout << "Error! Please enter a valid input" << endl;
		}
	}

	cout << "Okay" << endl;

	return 0;
}