/*Copyright 2013, Szabolcs Makai
  Project started on 11/11/2013
        Chemoton modelling based on the work Ferenc Békés and Tibor Gánti.
*/

#include "chemotonbf.h"
#include "fixedratereaction.h"
#include "concdependentreaction.h"
#include "polimerization.h"
#include "membranegrowthreaction.h"
#include <stdio.h>
#include <sstream>
using namespace gt;
ChemotonBF::ChemotonBF() : Subject()
{
    polymer_length = 30;
    tod = 0;
    isDiffusive = false;
    setup();
}

void ChemotonBF::setup(){

    numDivison = 0;
    addReagents();
    polymLimitUp = new double(30);
    polymLimitDown = new double(30);
    replicationtime = "Replication time:";
    reactions = vector<ReactionBase*>(); //cikk alapján

    reagent* enzyme = new reagent();
    //extra chemoton, ami az emzimet termeli
//    addChemoton(4,1.0,"B",this->getReagentByName("V"), enzyme, 2);

    //making GANTI féle chemoton
    vector<reagent*> left = vector<reagent*>();
    vector<reagent*> right = vector<reagent*>();
    vector<double> lcoeff = vector<double>();
    vector<double> rcoeff = vector<double>();

    //x+a1 <-> a2
    left.push_back(getReagentByName("X"));
    left.push_back(getReagentByName("A1"));
    right.push_back(getReagentByName("A2"));
    lcoeff.push_back(1.0);
    lcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
    this->addReaction("x+a1 <-> a2", left, right, lcoeff, rcoeff, 1,0);
    left.clear();
    right.clear();
    lcoeff.clear();
    rcoeff.clear();

    // a2 <-> a3 + y
    left.push_back(getReagentByName("A2"));
    right.push_back(getReagentByName("A3"));
    right.push_back(getReagentByName("Y"));
    lcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
//    this->addEnzymeReaction("a2 + s <-> a3 + y + s", getReagentByName("B3"), left, right, lcoeff, rcoeff, 2, 0 );
    this->addReaction("a2 <-> a3 + y", left, right, lcoeff, rcoeff, 1,1);
    left.clear();
    right.clear();
    lcoeff.clear();
    rcoeff.clear();

    // a3 <-> a4 + v
    left.push_back(getReagentByName("A3"));
    right.push_back(getReagentByName("A4"));
    right.push_back(monomer);
    lcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
//    this->addEnzymeReaction("a3 <-> a4 + v", getReagentByName("B2"), left, right, lcoeff, rcoeff, 5.0,0);
    this->addReaction("a3 <-> a4 + v", left, right, lcoeff, rcoeff, 1,1);
    left.clear();
    right.clear();
    lcoeff.clear();
    rcoeff.clear();

    // a4 <-> a5 + T
    left.push_back(getReagentByName("A4"));
    right.push_back(getReagentByName("A5"));
    right.push_back(getReagentByName("T"));
    lcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
    rcoeff.push_back(1.0);
//    this->addEnzymeReaction("a4 <-> a5 + T", getReagentByName("B3"), left, right, lcoeff, rcoeff, 5.0,0);
    this->addReaction("a4 <-> a5 + T", left, right, lcoeff, rcoeff, 1,1);
    left.clear();
    right.clear();
    lcoeff.clear();
    rcoeff.clear();

//    // a5 <-> 2a1
    left.push_back(getReagentByName("A5"));
    right.push_back(getReagentByName("A1"));
    lcoeff.push_back(1.0);
    rcoeff.push_back(2.0);
//    this->addEnzymeReaction("a5 <-> 2a1", getReagentByName("B3"), left, right, lcoeff, rcoeff, 5.0, 0);
    this->addReaction("a5 <-> 2a1", left, right, lcoeff, rcoeff, 1,1);
    left.clear();
    right.clear();
    lcoeff.clear();
    rcoeff.clear();


    membr = new MembraneGrowthReaction(30, "T -> S");
    membr->addBuildingBlock(1, getReagentByName("T"));
    membr->addSurface(membrane);
    membr->krate = 10.0;
    membr->rrate = 0;
    reactions.push_back(membr);


    polymer_length = 30;
    //pVn <-> pVnV1
    ConcDependentReaction* cdr = new ConcDependentReaction("pVn -> pVnV1");
    cdr->addReagentLeft(1, polymer);
    cdr->addReagentRight(1, getReagentByName("pVnV1"));
    cdr->addKLimiter(polymLimitUp, polymLimitDown, 1,monomer);
    cdr->rrate = 0;
    reactions.push_back(cdr);

//    //pVnV1 + (n-1)V -> 2pVn - polimerizáció
    polim = new Polimerization(polymer_length, "pVnV1 + (n-1)V -> 2pVn");
    polim->addReagentLeft(1, getReagentByName("pVnV1"));
    polim->addMonomer(polymer_length, monomer);
    polim->addPolimer(2, polymer);
    polim->krate = 1;
    polim->rrate = 0;
    reactions.push_back(polim);

    volume = 1;
    surface = calculateSurface();
    nOfpolimer = polymer->conc * volume;
    osmosis = calculateOsmosis();
    figyelo = false;
    this->osmoticchange = 0;

}
void ChemotonBF::setDiffusive(bool d) {
    isDiffusive = d;
}

