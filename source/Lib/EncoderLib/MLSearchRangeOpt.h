#include <cstdlib> // Necessário para rand() e srand()
#include <ctime>   // Necessário para time()

#define SR_MINIMUM 32
#define SR_MEDIUM 128
#define SR_MAXIMUM 384

#define ENABLE_DT_SR_OPT 1

class MLSearchRangeOpt {
    private:
        static int dynSearchRange;
    
    public:

        static void defineRandomSearchRange();
        static void defineStaticSearchRange();

        static int getDynSearchRange() { return dynSearchRange; }
        
};