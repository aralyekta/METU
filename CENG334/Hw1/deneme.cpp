#include <iostream>
#include <list>
#include <cstring>
#include <limits>
#include <queue>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void method(int pip1read, int pip2write)
{
    char buf[500];
    while (read(pip1read, &buf, 1) > 0)
    {
        cerr << "Got the char " << buf[0] << endl;
        write(pip2write, buf, 1);
    }
    cerr << "EOF received" << endl;
    close(pip2write);
}

int main()
{

    char *args[] = {"ls", NULL};
    execvp("/bin/ls", args);
    cout << "Print after exec" << endl;
    // int pipe1[2];
    // int pipe2[2];

    // pipe(pipe1);
    // pipe(pipe2);

    // char buf[512];

    // int stdCout = dup(1);

    // if (fork())
    // {
    //     if (fork())
    //     {
    //         close(pipe1[0]);
    //         close(pipe2[0]);
    //         close(pipe2[1]);
    //         dup2(pipe1[1], 1); // YOU ALSO NEED TO CLOSE 1
    //         close(pipe1[1]);

    //         cout << "asdasd";

    //         cout << "bebebe";
    //         // _exit(EXIT_SUCCESS);
    //     }
    //     else
    //     {
    //         // char *chr = new char;
    //         close(pipe1[0]);
    //         close(pipe1[1]);
    //         close(pipe2[1]);
    //         dup2(pipe2[0], 0);
    //         close(pipe2[0]);
    //         // int i = 0;

    //         string line;
    //         while (read(0, &buf, 1) > 0)
    //         {
    //             cerr << "Read the char " << buf[0] << endl;
    //         }
    //         cerr << "\nEnded reading from repeater" << endl;
    //         // while (read(0, chr, 1) > 0)
    //         // {
    //         //     buf[i++] = *chr;
    //         //     cerr << "Read " << chr << endl;
    //         // }
    //         // cerr << "Whole word is: " << buf << endl;
    //         // close(pipe2[0]);
    //         // delete chr;
    //         // _exit(EXIT_SUCCESS);
    //     }
    // }
    // else
    // {
    //     close(pipe1[1]);
    //     close(pipe2[0]);
    //     if (fork())
    //     {
    //         method(pipe1[0], pipe2[1]);
    //     }
    //     else
    //     {
    //         close(pipe1[0]);
    //         close(pipe2[1]);
    //     }
    // }

    // dup2(stdCout, 1);

    // if (fork())
    // {
    //     if (fork())
    //     {
    //         dup2(pipe1[1], 1);
    //         // close(pipe1[1]);
    //         cout << "asdasd";
    //         close(1);
    //         cerr << "Outed asdasd" << endl;
    //     }
    //     else
    //     {
    //         dup2(pipe2[0], 0);
    //         // close(pipe2[0]);
    //         close(pipe1[1]);
    //         string line;
    //         while (cin)
    //         {
    //             getline(cin, line);
    //             cerr << "Read " << line << endl;
    //             cout << line << endl;
    //         }
    //     }
    // }

    // close(pipe1[0]);
    // close(pipe1[1]);
    // close(pipe2[0]);
    // close(pipe2[1]);
}