#ifndef RUNGEKUTTAENGINE_H
#define RUNGEKUTTAENGINE_H

#include "SFML/Graphics.hpp"
#include "diffusion_simulator.h"
#include "chemotonbf.h"
namespace gt {
class RungeKuttaEngine : public gt::ChemotonBF
{
public:
    RungeKuttaEngine();
    void restart();
    double step();
    double getSpeed(int index);
//    virtual void notify(rg::Event e, rg::Subject* caller);
private:
    bool oneStep(double* ti, double* dt);
    double reactionODEs(double, double dx[], int n , bool temp);
    void reactioODEsDiffusive(double, rdmap rm, int n, bool temp);
    bool rk4_dn1(double, double, double [], int);
    double *ti;
    double *dt;
    double *tf;
    double *speed;
    double dtmax;
    double out_t;
    double tmax;
    int downcounter;
    int stepup;
    bool nonsense;
//    int n;
};
}
#endif // RUNGEKUTTAENGINE_H
