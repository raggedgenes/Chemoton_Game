#ifndef RK4ENGINE_H
#define RK4ENGINE_H
/*
 Solver for a system of n first order Ordinary Differential Equations
 (initial value problem)
 Method: calls 4th-order Runge-Kutta
 Can be used for solving a system of n/2 second order ODE

 Demo version for 2D projectile motion
 AG: Last revision October 2009
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include "chemotonbf.h"
#include <SFML/System.hpp>
#include "../observer/eventdispatcher.h"

namespace gt {
class ChemotonBF;
class RK4Engine : public rg::Observer
{
public:
    explicit RK4Engine();
    gt::ChemotonBF *chemoton;
    void simulate();
    sf::Vector2f nextStep(int mit);
    double getValue(int mit);
    virtual void notify(rg::Event e, rg::Subject* caller);
private:
    void oneStep(double* ti, double* dt);
    double reactionODEs(double, double dx[], int n , bool temp);
    bool rk4_dn1(double, double, double [], int);
    double simaDx(double(*)(double, double [], int, bool ), double, double, double [], int);
    int n;
    int downcounter;
    int stepup;
    bool nonsense;
    double prev;
    double* ti;
    double* tf;
    double* dt;
    double dtmax, tmax, out_t;
    ofstream file;
};
}
#endif // RK4ENGINE_H
