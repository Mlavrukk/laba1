#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#pragma warning(disable : 4996)
using namespace std;

struct point {
	double x, y;
	point() {
		x = 0;
		y = 0;
	}
	point(double _x, double _y) {
		x = _x;
		y = _y;
	}
	point(const point& p) {
		x = p.x;
		y = p.y;
	}
	friend ostream& operator<<(ostream& os, const point& rhs)
	{
		os << "point: (" << rhs.x << "," << rhs.y << ")" << endl;
		return os;
	}
};

class Lines {
	point* data = nullptr;
	int size;
	double Eps=0;
public:
	Lines() {
		size = 1;
		data = new point[size];
		data[0] = point(0, 0);
	}

	Lines(int _size) {
		if (_size < 1) throw exception("Invalid syntaxis");
		size = _size;
		data = new point[size];
		for (size_t i = 0; i < size; i++)
		{
			cout << "[" << i << "]: x=";
			double _x=0, _y=0;
			cin >> _x;
			cout << "y=";
			cin >> _y;
			data[i] = point(_x, _y);
		}
	}
	
	Lines(const Lines& l) {
		size = l.size;
		data = new point[size];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = l.data[i];
		}
	}

	Lines(const point& p) {
		size = 1;
		data = new point[size];
		data[0] = p;
	}

	Lines(double _x,double _y) {
		size = 1;
		data = new point[size];
		data[0] = point(_x,_y);
	}

	~Lines() {
		delete[] data;
		data = nullptr;
	}

	int get_size() const {
		return size;
	}

	point& operator[](int i) {
		if (i >= size and i < 0) {
			throw "Invalid index";
		}
		return data[i];
	}

	friend ostream& operator<<(ostream& os, const Lines& rhs)
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
		{
			throw exception("Error init");
		}

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			throw exception("Error create window");
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBegin(GL_LINE_STRIP);
			for (size_t i = 0; i < rhs.size; i++)
			{
				glVertex2f(rhs.data[i].x, rhs.data[i].y);
			}
			glEnd();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();
		os << endl;
		return os;
	}

	Lines& operator+=(const Lines& l) {
		point* temp = new point[l.size + size];

		for (int i = 0; i < size; ++i)
		{	
			temp[i] = data[i];
		}

		for (int i = size; i < l.size+size; ++i)
		{
			temp[i] = l.data[i - size];
		}

		size += l.size;
		delete[] data;

		data = temp;
		return *this;
	}

	Lines operator+(const Lines& l) const {
		Lines temp(*this);
		temp += l;
		return temp;
	}

	Lines& operator+=(const point& p) {
		point* temp = new point[size + 1];
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}

		temp[size++] = p;

		delete[] data;
		data = temp;

		return *this;
	}

	Lines operator+(const point& p) const {
		Lines temp(*this);
		temp += p;
		return temp;
	}

	friend Lines operator+(const point& p, const Lines& l) {
		Lines temp(p);
		temp += l;
		return temp;
	}

	bool operator==(const Lines& l) {
		if (l.size != size) {
			return false;
		}
		else {
			cout << "Enter the accuracy: ";
			cin >> Eps;
			for (size_t j = 0; j < size; j++)
			{
				if (fabs(data[j].x - l.data[j].x) > Eps or fabs(data[j].y - l.data[j].y) > Eps) {
					return false;
				}
			}
			return true;
		}
	}
	bool operator!=(const Lines& l) {
		return !(*this == l);
	}

	double length() const {
		double len = 0;
		for (size_t i = 0; i < size-1; i++)
		{
			len += pow(pow(data[i + 1].x - data[i].x, 2) + pow(data[i + 1].y - data[i].y, 2), 0.5);
		}
		return len;
	}
};