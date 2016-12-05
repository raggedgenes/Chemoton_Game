#ifndef SWITCHINGRATEREACTION_H
#define SWITCHINGRATEREACTION_H

#include "reakcionbase.h"

using namespace std;

typedef struct range range;

struct range {
    double* limit;
    double rate;
    double* visszalimit;
    range(double* li, double* _vLi, double _k){
        limit = li;
        visszalimit = _vLi;
        rate = _k;
    }
};

class ConcDependentReaction : public ReactionBase
{
public:
    ConcDependentReaction();
    ConcDependentReaction(string txt);

    vector<reagent*> kconc;
    vector<reagent*> rconc;
    vector<range> kranges;
    vector<range> rranges;
    double k();
    double r() ;

    void addKLimiter(double* limit, double* vissza, double k, reagent *reag);
    void addRLimiter(double* limit, double* vissza, double r, reagent *reag);
private:
    void setup();
    int ON; //1 : on 0: off
};

#endif // SWITCHINGRATEREACTION_H
