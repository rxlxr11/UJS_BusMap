#ifndef IO_H
#define IO_H
#include "map.h"
//×·¼ÓÊý¾Ý
void append(char* ,char* );
void write_Point(char*,Point);
void readPoint(char *,Point *);
void readAll(char *,char **);
void write_all(char*,char **);
void write_bus(char*, LinkList*);
//print
void loginInter(void);
void adminMenu(void);
void stuMenu(void);
void printBus(LinkList*);
void printWay(wayNode*);
#endif
