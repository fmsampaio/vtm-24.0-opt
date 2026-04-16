#include "TimeProfiler.h"

std::vector<time_point> TimeProfiler::previous;
std::vector<duration> TimeProfiler::durations;
std::vector<int> TimeProfiler::calls;
std::string TimeProfiler::reportFileName;

std::map<STAGE, std::string> TimeProfiler::stageToString;

void TimeProfiler::init()  {
    durations.resize( NUM_STAGES );
    previous.resize( NUM_STAGES );
    calls.resize( NUM_STAGES );

    for( size_t i = 0; i < NUM_STAGES; ++i ) {
        durations[i] = durations[i].zero();
        calls[i] = 0;
    }

    stageToString[IME]= "IME";
    stageToString[INTER_PRED] = "INTER_PRED";
    stageToString[ENCODER] = "ENCODER";
}

void TimeProfiler::start( STAGE s ) {
    previous[s] = clock_s::now();
}

void TimeProfiler::stop( STAGE s ) {
    time_point now = clock_s::now();
    durations[s] += ( now - previous[s] );
    calls[s] ++;
}

void TimeProfiler::report() {
    std::cout << "\nTime Profiler Report\n";
    std::cout << "Stage;Calls;Time(ms);TimePerCall(ms)\n";
    for( size_t i = 0; i < NUM_STAGES; ++i ) {
        STAGE s = (STAGE) i;
        double duration = durations[i].count();
        std::cout << stageToString[s] << ";" << calls[s] << ";" << duration << ";" << (duration / calls[i]) << std::endl;
    }
}