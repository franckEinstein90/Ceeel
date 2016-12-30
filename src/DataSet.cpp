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

void DataSet::insert_left(bt* new_node, bt* tree_head) {
	if (!tree_head->left) {
		tree_head->left = new_node;
	}
}
void DataSet::insert_right(bt* new_node, bt* tree_head) {
}
DataSet::bt* DataSet::find_insert_pt(bt* new_node, bt* tree_head) {
	if (tree_head->x_value < new_node->x_value) {
		insert_right(new_node, tree_head);
		return tree_head;
	}
	if (tree_head->x_value > new_node->x_value) {
		insert_left(new_node, tree_head);
		return tree_head;
	}
}
void DataSet::insert_in_bt(float xval, float yval){
	bt* new_node = new bt(xval, yval);
	if (xy_values == NULL) {
		xy_values = new bt(xval, yval);
		return;
	}
	find_insert_pt(new_node, xy_values);
}

DataSet::DataSet():xy_values(NULL)
{
}


DataSet::~DataSet()
{
}
