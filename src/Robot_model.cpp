#include "Robot_part.h"
#include "Robot_model.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

Robot_model::Robot_model(string _name, int _model_number, string _image_filename, double _price)
{
	name = _name;
	model_number = _model_number;
	image_filename = _image_filename;
	price = _price;
}

void Robot_model::attach_torso(Robot_part* _torso)
{
	torso = _torso;
}

void Robot_model::attach_head(Robot_part* _head)
{
	head = _head;
}

void Robot_model::attach_locomotor(Robot_part* _locomotor)
{
	locomotor = _locomotor;
}

int Robot_model::attach_arm(Robot_part* _arm)
{
	//if (torso == NULL)
	//	return 1;	
	//if (arm.size() < torso->get_max_arms())
		arm.push_back(_arm);
	//else
	//	return 2;
	return 0;
}

int Robot_model::attach_battery(Robot_part* _battery)
{
	if (torso == NULL)
		return 1;
	if (battery.size() < torso->get_battery_compartments())
		battery.push_back(_battery);
	else
		return 2;
	return 0;
}

string Robot_model::get_name()
{
	return name;
}

int Robot_model::get_model_number()
{
	return model_number;
}

string Robot_model::get_image_filename()
{
	return image_filename;
}


double Robot_model::get_price()
{
	return price;
}

double Robot_model::cost()
{
	double total_cost = torso->get_cost() + head->get_cost() + locomotor->get_cost();
	int i;	
	for (i = 0; i < arm.size(); i++)
		total_cost += arm.at(i)->get_cost();
	for (i = 0; i < battery.size(); i++)
		total_cost += battery.at(i)->get_cost();
	return total_cost;
}

double Robot_model::weight()
{
	double weight =  torso->get_weight() + head->get_weight() + locomotor->get_weight();
	int i;	
	for (i = 0; i < arm.size(); i++)
		weight+= arm.at(i)->get_weight();
	for (i = 0; i < battery.size(); i++)
		weight+= battery.at(i)->get_weight();
	return weight;
}

double Robot_model::max_speed()
{
	if (weight() < locomotor->get_weight() * 5)
		return locomotor->get_max_speed();
	else
		return locomotor->get_max_speed() * ( (locomotor->get_weight() * 5) / weight() );
}

double Robot_model::max_battery_life()
{
	double battery_life = 0;
	double max_energy = 0;
	for (int i = 0; i < battery.size(); i++)
		max_energy += battery.at(i)->get_max_energy();
	double ave_power_consumption = head->get_power() + 0.4*(arm.at(0)->get_power() + arm.at(1)->get_power() ) + 0.15 * locomotor->get_power();
	battery_life = max_energy * 1000 / ave_power_consumption;
	return battery_life;
}

Robot_part* Robot_model::get_arm(int i)
{
	return arm.at(i);
}

Robot_part* Robot_model::get_torso()
{
	return torso;
}
Robot_part* Robot_model::get_head()
{
	return head;
}

Robot_part* Robot_model::get_locomotor()
{
	return locomotor;
}

Robot_part* Robot_model::get_battery(int i)
{
	return battery.at(i);
}

Robot_part* Robot_model::get_part(part_t p, int i)
{
	if (p == ARM)
		return get_arm(i);
	if (p == TORSO)
		return get_torso();
	if (p == HEAD)
		return get_head();
	if (p == LOCOMOTOR)
		return get_locomotor();
	if (p == BATTERY)
		return get_battery(i);
}

bool Robot_model::power_limited()
{
	double power_consumption = head->get_power() + locomotor->get_power();
	for (int i = 0; i < 2; i++)
	{
		power_consumption += arm.at(i)->get_power();
	}
	double battery_power = 0;
	for (int i = 0; i < battery.size(); i++)
	{
		battery_power += battery.at(i)->get_power();
	}
	if (power_consumption > battery_power)
		return true;
	else
		return false;
}

void Robot_model::save(ofstream& ost, vector<int> var)
{
	ost << name << endl;
	ost << model_number << endl;
	ost << image_filename << endl;
	ost << price << endl;
	for (int i = 0; i < var.size(); i++)
		ost << var.at(i) << endl;
}
