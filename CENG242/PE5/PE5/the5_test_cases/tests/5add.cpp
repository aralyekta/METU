#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path[2] = {1, 1};
    PathTracker pt = PathTracker();
    pt.summary();

    pt += path;
    pt.summary();

    return 0;
}