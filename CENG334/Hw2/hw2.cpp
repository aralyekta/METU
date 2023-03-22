#include <iostream>
#include <vector>
#include <tuple>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
// #include <time.h>
#include <chrono>
#include "hw2_output.c"
#include "helpers.cpp"

// A private locks the area, waits, starts to collect cigbutts
// A private collects cigbutts from left to right, top to bottom (finish the row first, then move to the other row)
// A private waits if its area is already locked
// After a private collects every cigbutt, the thread stops

// Each thread may store the remaining cells, and remove the cells when they finish it
// So starting and continuing could be the same, lock the area and start collecting
// They should wait ONLY IF there are cells to be cleaned, if they are all clean, exit immediately

// A private should NOT lock even if a single cell is blocked
// Privates should wait concurrently
// Semaphores make sense for the orders

// Her zaman order tepkilerden önce gelmeli. O ZAMAN PRİNTLEDİKTEN SONRA cv semaphore falan ayarla
// Semaphore'u proper private sayısına ayarla
// Emri uygulayan her private semaphore'u bir düşürsün. Emri uygulayan private'lar...
//      Emir bitti cvsini beklesin. Bu cv ise emir semaphore'u 0 olunca ayarlanacak. Thread kodunda
// Ondan sonra normal executionına devam etsin

// Break - Continue arasını broadcast ile yap. Continue cvsi gelene kadar beklesin. Cv gelince broadcast et.

/*
https://docs.oracle.com/cd/E19455-01/806-5257/6je9h032r/index.html
    pthread_mutex_lock();
        while(condition_is_false)
            pthread_cond_wait();
    pthread_mutex_unlock();
*/

// You can't delete and recreate a thread for the break and continue orders.
// If it receives a break order, it should wait until a continue order, with preserving the thread
// Yanlış emirlere tepki verilmeyecek
// Private wait ederken break gelirse anında bırakacak. CV'li waite geç yani.

using namespace std;

// pthread_mutex_t **smokerCellMutexes;
pthread_mutex_t modifyGridPermission;

pthread_cond_t orderIncoming;
pthread_mutex_t orderIncomingMutex;

pthread_mutex_t availablePrivatesMutex;
int availablePrivates;

sem_t giveTheOrder;

sem_t orderGiven;

sem_t everyoneIsReady;

sem_t executeOrder;

pthread_mutex_t numOfProperPrivatesMutex;
pthread_mutex_t numOfSmokersMutex;

pthread_mutex_t readyPrivatesMutex;
int readyPrivates;

pthread_cond_t anAreaFreed;
pthread_mutex_t anAreaFreedMutex;

order globalOrdr;
pthread_mutex_t orderMutex;

int numOfProperPrivates;
int numOfSmokers;

// vector<Coordinate *> lockedAreas;
pthread_mutex_t lockedAreasMutex;
bool **lockedAreas;

int **smokingGrid;
pthread_mutex_t smokingGridMutex;

vector<int *> smokerCells;
pthread_mutex_t smokerCellsMutex;

sem_t canGiveOrder;

template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
result_t since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

void incrementSmokers(int x, int y)
{
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            smokingGrid[i][j]++;
        }
    }
}

void lock3x3(int x, int y)
{
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            lockedAreas[i][j] = true;
        }
    }
}

void unlock3x3(int x, int y)
{
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            lockedAreas[i][j] = false;
        }
    }
}

void waitForOrder(int gid)
{

    bool last = false;

    pthread_mutex_lock(&availablePrivatesMutex);
    pthread_mutex_lock(&numOfProperPrivatesMutex);

    availablePrivates++;
    // if (forStop)
    // {
    pthread_mutex_lock(&numOfSmokersMutex);
    if ((numOfProperPrivates + numOfSmokers) == availablePrivates)
    {
        cerr << "Private " << gid << " is the last one being available" << endl;
        last = true;
    }
    else
    {
        cerr << "Private " << gid << " got available, but not last" << endl;
    }
    // }
    // else
    // {
    //     if (numOfProperPrivates == availablePrivates)
    //     {
    //         cerr << "Private " << gid << " is the last one being available" << endl;
    //         last = true;
    //     }
    //     else
    //     {
    //         cerr << "Private " << gid << " got available, but not last" << endl;
    //     }
    // }

    if (last)
    {
        // pthread_cond_signal(&giveTheOrder);
        sem_post(&giveTheOrder);
        cerr << "Signalled give the order" << endl;
    }

    pthread_mutex_unlock(&numOfSmokersMutex);
    pthread_mutex_unlock(&numOfProperPrivatesMutex);
    pthread_mutex_unlock(&availablePrivatesMutex);

    sem_wait(&orderGiven);

    // pthread_mutex_lock(&orderGivenMutex);
    // pthread_cond_wait(&orderGiven, &orderGivenMutex);
    // pthread_mutex_unlock(&orderGivenMutex);

    cerr << "Private " << gid << " will get ready for the order " << endl;
}

void startExecutingOrder(int gid)
{
    bool last = false;
    pthread_mutex_lock(&readyPrivatesMutex);
    pthread_mutex_lock(&numOfProperPrivatesMutex);

    readyPrivates++;

    // if (forStop)
    // {
    pthread_mutex_lock(&numOfSmokersMutex);
    if ((numOfProperPrivates + numOfSmokers) == readyPrivates)
    {
        cerr << "Private " << gid << " is the last one being ready" << endl;
        last = true;
    }
    else
    {
        cerr << "Private " << gid << " got ready, but not last" << endl;
    }

    // }
    // else
    // {
    //     if (numOfProperPrivates == readyPrivates)
    //     {
    //         cerr << "Private " << gid << " is the last one being ready" << endl;
    //         last = true;
    //     }
    //     else
    //     {
    //         cerr << "Private " << gid << " got ready, but not last" << endl;
    //     }
    // }

    if (last)
    {
        // pthread_cond_signal(&everyoneIsReady);
        sem_post(&everyoneIsReady);
        cerr << "Signalled everyoneIsReady" << endl;
    }

    pthread_mutex_unlock(&numOfSmokersMutex);
    pthread_mutex_unlock(&numOfProperPrivatesMutex);
    pthread_mutex_unlock(&readyPrivatesMutex);

    sem_wait(&executeOrder);

    cerr << "Private " << gid << " will start executing the order " << endl;
}

