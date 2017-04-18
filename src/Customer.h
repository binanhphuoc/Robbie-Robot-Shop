#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer
{
	string name;
	int customer_number;
	string phone_number;
	string email_address;
public:
	Customer(string _name, int _customer_number, string _phone_number, string _email_address) : name{_name}, customer_number{_customer_number}, phone_number{_phone_number}, email_address{_email_address} {}
	string get_name() {return name;}
	int get_customer_number() {return customer_number;}
	string get_phone_number() {return phone_number;}
	string get_email_address() {return email_address;}
};

#endif

