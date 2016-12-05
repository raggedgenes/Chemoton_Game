#include "rk4engine.h"

using namespace gt;
RK4Engine::RK4Engine()
{
   // n = 10; //X, A1-5, Y, V, T, pVn, pVs, Tm
    chemoton = new gt::ChemotonBF();
    chemoton->register_observer(rg::Event("division"),this);
    ti = new double(0.0);
    dt = new double(0.01);
    tf = new double(0.0);
    dtmax = 0.01;
    out_t = 0.01;
    tmax = 400.0;

    file.open ("chemoton_out_9.txt");         // write results to this file
    /* output format */
    file.precision(6);
    file.setf(ios::scientific | ios::showpoint);
    std::cout.precision(4);
    std::cout.setf(ios::scientific | ios::showpoint);
    n = chemoton->getNumberOfReagents();
    file << "t";
    for (int i =0; i < n; ++i) {
        file << "\t" << chemoton->reagents.at(i)->name;
    }
    file << "\t" << "summa A";
    file << "\tpVn db";
    file << "\tVolume";
    file << "\tOsmosis";
    file << endl;
    file << "0";
    for (int i =0; i < n; ++i) {
        file << "\t" << chemoton->reagents.at(i)->conc;
    }
    file << "\t" << chemoton->getSummaReagents(1,5);
    file << "\t" << chemoton->getNofPolimer();
    file << "\t" << chemoton->getVolume();
    file << "\t" << chemoton->getOsmosis();
    file << endl;
    downcounter = 0;
    stepup = 0;
    nonsense = false;
    prev = 0;
}
void RK4Engine::simulate() {
    std::cout << "simulate" << endl;
    while (*ti <= tmax)
    {
        if (downcounter > 1000) break;
        oneStep(ti, dt);
    }
}

void RK4Engine::oneStep(double* ti, double* dt){

    n = chemoton->getNumberOfReagents();
    double xf[n];
    *tf = *ti + *dt;
    /*=================================*/
    nonsense = rk4_dn1(*ti, *tf, xf, n);
    //simaDx(dnx, ti, tf, xf, n);
    /*=================================*/
    // ellenõriz és kiír
    if (nonsense) {
//        std::cout << "Nonsense" << endl;
        *dt = *dt/2;
        //std::cout << "dt = " << dt << endl;
        stepup = 0;
        downcounter++;
        return;
    } else {

        stepup++;
        if ((*ti - prev) >= out_t) {
//            std::cout << "ok. ti = " << *ti << endl;
            file << *ti;
            for (int i =0; i < n; ++i) {
                file << "\t" << chemoton->reagents.at(i)->conc;
                // if (chemoton->reagents[i]->conc < 0.0) nonsense = true;
            }
            file << "\t" << chemoton->getSummaReagents(1, 5);
            file << "\t" << chemoton->getNofPolimer();
            file << "\t" << chemoton->getVolume();
            file << "\t" << chemoton->getOsmosis();
            file << "\t" << endl;
            prev = *ti;
        }
        if (stepup > 50) {
            if (*dt < dtmax/2) {
                *dt *= 2;
            } else {
                *dt = dtmax;
            }
        }
        // prepare for the next step

        for (int i = 0; i<n; i = i+1)
        {
            chemoton->reagents.at(i)->conc = xf[i];
        }
        chemoton->adjustConcentrationToVolume(*ti, *tf);
        downcounter = 0;
        *ti = *tf;
    }
//    std::cout << "oneStep" << endl;
}

/*==============================================================
  System of first order differential equations for the RK solver

  For a system of n first-order ODEs
  x [] array - x values
  dx[] array - dx/dt values

  For a system of n/2 second order ODEs follow the agreement
  In:  x[] array
  # first n/2 elements are x
  # last  n/2 elements are dx/dt
  Out: dx[] array
  # first n/2 elements are first order derivatives  (or dx/dt)
  # last  n/2 elements are second order derivatives (or d2x/dt2)
  example: 2D projectile motion in (x,y) plane
  In           Out
  x[0] - x     dx[0] - x'
  x[1] - y     dx[1] - y'
  x[2] - x'    dx[2] - x"
  x[3] - y'    dx[3] - y"
==============================================================*/

double RK4Engine::reactionODEs(double t, double dx[], int n, bool temp) {
        for (int i=0; i < n; ++i) {
            dx[i] = chemoton->flux(i,temp);
        }
        return 0;
}
/*==========================================================
 rk4_dn1.cpp: Solution of a system of n first-order ODE
 method:      Runge-Kutta 4th-order
 written by: Alex Godunov
 last revision: 7 October 2009
----------------------------------------------------------
 call ...
 dnx(t,x[],dx[],n)- functions dx/dt   (supplied by a user)
 input ...
 ti    - initial time
 tf    - solution time
 xi[]  - initial values
 n     - number of first order equations
 output ...
 xf[]  - solutions
==========================================================*/
bool RK4Engine::rk4_dn1(double ti, double tf, double xf[], int n)
{
      double h, t,dx[n];
      double k1[n],k2[n],k3[n],k4[n];
      int j;
      bool nonsense = false;
      h = tf-ti;
      t = ti;
//k1
      reactionODEs(t, dx, n, false);
      for (j = 0; j<=n-1; j = j+1)
        {
          k1[j] = h*dx[j];
          chemoton->reagents.at(j)->tempconc  = chemoton->reagents.at(j)->conc + k1[j]/2.0;
        }
//k2
      reactionODEs(t+h/2.0, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k2[j] = h*dx[j];
          chemoton->reagents.at(j)->tempconc  = chemoton->reagents.at(j)->conc + k2[j]/2.0;
        }
//k3
      reactionODEs(t+h/2.0, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k3[j] = h*dx[j];
          chemoton->reagents.at(j)->tempconc  = chemoton->reagents.at(j)->conc + k3[j];
        }
//k4 and result
      reactionODEs(t+h, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k4[j] = h*dx[j];
          xf[j] = chemoton->reagents.at(j)->conc + k1[j]/6.0+k2[j]/3.0+k3[j]/3.0+k4[j]/6.0;
          if (xf[j] < 0) {
              nonsense = true;
              break;
          }
        }
    return nonsense;
}

double RK4Engine::simaDx(double(dnx)(double, double [], int, bool), double ti, double tf, double xf[], int n) {
    double h = tf-ti;
    double dx[n];
    dnx(0,dx,n,false);
    for (int j = 0; j < n; j++) {
        xf[j] = chemoton->reagents.at(j)->conc + dx[j]*h;
    }
    return NULL;
}
sf::Vector2f RK4Engine::nextStep(int mit = 1) {
    sf::Vector2f ret;
    if (downcounter < 1000) {
        oneStep(ti, dt);
        ret.y = chemoton->reagents[mit]->conc;
    }
    ret.x = *ti;
    return ret;
}
double RK4Engine::getValue(int mit){
    return chemoton->reagents[mit]->conc;
}
void RK4Engine::notify(rg::Event e, rg::Subject *caller){
    std::cout << "division at " << *ti << std::endl;
}
