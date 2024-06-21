#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace P6 {
	class MyVector {
		public:
			float x, y, z;
			MyVector() : x(0), y(0), z(0){}
			MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
			explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

		public:
			void operator+= (const MyVector v);
			MyVector operator+ (const MyVector v); // Addition
			MyVector operator- (const MyVector v); // Subtraction
			MyVector operator/ (const float v); // Division
			MyVector operator* (const MyVector v); // Component Product
			MyVector operator* (const float scalarMul); // Scalar Multiplication
			float dotProduct(const MyVector v); // Dot Product
			MyVector vectorProduct(const MyVector v); // Vector Product
			float magnitude(); // Magnitude
			MyVector normalize(); // Direction
	};
}