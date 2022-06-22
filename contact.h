#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
using namespace std;

template <class T>
class MyVector;

//Declaring and defining the Contact class
class Contact
{
private:
	string fname;
	string lname;
	string email;
	string primaryPhone;
	string city;
	string country;
	bool isFav;

public:
	Contact() {} //default constructor
	Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav) //non-default constructor
	{
		this->fname = fname;
		this->city = city;
		this->country = country;
		this->email = email;
		this->isFav = isFav;
		this->lname = lname;
		this->primaryPhone = primaryPhone;
	}
	bool setFav() { isFav = true; } //setter
	bool removeFav() { isFav = false; } 
	string getfname() { return fname; } //getter

	//friend classes
	friend class Node;
	friend class ContactBST;
	template <typename T>
	friend class MyVector;
};

#endif