order getGlobalOrder()
{
    order ordr;
    pthread_mutex_lock(&orderMutex);
    ordr = globalOrdr;
    pthread_mutex_unlock(&orderMutex);
    return ordr;
}

pair<bool, order> lockAreaForSmoker(int x, int y, int sid)
{

checkAreasForSmoker:
    sem_post(&canGiveOrder);
    cerr
        << "Called lockAreaForSmoker for sid " << sid << endl;

    pthread_mutex_lock(&lockedAreasMutex);
    pthread_mutex_lock(&smokingGridMutex);

    Coordinate leftUpperCorner(x - 1, y - 1);

    bool locked = false;

    for (int i = leftUpperCorner.x; i < leftUpperCorner.x + 3; i++)
    {
        for (int j = leftUpperCorner.y; j < leftUpperCorner.y + 3; j++)
        {
            if (lockedAreas[i][j] == true && smokingGrid[i][j] == 0)
            {
                locked = true;
                break;
            }
        }
        if (locked)
            break;
    }

    pthread_mutex_lock(&smokerCellsMutex);

    for (int i = 0; i < smokerCells.size(); i++)
    {
        if (x == smokerCells[i][0] && y == smokerCells[i][1])
        {
            locked = true;
            break;
        }
    }

    pthread_mutex_unlock(&smokerCellsMutex);
    if (locked)
    {
        cerr << "Smoker " << sid << " has an overlap so they'll wait" << endl;
        pthread_mutex_unlock(&lockedAreasMutex);
        // pthread_mutex_unlock(&smokerCellMutexes[x][y]);
        pthread_mutex_unlock(&smokingGridMutex);

        pthread_mutex_lock(&anAreaFreedMutex);
        pthread_cond_wait(&anAreaFreed, &anAreaFreedMutex);
        pthread_mutex_unlock(&anAreaFreedMutex);

        cerr << "The smoker " << sid << " woke up from area waiting" << endl;

        order globalOrdr = getGlobalOrder();
        if (globalOrdr == STOP)
        {
            // Stop
            cerr << "Stop order came to smoker " << sid << " while they are smoking, returning from lockarea" << endl;
            pair<bool, order> returnVal = {false, STOP};
        }
        else
        {
            if (globalOrdr == BREAK || globalOrdr == CONTINUE)
            {
                waitForOrder(sid);
                cerr << "Smoker " << sid << " got the order " << globalOrdr << endl;

                startExecutingOrder(sid);

                cerr << "Smoker " << sid << " will execute the order" << endl;
            }
            else
            {
                cerr << "It is not a stop order, smoker " << sid << " will check the area again" << endl;
            }
            goto checkAreasForSmoker;
        }
    }
    else
    {
        cerr << "Smoker " << sid << " will claim the area " << x << " " << y << endl;

        lock3x3(leftUpperCorner.x, leftUpperCorner.y);
        incrementSmokers(leftUpperCorner.x, leftUpperCorner.y);

        int *cell = new int[2]{x, y};

        pthread_mutex_lock(&smokerCellsMutex);
        smokerCells.push_back(cell);
        pthread_mutex_unlock(&smokerCellsMutex);

        pthread_mutex_unlock(&lockedAreasMutex);
        pthread_mutex_unlock(&smokingGridMutex);

        pthread_mutex_unlock(&smokingGridMutex);
        pthread_mutex_unlock(&lockedAreasMutex);
    }
    pair<bool, order> returnVal = {true, NONE};
    return returnVal;
}

int getNumOfProperPrivates()
{
    int result;
    pthread_mutex_lock(&numOfProperPrivatesMutex);
    result = numOfProperPrivates;
    pthread_mutex_unlock(&numOfProperPrivatesMutex);
    return result;
}

int getNumOfSmokers()
{
    int result;
    pthread_mutex_lock(&numOfSmokersMutex);
    result = numOfSmokers;
    pthread_mutex_unlock(&numOfSmokersMutex);
    return result;
}

bool notifyOrder(order ordr)
{
    bool stopOrderCame = false;
    if (ordr == BREAK)
    {
        hw2_notify(ORDER_BREAK, 0, 0, 0);
    }
    else if (ordr == CONTINUE)
    {
        hw2_notify(ORDER_CONTINUE, 0, 0, 0);
    }
    else if (ordr == STOP)
    {
        hw2_notify(ORDER_STOP, 0, 0, 0);
        stopOrderCame = true;
    }
    return stopOrderCame;
}

void decrementNumOfProperPrivates()
{
    pthread_mutex_lock(&numOfProperPrivatesMutex);
    numOfProperPrivates--;
    pthread_mutex_unlock(&numOfProperPrivatesMutex);
}

void setNumOfSmokers(int num)
{
    pthread_mutex_lock(&numOfSmokersMutex);
    numOfSmokers = num;
    pthread_mutex_unlock(&numOfSmokersMutex);
}

void decrementNumOfSmokers()
{
    pthread_mutex_lock(&numOfSmokersMutex);
    numOfSmokers--;
    pthread_mutex_unlock(&numOfSmokersMutex);
}

void setNumOfProperPrivates(int num)
{
    pthread_mutex_lock(&numOfProperPrivatesMutex);
    numOfProperPrivates = num;
    pthread_mutex_unlock(&numOfProperPrivatesMutex);
}

void setGlobalOrderWith(order ordr)
{
    pthread_mutex_lock(&orderMutex);
    globalOrdr = ordr;
    pthread_mutex_unlock(&orderMutex);
    cerr << "Set the global order as " << ordr << endl;
}

