#include <iostream>
#include <vector>

using namespace std;

class Process
{
public:
    vector<char *> argv;

    Process(vector<char *> argv)
    {
        this->argv = argv;
    }

    ~Process()
    {
        vector<char *>::iterator itr;
        for (itr = argv.begin(); itr != argv.end(); itr++)
        {
            delete[] * itr;
        }
    }

    char **getArgs()
    {
        vector<char *>::iterator itr;
        int argIndex = 1;
        for (itr = argv.begin() + 1; itr != argv.end(); itr++, argIndex++)
            ;

        char **args = new char *[argIndex + 1];
        argIndex = 0;
        for (itr = argv.begin(); itr != argv.end(); itr++, argIndex++)
        {
            args[argIndex] = *itr;
        }
        args[argIndex] = NULL;
        return args;
    }

    void print()
    {
        vector<char *>::iterator itr;
        for (itr = argv.begin(); itr != argv.end(); itr++)
        {
            // cout << *itr << " ";
        }
        // cout << endl;
    }
};

class Bundle
{
public:
    char *bundleName;
    vector<Process *> processes;

    Bundle(char *bundleName)
    {
        this->bundleName = bundleName;
    }

    ~Bundle()
    {
        vector<Process *>::iterator itr;
        for (itr = processes.begin(); itr != processes.end(); itr++)
        {
            delete *itr;
        }
        delete[] bundleName;
    }

    // Old argument: char **argv
    void insertProcess(vector<char *> argVector)
    {
        // vector<char *> argVector;
        // int argIndex = 0;
        // for (char *arg = argv[argIndex]; arg; arg = argv[++argIndex])
        // {
        //     argVector.push_back(arg);
        // }
        Process *process = new Process(argVector);
        processes.push_back(process);
    }

    void print()
    {
        vector<Process *>::iterator itr;
        // cout << "Bundle: " << bundleName << endl;
        for (itr = processes.begin(); itr != processes.end(); itr++)
        {
            (*itr)->print();
        }
    }
};

void printArgs(char **argv)
{
    int argIndex = 0;
    for (char *arg = argv[argIndex]; arg; arg = argv[++argIndex])
    {
        // cout << "Argument #" << argIndex << ": " << arg << endl;
    }
}

int sizeofCharPtr(char *str)
{
    int index = 0;
    char *ptr;
    for (ptr = str; *ptr; ptr++)
    {
        index++;
    }
    return index;
}
