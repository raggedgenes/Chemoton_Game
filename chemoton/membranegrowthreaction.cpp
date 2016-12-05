#include "membranegrowthreaction.h"

MembraneGrowthReaction::MembraneGrowthReaction(double _m, std::string txt) : FixedRateReaction(txt)
{
    size = _m;
}
//double MembraneGrowthReaction::k() {
//    return krate;
//}
//double MembraneGrowthReaction::r() {
//    return rrate;
//}

void MembraneGrowthReaction::addBuildingBlock(double n, reagent *reag) {
    bal.push_back(reag);
    in.push_back(n);
    //decomp
    reag->addDecompositionReaction(n,this);
}

void MembraneGrowthReaction::addSurface(reagent *membrane){
    jobb.push_back(membrane);
    out.push_back(1);
    membrane->addProductionReaction(1.0/size, this);
    this->membrane = membrane;
}

void MembraneGrowthReaction::setMembraneSize(double s) {
    this->size = s;
    this->membrane->changeProdStochio(this, s);
}