int incrementIntWithMutex(int *val, pthread_mutex_t *mutex, int gid, bool isReady)
{
    pthread_mutex_lock(mutex);
    (*val)++;
    int result = *val;
    if (isReady)
    {
        cerr << "Private " << gid << " incremented the number of ready privates to " << *val << endl;
    }
    else
    {
        cerr << "Private " << gid << " incremented the number of available privates to " << *val << endl;
    }
    pthread_mutex_unlock(mutex);
    return result;
}

int getIntWithMutex(int *val, pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    int result = *val;
    pthread_mutex_unlock(mutex);
    return result;
}

void resetIntWithMutex(int *val, pthread_mutex_t *mutex, bool isReady)
{
    pthread_mutex_lock(mutex);
    (*val) = 0;
    if (isReady)
    {
        cerr << "The number of ready privates is reset to 0" << endl;
    }
    else
    {
        cerr << "The number of available privates is reset to 0" << endl;
    }
    pthread_mutex_unlock(mutex);
}

bool isLocked(Coordinate l1, Coordinate r1)
{
    cerr << "Will wait for lockedAreasMutex" << endl;
    // pthread_mutex_lock(&lockedAreasMutex);
    cerr << "Waited for lockedAreasMutex" << endl;

    for (int i = l1.x; i <= r1.x; i++)
    {
        for (int j = l1.y; j <= r1.y; j++)
        {
            cerr << "Checking " << i << " " << j << endl;
            if (lockedAreas[i][j] == true)
            {
                // pthread_mutex_unlock(&lockedAreasMutex);
                return true;
            }
        }
    }

    // pthread_mutex_unlock(&lockedAreasMutex);

    return false;
}

// Note that the lockedAreasMutex is being held in the process
void lock(Coordinate l1, Coordinate r1)
{

    for (int i = l1.x; i <= r1.x; i++)
    {
        for (int j = l1.y; j <= r1.y; j++)
        {
            lockedAreas[i][j] = true;
        }
    }
}

// Note that the lockedAreasMutex is being held in the process
void unlock(Coordinate l1, Coordinate r1)
{

    for (int i = l1.x; i <= r1.x; i++)
    {
        for (int j = l1.y; j <= r1.y; j++)
        {
            lockedAreas[i][j] = false;
        }
    }
}

pair<order, Coordinate *> lockArea(int x, int y, int si, int sj, int gid)
{
    // Iterate through the locked areas to see if a cell is locked
    // If it is, wait for a anAreaFreed signal
    // If it isn't, lock it and add it to the lockedAreas

    Coordinate l1(x, y);
    Coordinate r1(x + si - 1, y + sj - 1);

    vector<Coordinate *>::iterator itr;

checkAreas:

    // cerr << "Size of lockedAreas: " << lockedAreas.size() << endl;

    cerr << "Calling isLocked for gid " << gid << endl;

    pthread_mutex_lock(&lockedAreasMutex);
    bool locked = isLocked(l1, r1);

    cerr << "isLocked returned " << locked << " for gid " << gid << endl;

    Coordinate *area = nullptr;

    if (locked)
    {
        cerr << "Private " << gid << " has an overlap so they'll wait" << endl;
        // cerr << "There is an overlap on " << x << " " << y << " " << si << " " << sj << endl;
        // Privates waiting for an area shall be available
        pthread_mutex_unlock(&lockedAreasMutex);
        pthread_mutex_lock(&anAreaFreedMutex);
        pthread_cond_wait(&anAreaFreed, &anAreaFreedMutex);
        pthread_mutex_unlock(&anAreaFreedMutex);

        cerr << "The private " << gid << " woke up from area waiting" << endl;

        order globalOrdr = getGlobalOrder();
        if (globalOrdr == NONE)
        {
            cerr << "An area is freed or an order will be given, private " << gid << " wake up" << endl;
            goto checkAreas;
        }
        else
        {
            pair<order, Coordinate *> returnVal = {globalOrdr, area};
            return returnVal;
        }
    }
    else
    {

        cerr << "Private " << gid << " has no overlap, they'll claim the area " << endl;
        area = new Coordinate[2];
        area[0] = l1;
        area[1] = r1;
        lock(area[0], area[1]);
        pthread_mutex_unlock(&lockedAreasMutex);

        cerr << "Private " << gid << " has no overlap, they claimed the area " << endl;
    }
    pair<order, Coordinate *> returnVal = {NONE, area};
    return returnVal;
}

void unlockArea(int x, int y, int si, int sj, Coordinate *lockedCoordinate, int gid)
{
    // cerr << "The area " << lockedCoordinate->x << " " << lockedCoordinate->y << " will be unlocked by " << gid << endl;
    // cerr << "Num of locked areas: " << lockedAreas.size() << endl;
    Coordinate l1(x, y);
    Coordinate r1(x + si - 1, y + sj - 1);

    vector<Coordinate *>::iterator itr;

    unlock(l1, r1);

    // bool found = false;

    // for (itr = lockedAreas.begin(); itr != lockedAreas.end(); itr++)
    // {
    //     if ((*itr) == lockedCoordinate)
    //     {
    //         found = true;
    //         break;
    //     }
    // }

    // if (found)
    // {
    //     lockedAreas.erase(itr);
    //     cerr << "Private " << gid << " unblocked the area" << endl;
    //     delete[] lockedCoordinate;
    // }
    // else
    // {
    //     cerr << "The area to be unlocked is not found " << endl;
    // }

    pthread_cond_broadcast(&anAreaFreed);
}

int waitMs(int timeInMs)
{
    struct timeval tv;
    struct timespec ts;

    gettimeofday(&tv, NULL);
    ts.tv_sec = time(NULL) + timeInMs / 1000;
    ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * (timeInMs % 1000);
    ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
    ts.tv_nsec %= (1000 * 1000 * 1000);
    pthread_mutex_lock(&orderIncomingMutex);
    int result = pthread_cond_timedwait(&orderIncoming, &orderIncomingMutex, &ts);
    pthread_mutex_unlock(&orderIncomingMutex);

    return result;
}

