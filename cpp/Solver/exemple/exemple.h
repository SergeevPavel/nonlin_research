/*
 * exemple.h
 *
 *  Created on: Mar 1, 2014
 *      Author: mikhail
 *
 * f1: y' = t
 * f2: y' = 2*y
 * f3: y' = t + y
 * f4: y'' + y - y^3 = 0
 * f5: y'' + y - (1 + 1.3cos(2t))y^3
 * f6: system y[i] = t*y[i+1], dimension = 4
 */

#ifndef EXEMPLE_H_
#define EXEMPLE_H_

#include "RKSolver.h"
#include <initializer_list>

using namespace RKSolver;

Point<1> f1(Point<1> y, double t) {
	Point<1> fy;
	fy[1] = t;
	return fy;
}

Point<1> f2(Point<1> y, double t) {
	Point<1> fy;
	fy = y*2.0;
	return fy;
}
/*
Point<1> f3(Point<1> y, double t) {
	Point<1> fy;
	fy = t + y;
	return fy;
}

Point<2> f4(Point<2> y, double t) {
	Point<2> fy;
	fy[1] = y[2];
	fy[2] = pow(y[1],3) - y[1];
	return fy;
}

Point<2> f5(Point<2> y, double t) {
	Point<2> fy;
	fy[1] = y[2];
	fy[2] = (1 + 1.3*cos(2*t)) * pow(y[1],3) - y[1];
	return fy;
}

Point<4> f6(Point<4> y, double t) {
	Point<4> fy;
	fy[1] = t*y[2];
	fy[2] = t*y[3];
	fy[3] = t*y[4];
	fy[4] = t*y[5];
	return fy;
}*/

#endif /* EXEMPLE_H_ */
