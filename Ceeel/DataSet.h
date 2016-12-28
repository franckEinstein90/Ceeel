#pragma once

#include <string> 
#include <vector>
#include <sstream>

using namespace std;
class DataSet
{
public:
	vector<double> x_values;
	vector<double> y_values;
public:
	DataSet();
	~DataSet();
	void get_raw_input(string);
};

