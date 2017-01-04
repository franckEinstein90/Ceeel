#include "stdafx.h"
#include "DataSet.h"


void DataSet::get_raw_input(string data, size_t dimension) {
	if (dimension < 1 || dimension > 3) {
		throw DataSet_Error("Bad Dimension Specification");
	}
	this->m_dimentions = dimension;
	
	x_values.clear();
	y_values.clear();
	z_values.clear();
	stringstream ss(data);
	double x, y, z;
	while (ss.good()) {
		ss >> x;
		x_values.push_back(x);
		if (dimension > 1) {
			ss >> y;
			y_values.push_back(y);
		}
		else {
			y_values.push_back(0.0);
		}
		if (dimension > 2) {
			ss >> z;
			z_values.push_back(z);
		}
		else {
			z_values.push_back(0.0);
		}
	}
}

tuple<double, double, double> DataSet::operator[](size_t idx) const {
	if (idx < 0) {
		throw DataSet_Error("Bad size index");
	}
	return make_tuple(x_values[idx], y_values[idx], z_values[idx]);
}
DataSet::DataSet()
{
}


DataSet::~DataSet()
{
}
