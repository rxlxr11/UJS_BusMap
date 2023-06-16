#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	//定义用户
	typedef struct{
		char name[20];
		char password[20];
		int access;
	}user;
	//定义邻居节点结构
	//id为唯一标识
	//distance为节点到邻居节点距离 
	//route为节点到邻居节点的可用方式
	typedef struct neighbour{
		int id;
		float distance;
		char route[10];
		struct neighbour *next;
	}Neighbour; 
	//定义各点 
	//name节点名称
	//n为邻居节点的集合 
	typedef struct point{
		int id;
		char name[10];
		Neighbour *first;
	}Point;

	//路线规划
	typedef struct way{
		int id;
		char name[10];
		char route[10];
		struct way *next;
	}wayNode;
	//定义链表节点
	typedef struct node{
		char name[10];
		struct node *prior;
		struct node *next;
	}LNode,LinkList;
	int login(char *);
	void registe();
	LinkList* createLink(char *);
	void insert_wayNode(wayNode *,int,char *,char *);
	void copy_way(wayNode*,wayNode*);
	wayNode* createWay(void);
	Neighbour* find_Neighbour(int , Point);
	char* edit_point_file_name(int);
	char* edit_bus_file_name(char *);
#endif
