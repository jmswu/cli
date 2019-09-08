#include <stdio.h>
#include <stdint.h>
#include "cli.h"


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
