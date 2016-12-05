#include "polimerization.h"

Polimerization::Polimerization(int _p, string txt) : FixedRateReaction(txt), plength(_p) {
}

double Polimerization::k() {
    return krate;
}
double Polimerization::r() {
    return rrate;
}

void Polimerization::addMonomer(int n, reagent* reag) {
    bal.push_back(reag);
    in.push_back(n/plength);
    //decomp
    this->monomer = reag;
    monomer->addDecompositionReaction(n,this);
}
void Polimerization::addPolimer(int n, reagent *reag) {
    addReagentRight(n, reag);
}

void Polimerization::setPolymerLength(int p) {
    plength = p;
    this->monomer->changeDecompStochio(this,p);
}
