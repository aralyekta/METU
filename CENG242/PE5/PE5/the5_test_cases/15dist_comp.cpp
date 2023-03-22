#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path1[4] = {1, 1, 2, 2};
    int path2[2] = {3, 3};
    PathTracker pt1 = PathTracker(path1, 2);
    PathTracker pt2 = PathTracker(path2, 1);
    pt1.summary();
    pt2.summary();

    std::cout << "pt1 == pt2: " << (pt1 == pt2.distance) << "\n";

    return 0;
}