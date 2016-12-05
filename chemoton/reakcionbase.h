#ifndef REAKCIONBASE_H
#define REAKCIONBASE_H

#include <string>
#include <vector>
#include "diffusion_simulator.h"
using namespace std;
typedef struct reagent reagent;

class ReactionBase
{
public:
    // aA + bB <-> cC + dD
    // k: -->
    // r: <--
    ReactionBase();
    ReactionBase(string txt);
    double krate;
    double rrate;
    string notes;
    vector<double> in; //precursors mol
    vector<double> out; // termék mol
    vector<reagent*> bal;
    vector<reagent*> jobb;
    int getNforReagent(reagent* reag);

    void addReagentLeft(double n, reagent* reag);
    void addReagentRight(double n, reagent* reag);
    virtual double k() = 0;
    virtual double r() = 0;

private:
    void init();
};

// Reagent definition
struct reagent {

    double conc; //ezt ne használjuk beállításra
    double tempconc;
    double fixconc;
    double f; //membrane permeability
    string name;
    char function;
//    gt::rdmap rdmap;
    vector<ReactionBase*> prod;
    vector<ReactionBase*> decomp;
    vector<double> pn; //mól száma a termelõdési reakcióban
    vector<double> dn; //mól száma a lebontási reakcióban

    reagent () {
        conc = 0;
        tempconc = 0;
        fixconc = 0;
        function = 'i'; //Secretum, Nutritient, Inner, Enzyme, surFace, enzyme-Complex
        pn = vector<double>();
        dn = vector<double>();
        prod = vector<ReactionBase*>();
        decomp = vector<ReactionBase*>();
        name = "undefined reagent";
        f = 1;
    }
    reagent (double _conc, char _function, string _name): conc(_conc), name(_name), function(_function) {
        tempconc = 0;
        pn = vector<double>();
        dn = vector<double>();
        prod = vector<ReactionBase*>();
        decomp = vector<ReactionBase*>();
        fixconc = 0;
        f = 1;
        if (function != 'i') {
            fixconc = conc;
//            rdmap = gt::rdmap(200, conc);
        }
    }
    void addDecompositionReaction(double d, ReactionBase* reac) {
//        if (function == 'i') {
//            decomp.push_back(reac);
//            dn.push_back(d);
//        }
        decomp.push_back(reac);
        dn.push_back(d);
    }
    void addProductionReaction(double p, ReactionBase* reac) {
//        if (function == 'i') {
//            prod.push_back(reac);
//            pn.push_back(p);
//        }
        prod.push_back(reac);
        pn.push_back(p);
    }
    void volumeAdjust(double growth) {
        if (function != 'f') {
            conc *= growth;
        }
    }

    void changeDecompStochio(ReactionBase* ennek, double erre) {
        for (unsigned int i = 0; i < decomp.size(); i++) {
            if (decomp.at(i) == ennek) dn.at(i) = erre;
        }
    }
    void changeProdStochio(ReactionBase* ennek, double erre) {
        for (unsigned int i = 0; i < prod.size(); i++) {
            if (prod.at(i) == ennek) pn.at(i) = erre;
        }
    }

//    double setConc(double c) {
//        conc = c;
//    }
};

#endif // REAKCIONBASE_H