order collectCigbutts(int x, int y, int si, int sj, int gid, int tg, int **grid)
{
    // cerr << "\tEntered collectCigbutts for " << gid << endl;
    order incomingOrder = NONE;
    for (int i = x; i < x + si; i++)
    {
        for (int j = y; j < y + sj; j++)
        {
            while (grid[i][j] > 0)
            {
                auto start = std::chrono::steady_clock::now();
                // int secondElapsedTime = since(start).count();
                int timeToWait = tg;
            wait:
                if (timeToWait > 0)
                {
                    int result = waitMs(timeToWait);
                    int elapsedTime = since(start).count();
                    cerr << "waitMs returned " << result << " for gid " << gid << " and the elapsed time is: " << elapsedTime << endl;
                    if (result == 0)
                    {
                        // If an order is coming
                        incomingOrder = getGlobalOrder();
                        cerr << "Incoming global order is: " << incomingOrder << endl;

                        // Take a break if it is BREAK
                        // Keep waiting if it is CONTINUE
                        // Stop if it is STOP
                        if (incomingOrder == BREAK || incomingOrder == STOP)
                        {
                            return incomingOrder;
                        }

                        else if (incomingOrder == CONTINUE)
                        {

                            waitForOrder(gid);
                            startExecutingOrder(gid);

                            // incrementIntWithMutex(&availablePrivates, &availablePrivatesMutex, gid, false);
                            // incrementIntWithMutex(&readyPrivates, &readyPrivatesMutex, gid, true);
                            timeToWait -= elapsedTime;
                            goto wait;
                        }
                    }
                }

                cerr << "\t\tCame at decrementing for private " << gid << endl;
                // If an order is not present, this means we just timed out
                pthread_mutex_lock(&modifyGridPermission);
                grid[i][j]--;
                pthread_mutex_unlock(&modifyGridPermission);
                hw2_notify(PROPER_PRIVATE_GATHERED, gid, i, j);
                cerr << "\t\tDecremented for private " << gid << endl;
            }
        }
    }
    // cerr << "\tExiting collectCigbutts for " << gid << endl;
    return incomingOrder;
}

pair<int, int> getCellToSmoke(int centerX, int centerY, int itrNumber)
{
    int moddedItr = itrNumber % 8;
    switch (moddedItr)
    {
    case 0:
        return pair<int, int>{centerX - 1, centerY - 1};
    case 1:
        return pair<int, int>{centerX - 1, centerY};
    case 2:
        return pair<int, int>{centerX - 1, centerY + 1};
    case 3:
        return pair<int, int>{centerX, centerY + 1};
    case 4:
        return pair<int, int>{centerX + 1, centerY + 1};
    case 5:
        return pair<int, int>{centerX + 1, centerY};
    case 6:
        return pair<int, int>{centerX + 1, centerY - 1};
    case 7:
        return pair<int, int>{centerX, centerY - 1};
    }
    return pair<int, int>{-1, -1};
}

bool checkIfClean(int x, int y, int si, int sj, int **grid)
{
    for (int i = x; i < x + si; i++)
    {
        for (int j = y; j < y + sj; j++)
        {
            if (grid[i][j] > 0)
                return 0;
        }
    }
    return 1;
}

class ProperPrivate
{

public:
    int gid;
    int si, sj;
    int tg;
    vector<int *> areas;
    int **grid;
    ProperPrivate(int gidArg, int siArg, int sjArg, int tgArg,
                  int **grid)
    {
        this->gid = gidArg;
        this->si = siArg;
        this->sj = sjArg;
        this->tg = tgArg;
        this->grid = grid;
    }

    void addArea(int x, int y)
    {
        int *pair = new int[2];
        pair[0] = x;
        pair[1] = y;
        this->areas.push_back(pair);
    }

    ~ProperPrivate()
    {
        vector<int *>::iterator itr;
        for (itr = areas.begin(); itr != areas.end(); itr++)
        {
            delete[] * itr;
        }
        // delete this->thread;
    }

    // pthread_t *getThread()
    // {
    //     return this->thread;
    // }

    void print()
    {
        cerr << "Proper private: " << gid << endl;
        cerr << "Area lock information: " << si << " " << sj << endl;
        cerr << "Areas to clean: " << endl;
        vector<int *>::iterator itr;
        for (itr = areas.begin(); itr != areas.end(); itr++)
        {
            cerr << (*itr)[0] << " " << (*itr)[1] << endl;
        }
    }
};

class Smoker
{
public:
    int sid;
    int tg;
    vector<int *> cells;
    int **grid;

    Smoker(int sidArg, int tgArg, int **gridArg)
    {
        this->sid = sidArg;
        this->tg = tgArg;
        this->grid = gridArg;
    }

    ~Smoker()
    {
        vector<int *>::iterator itr;
        for (itr = cells.begin(); itr != cells.end(); itr++)
        {
            delete[](*itr);
        }
    }

    void addCell(int *cell)
    {
        cells.push_back(cell);
    }

    void print()
    {
        cerr << "Smoker " << sid << endl;
        cerr << "Time to wait: " << tg << endl;
        cerr << "Cells to smoke on:" << endl;
        vector<int *>::iterator itr;
        for (itr = cells.begin(); itr != cells.end(); itr++)
        {
            cerr << (*itr)[0] << " " << (*itr)[1] << " " << (*itr)[2] << endl;
        }
    }
};

