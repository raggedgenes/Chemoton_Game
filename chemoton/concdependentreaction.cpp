#include "concdependentreaction.h"

ConcDependentReaction::ConcDependentReaction() : ReactionBase()
{
    setup();
}
ConcDependentReaction::ConcDependentReaction(string txt) : ReactionBase(txt) {
    setup();
}
void ConcDependentReaction::setup() {
    kconc = vector<reagent*>();
    rconc = vector<reagent*>();
    kranges = vector<range>();
    rranges = vector<range>();
    krate = rrate = 0;
    ON = 0;
}
void ConcDependentReaction::addKLimiter(double *limit, double *vissza, double k, reagent *reag) {
    kconc.push_back(reag);
    if (*vissza > *limit) *vissza = *limit;
    kranges.push_back(range(limit,vissza, k));
}
void ConcDependentReaction::addRLimiter(double* limit, double* vissza, double r, reagent *reag) {
    rconc.push_back(reag);
    if (*vissza > *limit) *vissza = *limit;
    rranges.push_back(range(limit,vissza, r));
}

double ConcDependentReaction::k() {
    for (unsigned int i = 0; i < kconc.size(); i++) {
        if (*(kranges.at(i).visszalimit) > *(kranges.at(i).limit)) {
            *(kranges.at(i).visszalimit) = *(kranges.at(i).limit);
        }
        if (ON == 1) {
            if (kconc.at(i)->conc < *(kranges.at(i).visszalimit)) {
                ON = 0;
                krate = 0;
                break;
            }
        } else {
            if (kconc.at(i)->conc < *(kranges.at(i).limit)) {
                krate = 0;
                break;
            } else {
                krate = kranges.at(i).rate;
                ON = 1;
                break;
            }
        }
    }
    return krate;
}
double ConcDependentReaction::r() {
    for (unsigned int i = 0; i < rconc.size(); i++) {
        if (kconc.at(i)->conc < *(rranges.at(i).limit)) {
            rrate = 0;
            break;
        } else {
            rrate = rranges.at(i).rate;
            //ON = true;
            break;
        }
    }
    return rrate;
}
