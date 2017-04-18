#include "Robot_part.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	Robot_part* current;

	ifstream ist{"test_data.txt"};
	
	int p;
	ist >> p;
	while(p != -1)
	{
		ostringstream oss;

		string temp, str;
		part_t part; getline(ist, temp);
		
		string name; getline(ist, name);

		int model_number;
		ist >> model_number; getline(ist, temp);
	
		double cost;
		ist >> cost; getline(ist, temp);
	
		double weight = 0;
		/*ist >> weight; getline(ist, temp);*/

		string description; getline(ist, description);
		
		part = (part_t) p;
		if (part == ARM)
		{
			double max_power;
			ist >> max_power; getline(ist, temp);
			current = new Arm(name, model_number, cost, weight, description, "", max_power);
			oss << "Arm " << current->get_name() << " (model " << current->get_model_number() << ") "
      << "costs $" << current->get_cost() 
      << " and uses " << current->get_power() << " watts";
		}
		else if (part == HEAD)
		{
			double power;
			ist >> power; getline(ist, temp);
			current = new Head(name, model_number, cost, weight, description, "", power);
			oss << "Head " << current->get_name() << " (model " << current->get_model_number() << ") "
      << "costs $" << current->get_cost() 
      << " and uses " << current->get_power() << " watts";
		}
		else if (part == BATTERY)
		{
			double energy, power;
			ist >> energy; getline(ist, temp);
			ist >> power; getline(ist, temp);
			current = new Battery(name, model_number, cost, weight, description, "", energy, power);
			oss << "Battery " << current->get_name() << " (model " << current->get_model_number() << ") "
      << "costs $" << current->get_cost() 
      << " and energy " << current->get_max_energy() << " and uses " << current->get_power() << " watts";
		}
		else if (part == LOCOMOTOR)
		{
			double power,speed;
			ist >> power; getline(ist, temp);
			ist >> speed; getline(ist, temp);
			current = new Locomotor(name, model_number, cost, weight, description, "", power, speed);
			oss << "Locomotor " << current->get_name() << " (model " << current->get_model_number() << ") "
      << "costs $" << current->get_cost() 
      << " and speed " << current->get_max_speed() <<" and uses " << current->get_power() << " watts";
		}
		else if (part == TORSO)
		{
			int compartments;
			ist >> compartments; getline(ist, temp);
			current = new Torso(name, model_number, cost, weight, description, "", compartments);
			oss << "Torso " << current->get_name() << " (model " << current->get_model_number() << ") "
      << "costs $" << current->get_cost() 
      << " and compartments " << current->get_battery_compartments() << " watts";
		}
		
		if (oss.str() != current->get_description())
			cerr << "FAIL PART " << p << endl;
		delete current;
		ist >> p;
	}
	return 0;
}
