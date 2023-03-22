#include "helpers.cpp"
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>

void repeaterFunc(int inputPipeRead, vector<int *> outputPipesWrite, char *bundle)
{
    /*
    Repeater process shall connect to the output pipes and copy the values it reads
    From its input pipe to each output pipe
    If the input pipe is closed, then close all connections to the output pipes
    It is assumed that the pipe connections are already established
    */

    // cerr << "Entered the repeater func. for bundle: " << bundle << ". Input pipe is: " << inputPipeRead << endl;

    char buf[512];

    while (read(inputPipeRead, &buf, 1) > 0)
    {
        // if (bundle[0] == 'p' && bundle[1] == 'b' && bundle[2] == '3')
        //     cerr << "Read " << buf[0] << " " << (int)buf[0] << endl;
        char chr = buf[0];
        for (vector<int *>::iterator itr = outputPipesWrite.begin(); itr != outputPipesWrite.end(); itr++)
        {
            // cerr << "Sending " << chr << " to pipe: " << (*itr)[1] << endl;
            write((*itr)[1], &chr, 1);
        }
    }

    // if (bundle[0] == 'p' && bundle[1] == 'b' && bundle[2] == '3')
    //     cerr << "Got EOF in repeater, will close everything" << endl;

    // Close the write ends of the successor pipes
    // for (itr = outputPipesWrite.begin(); itr != outputPipesWrite.end(); itr++)
    // {
    //     close(*itr);
    // }

    _exit(EXIT_SUCCESS);
}

class BundleExec
{
public:
    Bundle *bundle;
    char *input;
    char *output;

    BundleExec(Bundle *bundle, char *input, char *output)
    {
        this->bundle = bundle;
        this->input = input;
        this->output = output;
    }

    ~BundleExec()
    {
        delete bundle;
        if (input)
            delete[] input;
        if (output)
            delete[] output;
    }
};

class BundleList
{
public:
    vector<BundleExec *> bundleList;

    ~BundleList()
    {
        vector<BundleExec *>::iterator itr;
        for (itr = bundleList.begin(); itr != bundleList.end(); itr++)
        {
            delete *itr;
        }
    }

    void insertBundle(BundleExec *bundle)
    {
        bundleList.push_back(bundle);
    }

