#include "MLSearchRangeOpt.h"

int MLSearchRangeOpt::dynSearchRange;
std::vector<CtuData> MLSearchRangeOpt::mvStorage(MAX_FRAMES * MAX_CTUS_PER_FRAME);
int MLSearchRangeOpt::numCtusWidth, MLSearchRangeOpt::numCtusHeight;
std::ofstream MLSearchRangeOpt::reportFile("mvs_report.txt");

/*
 * Methods to init and finish routines 
 */

void MLSearchRangeOpt::init(int frameWidth, int frameHeight) {
    numCtusWidth = std::ceil(frameWidth / 128.0);
    numCtusHeight = std::ceil(frameHeight / 128.0);
}

void MLSearchRangeOpt::finish() {
    reportFile.close();
}

/*
 * Methods to handle integer MVs storage for features calculatuion
 */

void MLSearchRangeOpt::storeMv(int framePoc, int xCU, int yCU, int xMv, int yMv, uint8_t imv) {
    int ctuPos = getCtuPos(framePoc, xCU, yCU);

    CtuData& ctuData = mvStorage[ctuPos];
    MvData& mvData = ctuData.listaMvsPerCtu[ctuData.quantidadeCus];
    ctuData.quantidadeCus ++;

    std::cout << "[" << static_cast<int>(imv) << "] MV (" << xMv << "," << yMv << ") --> ";

    xMv = (xMv >= 0) ? (xMv + 8) >> 4 : -((-xMv + 8) >> 4);
    yMv = (yMv >= 0) ? (yMv + 8) >> 4 : -((-yMv + 8) >> 4);

    std::cout << "(" << xMv << "," << yMv << ")" << std::endl;

    mvData.xMv = xMv;
    mvData.yMv = yMv;
    mvData.imv = static_cast<int>(imv);
}

void MLSearchRangeOpt::reportMvs(int framePoc) {
    reportFile << "[INFO] FRAME " << framePoc << std::endl;
    for (int yCtu = 0; yCtu < numCtusHeight; yCtu ++) {
        for (int xCtu = 0; xCtu < numCtusWidth; xCtu ++) {          
            int ctuPos = getCtuPos(framePoc, xCtu * 128, yCtu * 128);
            CtuData& ctuData = mvStorage[ctuPos];
            
            reportFile << "[INFO] CTU (" << xCtu << "," << yCtu << ") [" << ctuData.quantidadeCus << "] {" << ctuPos << "}" << std::endl;
            for (int posCu = 0; posCu < ctuData.quantidadeCus; posCu ++) {
                MvData& mvData = ctuData.listaMvsPerCtu[posCu];
                reportFile << "(" << mvData.xMv << "," << mvData.yMv << ")[" << static_cast<int>(mvData.imv) << "] ";
            }
            reportFile << std::endl;
        }
    }
}

/***
 * Methods to dynamically define the search range
 */
 void MLSearchRangeOpt::defineMLOptSearchRange() {
    // TODO Call DT logic according to our search range optimization scheme
    // TODO As result, the static attribute "dynSearchRange" must be defined with the predicted search range

    if(isWithin32()) {
        dynSearchRange = 32;
    }
    else if(isWithin128()) {
        dynSearchRange = 128;
    }
    else {
        dynSearchRange = 384;
    }
}

void MLSearchRangeOpt::defineStaticSearchRange() {
    dynSearchRange = 32;
}

void MLSearchRangeOpt::defineRandomSearchRange() {
    std::srand(std::time(0));

    int randValue = std::rand() % 3;
    if(randValue == 0) {
        dynSearchRange = 32;
    }
    else if(randValue == 1) {
        dynSearchRange = 128;
    }
    else {
        dynSearchRange = 384;
    }
}

/**
 * Decision trees
 */
bool MLSearchRangeOpt::isWithin32() {
    return true; //TODO implement decision tree logic
}

bool MLSearchRangeOpt::isWithin64() {
    return true; //TODO implement decision tree logic
}

bool MLSearchRangeOpt::isWithin128() {
    return true; //TODO implement decision tree logic
}
