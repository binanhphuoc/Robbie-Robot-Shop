#ifndef UTILITY_H
#define UTILITY_H

#include "View.h"
#include <string>
#include <vector>

using namespace std;

enum Object{PART, MODEL, SA, BC, ORDER, NONE};

class Utility
{
public:
	static int get_cmd(Menu menu, string prompt = "", string title = "");
	static bool valid_cmd(string choice, int min, int max, int& ch);
	static bool valid_int_input(string input, int& ch);
	static bool valid_double_input(string input, double& ch);
	static bool valid_input(vector<string> input, Object o, void* p = NULL);
	static bool valid_input_part(vector<string> input, part_t p, vector<double>& output);	

	static string get_string_input(string prompt);
	static int get_int_input(string prompt, int min = -1, int max = -1);
	static double get_double_input(string prompt);
	static bool isDigit(char c);
};

#endif
