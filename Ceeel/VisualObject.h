#pragma once

#include <glm/vec3.hpp>
using namespace glm;

#include <vector>
#include <string>
using namespace std;

#include "DataSet.h"
class VisualObject
{
protected:
	vector<vec3> vertices;
public:
	VisualObject();
	~VisualObject();

	virtual void draw() = 0;
};


class PointCloud : VisualObject {
public:
	PointCloud(istream&);
};

class PointCloud2D : VisualObject {
public:
	PointCloud2D(DataSet&);
	void draw();
};

class Mesh : VisualObject{
protected:
	class Triangle {
	public:
		//first element is the index of the vertex in the parent vector
		//second elmt is the idx o the normal in the parent's normal vector
		vector<int> point_indices;
		vector<int> normal_indices;
		void draw(vector<vec3>&, vector<vec3>&);
		Triangle(vector<string>);
	};
protected:
	void read_vertex_data(const string&);
	void read_face_data(const string&);
	void read_normal_data(const string&);
public:
	vector<vec3> normals;
	vector<Triangle> triangles;
	void draw();
	void read_from_obj_file(const string&);
};

