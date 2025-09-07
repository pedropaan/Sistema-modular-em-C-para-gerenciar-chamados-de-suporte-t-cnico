#include "../include/log.h"
#include <time.h>

void log_msg(FILE* logf, const char* nivel, const char* msg) {
    time_t now = time(NULL); char buf[20]; strftime(buf,sizeof buf,"%Y-%m-%d %H:%M:%S",localtime(&now));
    if (logf){ fprintf(logf,"[%s] %s: %s\n",buf,nivel,msg); fflush(logf); }
}