void ChemotonBF::addReagents() {
    reagents = vector<reagent*>();
    //set up initial conc.
    reagents.push_back(new reagent(100,'n',"X"));
//    reagents[0]->f = 0.3;
    for (int i = 1; i < 6; i++){
        //A1-A5
        ostringstream convert;
        convert << "A" << i;
        string index = convert.str();
        reagents.push_back(new reagent(6,'i', index));
    }
    reagent* waste = createReagent(0.1,'s', "Y");
//    waste->f = 0.6;
    monomer = createReagent(0,'i', "V");
    lipid = createReagent(0,'i', "T");
    createReagent(0,'i', "pVnV1");
    membrane = createReagent(1, 'f', "S");
    polymer = createReagent(1,'i', "pVn");
//    reagent* enzyme = new reagent(6.0, 'e', "enzyme");
//    reagents.push_back(enzyme); //12
}
reagent* ChemotonBF::createReagent(double c, char function, string name){
    reagents.push_back(new reagent(c, function, name));
    return reagents.at(reagents.size()-1);
}
void ChemotonBF::addChemoton(int n, double init_conc, std::string name, reagent* inlink, reagent* outlink, int outlink_index) {
    int offset = reagents.size();
    for (int i = 0; i < n; i++) {
        ostringstream convert;
        convert << name << i;
        string nev = convert.str();
        createReagent(init_conc, 'i', nev);
    }
    *outlink = *(createReagent(0.0, 'i', "outlink"));
    vector<reagent*> left = vector<reagent*>();
    vector<reagent*> right = vector<reagent*>();
    vector<double> lcoeff = vector<double>();
    vector<double> rcoeff = vector<double>();
    for (int r = offset; r < (offset + n); r++) {
        left.push_back(reagents[r]);
        lcoeff.push_back(1.0);
        if ((r+1) == (offset + n)) {
            right.push_back(reagents.at(offset));
            rcoeff.push_back(2.0);
        } else {
            right.push_back(reagents.at(r+1));
            rcoeff.push_back(1.0);
        }
        if (r == offset) {
            left.push_back(inlink);
            lcoeff.push_back(1.0);
        }
        if (r == (offset + outlink_index)) {
//            right.push_back(outlink);
//            rcoeff.push_back(1.0);
        }
        this->addReaction(name, left, right, lcoeff, rcoeff, 1,1);
        left.clear();
        right.clear();
        lcoeff.clear();
        rcoeff.clear();
    }
}

