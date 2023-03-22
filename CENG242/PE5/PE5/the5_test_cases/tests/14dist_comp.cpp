#include <iostream>
#include "../path_tracker.h"

int main()
{
    int path1[4] = {1, 1, 2, 2};
    PathTracker pt1 = PathTracker(path1, 2);
    pt1.summary();

    std::cout << "pt1 == 5: " << (pt1 == 5) << "\n";

    return 0;
}