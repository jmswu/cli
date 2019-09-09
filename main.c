#include <stdio.h>
#include <stdint.h>
#include "cli.h"

void l1_test1_func(char*, void*, void*);        // level 1 command, test1
void l1_test2_func(char*, void*, void*);        // level 1 command, test2
void l1_test3_func(char*, void*, void*);        // level 1 command, test3

int main(int argc, char *argv[])
{

    // declare command line structure
    cli_struct_t cmd_L1[3], cmd_L2[4];

    // initialise command line structure
    cli_param_init(cmd_L1, sizeof(cmd_L1)/sizeof(cmd_L1[0]));
    cli_param_init(cmd_L2, sizeof(cmd_L2)/sizeof(cmd_L2[0]));
    
    // built command line, level 1
    cmd_L1[0].callback = l1_test1_func;
    cmd_L1[0].cmd = "cmd1";

    cmd_L1[1].callback = l1_test2_func;
    cmd_L1[1].cmd = "cmd2";

    cmd_L1[2].callback = l1_test3_func;
    cmd_L1[2].cmd = "cmd3";

    printf("\n");

    // put command line into an array
    cli_struct_t* cmd_list[] = {
        &cmd_L1[0],
        &cmd_L1[1],
        &cmd_L1[2]
    };

    const int buff_size = 100; 
    char buff[buff_size];
    int rc;
    while(1){
        buff[0] = 0;
        printf("\ncmd:");
        fgets(buff, buff_size, stdin);

        rc = cli_scan(buff, cmd_list[0], sizeof(cmd_list)/sizeof(cmd_list[0]));
        if (rc == 0){
            printf("bad command, try:\n");
            for(int i = 0; i < sizeof(cmd_list)/sizeof(cmd_list[0]); i++){
                printf("%s\n", cmd_list[i]->cmd);
            }
        }
    }
    return 0;
}

void l1_test1_func(char* input, void* arg1, void* arg2){
    printf("Running L1_test_1\n\n");
}

void l1_test2_func(char* input, void* arg1, void* arg2){
    printf("Running L1_test_2\n\n");
}

void l1_test3_func(char* input, void* arg1, void* arg2){
    printf("Running L1_test_3\n\n");
}