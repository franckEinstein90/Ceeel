#include "stdafx.h"
#include "VisualObject.h"

#include <glm/vec3.hpp>
using namespace glm;

#include <vector>
#include <fstream>
#include <string>
using namespace std;

#include "DataSet.h"


PointCloud::PointCloud(istream& is) {

}

PointCloud2D::PointCloud2D(DataSet& ds) {
	for (int i = 0; i < ds.x_values.size(); i++) {
		vec3 new_data_point;
		new_data_point.x = ds.x_values[i];
		new_data_point.y = ds.y_values[i];
		new_data_point.z = 0.0;
	}

}
void PointCloud2D::draw() {

}
Mesh::Triangle::Triangle(vector<string> params) :
	point_indices(3),
	normal_indices(3) {
	for (int i = 0; i < params.size(); i++) {

		int pos_of_dash = params[i].find("//");
		params[i].replace(pos_of_dash, 2, " ");
		istringstream s(data(params[i]));
		s >> point_indices[i] >> normal_indices[i];
		point_indices[i]--; normal_indices[i]--;
	}
}

void Mesh::Triangle::draw(vector<glm::vec3>& vertices, vector<glm::vec3>& normals) {
	for (auto ver : point_indices) {
		glm::vec3 point = vertices[ver];
		glVertex3f(point.x, point.y, point.z);
	}
}
void Mesh::read_vertex_data(const string& is) {
	istringstream s(is);
	glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
	vertices.push_back(v);
}
void Mesh::read_face_data(const string& is) {
	istringstream s(is);
	vector<string> parameters(3);
	s >> parameters[0] >> parameters[1] >> parameters[2];
	Mesh::Triangle t(parameters);
	this->triangles.push_back(t);
}
void Mesh::read_normal_data(const string& is) {
	istringstream s(is);
	glm::vec3 v; s >> v.x >> v.y >> v.z;
	normals.push_back(v);
}
void Mesh::read_from_obj_file(const string& file_name) {
	ifstream infile(file_name);
	string info_package;
	//infile.open(file_name);
	if (!infile) {
		AfxMessageBox(_T("unable to open model input file"));
	}
	while (getline(infile, info_package)) {
		if (info_package.substr(0, 2) == "v ")
		{
			read_vertex_data(info_package.substr(2));
		}
		else if (info_package.substr(0, 2) == "f ")
		{
			read_face_data(info_package.substr(2));
		}
		else if (info_package.substr(0, 2) == "vn") {
			read_normal_data(info_package.substr(3));
		}
		else if (info_package[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}
}

void Mesh::draw() {

	glBegin(GL_TRIANGLES);
	glColor3f(TOKEN_COLOR);
	for (auto t : triangles) {
		t.draw(this->vertices, this->normals);
	}
	glEnd();
}


VisualObject::VisualObject()
{
}


VisualObject::~VisualObject()
{
}
