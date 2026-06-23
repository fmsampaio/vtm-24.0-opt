#include <iostream>
#include <cstdlib> // Necessário para rand() e srand()
#include <ctime>   // Necessário para time()
#include <cmath>

#include <vector>
#include <fstream>
#include <cstdint>

#define ENABLE_DT_SR_OPT            1
#define ENABLE_REPORT_MVS           1

const int MAX_CUS_PER_CTU =         1024; 
const int MAX_FRAMES =              33;
const int MAX_CTUS_PER_FRAME =      510;

struct MvData {
    int16_t  xMv;
    int16_t  yMv;
    uint8_t imv;
};

struct CtuData {
    MvData listaMvsPerCtu[MAX_CUS_PER_CTU];
    int quantidadeCus = 0; // Quantas CUs Inter foram salvas aqui
};

class MLSearchRangeOpt {
    private:
        static int dynSearchRange;
        static std::vector<CtuData> mvStorage;
        static int numCtusWidth, numCtusHeight;
        static std::ofstream reportFile;
    
    public:

        static void init(int frameWidth, int frameHeight);
        static void finish();

        static void storeMv(int framePoc, int xCU, int yCU, int xMv, int yMv, uint8_t imv);
        static void reportMvs(int framePoc);

        static void defineRandomSearchRange();
        static void defineStaticSearchRange();

        static void collectFeatures();
        static void defineMLOptSearchRange();

        static bool isWithin32();       //TODO implement decision tree
        static bool isWithin64();       //TODO implement decision tree
        static bool isWithin128();      //TODO implement decision tree

        static int getDynSearchRange() { return dynSearchRange; }
        
        // Utilitary methods
        static int getCtuPos(int framePoc, int xCU, int yCU) { return  (framePoc * MAX_CTUS_PER_FRAME) + (xCU / 128) + ((yCU / 128) * numCtusWidth); }
        static int getFracMvShift(int imv);
        static bool isQuadPelMv(int imv) { return imv == 2; }        
};