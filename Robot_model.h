#ifndef ROBOT_MODEL_H
#define ROBOT_MODEL_H

#include "Robot_part.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Robot_model
{
	string name = "";
	int model_number = -1;
	double price = 0;
	Robot_part* torso = NULL;
	Robot_part* head = NULL;
	Robot_part* locomotor = NULL;
	vector<Robot_part*> arm;
	vector<Robot_part*> battery;
public:
	Robot_model(string _name, int _model_number, double _price);
	void attach_torso(Robot_part* _torso);
	void attach_head(Robot_part* _head);
	void attach_locomotor(Robot_part* _locomotor);
	int attach_arm(Robot_part* _arm);
	int attach_battery(Robot_part* _battery);
	string get_name();
	Robot_part* get_torso();
	Robot_part* get_head();
	Robot_part* get_locomotor();
	Robot_part* get_battery(int i);
	Robot_part* get_arm(int i);
	Robot_part* get_part(part_t p, int i = 0);
	int get_model_number();
	double get_price();
	double cost();
	double weight();
	double max_speed();
	double max_battery_life();
	void save(ofstream& ost, vector<int> var);
};

#endif
