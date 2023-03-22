#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path[2] = {1, 1};
    PathTracker pt = PathTracker(path, 1);
    pt.summary();

    return 0;
}