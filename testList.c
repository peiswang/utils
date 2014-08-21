#include "sample.h"

int main()
{
    struct samples* sn = loadSample("sample.dat");
    printSample(sn);
    return 0;
}
