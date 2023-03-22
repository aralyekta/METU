#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path[4] = {1, 1, -1, -1};
    PathTracker pt = PathTracker(path, 2);
    pt.summary();

    return 0;
}