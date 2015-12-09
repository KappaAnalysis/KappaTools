#include "Plot_Run.h"

run_id Plot_Run::run = -1;
lumi_id Plot_Run::lumi = -1;
bool Plot_Run::useLumi = false;

std::list<Plot_Run_Holder> Plot_Run::instances;
