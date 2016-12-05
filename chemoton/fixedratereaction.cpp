#include "fixedratereaction.h"

FixedRateReaction::FixedRateReaction() : ReactionBase()
{
}
FixedRateReaction::FixedRateReaction(string txt) : ReactionBase(txt) {
}

double FixedRateReaction::k() {
    return krate;
}
double FixedRateReaction::r() {
    return rrate;
}
