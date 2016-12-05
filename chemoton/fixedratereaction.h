#ifndef FIXEDRATEREACTION_H
#define FIXEDRATEREACTION_H

#include "reakcionbase.h"

class FixedRateReaction : public ReactionBase
{
public:
    FixedRateReaction();
    FixedRateReaction(string txt);
    double k();
    double r();
};

#endif // FIXEDRATEREACTION_H
