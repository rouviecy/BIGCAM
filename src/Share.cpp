#include "Share.h"

using namespace std;

Share::Share(){}

void Share::Lock(){mu.lock();}
void Share::Unlock(){mu.unlock();}
