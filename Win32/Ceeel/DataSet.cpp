#include "stdafx.h"
#include "DataSet.h"

void DataSet::get_raw_input(string data) {
	x_values.clear();
	y_values.clear();
	stringstream ss(data);
	double x, y;
	while (ss >> x >> y) {
		x_values.push_back(x);
		y_values.push_back(y);
	}
}
DataSet::DataSet()
{
}


DataSet::~DataSet()
{
}
