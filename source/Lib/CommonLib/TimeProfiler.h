
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>

#include <stack>
#include <array>
#include <vector>
#include <chrono>
#include <map>

enum STAGE {  
  IME = 0,
  INTER_PRED = 1,
  ENCODER = 2,

  NUM_STAGES = 3
};

typedef std::milli rep;
typedef std::chrono::steady_clock clock_s;
typedef std::chrono::time_point<clock_s> time_point;
typedef std::chrono::duration<double, rep> duration;

class TimeProfiler {  

  public:
    static std::vector<time_point> previous;
    static std::vector<duration> durations;
    static std::vector<int> calls;
    static std::map<STAGE, std::string> stageToString;
    static std::string reportFileName;

    static void init();
    static void start( STAGE s );
    static void stop( STAGE s );
    static void report();
};