#include <iostream>
#include <vector>
#include <tuple>
#include <pthread.h>
// #include "hw2_output.h"

// A private locks the area, waits, starts to collect cigbutts
// A private collects cigbutts from left to right, top to bottom (finish the row first, then move to the other row)
// A private waits if its area is already locked
// After a private collects every cigbutt, the thread stops

// Each thread may store the remaining cells, and remove the cells when they finish it
// So starting and continuing could be the same, lock the area and start collecting
// They should wait ONLY IF there are cells to be cleaned, if they are all clean, exit immediately

// A private should NOT lock even if a single cell is blocked

using namespace std;

class ProperPrivate
{
    int gid;
    int si, sj;
    int tg;
    // pthread_t *thread; // This is problematic when accessed
    vector<int *> areas;

public:
    ProperPrivate(int gidArg, int siArg, int sjArg, int tgArg)
    {
        this->gid = gidArg;
        this->si = siArg;
        this->sj = sjArg;
        this->tg = tgArg;
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

void initializeThread()
{
    cout << "asdasd" << endl;
}

void *runThread(void *ptr)
{
    ptr = (ProperPrivate *)ptr;
    initializeThread();
}

class Input
{
    int i;
    int j;
    int **grid;
    vector<ProperPrivate *> properPrivates;

public:
    Input(int i, int j)
    {
        this->i = i;
        this->j = j;
        grid = new int *[i];
        for (int c = 0; c < i; c++)
        {
            grid[c] = new int[j];
        }
    }

    vector<ProperPrivate *> &getProperPrivates()
    {
        return properPrivates;
    }

    int numOfProperPrivates()
    {
        return properPrivates.size();
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
        vector<ProperPrivate *>::iterator itr;
        for (itr = properPrivates.begin(); itr != properPrivates.end(); itr++)
        {
            (*itr)->print();
        }
    }

    ~Input()
    {
        for (int c = 0; c < i; c++)
        {
            delete[] grid[c];
        }
        delete[] grid;

        vector<ProperPrivate *>::iterator itr;
        for (itr = properPrivates.begin(); itr != properPrivates.end(); itr++)
        {
            delete (*itr);
        }
    }

    void addProperPrivate(ProperPrivate *priv)
    {
        properPrivates.push_back(priv);
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
        ProperPrivate *priv = new ProperPrivate(gid, si, sj, tg);
        for (int l = 0; l < numOfAreas; l++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            priv->addArea(x, y);
        }
        input.addProperPrivate(priv);
    }
    return input;
}

int main()
{
    Input input = readInput();
    input.print();

    int numOfProperPrivates = input.numOfProperPrivates();

    vector<ProperPrivate *>::iterator itr = input.getProperPrivates().begin();
    pthread_t threads[numOfProperPrivates];
    for (int c = 0; c < numOfProperPrivates; c++, itr++)
    {
        pthread_create(&threads[c], nullptr, runThread, *itr);
    }

    for (int c = 0; c < numOfProperPrivates; c++)
    {
        pthread_join(threads[c], nullptr);
    }

    // for (int c = 0; c < numOfProperPrivates; c++, itr++)
    // {
    //     pthread_join(*((*itr)->getThread()), nullptr);
    // }

    // for (int c = 0; c < numOfProperPrivates; c++)
    // {
    //     pthread_join(*threads[c], nullptr);
    // }

    return 0;
}

// struct timespec rem;

// struct timeval now;

// gettimeofday(&now, NULL);

// ts.tv_sec = tv.tv_sec;
// ts.tv_nsec = tv.tv_usec * 1000;

// struct timespec req = {
//     (int)(milliseconds / 1000),
//     (milliseconds % 1000) * 1000000};

// struct timespec req;
// req.tv_sec = now.tv_sec + (int)(milliseconds / 1000);
// req.tv_nsec = now.tv_usec + (milliseconds % 1000) * 1000000;

// struct timespec req = {1000, 10000000};
// return nanosleep(&req, &rem);