void ChemotonBF::addReaction(string name, vector<reagent*> left, vector<reagent *> right, vector<double> lcoeff, vector<double> rcoeff, double k, double r) {
    FixedRateReaction* reaction = new FixedRateReaction(name);
    for (unsigned int i = 0; i < left.size(); i++) {
        reaction->addReagentLeft(lcoeff[i], left[i]);
    }
    for (unsigned int i = 0; i < right.size(); i++) {
        reaction->addReagentRight(rcoeff[i], right[i]);
    }
    reaction->krate = k;
    reaction->rrate = r;
    reactions.push_back(reaction);
}

void ChemotonBF::addEnzymeReaction(string name, reagent* enzyme, vector<reagent*> left, vector<reagent *> right, vector<double> lcoeff, vector<double> rcoeff, double k, double r) {
    //reagent AS
    reagent* as = new reagent(0.0, 'e', name + " complex");
    reagents.push_back(as);
    FixedRateReaction *elso = new FixedRateReaction(name + " assoc");
    elso->addReagentLeft(1.0, enzyme);
    for (unsigned int i = 0; i < left.size(); i++) {
        elso->addReagentLeft(lcoeff[i], left[i]);
    }
    elso->addReagentRight(1.0, as);
    FixedRateReaction *disszoc = new FixedRateReaction(name + " dissoc");
    disszoc->addReagentLeft(1.0, as);
    for (unsigned int i = 0; i < right.size(); i++) {
        disszoc->addReagentRight(rcoeff[i], right[i]);
    }
    disszoc->addReagentRight(1.0, enzyme);
    elso->krate = k;
    disszoc->rrate = r;
    //adding to reactions
    reactions.push_back(elso);
    reactions.push_back(disszoc);
}
// -------------------------------------------------------------------------------------   Concentration-Volume specific  --------------------------------------------------------------------------------
void ChemotonBF::adjustConcentrationToVolume(double ti, double tf) {
//    double actualpolimer = reagents.at(9)->conc*volume;
    double newvolume = calculateVolume();
    double growth = volume / newvolume;

    // -1 kell, mert az utolsó a felület maga
    for (unsigned int i = 1; i < (reagents.size()); i++) {
        reagents.at(i)->volumeAdjust(growth);
    }
    volume = newvolume;
    surface = calculateSurface();
    if (calculateOsmoticChange(ti, tf) < 0.0)
    {
        this->osmoticchange += calculateOsmoticChange(ti, tf);
    } else if (this->osmoticchange < 0.0){
        if (osmoticchange < -1) {
            divide(ti);
            this->osmoticchange = 0;
        }
    } else {
        this->osmoticchange = 0;
    }
//    if (membrane->conc > 2.0) divide(ti);
    osmosis = calculateOsmosis();
    concWatch = getReagentByName("A1")->conc;
}
double ChemotonBF::calculateOsmoticChange(double ti, double tf) {
    return calculateOsmosis()-osmosis;
}

void ChemotonBF::divide(double ti) {
//    std::cout << "before division at ti: "<< ti <<" polimer: " << reagents.at(9)->conc*volume << "------- osmosis: " << getOsmosis() << endl;
    figyelo = false;
//    std::cout << "membrane: " << membrane->conc << " Polimer no.: " << this->getNofPolimer()<< " omchange: " << osmoticchange << endl;
    membrane->conc /= 2.0;
    double halfvolume = calculateVolume();
    numDivison ++;
    volume = halfvolume;
    surface = calculateSurface();
    osmosis = calculateOsmosis();
    this->notify_observers(rg::Event("division"));
//    std::cout << "ido: " << ti << " / A5: " << reagents.at(5)->conc << " A1: " << getReagentByName("A1")->conc << endl;
    std::ostringstream convert;
    convert << "Replication time: " << ti-tod;
    replicationtime = convert.str();
    tod = ti;
}
// ----------------------------------------------------------------- calculate properties --------------------------------------------------------------------------------------
double ChemotonBF::calculateSurface() {
    return membrane->conc;
}
double ChemotonBF::calculateVolume() {
    return pow(membrane->conc,1.5);
}
double ChemotonBF::calculateOsmosis() {
//    return -1*std::log(1/(getSummaReagents(1,10)*18+1));
    return getSummaReagents(1,reagents.size()-1)/reagents.size();
//    return getValueByName("pVn");
}
// -------------------------------------------------------------------------------------------------------  dA/dt  ------------------------------------------------------------------------------
double ChemotonBF::flux(int melyik, bool temp) {
    double decomp = (reagents.at(melyik)->decomp.size() > 0)? dxdt(melyik, reagents.at(melyik)->dn, reagents.at(melyik)->decomp, temp): 0;

    double prod = (reagents.at(melyik)->prod.size() > 0)? dxdt(melyik, reagents.at(melyik)->pn, reagents.at(melyik)->prod, temp):0;
    double konc;
    if (temp) {
        konc = reagents[melyik]->tempconc;
    } else {
        konc = reagents[melyik]->conc;
    }
    switch(reagents[melyik]->function) {
    case 'n':
        prod += reagents[melyik]->f*(reagents[melyik]->fixconc - konc);
        break;
    case 's':
        decomp += reagents[melyik]->f*konc;
        break;
    case 'c':
//        return (reagents[12]->fixconc - reagents[12]->conc);
        break;
    }
    return (prod - decomp);
}
double ChemotonBF::fluxRD(int melyik, unsigned int i, unsigned int j, bool temp) {
}

