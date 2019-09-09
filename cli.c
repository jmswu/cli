#include <stdio.h>
#include <stdint.h>
#include "cli.h"
#include <ctype.h>

void cli_default(char* input, int arg1, int arg2){
    printf("input: %s, arg1: %d, arg2: %d\n", input, arg1, arg2);
}

void cli_param_init(cli_struct_t* cli_struct, unsigned int cli_num){
    for(unsigned int i = 0; i < cli_num; i++){
        cli_struct[i].cmd = "default";
        cli_struct[i].callback = cli_default;
        cli_struct[i].arg1 = 0;
        cli_struct[i].arg2 = 0;
        cli_struct[i].option_count = 0;
        cli_struct[i].next = (cli_struct_t*)NULL;
    }
}

void cli_print(cli_struct_t* cli_struct, unsigned int cli_num){
    for(unsigned int i = 0; i < cli_num; i++){
        printf("cmd: %s, cb: %p, arg1: %d, arg2: %d, count: %d, next: %p\n",
            cli_struct[i].cmd,
            cli_struct[i].callback,
            cli_struct[i].arg1,
            cli_struct[i].arg2,
            cli_struct[i].option_count,
            cli_struct[i].next);
    }
}

// parse a pattern in the buffer
// @param - char* buffer, char array needs to be parsed
// @param - const char* pattern, char array of pattern
// @return - 0 if no match, new pointer after the pattern if there is a match
char* cli_parse(char* buffer, const char* pattern);

char* cli_parse(char* buffer, const char* pattern)
{
    char p;  // store one char in pattern
    char b;  // store one char in buffer
    
    // make sure its a valid pointer
    if(buffer == 0)
        return 0;
    
    // skip all space
    while(isspace(*buffer))
        ++buffer;
    
    while(1)
    {
        // get one char from the pattern, then set the pointer to next 
        // char in pattern. 
        p = *pattern++;

        // check if it's end of the pattern, return new buffer pointer 
        // if its the end of pattern
        if(p == 0){
            // check the next char in the buffer is space, or its end of string
            // or, may result in a fake mis-match.
            // eg buffer = "hello", pattern = "he", this will come back as positive
            // also can use isspace() to check for space instead of checking for 0x20
            if ((*buffer == 0x20) || (*buffer == 0) || (*buffer == 0x0A))
                return buffer;
        }

        // convert to lower case for comparison, 
        b = tolower(*buffer++);

        // exit loop if the end of the buffer is reached, 
        // or the there is a mis-match in the data
        // continue to the next one if they are match, 
        // and not the end of the buffer
        if(b == 0 || b != p)
            break;
    }
    return 0;
}


void cli_scan(char* input, cli_struct_t* cli_list, int cli_num){
    //cli_print(cli_list, cli_num);

    char* return_ptr;       // return pointer from cli_parse()
    cli_struct_t cmd;       // one command from the cli_list

    // loop through all the command from the list
    for(int i = 0; i < cli_num; i++){

        // get one command from the list
        cmd = cli_list[i]; 

        cli_print(&cmd, 1);

        // parse the command in the user input
        return_ptr = cli_parse(input, cmd.cmd);

        printf("ptr: %p\n", return_ptr);

        // if a match is found
        if (return_ptr){
            cmd.callback(return_ptr, cmd.arg1, cmd.arg2);
        }
    }
}