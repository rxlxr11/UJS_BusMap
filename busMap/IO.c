#include "IO.h"
#include "function.h"
//׷������
void append(char* name,char* s) {
	FILE *f;
	f = fopen(name,"a+");
	fprintf(f,"%s\n",s);
	fclose(f);
}
//��ȡ�ڵ�����
void readPoint(char *name,Point *p){
	FILE *f;
	f = fopen(name,"r");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		fscanf(f,"%d %s\n",&p->id,p->name);
		p->first=NULL;
		int x;
		float y;
		char s[10];
		while(fscanf(f,"%d %f %s\n",&x,&y,s) != EOF){
			Neighbour *n;
			n=(Neighbour*)malloc(sizeof(Neighbour));
			n->id=x;
			n->next=p->first;
			n->distance=y;
			strcpy(n->route,s);
			p->first=n;
		}
	}
	fclose(f);
}
//д��ڵ�����
void write_Point(char *name,Point p){
	FILE *f;
	f = fopen(name,"w+");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		fprintf(f,"%d %s\n",p.id,p.name);
		Neighbour *n=p.first;
		while(n!=NULL){
			fprintf(f,"%d %.2f %s\n",n->id,n->distance,n->route);
			n=n->next;
		}
	}
	fclose(f);
}
//��ȡall�ļ�
void readAll(char *name,char **s){
	FILE *f;
	f = fopen(name,"r");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		int i=0;
		s[i]=(char*)malloc(100*sizeof(char));
		while(fscanf(f,"%s\n",s[i]) != EOF){
			i++;
			s[i]=(char*)malloc(100*sizeof(char));
		}
	}
	fclose(f);
}
void write_bus(char *s,LinkList* L){
	LinkList *T=L;
	FILE *F=fopen(s,"w+");
	while(T->next!=NULL){
		//TODO
		fprintf(F,"%s\n",T->name);
		T=T->next;
	}
}
//��¼
void loginInter(){
	printf("+-------------------------------+\n");
	printf("|         ��·��ѯϵͳ          |\n");
	printf("+-------------------------------+\n");
	printf("|          1. ��¼              |\n");
	printf("|          2. ע��              |\n");
	printf("|         -1. �˳�              |\n");
	printf("+-------------------------------+\n");
}
//����Ա�˵�
void adminMenu(){
	printf("+-------------------------------+\n");
	printf("|         ��·��ѯϵͳ          |\n");
	printf("+-------------------------------+\n");
	printf("|1. ����������·                |\n");
	printf("|2. �޸����й�����·            |\n");
	printf("|3. ɾ��������·վ��            |\n");
	printf("|4. ����վ��                    |\n");
	printf("+-------------------------------+\n");
	printf("|5. ��ѯ�����õ�����й���·��  |\n");
	printf("|6. ��ѯ���й���·��            |\n");
	printf("|7. ��ѯ���пɴ�·��            |\n");
	printf("|8. ����·�߹滮                |\n");
	printf("|9. ��ѯһ�㵽����վ������·��|\n");
	printf("|10.�鿴�Ƿ��л���              |\n");
	printf("|-1.�˳�                        |\n");
	printf("+-------------------------------+\n");
}
//ѧ���˲˵�
void stuMenu(){
	printf("+-------------------------------+\n");
	printf("|         ��·��ѯϵͳ          |\n");
	printf("+-------------------------------+\n");
	printf("|1. ��ѯ�����õ�����й���·��  |\n");
	printf("|2. ��ѯ���й���·��            |\n");
	printf("|3. ��ѯ���пɴ�·��            |\n");
	printf("|4. ����·�߹滮                |\n");
	printf("|5. ��ѯһ�㵽����վ������·��|\n");
	printf("|6. �鿴�Ƿ��л���              |\n");
	printf("|-1.�˳�                        |\n");
	printf("+-------------------------------+\n");
}
void printBus(LinkList* L){
	LNode* p=(LNode*)malloc(sizeof(LNode));
	char temp[10];
	strcpy(temp,L->name);
	char **contain;
	contain=(char**)malloc(sizeof(char*));
	splitComma(temp,contain);
	char busName[10];
	strcpy(busName,contain[0]);
	strcpy(temp,contain[1]);
	float f=atof(temp);
	p=L->next;
	printf("+========================================================================+\n");
	printf(" %s����,��Ʊ:%.2fԪ	",busName,f);
	while(p!=NULL){
		printf("%s",p->name);
		if(p->next!=NULL){
			printf("<-->");
		}
		p=p->next;
	}
	printf("\n");
	printf("+========================================================================+\n");
	
}
void printWay(wayNode *n){
	printf("+==============================================================================================+\n");
	printf(" %s", n->name);
	while(n != NULL){
		//TODO
		n=n->next;
		if(n!=NULL){
			//TODO
			printf("--%s-->",n->route);
			printf("%s",n->name);
		}
	}
	printf("\n");
	printf("+==============================================================================================+\n");
}
