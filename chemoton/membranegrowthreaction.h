#ifndef MEMBRANEGROWTHREACTION_H
#define MEMBRANEGROWTHREACTION_H

#include "string"
#include "fixedratereaction.h"

class MembraneGrowthReaction : public FixedRateReaction
{
public:
    MembraneGrowthReaction(double _m, std::string txt);

    void addBuildingBlock(double n, reagent * reag);
    void addSurface(reagent* membrane);
    int Surface() const;
    void setMembraneSize(double s);

private:
    double size;
    int surface;
    reagent* membrane;
};

#endif // MEMBRANEGROWTHREACTION_H
