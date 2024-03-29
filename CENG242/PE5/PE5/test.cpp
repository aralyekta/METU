#include <iostream>
#include "path_tracker.h"

int main()
{

    /*
    PathTracker pt = PathTracker();
    int coord[2] = {3,5};
    pt.summary();

    pt += coord;
    pt.summary();

    coord[0] = -3;
    coord[1] = 1;
    pt += coord;
    pt.summary();

    coord[0] = -2;
    coord[1] = -6;
    pt += coord;
    pt.summary();
    */

    /*
    int existing_path[10] = {1,2,3,4,5,6,7,8,9,10};
    PathTracker pt = PathTracker(existing_path, 5);
    pt.summary();
    */

    int existing_path1[2] = {25, 30};
    int existing_path2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    PathTracker pt1 = PathTracker(existing_path1, 1);
    PathTracker pt2 = PathTracker(existing_path2, 5);

    pt1.summary();
    pt2.summary();

    std::cout << "pt1 == pt2: " << (pt1 == pt2) << "\n";
    std::cout << "pt1 > pt2: " << (pt1 > pt2) << "\n";
    std::cout << "pt1 < pt2: " << (pt1 < pt2) << "\n";
    // notice that distance can be compared with a floating-point
    // not another PathTracker object.
    std::cout << "distance comparison: " << (pt1 == pt2.distance) << "\n";

    return 0;
}
