#include <iostream>
#include <cmath>
#include <string>

double toRadians(double degrees) { return degrees * 3.14159265 / 180.0; }

double toDegrees(double radians) { return radians * 180.0 / 3.14159265; }

double quadraticMinus(double a, double b, double c) { return (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a); }
double quadraticPlus(double a, double b, double c)  { return (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a); }

const double GRAVITY = -9.81;

// SUVAT values = s, u, v, a, t
double u, theta, height, u_horizontal, u_vertical, v_horizontal, v_vertical;

void getInputs() {
	std::cout << "Enter inital velocity of the projectile as it is shot (m/s): ";
	std::cin >> u;
	std::cout << "Enter the angle from the horizontal at which the projectile is shot (degrees): ";
	std::cin >> theta;
	std::cout << "Enter the height from the landing plane (ground) that the projectile is shot from (m): ";
	std::cin >> height;
	u_horizontal = u * cos(toRadians(theta));
	u_vertical = u * sin(toRadians(theta));
}


double findTime() {
	if (quadraticMinus(GRAVITY, (2 * u_vertical), (height * 2)) <= quadraticPlus(GRAVITY, (2 * u_vertical), (height * 2))) {
		return quadraticPlus(GRAVITY, (2 * u_vertical), (height * 2));
	}
	else if (quadraticMinus(GRAVITY, (2 * u_vertical), (height * 2)) >= quadraticPlus(GRAVITY, (2 * u_vertical), (height * 2))) {
		return quadraticMinus(GRAVITY, (2 * u_vertical), (height * 2));
	}
}

void getFinalVelocities() {
	v_horizontal = u_horizontal;
	v_vertical = u_vertical + (GRAVITY * findTime());
}

double getDistanceH() { return u_horizontal * findTime(); }
double getDistanceTotal() {	return sqrt(pow(getDistanceH(), 2) + pow(height, 2)); }
double getFinalVelocity() { return sqrt(pow(v_horizontal, 2) + pow(v_vertical, 2)); }
double findAngleOfGroundCollision() { return abs(toDegrees(atan(v_vertical/v_horizontal))); }

int main() {
	std::cout << "This is a projectile calculator written by GaryTheBlobfish\nThings to take note before using:\n- Air resistance is considered to be negligible so in reality,\nthe calculations done by this calculator are slightly exaggerated\n\n";
	getInputs();
	std::cout << "\ntime in the air: " + std::to_string(findTime()) + " seconds\n\n";
	getFinalVelocities();
	std::cout << "resultant velocity as it hits the ground: " + std::to_string(getFinalVelocity()) + " m/s\n\n";
	std::cout << "angle it hits the ground: " + std::to_string(findAngleOfGroundCollision()) + " degrees\n\n";
	std::cout << "horizontal distance travelled: " + std::to_string(getDistanceH()) + "m\n\n";
	std::cout << "total displacement from start point: " + std::to_string(getDistanceTotal()) + " m\n\n";
	return 0;
}
