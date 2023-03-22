#include <pthread.h>

enum order
{
    NONE,
    BREAK,
    CONTINUE,
    STOP
};

class Coordinate
{
public:
    int x;
    int y;
    Coordinate()
    {
        this->x = 0;
        this->y = 0;
    }

    Coordinate(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(Coordinate coord)
    {
        bool xSame = (x == coord.x);
        bool ySame = (y == coord.y);
        return xSame && ySame;
    }
};
