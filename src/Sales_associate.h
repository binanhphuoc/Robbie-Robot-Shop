#ifndef SALES_ASSOCIATE_H
#define SALES_ASSOCIATE_H

#include <string>

using namespace std;

class Sales_associate
{
	string name;
	int employee_number;
	string username;
	string password;
	bool active = false;
	
public:
	Sales_associate(string _name, int _employee_number, string _username, string _password) : name(_name), employee_number(_employee_number), username{_username}, password{_password} {}
	string get_name() {return name;}
	int get_employee_number() {return employee_number;}
	string get_username() {return username;}
	string get_password() {return password;}
	bool get_active() {return active;}
	void set_active(bool val) { active = val; }

};

#endif
