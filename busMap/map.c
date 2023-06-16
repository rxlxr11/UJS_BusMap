#include "map.h"
//登录
int login(char *name){
	int flag=-1;
	user *u;
	u=(user*)malloc(sizeof(user));
	char* userFile="D:/study/za/dataStructure/user/all.txt";
	FILE *f=fopen(userFile,"r");
	if(f==NULL)
	{	
		printf("open file error");
		exit(0);
	}	
	else{
		int a;
		while(fscanf(f,"%s %s %d\n",u->name,u->password,&u->access) != EOF){
			a=strcmp(u->name,name);
			if(a==0){
				//TODO
				char s[20];
				int i=2;
				for(;i>=0;i--){
					//TODO
					int b;
					printf("请输入密码：");
					scanf("%s",s);
					b=strcmp(u->password,s);
					if(b==0){
						printf("登录成功\n");
						flag = u->access;
						break;
					}
					else{
						printf("密码错误,你还有%d次机会\n",i);
					}
				}
				break;	
			}
		}
		if(a!=0)
			printf("未找到该用户\n");
	}
	return flag;
}
//注册
void registe(){
	int a=-1,flag,b=-1;
	user *u;
	u=(user*)malloc(sizeof(user));
	char* userFile="D:/study/za/dataStructure/user/all.txt";
	FILE *f=fopen(userFile,"a+");
	char name[20];
	char password[20];
	printf("请输入用户名：");
	scanf("%s",name);
	flag=0;
	while(1){
		int len=strlen(name);
		if(len>20){
			printf("不符合规则，请重新输入：");
			scanf("%s",name);
		}
		else{
			break;
		}
	}
	while(flag!=1){
		rewind(f);
		b=-1;
		while(fscanf(f,"%s %s %d\n",u->name,u->password,&u->access) != EOF){
			a=strcmp(u->name,name);
			if(a == 0){
				//TODO
				printf("用户名已存在,请重新输入\n");
				b=0;
			}
		}
		if(b!=0){
			flag=1;
			strcpy(u->name,name);
			break;
		}
		printf("请输入用户名：");
		scanf("%s",name);
	}
	printf("请输入密码：");
	scanf("%s",password);
	while(1){
		int len=strlen(password);
		if(len>20){
			printf("不符合规则，请重新输入：");
			scanf("%s",password);
		}
		else{
			strcpy(u->password,password);
			break;
		}
	}
	fprintf(f,"%s %s %d\n",u->name,u->password,0);
	fclose(f);
	printf("注册成功");
}

//创建公交链路
LinkList* createLink(char *s){
	LinkList* L;
	L=(LNode*)malloc(sizeof(LNode));
	L->next=NULL;
	L->prior=NULL;
	FILE *f;
	f=fopen(s,"r");
	fscanf(f,"%s",L->name);
	char str[20];
	while(fscanf(f,"\n%s",str) != EOF){
		LNode* p=(LNode*)malloc(sizeof(LNode));
		strcpy(p->name,str);
		p->next=L->next;
		p->prior=L;
		if(L->next!=NULL)
			L->next->prior=p;
		L->next=p;
	}
	fclose(f);
	return L;
}
//尾插法
void insert_wayNode(wayNode *n,int id,char *name,char *route){
	while(n->next!=NULL){
		n=n->next;
	}
	wayNode *x=(wayNode*)malloc(sizeof(wayNode));
	x->id=id;
	strcpy(x->name,name);
	strcpy(x->route,route);
	x->next=NULL;
	n->next=x;
}
void copy_way(wayNode *source,wayNode *wcopy){
	wcopy->next=NULL;
	wayNode *wc=(wayNode*)malloc(sizeof(wayNode));
	wc=source->next;
	while(wc!=NULL){
		insert_wayNode(wcopy,wc->id,wc->name,wc->route);
		wc=wc->next;
	}
}
wayNode* createWay() {
	wayNode *n;
	n = (wayNode*)malloc(sizeof(wayNode));
	return n;
}
Neighbour* find_Neighbour(int id, Point p) {
	Neighbour *n = p.first;
	while (n != NULL) {
		//TODO
		if (id == n->id) {
			//TODO
			break;
		}
		n = n->next;
	}
	return n;
}
char* edit_point_file_name(int id){
	char *fileN;
	fileN=(char*)malloc(200*sizeof(char));
	strcpy(fileN,"D:/study/za/dataStructure");
	strcat(fileN,"/point/");
	char name[10];
	sprintf(name,"%d",id);
	strcat(fileN,name);
	strcat(fileN,".txt");
	return fileN;
}
char* edit_bus_file_name(char *name){
	char *fileN;
	fileN=(char*)malloc(200*sizeof(char));
	strcpy(fileN,"D:/study/za/dataStructure");
	strcat(fileN,"/bus/");
	strcat(fileN,name);
	strcat(fileN,".txt");
	return fileN;
}
