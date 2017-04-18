#ifndef ROBOT_PART_H
#define ROBOT_PART_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

enum part_t{HEAD, ARM, LOCOMOTOR, BATTERY, TORSO};

class Robot_part
{
private:
	part_t part; 	
	string name;
	int model_number = -1;
	double cost = 0;
	double weight = 0;
	string description;
	string image_filename;
public:
	Robot_part(part_t _part, string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename) : part{_part}, name{_name}, model_number{_model_number}, cost{_cost}, weight{_weight}, description{_description}, image_filename{_image_filename} {}
	Robot_part() {}
	part_t get_part() {return part;}
	void set_part(part_t p) {part = p;}
	string get_name() {return name;}
	int get_model_number() {return model_number;}
	double get_cost() {return cost;}
	double get_weight() {return weight;}
	string get_description() {return description;}
	string get_image_filename() {return image_filename;}
	virtual double get_power() {return 0;}
	virtual double get_max_energy() {return 0;}
	virtual double get_max_speed() {return 0;}
	virtual int get_battery_compartments() {return 0;}
	//virtual int get_max_arms() {return 0;}
	
	void save_part(ofstream& ost)
	{
		ost << (int) part << endl; 	
		ost << name << endl;
		ost << model_number << endl;
		ost << cost << endl;
		ost << weight << endl;
		ost << description << endl;
		ost << image_filename << endl;
	}
	virtual void save(ofstream& ost) {}
	void load(ifstream& ist)
	{
		string str;
		getline(ist, name);
		ist >> model_number; getline(ist, str);
		ist >> cost; getline(ist, str);
		ist >> weight; getline(ist, str);
		getline(ist, description);
		getline(ist, image_filename);
	}
	
};

class Arm : public Robot_part
{
private:	
	double max_power;
public:
	Arm(string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename, double _max_power) : Robot_part(ARM, _name, _model_number, _cost, _weight, _description, _image_filename) 
	{
		max_power = _max_power;
	}
	
	Arm(ifstream& ist)
	{
		set_part(ARM);
		string str;
		load(ist);
		ist >> max_power; getline(ist, str);
	}
	double get_power() {return max_power;}
	void save(ofstream& ost) 
	{
		save_part(ost);
		ost << max_power << endl;
	}
};

class Head : public Robot_part
{
private:
	double power;
public:
	Head(string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename, double _power) : Robot_part(HEAD, _name, _model_number, _cost, _weight, _description, _image_filename) 
	{
		power = _power;
	}
	Head(ifstream& ist)
	{
		set_part(HEAD);
		string str;
		load(ist);
		ist >> power; getline(ist, str);
	}
	double get_power() {return power;}
	void save(ofstream& ost) 
	{
		save_part(ost);
		ost << power << endl;
	}
};

class Battery : public Robot_part
{
private:
	double max_energy;
	double power_available;
public:
	Battery(string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename, double _max_energy, double _power_available) : Robot_part(BATTERY, _name, _model_number, _cost, _weight, _description, _image_filename) 
	{
		max_energy = _max_energy;
		power_available = _power_available;
	}
	
	Battery(ifstream& ist)
	{
		set_part(BATTERY);
		string str;
		load(ist);
		ist >> max_energy; getline(ist, str);
	}
	double get_max_energy() {return max_energy;}
	double get_power() {return power_available;}
	void save(ofstream& ost) 
	{
		save_part(ost);
		ost << max_energy << endl;
	}
};

class Locomotor : public Robot_part
{
private:
	double max_speed;
	double max_power;
public:
	Locomotor(string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename, double _max_power, double _max_speed) : Robot_part(LOCOMOTOR, _name, _model_number, _cost, _weight, _description, _image_filename) 
	{
		max_power = _max_power;
		max_speed = _max_speed;
	}
	Locomotor(ifstream& ist)
	{
		set_part(LOCOMOTOR);
		string str;
		load(ist);
		ist >> max_speed; getline(ist, str);
		ist >> max_power; getline(ist, str);
	}
	double get_max_speed() {return max_speed;}
	double get_power() {return max_power;}
	void save(ofstream& ost) 
	{
		save_part(ost);
		ost << max_speed << endl;
		ost << max_power << endl;
	}
};

class Torso : public Robot_part
{
private:
	int battery_compartments;
	//int max_arms;
public:
	Torso(string _name, int _model_number, double _cost, double _weight, string _description, string _image_filename, int _battery_compartments/*, int _max_arms*/) : Robot_part(TORSO, _name, _model_number, _cost, _weight, _description, _image_filename) 
	{
		battery_compartments = _battery_compartments;
		//max_arms = _max_arms;
	}
	Torso(ifstream& ist)
	{
		set_part(TORSO);
		string str;
		load(ist);
		ist >> battery_compartments; getline(ist, str);
	}
	int get_battery_compartments() {return battery_compartments;}
	//int get_max_arms() {return max_arms;}
	void save(ofstream& ost) 
	{
		save_part(ost);
		ost << battery_compartments << endl;
	}
};
#endif
