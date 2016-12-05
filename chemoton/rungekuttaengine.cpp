#include "rungekuttaengine.h"

using namespace gt;
RungeKuttaEngine::RungeKuttaEngine() : ChemotonBF()
{
//    this->setup();
    restart();
}
void RungeKuttaEngine::restart() {
    this->setup();
    ti = new double(0.0);
    dt = new double(0.01);
    tf = new double(0.0);
    dtmax = 0.01;
    out_t = 0.01;
    tmax = 400.0;
    downcounter = 0;
    stepup = 0;
    nonsense = false;
}

double RungeKuttaEngine::step() {
    while (oneStep(ti, dt)) {
        if (downcounter > 1000) {
            break;
        }
    }
    return *ti;
}

bool RungeKuttaEngine::oneStep(double* ti, double* dt){

    int n = reagents.size();
    double xf[n];
    *tf = *ti + *dt;
    /*=================================*/
    nonsense = rk4_dn1(*ti, *tf, xf, n);
    /*=================================*/
    // ellenõriz és kiír
    if (nonsense) {
//        std::cout << "Nonsense" << endl;
        *dt = *dt/2;
        //std::cout << "dt = " << dt << endl;
        stepup = 0;
        downcounter++;
        return nonsense;
    } else {
        stepup++;
        if (stepup > 50) {
            if (*dt < dtmax/2) {
                *dt *= 2;
            } else {
                *dt = dtmax;
                stepup = 0;
            }
            if (*dt == 0) {
                *dt = dtmax;
            }
        }
        // prepare for the next step

        for (int i = 0; i<n; i = i+1)
        {
            reagents.at(i)->conc = xf[i];
        }
        this->adjustConcentrationToVolume(*ti, *tf);
        downcounter = 0;
        *ti = *tf;
    }
    return nonsense;
//    std::cout << "oneStep" << endl;
}
double RungeKuttaEngine::reactionODEs(double t, double dx[], int n, bool temp) {
        for (int i=0; i < n; ++i) {
            dx[i] = this->flux(i,temp);
        }
        return 0;
}
void RungeKuttaEngine::reactioODEsDiffusive(double, rdmap rm, int n, bool temp) {

}

bool RungeKuttaEngine::rk4_dn1(double ti, double tf, double xf[], int n)
{
      double h, t, dx[n];
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
          this->reagents.at(j)->tempconc  = this->reagents.at(j)->conc + k1[j]/2.0;
        }
//k2
      reactionODEs(t+h/2.0, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k2[j] = h*dx[j];
          this->reagents.at(j)->tempconc  = this->reagents.at(j)->conc + k2[j]/2.0;
        }
//k3
      reactionODEs(t+h/2.0, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k3[j] = h*dx[j];
          this->reagents.at(j)->tempconc  = this->reagents.at(j)->conc + k3[j];
        }
//k4 and result
      reactionODEs(t+h, dx, n, true);
      for (j = 0; j<=n-1; j = j+1)
        {
          k4[j] = h*dx[j];
          xf[j] = this->reagents.at(j)->conc + k1[j]/6.0+k2[j]/3.0+k3[j]/3.0+k4[j]/6.0;
          if (xf[j] < 0) {
              nonsense = true;
              break;
          }
        }
      //speed = dx;
    return nonsense;
}

double RungeKuttaEngine::getSpeed(int index) {
    return speed[index];
}