double ChemotonBF::dxdt(int melyik, vector<double> self, vector<ReactionBase*> reac, bool temp) {
    double Xconc = 0;
    if (self.size() == reac.size()) {
        for (unsigned int i = 0; i < reac.size(); i++) {
            Xconc += (self[i]*reac[i]->k()*PowerProduct(reac[i]->in,reac[i]->bal,melyik, temp) - self[i]*reac[i]->r()*PowerProduct(reac[i]->out,reac[i]->jobb,melyik, temp));
        }
    } else {
//        std::cout << "Hiba. self.size nem egyenlõ reac.size" << endl;
    }

    return Xconc;
}
double ChemotonBF::PowerProduct( vector<double> a, vector<reagent*> reagPointer, int melyik, bool temp) {
    double ret = 0;
    if (a.size() == reagPointer.size()) {
        if (reagPointer.size() > 0) {
            ret = 1;
            for (unsigned int i = 0; i < a.size(); ++i) {
                reagent* reag = reagPointer.at(i);
                double conc = (melyik == (int)i && temp) ? reag->tempconc : reag->conc;
//                double conc = reag->conc;
                ret *= pow(conc, a.at(i));
            }
        }
    } else {
//        std::cout << "Hiba. a.size nem egyenlõ participants.size" << endl;
    }
    return ret;
}

// -------------------------------------------------------------------------------------- gets and sets --------------------------------------------------------------------------------
double ChemotonBF::getSummaReagents(int from, int to) {
    double ret = 0;
    for (int i =from; i <= to; i++) {
        ret += reagents[i]->conc;
    }
    return ret;
}

int ChemotonBF::getNumberOfReagents() const {
    return this->reagents.size();
}
double ChemotonBF::getMonomerConc() const {
    return monomer->conc;
}
double ChemotonBF::getSurface() const {
    return surface;
}
double ChemotonBF::getOsmosis() const {
    return osmosis;
}
double ChemotonBF::getVolume() const {
    return volume;
}
double ChemotonBF::getNofPolimer() const {
    return polymer->conc*volume;
}
double ChemotonBF::getValue(int minek) const {
    return this->reagents[minek]->conc;
}
double ChemotonBF::getValueByName(string name) const {
    return this->getReagentByName(name)->conc;
}
int ChemotonBF::getPolymerLength() const {
    return this->polymer_length;
}
void ChemotonBF::setPolymerLength(int h) {
    this->polymer_length = h;
    polim->setPolymerLength(this->polymer_length);
}
reagent* ChemotonBF::getReagentByName(string name) const {
    for (int i = 0; i < reagents.size(); i++) {
        if (reagents[i]->name == name) return reagents[i];
    }
    return NULL;
}
void ChemotonBF::setMembraneSize(double s) {
    membr->setMembraneSize(1/s);
}