void *runProperPrivate(void *ptr)
{
    ProperPrivate *properPrivatePtr = (ProperPrivate *)ptr;
    int gid = properPrivatePtr->gid;
    hw2_notify(PROPER_PRIVATE_CREATED, gid, 0, 0);
    vector<int *> areas = properPrivatePtr->areas;
    int si = properPrivatePtr->si;
    int sj = properPrivatePtr->sj;
    int **grid = properPrivatePtr->grid;
    int tg = properPrivatePtr->tg;

    while (!areas.empty())
    {
        sem_post(&canGiveOrder);
        cerr << "Iterating the areas of " << gid << endl;
        int x = (*areas.begin())[0];
        int y = (*areas.begin())[1];

        pair<order, Coordinate *>
            result = lockArea(x, y, si, sj, gid);
        order incomingOrder = result.first;
        Coordinate *lockedCoordinate = result.second;
        if (lockedCoordinate)
            hw2_notify(PROPER_PRIVATE_ARRIVED, gid, x, y);

        if (incomingOrder == NONE)
        {
            cerr << "No order, " << gid << " will execute normally " << endl;
            cerr << "\tCheckIfClean is: " << checkIfClean(x, y, si, sj, grid) << endl;
            if (!checkIfClean(x, y, si, sj, grid))
            {
                cerr << "Private " << gid << " will start to collect cigbutts " << endl;
                incomingOrder = collectCigbutts(x, y, si, sj, gid, tg, grid);
            }

            if (checkIfClean(x, y, si, sj, grid))
            {
                areas.erase(areas.begin());
            }
        }

        incomingOrder = getGlobalOrder();

        cerr << "Incoming order for gid: " << gid << " is " << incomingOrder << endl;

        if (incomingOrder != NONE)
        {
            cerr << "Private " << gid << " will get the order " << incomingOrder << endl;
            // Wait here for the second trigger of the same order
            if (incomingOrder == BREAK)
            {
                // Wait for the CONTINUE, continue looping after it arrives

                waitForOrder(gid);

                cerr << "Private " << gid << " got the order " << incomingOrder << endl;

                // availablePrivates should be 0 here

                // BEFORE waiting for the continue signal, wait until each thread gets ready to execute
                // the break command and the semaphore is signaled by all of them

                startExecutingOrder(gid);

                cerr << "Private " << gid << " will execute the order" << endl;
                // readyPrivates should be 0 here
                // Every private got the order, now they will execute it
                // The order is finally given, now the private can act accordingly
                // Which is to wait for a continue signal

                if (lockedCoordinate)
                    unlockArea(x, y, si, sj, lockedCoordinate, gid);
                hw2_notify(PROPER_PRIVATE_TOOK_BREAK, gid, 0, 0);

                cerr << "Private " << gid << " will wait for a continue order" << endl;
            // The CONTINUE order will only be given in orderIncoming, orderGiven is unnecessary in this case
            waitForOrder:
                sem_post(&canGiveOrder);
                pthread_mutex_lock(&orderIncomingMutex);
                pthread_cond_wait(&orderIncoming, &orderIncomingMutex);
                pthread_mutex_unlock(&orderIncomingMutex);

                order givenOrder = getGlobalOrder();

                cerr << "Private " << gid << " got an order, it is: " << givenOrder << endl;

                // availablePrivates should be 0 here

                if (givenOrder == CONTINUE)
                {
                    cerr << "Private " << gid << " will get the continue order" << endl;
                    // CONTINUE order came in a wrong state

                    waitForOrder(gid);

                    // Make sure that each private is ready to execute the order

                    startExecutingOrder(gid);

                    hw2_notify(PROPER_PRIVATE_CONTINUED, gid, 0, 0);

                    continue;
                }
                else if (givenOrder == STOP)
                {
                    cerr << "Private " << gid << " will get the stop order" << endl;

                    waitForOrder(gid);

                    cerr << "Private " << gid << " got the stop order" << endl;

                    startExecutingOrder(gid);

                    if (lockedCoordinate)
                        unlockArea(x, y, si, sj, lockedCoordinate, gid);

                    hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
                    decrementNumOfProperPrivates();
                    return nullptr;
                }
                else if (givenOrder == BREAK)
                {
                    cerr << "Private " << gid << " will get the break order" << endl;

                    waitForOrder(gid);

                    cerr << "Private " << gid << " got the break order, but they are already taking a break" << endl;

                    startExecutingOrder(gid);

                    goto waitForOrder;
                }
            }
            else if (incomingOrder == STOP)
            {
                cerr << "Private " << gid << " will get the stop order" << endl;
                // Exit the thread after receiving the order
                // Increment the semaphore to notify the main program that the private waits for the order

                waitForOrder(gid);
                // The order is finally given, now the private can act accordingly
                // Which is to exit the thread immediately
                cerr << "Private " << gid << " got the stop order" << endl;

                startExecutingOrder(gid);

                if (lockedCoordinate)
                    unlockArea(x, y, si, sj, lockedCoordinate, gid);

                hw2_notify(PROPER_PRIVATE_STOPPED, gid, 0, 0);
                decrementNumOfProperPrivates();
                return nullptr;
            }
            else if (incomingOrder == CONTINUE)
            {
                cerr << "Private " << gid << " will get the continue order" << endl;
                // CONTINUE order came in a wrong state

                waitForOrder(gid);

                cerr << "Private " << gid << " got the continue order, but they are already working" << endl;

                startExecutingOrder(gid);
                continue;
            }
        }

        unlockArea(x, y, si, sj, lockedCoordinate, gid);
        hw2_notify(PROPER_PRIVATE_CLEARED, gid, 0, 0);
    }

    decrementNumOfProperPrivates();
    hw2_notify(PROPER_PRIVATE_EXITED, gid, 0, 0);
    return nullptr;
}

order smoke(int upperLeftX, int upperLeftY, int count, int sid, int tg, int **grid)
{
    order incomingOrder = NONE;
    int itrNum = 0;
    while (count > 0)
    {
        auto start = std::chrono::steady_clock::now();
        int timeToWait = tg;
    waitSmoke:
        if (timeToWait > 0)
        {
            int result = waitMs(timeToWait);
            int elapsedTime = since(start).count();
            cerr << "waitMs returned " << result << " for sid " << sid << " and the elapsed time is: " << elapsedTime << endl;
            if (result == 0)
            {
                incomingOrder = getGlobalOrder();
                cerr << "Incoming global order is: " << incomingOrder << endl;
                if (incomingOrder == STOP)
                {
                    return incomingOrder;
                }
                else
                {
                    waitForOrder(sid);
                    startExecutingOrder(sid);
                    timeToWait -= elapsedTime;
                    goto waitSmoke;
                }
            }
        }

        // Waited, will now decrement
        pair<int, int> cellToSmoke = getCellToSmoke(upperLeftX + 1, upperLeftY + 1, itrNum);
        itrNum++;
        pthread_mutex_lock(&modifyGridPermission);
        grid[cellToSmoke.first][cellToSmoke.second]++;
        pthread_mutex_unlock(&modifyGridPermission);
        hw2_notify(SNEAKY_SMOKER_FLICKED, sid, cellToSmoke.first, cellToSmoke.second);
        cerr << "\t\tIncremented the cell " << cellToSmoke.first << " " << cellToSmoke.second << " for private" << endl;
        count--;
    }
    cerr << "Smoker " << sid << "exits the smoke function with return val " << incomingOrder << endl;
    return incomingOrder;
}

