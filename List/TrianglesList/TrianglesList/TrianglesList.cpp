// TrianglesList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class NoTrianglesException : public std::exception
{
public:
	NoTrianglesException(const std::string& message) : m_message(message) {}
	const char* what() const noexcept override
	{
		return m_message.c_str();
	}
private:
	std::string m_message;
};

class NoSuchFileException : public std::exception
{
public:
	NoSuchFileException(const std::string& message) : m_message(message) {}
	const char* what() const noexcept override
	{
		return m_message.c_str();
	}
private:
	std::string m_message;
};

struct Triangle {
	double a, b, c;
	double area;

	Triangle(double a_, double b_, double c_) {
		a = a_;
		b = b_;
		c = c_;
		double p = (a + b + c) / 2;
		area = sqrt(p * (p - a) * (p - b) * (p - c));
	}

	bool operator<(const Triangle& other) const {
		return area < other.area;
	}
};

std::vector<Triangle> readTrianglesFromFile(const std::string& filename) {
	std::vector<Triangle> triangles;
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw NoSuchFileException(filename + "was not found.");
	}

	double a, b, c;
	while (file >> a >> b >> c) {
		Triangle t(a, b, c);
		triangles.push_back(t);
	}
	return triangles;
}

void sortTrianglesByArea(vector<Triangle>& triangles) {
	if (triangles.empty()) {
		throw NoTrianglesException("No trinagles provided");
	}
	sort(triangles.begin(), triangles.end());
}

vector<Triangle> filterTrianglesByPerimeter(const vector<Triangle>& triangles, double minPerimeter, double maxPerimeter) {
	vector<Triangle> filteredTriangles;
	if (triangles.empty()) {
		throw NoTrianglesException("No trinagles provided");
	}

	for (const Triangle& t : triangles) {
		double perimeter = t.a + t.b + t.c;
		if (perimeter >= minPerimeter && perimeter <= maxPerimeter) {
			filteredTriangles.push_back(t);
		}
	}
	return filteredTriangles;
}


void writeTrianglesToFile(const vector<Triangle>& triangles, const string& filename)
{
	if (triangles.empty()) {
		throw NoTrianglesException("No trinagles provided to save them to the file");
	}

	ofstream file(filename);

	if (!file.is_open()) {
		throw NoSuchFileException(filename + " was not found.");
	}

	for (const Triangle& t : triangles) {
		file << t.a << " " << t.b << " " << t.c << " " << t.area << endl;
	}
}

int main() {
	string inputFilename = "D:\\triangles.txt";
	string outputFilename1 = "sorted_triangles.txt";
	string outputFilename2 = "filtered_triangles.txt";

	double minPerimeter = 10;
	double maxPerimeter = 20;

	try {
		auto triangles = readTrianglesFromFile(inputFilename);
		sortTrianglesByArea(triangles);
		writeTrianglesToFile(triangles, outputFilename1);
		auto filteredTriangles = filterTrianglesByPerimeter(triangles, minPerimeter, maxPerimeter);
		writeTrianglesToFile(filteredTriangles, outputFilename2);
	}
	catch (NoSuchFileException ex) {
		cout << ex.what();
		return -1;
	}
	catch (NoTrianglesException nex) {
		cout << nex.what();
		return -1;
	}
	

	return 0;
}


