#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

#include "canvas.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "cube.hpp"
#include "triangle.hpp"

/*
#define FP_X( x ) (round((x + 1) * (W_WIDTH)  / 2 - 1))
#define FP_Y( y ) (round((y + 1) * (W_HEIGHT) / 2 - 1))
#define PF_X( x ) (-1 + ((float) 2 * (x) + 1) / (W_WIDTH))
#define PF_Y( y ) (-1 + ((float) 2 * (W_HEIGHT - 1 - y) + 1) / (W_HEIGHT))
*/

/*class Rect
{
	int left_, low_, width_, height_;
public:
	Rect(int left, int low, int width, int height)
	: left_  (left)
	, low_   (low)
	, width_ (width)
	, height_(height)
	{ }
	
	void Draw(Canvas &canvas) const {
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				canvas[low_ + y][left_ + x] = col_red;
			}
		}
	}
};*/

int main() {
	Canvas canvas = Canvas(1920, 1080);
	
	float cube_arr[8][3] = {
		{-1,-1,-1},
		{-1, 1,-1},
		{ 1, 1,-1},
		{ 1,-1,-1},
		
		{-1,-1, 1},
		{-1, 1, 1},
		{ 1, 1, 1},
		{ 1,-1, 1}};
	Cube cube = Cube(cube_arr);
	//Cube cube2 = Cube(cube_arr);
	Vector3f c = Vector3f(.1, .1, .1, col_red);
	//cube.setCenter(c);
	
	Vector3f a = Vector3f(.0, .0, .1, col_white);
	Vector3f b = Vector3f(.0, .1, .1, col_green);
	Triangle triangle = Triangle(a, b, c);
	
	Matrix3f m  = Matrix3f(0, 0);
	//Matrix3f m2  = Matrix3f(0, 0);
	
	int mouse_fd = open("/dev/input/mice", O_RDWR | O_NONBLOCK);
	signed char mouse_data[3];
	
	Vector3f up = Vector3f(0, 1, 0);
	while(1) {
		float F = 0.00, T = 0.00;
		if (read(mouse_fd, mouse_data, sizeof(mouse_data)) > 0) {
			F = -0.01 * (signed char) mouse_data[1];
			T = -0.01 * (signed char) mouse_data[2];
		}
		
		float arr[3][3] = {{},{},{}};
		{
			float sF = sin(F),
				cF = cos(F);
			float sT = sin(T),
				cT = cos(T);
				
			Vector3f e3 = {cT * sF, sT, cT * cF};
			Vector3f e1 = up * e3;
			e1 /= e1.len();
			Vector3f e2 = e3 * e1;
			
			for(int i = 0; i < 3; i++) arr[0][i] = e1[i];
			for(int i = 0; i < 3; i++) arr[1][i] = e2[i];
			for(int i = 0; i < 3; i++) arr[2][i] = e3[i];
		}
		m = Matrix3f(arr);
		m.Transpose();
		
		up *= m;
		
		canvas.Rotate(m);
		cube.Rotate(m);
		//cube2.Rotate(m2);
		//triangle.Rotate(m);
		
		canvas.Clear();
		
		canvas.DrawChords();
		//canvas.DrawZoX();
		cube.Draw(canvas);
		//cube2.Draw(canvas);
		//triangle.Draw(canvas);
		
		canvas.Display();
	}
	
	return 0;
}