void removeSmokerCell(int x, int y, int sid)
{
    cerr << "removeSmokerCell called for sid: " << sid << " and x,y: " << x << " " << y << endl;
    pthread_mutex_lock(&smokerCellsMutex);
    vector<int *>::iterator itr;

    bool found = false;
    for (itr = smokerCells.begin(); itr != smokerCells.end(); itr++)
    {
        if (x == (*itr)[0] && y == (*itr)[1])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        int *ptr = *itr;
        smokerCells.erase(itr);
        delete[] ptr;
    }

    cerr << "The smoker cell to be deleted is found: " << found << endl;

    pthread_mutex_unlock(&smokerCellsMutex);
}

void *runSmoker(void *ptr)
{
    cerr << "Entered runSmoker" << endl;
    Smoker *smokerPtr = (Smoker *)ptr;
    cerr << "Got the smokerptr" << endl;
    int sid = smokerPtr->sid;
    int tg = smokerPtr->tg;
    cerr << "Got the variables" << endl;
    hw2_notify(SNEAKY_SMOKER_CREATED, sid, 0, 0);
    cerr << "Notified that the smoker is created" << endl;
    vector<int *> cells = smokerPtr->cells;
    int **grid = smokerPtr->grid;
    vector<int *>::iterator itr;

    while (!cells.empty())
    {
        cerr << "Will iterate cells of the smoker" << endl;
        sem_post(&canGiveOrder);
        int x, y, c;

        x = (*cells.begin())[0];
        y = (*cells.begin())[1];
        c = (*cells.begin())[2];
        cerr << "Smoker " << sid << " will wait for the cell " << x << " " << y << endl;
        pair<bool, order> result = lockAreaForSmoker(x, y, sid);
        bool areaLocked = result.first;
        order incomingOrder = result.second;

        cerr << "Smoker lockArea returned " << result.first << " and " << result.second << endl;

        if (areaLocked)
        {
            hw2_notify(SNEAKY_SMOKER_ARRIVED, sid, x, y);
        }

        incomingOrder = getGlobalOrder();

        if (incomingOrder == STOP)
        {
            cerr << "Smoker " << sid << " will get the stop order " << endl;
            waitForOrder(sid);
            cerr << "Smoker " << sid << " got the stop order " << endl;

            startExecutingOrder(sid);
            cerr << "Smoker will execute the stop order " << endl;

            if (areaLocked)
                unlockArea(x - 1, y - 1, 3, 3, nullptr, sid);

            // pthread_mutex_unlock(&smokerCellMutexes[x][y]);
            unlock3x3(x - 1, y - 1);
            pthread_cond_broadcast(&anAreaFreed);
            hw2_notify(SNEAKY_SMOKER_STOPPED, sid, 0, 0);
            decrementNumOfSmokers();
            if (areaLocked)
                removeSmokerCell(x, y, sid);
            return nullptr;
        }
        else
        {
            cerr << "Smoker " << sid << " will smoke normally" << endl;
            // Write the smoker version of collectCigbutts

            order incomingOrder = smoke(x - 1, y - 1, c, sid, tg, grid);

            if (incomingOrder == STOP)
            {
                cerr << "Smoker " << sid << " will get the stop order " << endl;
                waitForOrder(sid);
                cerr << "Smoker " << sid << " got the stop order " << endl;

                startExecutingOrder(sid);
                cerr << "Smoker will execute the stop order " << endl;

                if (areaLocked)
                    unlockArea(x - 1, y - 1, 3, 3, nullptr, sid);

                // pthread_mutex_unlock(&smokerCellMutexes[x][y]);
                unlock3x3(x - 1, y - 1);
                pthread_cond_broadcast(&anAreaFreed);
                hw2_notify(SNEAKY_SMOKER_STOPPED, sid, 0, 0);
                decrementNumOfSmokers();
                if (areaLocked)
                    removeSmokerCell(x, y, sid);
                return nullptr;
            }

            cerr << "Smoker " << sid << " will leave the area " << x << " " << y << endl;

            hw2_notify(SNEAKY_SMOKER_LEFT, sid, 0, 0);
            cells.erase(cells.begin());
            if (areaLocked)
                removeSmokerCell(x, y, sid);
        }
        // pthread_mutex_unlock(&smokerCellMutexes[x][y]);
        unlock3x3(x - 1, y - 1);
        pthread_cond_broadcast(&anAreaFreed);
    }
    hw2_notify(SNEAKY_SMOKER_EXITED, sid, 0, 0);
    decrementNumOfSmokers();
    return nullptr;
}

class Input
{
    int i;
    int j;

    vector<ProperPrivate *> properPrivates;
    vector<Smoker *> smokers;

public:
    int **grid;
    vector<pair<int, order>> orders;

    Input(int i, int j)
    {
        this->i = i;
        this->j = j;
        grid = new int *[i];
        lockedAreas = new bool *[i];
        // smokerCellMutexes = new pthread_mutex_t *[i];
        smokingGrid = new int *[i];
        for (int c = 0; c < i; c++)
        {
            grid[c] = new int[j];
            lockedAreas[c] = new bool[j];
            // smokerCellMutexes[c] = new pthread_mutex_t[j];
            smokingGrid[c] = new int[j];
            for (int l = 0; l < j; l++)
            {
                lockedAreas[c][l] = 0;
                smokingGrid[c][l] = 0;
                // pthread_mutex_init(&smokerCellMutexes[c][l], nullptr);
            }
        }
    }

