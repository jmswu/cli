#include <stdio.h>
#include <stdint.h>
#include "cli.h"

void test1_func(char*, int, int);
void test2_func(char*, int, int);
void test3_func(char*, int, int);

int main(int argc, char *argv[])
{


    cli_struct_t cmd_L1[3], cmd_L2[4];

    cli_param_init(cmd_L1, sizeof(cmd_L1)/sizeof(cmd_L1[0]));
    cli_param_init(cmd_L2, sizeof(cmd_L2)/sizeof(cmd_L2[0]));
    
    cmd_L1[0].callback = test1_func;
    cmd_L1[0].cmd = "cmd1";

    cmd_L1[1].callback = test2_func;
    cmd_L1[1].cmd = "cmd2";

    cmd_L1[2].callback = test3_func;
    cmd_L1[2].cmd = "cmd3";
    
    cli_print(cmd_L1, sizeof(cmd_L1)/sizeof(cmd_L1[0]));
    cli_print(cmd_L2, sizeof(cmd_L2)/sizeof(cmd_L2[0]));

    printf("\n");

    cli_struct_t* cmd_list[] = {
        &cmd_L1[0],
        &cmd_L1[1],
        &cmd_L1[2]
    };

    for(int i = 0; i < sizeof(cmd_list)/sizeof(cmd_list[0]); i++){
        cli_print(cmd_list[i], 1);
        cmd_list[i]->callback("hello", 1, 1);
    }

    
    return 0;
}

void test1_func(char* input, int arg1, int arg2){
    printf("test_1\n");
}

void test2_func(char* input, int arg1, int arg2){
    printf("test_2\n");
}

void test3_func(char* input, int arg1, int arg2){
    printf("test_3\n");
}