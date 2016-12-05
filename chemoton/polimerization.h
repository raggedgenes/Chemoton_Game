#ifndef POLIMERIZATION_H
#define POLIMERIZATION_H
#include "fixedratereaction.h"
class Polimerization : public FixedRateReaction
{
public:
    Polimerization(int _p, string txt);
    double k();
    double r() ;

    void setPolymerLength(int p);
    void addMonomer(int n, reagent *reag);
    void addPolimer(int n, reagent *reag);
    void createIntermedier(double conc);
private:
    int plength; //polimer hossza
    reagent* monomer;
};

#endif // POLIMERIZATION_H
