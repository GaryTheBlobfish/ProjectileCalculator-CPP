#include <iostream>
#include "Calculator.h"
#include <vector>
#include "vendor/pbPlots.hpp"
#include "vendor/supportLib.hpp"
#include <algorithm>

double findYCoord(double t) {
	double y;
	// s = ut + 1/2 at^2
	y = (u_vertical * t) + (0.5 * GRAVITY * pow(t, 2));
	y += height;
	return y;
}

double findXCoord(double t) {
	double x;
	// s = ut + 1/2 at^2
	x = (u_horizontal * t);
	return x;
}

double roundUp1dp(double d) {
	return std::ceil(d * 10) / 10.0;
}


int main() {
	getInputs();

	std::vector<double> ys;
	std::vector<double> xs;

	for (double t = 0.0; t < roundUp1dp(findTime()); t += 0.1) {
		ys.push_back(findYCoord(t));
		xs.push_back(findXCoord(t));
	}

	double y_range = getMaxHeight();
	double x_range = getDistanceH();
	double aspect = double(x_range) / double(y_range);
	int resx = 720;
	int resy = int(resx * aspect);

	RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();
	DrawScatterPlot(imageRef, resy, resx, &xs, &ys);
	std::vector <double >* pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "trajectory.png");
	DeleteImage(imageRef->image);


	return 0;
}