    vector<ProperPrivate *> &getProperPrivates()
    {
        return properPrivates;
    }

    vector<Smoker *> &getSmokers()
    {
        return smokers;
    }

    int numOfProperPrivates()
    {
        return properPrivates.size();
    }

    int numOfSmokers()
    {
        return smokers.size();
    }

    int getI()
    {
        return i;
    }

    int getJ()
    {
        return j;
    }

    void setGridCell(int i, int j, int val)
    {
        this->grid[i][j] = val;
    }

    int getGridCell(int i, int j)
    {
        return this->grid[i][j];
    }

    void addOrder(int ts, char orderStr[])
    {
        order ordr;
        if (strcmp("break", orderStr) == 0)
        {
            ordr = BREAK;
        }
        else if (strcmp("continue", orderStr) == 0)
        {
            ordr = CONTINUE;
        }
        else if (strcmp("stop", orderStr) == 0)
        {
            ordr = STOP;
        }
        else
        {
            ordr = NONE;
            cerr << "There has been an error in the parsing";
        }
        pair<int, order> orderPair(ts, ordr);
        orders.push_back(orderPair);
    }

    void print()
    {
        cerr << "Dimensions: " << i << " " << j << endl;
        cerr << "Grid is: " << endl;
        for (int c = 0; c < i; c++)
        {
            for (int l = 0; l < j; l++)
            {
                cerr << this->grid[c][l] << " ";
            }
            cerr << endl;
        }
        cerr << "Proper privates: " << endl;
        vector<ProperPrivate *>::iterator privateItr;
        for (privateItr = properPrivates.begin(); privateItr != properPrivates.end(); privateItr++)
        {
            (*privateItr)->print();
        }

        cerr << "Orders (if they exist): " << endl;
        vector<pair<int, order>>::iterator orderItr;
        for (orderItr = orders.begin(); orderItr != orders.end(); orderItr++)
        {
            cerr << (*orderItr).first << " " << (*orderItr).second << endl;
        }

        cerr << "Smokers (if they exist): " << endl;
        vector<Smoker *>::iterator smokerItr;
        for (smokerItr = smokers.begin(); smokerItr != smokers.end(); smokerItr++)
        {
            (*smokerItr)->print();
        }
    }

    ~Input()
    {
        for (int c = 0; c < i; c++)
        {
            delete[] grid[c];
            delete[] smokingGrid[c];
            delete[] lockedAreas[c];
            // delete[] smokerCellMutexes[c];
        }
        delete[] grid;
        delete[] smokingGrid;
        delete[] lockedAreas;
        // delete[] smokerCellMutexes;

        vector<ProperPrivate *>::iterator itr;
        for (itr = properPrivates.begin(); itr != properPrivates.end(); itr++)
        {
            delete (*itr);
        }
        for (int i = 0; i < smokers.size(); i++)
        {
            delete smokers[i];
        }
    }

    void addProperPrivate(ProperPrivate *priv)
    {
        properPrivates.push_back(priv);
    }

    void addSmoker(Smoker *smoker)
    {
        smokers.push_back(smoker);
    }
};

Input readInput()
{
    int i, j;
    scanf("%d %d", &i, &j);
    Input input(i, j);
    for (int c = 0; c < i; c++)
    {
        int val;
        for (int l = 0; l < j; l++)
        {
            scanf("%d", &val);
            input.setGridCell(c, l, val);
        }
    }
    int numOfProperPriv;
    scanf("%d", &numOfProperPriv);
    for (int c = 0; c < numOfProperPriv; c++)
    {
        int gid, si, sj, tg, numOfAreas;
        scanf("%d %d %d %d %d", &gid, &si, &sj, &tg, &numOfAreas);
        ProperPrivate *priv = new ProperPrivate(gid, si, sj, tg, input.grid);
        for (int l = 0; l < numOfAreas; l++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            priv->addArea(x, y);
        }
        input.addProperPrivate(priv);
    }

    int numOfOrders;
    scanf(" ");
    string line;
    getline(cin, line);
    cerr << "Line is: " << line << endl;
    if (line.empty())
    {
        cerr << "Line is empty, returning" << endl;
        return input;
    }

    const char *readLine = line.c_str();

    sscanf(readLine, "%d", &numOfOrders);
    for (int c = 0; c < numOfOrders; c++)
    {
        int ts;
        char orderString[20];
        scanf("%d %s", &ts, &orderString);
        input.addOrder(ts, orderString);
    }

    int numOfSmokers;
    scanf(" ");
    string line2;
    getline(cin, line2);
    cerr << "Line2 is: " << line2 << endl;
    if (line2.empty())
    {
        cerr << "Line2 is empty, returning" << endl;
        return input;
    }

    const char *readLine2 = line2.c_str();

    sscanf(readLine2, "%d", &numOfSmokers);

    for (int c = 0; c < numOfSmokers; c++)
    {
        int sid, tg, numOfCells;
        scanf("%d %d %d", &sid, &tg, &numOfCells);
        Smoker *smoker = new Smoker(sid, tg, input.grid);
        for (int l = 0; l < numOfCells; l++)
        {
            int *cellInfo = new int[3];
            int x, y, numOfCig;
            scanf("%d %d %d", &x, &y, &numOfCig);
            cellInfo[0] = x;
            cellInfo[1] = y;
            cellInfo[2] = numOfCig;
            smoker->addCell(cellInfo);
        }
        input.addSmoker(smoker);
    }

    return input;
}

