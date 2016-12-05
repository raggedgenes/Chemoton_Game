/*Copyright 2013, Szabolcs Makai
  Project started on 11/11/2013
        Chemoton modelling based on the work Ferenc Békés and Tibor Gánti.
*/

#ifndef CHEMOTONBF_H
#define CHEMOTONBF_H

#include <math.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "reakcionbase.h"
#include "polimerization.h"
#include "membranegrowthreaction.h"
#include "diffusion_simulator.h"
#include "../observer/eventdispatcher.h"

using namespace std;
namespace gt{
class ChemotonBF : public rg::Subject
{
public:
    explicit ChemotonBF();
    vector<ReactionBase*> reactions;
    vector<reagent*> reagents;
    double flux(int melyik, bool temp);
    double fluxRD(int melyik, unsigned int i, unsigned int j, bool temp);
    bool dummy;
    void addReagents();
    reagent* createReagent(double c, char function, string name);
    int getNumberOfReagents() const; // number of elements
    void adjustConcentrationToVolume(double ti, double tf);
    double getSummaReagents(int from, int to);
    double getVolume() const;
    double getOsmosis() const;
    double getSurface() const;
    double getMonomerConc() const;
    double getNofPolimer() const;
    double getValue(int minek) const;
    double getValueByName(std::string name) const;
    void setPolymerLength(int h);
    void setMembraneSize(double s);
    int getPolymerLength() const;
    string replicationtime;
    double* polymLimitUp;
    double* polymLimitDown;
    void setDiffusive(bool d);
    bool getDiffusive() const;
    void addChemoton(int n, double init_conc, std::string name, reagent *inlink, reagent *outlink, int outlink_index);
protected:
     void setup();
     bool isDiffusive;
     reagent* getReagentByName(std::string name) const;
private:
    int polymer_length;
    double dxdt(int melyik, const vector<double> self, vector<ReactionBase *> reac, bool temp);
    double PowerProduct(vector<double> a, vector<reagent*> reagPointer, int melyik, bool temp);
    bool figyelo;
    double calculateVolume();
    double calculateSurface();
    double calculateOsmosis();
    double calculateOsmoticChange(double ti, double tf);
    void divide(double ti);
    reagent* membrane;
    reagent* monomer;
    reagent* polymer;
    reagent* lipid;
    double osmoticchange;
    double osmosis;
    float osmoticCounterStart;
    double surface;
    double volume;
    double nOfpolimer;
    double concWatch;
    int numDivison;
    double tod; // time of division
    void addEnzymeReaction(string name, reagent *enzyme, vector<reagent *> left, vector<reagent *> right, vector<double> lcoeff, vector<double> rcoeff, double k, double r);
    void addReaction(string name, vector<reagent*> left, vector<reagent *> right, vector<double> lcoeff, vector<double> rcoeff, double k, double r);
    Polimerization* polim;
    MembraneGrowthReaction* membr;
};
}
#endif // CHEMOTONBF_H