    void executeBundles()
    {
        if (bundleList.size() == 1)
        {
            BundleExec *bundle = *(bundleList.begin());
            vector<Process *> processes = bundle->bundle->processes;
            vector<Process *>::iterator itr;
            int i = 0;
            // Iterate each process

            int inputFile = -1;
            int outputFile = -1;

            int forkCtr = 0;

            int savedStdin = dup(0);
            int savedStdout = dup(1);

            for (itr = processes.begin(); itr != processes.end(); itr++, i++)
            {
                char **args = (*itr)->getArgs();

                if (bundle->input)
                {
                    FILE *inputFile = fopen(bundle->input, "r");
                    dup2(fileno(inputFile), 0);
                    fclose(inputFile);
                }

                if (bundle->output)
                {
                    // O_APPEND mode of open() corrupts the file, thats why I use fopen() instead
                    FILE *outputFile = fopen(bundle->output, "a");
                    dup2(fileno(outputFile), 1);
                    fclose(outputFile);
                }

                forkCtr++;
                int forkRes = fork();
                if (forkRes == 0)
                {
                    // Child
                    // cerr << "Iteration #" << i << " and will execute " << args[0] << endl;

                    execvp(args[0], args);
                }
                delete[] args;
            }

            // Reap the children
            for (int j = 0; j < i; j++)
            {
                int var;
                wait(&var);
            }

            dup2(savedStdin, 0);
            dup2(savedStdout, 1);

            for (int i = 0; i < forkCtr; i++)
            {
                wait(NULL);
            }
        }
        else if (bundleList.size() > 1)
        {
            /*
            ** 1- Iterate each bundle
                Check if it has input/output file
                Check if it has a successor bundle
                    If no: Dont set anything (stdout)
                    If yes: Create a new pipe (for the repeater), set the outputs to it
                Check if it has a predecessor exists for echoessor bundle
                    If no: The input is from a file, do nothing
                    If yes: Create new input pipes for each process, connect them to the processes
                            Fork and run the repeater process (provide the input pipes), exit when it is done
                            Repeater process shall connect to the output pipes and copy the values it reads
                            From its input pipe to each output pipe
                            If the input pipe is closed, then close all connections to the output pipes
                            Close unnecessary pipe descriptors in the parent before forking
            ** 2- Iterate each process inside it
            ** 3- Reap the children
            */

            int bundleCtr = 0;
            int forkCtr = 0;
            int savedStdin = dup(0);
            int savedStdout = dup(1);
            int prevOutPipe[2] = {-1, -1};
            for (vector<BundleExec *>::iterator bundleItr = bundleList.begin(); bundleItr != bundleList.end(); bundleItr++, bundleCtr++)
            {
                bool predExists = false;
                bool succExists = false;
                if (bundleCtr > 0)
                    predExists = true;
                if (bundleItr + 1 != bundleList.end())
                    succExists = true;

                // TODO: Add file functionality
                int outPipe[2] = {-1, -1};

                int inputFile = -1;
                int outputFile = -1;

                if ((*bundleItr)->input)
                {
                    FILE *inputFile = fopen((*bundleItr)->input, "r");
                    dup2(fileno(inputFile), 0);
                    fclose(inputFile);
                }

                if ((*bundleItr)->output)
                {
                    FILE *outputFile = fopen((*bundleItr)->output, "a");
                    dup2(fileno(outputFile), 1);
                    fclose(outputFile);
                }

                vector<int *> InputPipes;
                char *bundleName = (*bundleItr)->bundle->bundleName;

                // cerr << "For bundle " << bundleName << " pred: " << predExists << " and succ: " << succExists << endl;

                if (succExists)
                {
                    pipe(outPipe);
                    dup2(outPipe[1], 1);
                    close(outPipe[1]);
                    // Dont worry about the write end of the out pipe
                    // Only worry about its read end
                }

                vector<Process *> processes = (*bundleItr)->bundle->processes;
                for (vector<Process *>::iterator itr = processes.begin(); itr != processes.end(); itr++)
                {
                    char **args = (*itr)->getArgs();
                    if (predExists)
                    {
                        int *inPipe = new int[2];
                        pipe(inPipe);
                        InputPipes.push_back(inPipe);
                        dup2(inPipe[0], 0);
                        close(inPipe[0]);
                    }

                    forkCtr++;
                    int parent = fork();
                    if (parent)
                    {
                    }
                    else
                    {
                        for (vector<int *>::iterator inPipeItr = InputPipes.begin(); inPipeItr != InputPipes.end(); inPipeItr++)
                        {
                            close((*inPipeItr)[1]);
                        }
                        close(outPipe[0]);
                        // cerr << "Executing " << args[0] << endl;

                        if ((*bundleItr)->input)
                        {
                            FILE *inputFile = fopen((*bundleItr)->input, "r");
                            dup2(fileno(inputFile), 0);
                            fclose(inputFile);
                        }
                        execvp(args[0], args);
                    }
                }

                if (predExists)
                {
                    forkCtr++;
                    int parent = fork();
                    if (parent)
                    {
                        for (vector<int *>::iterator inPipeItr = InputPipes.begin(); inPipeItr != InputPipes.end(); inPipeItr++)
                        {
                            close((*inPipeItr)[1]);
                        }
                        close(prevOutPipe[0]);
                    }
                    else
                    {
                        // cerr << "Executing repeater for " << bundleName << endl;
                        // close(prevOutPipe[1]);
                        repeaterFunc(prevOutPipe[0], InputPipes, bundleName);
                        // cerr << "Returned from repeater" << endl; // Shouldn't happen
                    }
                }

                close(prevOutPipe[0]);
                // close(prevOutPipe[1]); // Commenting this allowed me to send data from pb2 to pb3
                if (succExists)
                {
                    // cerr << "At bundle:" << bundleName << " and setting the prevOutPipe" << endl;
                    prevOutPipe[0] = outPipe[0];
                    prevOutPipe[1] = outPipe[1];
                }
                else
                {
                    close(outPipe[0]);
                }

                // This line prevents the repeater from reading the prevOutPipe
                // close(outPipe[0]);

                dup2(savedStdout, 1);
                dup2(savedStdin, 0); // If you dont do this, the main program will continue to read from the pipe instead of stdin
            }

            // Reap all of the children

            // cerr << "Fork ctr: " << forkCtr << endl;
            for (int i = 0; i < forkCtr; i++)
            {
                wait(NULL);
            }
        }
    }
};