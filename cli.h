#ifndef __CLI_H__
#define __CLI_H__

#include <stdio.h>
#include <stdint.h>

/*
 * cli call back function
 * @param char*     pointer to the user input
 * @param void*     pointer user argument 1
 * @param void*     pointer user argument 2
 */
typedef void (*cli_callback_t)(char*, void*, void*);

struct cli_struct
{
    const char* cmd;                // pointer to a command
    cli_callback_t callback;        // call back function to be executed
    void* arg1;                     // pointer call back argument 1
    void* arg2;                     // pointer call back argument 2
    int option_count;               // options counts
    struct cli_struct* next;        // cli_struct pointer array, these will 
                                    // the options for the current command
};

typedef struct cli_struct cli_struct_t;

/*
 * a default cli callback
 * 
 * @param char* input   pointer to user input string
 * @param void* arg1    pointer to optional argument 1 to the call back
 * @param void* arg2    pointer optional argument 2 to the call back
 */
void cli_default(char* input, void* arg1, void* arg2);

/*
 * Initial a cli struct
 * 
 * @param cli_struct* cli_struct        pointer to cli_struct_t
 * @param unsigned int cli_num          number of cli_struct_t to initialize
 */
void cli_param_init(cli_struct_t* cli_struct, unsigned int cli_num);


/*
 * print the content of a cli_struct_t
 * 
 * @param cli_struct_t* cli_struct      poiinter to cli_struct_t
 * @param unsigned int cli_num          number of cli_struct_t to print
 */
void cli_print(cli_struct_t* cli_struct, unsigned int cli_num);


/*
 * scan the input for command, and execute the
 * command as per callback
 * @param char* input               user command line input
 * @param cli_struct_t* cli_list    list commands to scan and associated call back function
 * @param int cli_num               number of command in the cli_list
 * @return                          0 = no match, 1 = match
 */
int cli_scan(char* input, cli_struct_t* cli_list, int cli_num);



#endif