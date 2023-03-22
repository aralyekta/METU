#include <stdio.h>
#include <iostream>
#include "parser.c"
#include "executeBundles.cpp"
using namespace std;

int main()
{
    string inputLine;
    vector<parsed_input> parsedInputVector;

    vector<Bundle *> definedBundles;

    Bundle *currentBundle;

    bool bundleCreate = 0;
    while (true)
    {
        parsed_input *parsedInput = new parsed_input;
        getline(cin, inputLine);
        char *convertedInput = new char[inputLine.size() + 2];

        // Convert the read file to a char *
        copy(inputLine.begin(), inputLine.end(), convertedInput);
        convertedInput[inputLine.size()] = ' '; // To be able to parse the string
        convertedInput[inputLine.size() + 1] = '\0';

        parse(convertedInput, bundleCreate, parsedInput);

        // cout << convertedInput << endl;

        if (bundleCreate)
        {
            if (parsedInput->command.type == PROCESS_BUNDLE_STOP)
            {
                bundleCreate = 0;
                // cout << "Bundle creation stopped" << endl;
                definedBundles.push_back(currentBundle);
                // cout << "Inserted the bundle: " << endl;
                // currentBundle->print();
                currentBundle = nullptr;
            }
            else
            {
                // cout << "Process, printing its arguments: " << endl;
                printArgs(parsedInput->argv);
                int index = 0;
                vector<char *> argVector;
                for (char *arg = parsedInput->argv[index]; arg; arg = parsedInput->argv[++index])
                {
                    char *argCopy = new char[sizeofCharPtr(arg) + 1];
                    strncpy(argCopy, arg, sizeofCharPtr(arg));
                    argCopy[sizeofCharPtr(arg)] = '\0';
                    free(arg);
                    argVector.push_back(argCopy);
                }
                free(parsedInput->argv);
                currentBundle->insertProcess(argVector);
            }
        }
        else
        {
            if (parsedInput->command.type == PROCESS_BUNDLE_CREATE)
            {
                bundleCreate = 1;
                // cout << "Bundle name to be created: " << parsedInput->command.bundle_name << endl;

                char *name = new char[sizeofCharPtr(parsedInput->command.bundle_name) + 1];
                strncpy(name, parsedInput->command.bundle_name, sizeofCharPtr(parsedInput->command.bundle_name));
                name[sizeofCharPtr(parsedInput->command.bundle_name)] = '\0';
                free(parsedInput->command.bundle_name);
                // delete[] name;
                currentBundle = new Bundle(name);
            }
            else if (parsedInput->command.type == PROCESS_BUNDLE_EXECUTION)
            {
                // cout << "Will execute bundles: " << parsedInput->command.bundle_count << endl;
                BundleList *bundleList = new BundleList;
                for (int i = 0; i < parsedInput->command.bundle_count; i++)
                {
                    bundle_execution bundle = parsedInput->command.bundles[i];
                    char *bundleName = new char[sizeofCharPtr(bundle.name) + 1];
                    char *input = nullptr;
                    char *output = nullptr;
                    strncpy(bundleName, bundle.name, sizeofCharPtr(bundle.name));
                    bundleName[sizeofCharPtr(bundle.name)] = '\0';
                    if (bundle.input)
                    {
                        input = new char[sizeofCharPtr(bundle.input) + 1];
                        strncpy(input, bundle.input, sizeofCharPtr(bundle.input));
                        input[sizeofCharPtr(bundle.input)] = '\0';
                    }
                    if (bundle.output)
                    {
                        output = new char[sizeofCharPtr(bundle.output) + 1];
                        strncpy(output, bundle.output, sizeofCharPtr(bundle.output));
                        output[sizeofCharPtr(bundle.output)] = '\0';
                    }
                    // if (input)
                    // cout << "input: " << input << endl;
                    // if (output)
                    // cout << "output: " << output << endl;
                    Bundle *deletedBundle = nullptr;
                    vector<Bundle *>::iterator itr;
                    for (itr = definedBundles.begin(); itr != definedBundles.end(); itr++)
                    {
                        if (strcmp(bundleName, (*itr)->bundleName) == 0)
                        {
                            deletedBundle = *itr;
                            // cout << "Erased the bundle from the defined bundles" << endl;
                            definedBundles.erase(itr);
                            // cout << "New size: " << definedBundles.size() << endl;
                            break;
                        }
                    }
                    if (deletedBundle)
                    {
                        // cout << endl;
                        BundleExec *copyBundle = new BundleExec(deletedBundle, input, output);
                        bundleList->insertBundle(copyBundle);
                    }
                    // cout << "Bundle: " << bundleName << endl;
                    delete[] bundleName;
                    free(bundle.name);
                    free(bundle.input);
                    free(bundle.output);
                }
                free(parsedInput->command.bundles);

                bundleList->executeBundles();

                delete bundleList;
            }
        }

        if (parsedInput->command.type == QUIT)
        {
            delete[] convertedInput;
            delete parsedInput;
            break;
        }

        delete[] convertedInput;
        delete parsedInput;
    }

    vector<Bundle *>::iterator itr;
    for (itr = definedBundles.begin(); itr != definedBundles.end(); itr++)
    {
        delete *itr;
    }

    return 0;
}