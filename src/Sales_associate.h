#ifndef SALES_ASSOCIATE_H
#define SALES_ASSOCIATE_H

#include <string>

using namespace std;

class Sales_associate
{
	string name;
	int employee_number;
	
public:
	Sales_associate(string _name, int _employee_number) : name(_name), employee_number(_employee_number) {}
	string get_name() {return name;}
	int get_employee_number() {return employee_number;}
};

#endif
