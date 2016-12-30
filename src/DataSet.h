#pragma once

#include <string> 
#include <vector>
#include <sstream>


#include "lapacke.h"


using namespace std;
class DataSet
{

	class bt {
	public:
		bt* left;
		bt* right;
		float x_value;
		float y_value;
		bt(float x, float y) :x_value(x), y_value(y), 
													left(NULL), right(NULL){}
	};
	bt* xy_values;
	void insert_right(bt*, bt*);
	void insert_left(bt*, bt*);
	bt* find_insert_pt(bt*, bt*);
	void insert_in_bt(float xval, float yval);
	
public:
	vector<double> x_values;
	vector<double> y_values;


public:
	DataSet();
	~DataSet();
	void get_raw_input(string);
};

