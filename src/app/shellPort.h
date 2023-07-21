#ifndef __SHELL_PORT
#define __SHELL_PORT
#include "../src/shell/shell_cpp.h"
#ifdef __cplusplus
extern "C"{
#endif
void userShellInit(void);
void printfMyIp();
#ifdef __cplusplus
}
#endif
#endif