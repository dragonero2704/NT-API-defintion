//helper macros
#ifndef _MACROS
#define _MACROS
#include <stdio.h>
#define ok(msg, ...) (printf("[+] " msg "\n", ##__VA_ARGS__))
#define success(msg, ...) (ok(msg, ##__VA_ARGS__))
#define warning(msg, ...) (printf("[!] " msg "\n", ##__VA_ARGS__))
#define error(msg, ...) (printf("[-] " msg "\n", ##__VA_ARGS__))
#define info(msg, ...) (printf("[i] " msg "\n", ##__VA_ARGS__))

#define fok(file, msg, ...) (fprintf(file, "[+] " msg "\n", ##__VA_ARGS__))
#define fsuccess(file, msg, ...) (ok(file, msg, ##__VA_ARGS__))
#define fwarning(file, msg, ...) (fprintf(file, "[!] " msg "\n", ##__VA_ARGS__))
#define ferror(file, msg, ...) (fprintf(file, "[-] " msg "\n", ##__VA_ARGS__))
#define finfo(file, msg, ...) (fprintf(file, "[i] " msg "\n", ##__VA_ARGS__))
#endif

//debug macros
//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#define debug(msg, ...) (printf("[DEBUG] " msg "\n", ##__VA_ARGS__))
#else
#define debug(msg, ...) 
#endif