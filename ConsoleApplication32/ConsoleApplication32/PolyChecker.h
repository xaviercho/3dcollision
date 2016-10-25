#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>

class PolyChecker
{
	struct Vector {
		double x, y, z;

		Vector operator-(Vector p) const {
			return Vector{ x - p.x, y - p.y, z - p.z };
		}

		Vector cross(Vector p) const {
			return Vector{
				y * p.z - p.y * z,
				z * p.x - p.z * x,
				x * p.y - p.x * y
			};
		}

		double dot(Vector p) const {
			return x * p.x + y * p.y + z * p.z;
		}

		double norm() const {
			return std::sqrt(x*x + y*y + z*z);
		}
	};

	using Point = Vector;

	struct Face {
		std::vector<Point> v;

		Vector normal() const {
			//assert(v.size() > 2);
			Vector dir1 = v[1] - v[0];
			Vector dir2 = v[2] - v[0];
			Vector n = dir1.cross(dir2);
			double d = n.norm();
			return Vector{ n.x / d, n.y / d, n.z / d };
		}
	};


	//This is the function where the magic happens.

	bool isInConvexPoly(Point const& p, std::vector<Face> const& fs) {
		for (Face const& f : fs) {
			Vector p2f = f.v[0] - p;         // f.v[0] is an arbitrary point on f
			double d = p2f.dot(f.normal());
			d /= p2f.norm();                 // for numeric stability

			constexpr double bound = -1e-15; // use 1e15 to exclude boundaries
			if (d < bound)
				return false;
		}

		return true;
	}

	//This is the only function we need to call.
	//Give it the x,y,z coordinates of the current point, in the check node method.
	//It will return true if the point is inside the polyhedron.

public:
	 bool pointInBounds(double xIn, double yIn, double zIn) {
		//assert(argc == 3 + 1);

		 //Here is a list of all of my Vertices, and their x,y,z coordinates.
		 //The fourth number should be left out.

		 //You will want to replace these/ make as many as you need for your polyhedron.
		 Point point0{ 0.0, 1,  0.0 };
		 Point point1{ -1, -1,  1 };
		 Point point2{ -1, -1,  1};
		 Point point3{ 1, -1,  1 };
		 Point point4{ 1, 1,  1 };
		 Point point5{ 1, 1,  1 };
		 Point point6{ 1, 1,  1 };
		 Point point7{ 1, 1,  1 };
		 Point point8{ 1, 1,  1 };

		char* end;
		Point p;

		p.x = xIn;
		p.y = yIn;
		p.z = zIn;

		//Here, each line describes one "face" of the polyhedron.
		//These are the triangles that make up the mesh.
		//I dont know why, but the fourth point is always ignored,
		//but we only need three points anyways.

		//The pattern goes:
		//Face{{indicesPart1,indicesPart2,indicesPart3, doesn't matter what you put here}},
		//Do this for your whole indices list.

		std::vector<Face> polyhedron{ // faces with 4 points, last point is ignored
			Face{ { point1, point2, point0, point0 } },
			Face{ { point2, point3, point0, point0 } },
			Face{ { point3, point4, point0, point0 } },
			Face{ { point4, point5, point0, point0 } },
			Face{ { point5, point6, point0, point0 } },
			Face{ { point6, point7, point0, point0 } },
			Face{ { point7, point8, point0, point0 } },
			Face{ { point8, point1, point0, point0 } },

			Face{ { point1, point3, point2, point0 } },
			Face{ { point3, point5, point4, point0 } },
			Face{ { point5, point7, point6, point0 } },
			Face{ { point7, point1, point8, point0 } },
		};

		//For whatever reason, my last two triangles broke it if they were included.
		//I think this might be because for my mesh they overlapped.
		//This probably wont be an issue.

		return(isInConvexPoly(p, polyhedron));


		//Now back in your main cpp file, checkNode should look like this:
		/*

		PolyChecker checker;

		//this function will check to see if the node is withing the box
		bool checkNode(struct pointNode * curr, GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, GLfloat zMin, GLfloat zMax)
		{
		return(checker.pointInBounds(curr->x, curr->y, curr->z));
		}

		*/
	}
};



#endif // HEADER_H



