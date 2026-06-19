#include "MLSearchRangeOpt.h"

int MLSearchRangeOpt::dynSearchRange;

void MLSearchRangeOpt::defineStaticSearchRange() {
    dynSearchRange = SR_MAXIMUM;
}

void MLSearchRangeOpt::defineRandomSearchRange() {
    std::srand(std::time(0));

    int randValue = std::rand() % 3;

    if(randValue == 0) {
        dynSearchRange = SR_MINIMUM;
    }
    else if(randValue == 1) {
        dynSearchRange = SR_MEDIUM;
    }
    else {
        dynSearchRange = SR_MAXIMUM;
    }
}