int main()
{
    hw2_init_notifier();
    auto start = std::chrono::steady_clock::now();

    pthread_mutex_init(&modifyGridPermission, nullptr);
    pthread_mutex_init(&orderIncomingMutex, nullptr);
    // pthread_mutex_init(&orderGivenMutex, nullptr);
    pthread_mutex_init(&orderMutex, nullptr);
    // pthread_mutex_init(&everyoneIsReadyMutex, nullptr);
    pthread_mutex_init(&numOfProperPrivatesMutex, nullptr);
    pthread_mutex_init(&numOfSmokersMutex, nullptr);
    pthread_mutex_init(&lockedAreasMutex, nullptr);
    sem_init(&canGiveOrder, 0, 0);
    // pthread_mutex_init(&giveTheOrderMutex, nullptr);

    // pthread_mutex_init(&executeOrderMutex, nullptr);
    // pthread_cond_init(&executeOrder, nullptr);

    // pthread_cond_init(&giveTheOrder, nullptr);
    pthread_cond_init(&orderIncoming, nullptr);
    // pthread_cond_init(&orderGiven, nullptr);
    // pthread_cond_init(&everyoneIsReady, nullptr);

    pthread_cond_init(&anAreaFreed, nullptr);
    pthread_mutex_init(&anAreaFreedMutex, nullptr);

    pthread_mutex_init(&smokerCellsMutex, nullptr);

    pthread_mutex_init(&smokingGridMutex, nullptr);

    sem_init(&executeOrder, 0, 0);
    sem_init(&everyoneIsReady, 0, 0);
    sem_init(&giveTheOrder, 0, 0);
    sem_init(&giveTheOrder, 0, 0);
    // sem_init(&orderIncoming, 0, 0);

    availablePrivates = 0;
    readyPrivates = 0;

    Input input = readInput();
    // input.print();

    bool stopOrderCame = false;

    setNumOfProperPrivates(input.numOfProperPrivates());
    setNumOfSmokers(input.numOfSmokers());

    vector<ProperPrivate *>::iterator itr = input.getProperPrivates().begin();
    vector<pthread_t> properPrivateThreads = vector<pthread_t>(getNumOfProperPrivates(), pthread_t());
    for (int c = 0; c < properPrivateThreads.size(); c++, itr++)
    {
        pthread_create(&properPrivateThreads[c], nullptr, runProperPrivate, *itr);
    }

    vector<Smoker *>::iterator itr2 = input.getSmokers().begin();
    vector<pthread_t> smokerThreads = vector<pthread_t>(getNumOfSmokers(), pthread_t());
    for (int c = 0; c < smokerThreads.size(); c++, itr2++)
    {
        pthread_create(&smokerThreads[c], nullptr, runSmoker, *itr2);
    }

    vector<pair<int, order>>::iterator orderItr;
    vector<pair<int, order>> orders = input.orders;
    for (orderItr = orders.begin(); orderItr != orders.end(); orderItr++)
    {
        int elapsedTime = since(start).count();
        while (elapsedTime < (*orderItr).first)
        {
            elapsedTime = since(start).count();
        }

        if (stopOrderCame || getNumOfProperPrivates() == 0)
        {
            notifyOrder((*orderItr).second);
            continue;
        }

        cerr << "The commander will broadcast the order incoming " << (*orderItr).second << endl;

        // if ((*orderItr).second == STOP)
        // {
        for (int i = 0; i < getNumOfProperPrivates() + getNumOfSmokers(); i++)
        {
            sem_wait(&canGiveOrder);
        }
        // }
        // else
        // {
        //     for (int i = 0; i < getNumOfProperPrivates(); i++)
        //     {
        //         sem_wait(&canGiveOrder);
        //     }
        // }

        setGlobalOrderWith((*orderItr).second);
        pthread_cond_broadcast(&orderIncoming);
        pthread_cond_broadcast(&anAreaFreed);
        cerr << "The commander broadcasted the order incoming" << endl;

        // Wait until each thread is available and waits for the order
        // Then send the order, clear the semaphore
        // Wait for all of them to respond then set the everyoneResponded (privates will wait for this)
        // Then the privates will actually execute the order

        int secondElapsedTime = since(start).count();
        cerr << "\tWill wait for the available privates. Ts: " << secondElapsedTime << endl;

        // pthread_mutex_lock(&giveTheOrderMutex);
        // pthread_cond_wait(&giveTheOrder, &giveTheOrderMutex);
        // pthread_mutex_unlock(&giveTheOrderMutex);

        sem_wait(&giveTheOrder);

        cerr << "\tWaited for the available privates. Ts: " << secondElapsedTime << endl;

        resetIntWithMutex(&availablePrivates, &availablePrivatesMutex, false);

        stopOrderCame = notifyOrder(globalOrdr);

        // pthread_cond_broadcast(&orderGiven);

        // sem_init(&orderGiven, 0, numOfProperPrivates);

        for (int i = 0; i < getNumOfProperPrivates() + getNumOfSmokers(); i++)
        {
            sem_post(&orderGiven);
        }

        cerr << "\tWill wait for the ready privates. Ts: " << secondElapsedTime << endl;

        // pthread_mutex_lock(&everyoneIsReadyMutex);
        // pthread_cond_wait(&everyoneIsReady, &everyoneIsReadyMutex);
        // pthread_mutex_unlock(&everyoneIsReadyMutex);

        sem_wait(&everyoneIsReady);

        cerr << "\tWaited for the ready privates. Ts: " << secondElapsedTime << endl;

        // pthread_cond_broadcast(&executeOrder);

        // sem_init(&executeOrder, 0, numOfProperPrivates);

        for (int i = 0; i < getNumOfProperPrivates() + getNumOfSmokers(); i++)
        {
            sem_post(&executeOrder);
        }

        resetIntWithMutex(&readyPrivates, &readyPrivatesMutex, true);

        setGlobalOrderWith(NONE);
    }

    for (int c = 0; c < smokerThreads.size(); c++)
    {
        pthread_join(smokerThreads[c], nullptr);
    }

    for (int c = 0; c < properPrivateThreads.size(); c++)
    {
        pthread_join(properPrivateThreads[c], nullptr);
    }

    // cerr << "The size of the locked areas: " << lockedAreas.size() << endl;

    return 0;
}
