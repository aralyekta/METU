#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path1[4] = {1, 1, 1, 1};
    int path2[2] = {2, 3};
    PathTracker pt1 = PathTracker(path1, 2);
    PathTracker pt2 = PathTracker(path2, 1);
    pt1.summary();
    pt2.summary();

    std::cout << "pt1 == pt2: " << (pt1 == pt2) << "\n";
    std::cout << "pt1 < pt2: " << (pt1 < pt2) << "\n";
    std::cout << "pt1 > pt2: " << (pt1 > pt2) << "\n";

    return 0;
}