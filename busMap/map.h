#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	//�����û�
	typedef struct{
		char name[20];
		char password[20];
		int access;
	}user;
	//�����ھӽڵ�ṹ
	//idΪΨһ��ʶ
	//distanceΪ�ڵ㵽�ھӽڵ���� 
	//routeΪ�ڵ㵽�ھӽڵ�Ŀ��÷�ʽ
	typedef struct neighbour{
		int id;
		float distance;
		char route[10];
		struct neighbour *next;
	}Neighbour; 
	//������� 
	//name�ڵ�����
	//nΪ�ھӽڵ�ļ��� 
	typedef struct point{
		int id;
		char name[10];
		Neighbour *first;
	}Point;

	//·�߹滮
	typedef struct way{
		int id;
		char name[10];
		char route[10];
		struct way *next;
	}wayNode;
	//��������ڵ�
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
