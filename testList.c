#include "sample.h"

int main()
{
    struct sample_node * sn = loadSample("sample.dat", 2);
    printSample(sn);
    return 0;
}
