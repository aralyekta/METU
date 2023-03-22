#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path[2] = {1, 1};
    PathTracker pt = PathTracker(path, 1);
    pt.summary();

    path[0] = -1;
    path[1] = -1;
    pt += path;
    pt.summary();

    return 0;
}