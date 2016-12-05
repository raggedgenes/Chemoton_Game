#include "reakcionbase.h"

ReactionBase::ReactionBase()
{
    notes = "non specified";
    init();
}
ReactionBase::ReactionBase(string txt) : notes(txt){
    init();
}
void ReactionBase::init() {
    krate = 1;
    rrate = 1;
    in = vector<double>();
    out = vector<double>();
    bal = vector<reagent*>();
    jobb = vector<reagent*>();
}

void ReactionBase::addReagentLeft(double n, reagent* reag) {
    bal.push_back(reag);
    in.push_back(n);
    //decomp
    reag->addDecompositionReaction(n,this);
}
void ReactionBase::addReagentRight(double n, reagent* reag) {
    jobb.push_back(reag);
    out.push_back(n);
    //prod
    reag->addProductionReaction(n, this);
}
int ReactionBase::getNforReagent(reagent* reag) {
    int n = 0;
    for (unsigned int i = 0; i < bal.size(); i++){
        if (reag == bal.at(i)) {
            n = in[i];
            break;
        }
    }
    for (unsigned int i = 0; i < jobb.size(); i++){
        if (reag == jobb.at(i)) {
            n = out[i];
            break;
        }
    }
    return n;
}

