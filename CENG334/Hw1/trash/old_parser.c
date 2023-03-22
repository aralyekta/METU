#include "old_parser.h"

using namespace std;

int parse(char *line, int is_bundle_creation, parsed_input *parsedInput)
{
    if (!parsedInput)
        return 0;
    int is_quoted;
    char buffer[256];
    int argument_count, argument_index;
    int index;

    memset(buffer, 0, sizeof(char) * 256);
    // Counts the number of arguments
    // index is the current index of the current argument
    if (is_bundle_creation)
    {
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        argument_count = 0;
        for (char *current = line; *current; current++)
        {
            if (is_quoted)
            {
                if (*current == '"')
                {
                    is_quoted = 0;
                }
                else
                    index++;
            }
            else
            {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current))
                {
                    if (index == 0)
                        continue;
                    argument_count++;
                    index = 0;
                }
                else
                    index++;
            }
        }

        parsedInput->parsed_input_union.argv = (char **)calloc(argument_count + 1, sizeof(char *));
        parsedInput->parsed_input_union.argv[argument_count] = NULL;
        parsedInput->parsed_input_type = INPUT_ARGS;
        printf("Parsed input type is set to args\n");

        is_quoted = 0;
        index = 0;
        for (char *current = line; *current; current++)
        {
            if (is_quoted)
            {
                if (*current == '"')
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            }
            else
            {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current))
                {
                    if (index == 0)
                        continue;
                    else if (strcmp(buffer, "pbs") == 0)
                    {
                        parsedInput->parsed_input_union.command.type = PROCESS_BUNDLE_STOP;
                        parsedInput->parsed_input_type = INPUT_COMMAND;
                        printf("Parsed input type is set to command\n");
                        return 1;
                    }
                    buffer[index++] = '\0';
                    parsedInput->parsed_input_union.argv[argument_index] = (char *)calloc(index, sizeof(char));
                    strcpy(parsedInput->parsed_input_union.argv[argument_index], buffer);
                    index = 0;
                    argument_index++;
                }
                else
                    buffer[index++] = *current;
            }
        }
    }
    else
    {
        is_quoted = 0;
        argument_count = 1;
        for (char *current = line; *current; current++)
        {
            if (is_quoted)
            {
                if (*current == '"')
                    is_quoted = 0;
            }
            else
            {
                if (*current == '"')
                    is_quoted = 1;
                else if (*current == '|')
                    argument_count++;
            }
        }
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        int is_next_input, is_next_output, executable_index;
        for (char *current = line; *current; current++)
        {
            if (is_quoted)
            {
                if (*current == '"')
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            }
            else
            {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current))
                {
                    if (index == 0)
                        continue;
                    buffer[index++] = '\0';
                    if (!argument_index)
                    {
                        if (strcmp(buffer, "pbc") == 0)
                        {
                            parsedInput->parsed_input_union.command.type = PROCESS_BUNDLE_CREATE;
                            parsedInput->parsed_input_type = INPUT_COMMAND;
                            printf("Parsed input type is set to command\n");
                        }
                        else if (strcmp(buffer, "pbs") == 0)
                        {
                            parsedInput->parsed_input_union.command.type = PROCESS_BUNDLE_STOP;
                            parsedInput->parsed_input_type = INPUT_COMMAND;
                            printf("Parsed input type is set to command\n");
                            return 1;
                        }
                        else if (strcmp(buffer, "quit") == 0)
                        {
                            parsedInput->parsed_input_union.command.type = QUIT;
                            parsedInput->parsed_input_type = INPUT_COMMAND;
                            printf("Parsed input type is set to command\n");
                            return 0;
                        }
                        else
                        {
                            parsedInput->parsed_input_union.command.type = PROCESS_BUNDLE_EXECUTION;
                            parsedInput->parsed_input_type = INPUT_COMMAND;
                            printf("Parsed input type is set to command\n");
                            parsedInput->parsed_input_union.command.bundle_count = argument_count;
                            parsedInput->parsed_input_union.command.bundles = (bundle_execution *)calloc(argument_count, sizeof(bundle_execution));

                            is_next_input = 0;
                            is_next_output = 0;
                            executable_index = 0;

                            parsedInput->parsed_input_union.command.bundles[executable_index].name = (char *)calloc(index, sizeof(char));
                            strcpy(parsedInput->parsed_input_union.command.bundles[executable_index].name, buffer);

                            parsedInput->parsed_input_union.command.bundles[executable_index].input = NULL;
                            parsedInput->parsed_input_union.command.bundles[executable_index].output = NULL;
                        }
                    }
                    else
                    {
                        if (parsedInput->parsed_input_union.command.type == PROCESS_BUNDLE_CREATE)
                        {
                            parsedInput->parsed_input_union.command.bundle_name = (char *)calloc(index, sizeof(char));
                            strcpy(parsedInput->parsed_input_union.command.bundle_name, buffer);
                            return 0;
                        }
                        else
                        {
                            if (argument_index % 2 == 1)
                            {
                                if (strcmp(buffer, "<") == 0)
                                    is_next_input = 1;
                                else if (strcmp(buffer, ">") == 0)
                                    is_next_output = 1;
                                else if (strcmp(buffer, "|") == 0)
                                    executable_index++;
                            }
                            else
                            {
                                if (is_next_input)
                                {
                                    parsedInput->parsed_input_union.command.bundles[executable_index].input = (char *)calloc(index, sizeof(char));
                                    strcpy(parsedInput->parsed_input_union.command.bundles[executable_index].input, buffer);
                                    is_next_input = 0;
                                }
                                else if (is_next_output)
                                {
                                    parsedInput->parsed_input_union.command.bundles[executable_index].output = (char *)calloc(index, sizeof(char));
                                    strcpy(parsedInput->parsed_input_union.command.bundles[executable_index].output, buffer);
                                    is_next_output = 0;
                                }
                                else
                                {
                                    parsedInput->parsed_input_union.command.bundles[executable_index].name = (char *)calloc(index, sizeof(char));
                                    strcpy(parsedInput->parsed_input_union.command.bundles[executable_index].name, buffer);
                                }
                            }
                        }
                    }
                    index = 0;
                    argument_index++;
                }
                else
                    buffer[index++] = *current;
            }
        }
    }
    return 0;
}
