#pragma once

#include <string> 
#include <vector>
#include <sstream>
#include <tuple>

#include "lapacke.h"


using namespace std;

class DataSet;
class Line {
	double x_0;
	double slope;
	public:
		Line(double x=0.0, double s=0.0):x_0(x), slope(s) {};
		DataSet* to_DataSet(const vector<double>& points);
};

class DataSet_Error {
protected:
	string m_error_description;
public:
	DataSet_Error(const string& e_d):m_error_description(e_d) {

	}
};
//DataSet holds data points in 
//1, 2, or 3 dimensions. 
class DataSet
{
protected:
	size_t m_dimension;

protected:  //values
	vector<double> x_values;
	vector<double> y_values;
	vector<double> z_values;

protected: //operations
	Line* linear_regression();
	
public:
	DataSet();
	~DataSet();
	void get_raw_input(string, size_t);
	size_t size()const {
		return x_values.size();
	}
public:
	tuple<double, double, double> operator[](size_t)const;
	
};

