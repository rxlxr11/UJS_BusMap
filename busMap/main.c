#include "IO.h"
#include "function.h"
#include "map.h"
#define MAX 99999999
#define MAXSIZE 25
Point allPoint[MAXSIZE];
LinkList* busRoute[10];
//定义速度
float humanV=2.7;
float busV=8.3;
char* fileName="D:/study/za/dataStructure";
char* busAllFileName="D:/study/za/dataStructure/bus/all.txt";
char* pointAllFileName="D:/study/za/dataStructure/point/all.txt";
char* userAllFileName="D:/study/za/dataStructure/user/all.txt";
char **pointFileName, **busFileName;
int busCount=0;
int pointCount=0;
//纪录公交线路名称
char busName[10][10];
//记录对应公交价格
float busPrice[10];
//记录所有站点名称
char allPointName[MAXSIZE][10];
//记录站点id
int allPointId[MAXSIZE];
//初始化
void init() {
	printf("初始化中请稍后...\n");
	FILE *f;
	f = fopen("D:/study/za/dataStructure/demo.txt", "r");
	if (f == NULL) {
		printf("error");
		exit(0);
	} else {
		fscanf(f,"%d\n",&pointCount);
		fscanf(f, "%d\n", &busCount);
	}
	fclose(f);
	pointFileName = (char**)malloc(25 * sizeof(char*));
	busFileName = (char**)malloc(10 * sizeof(char*));
	readAll(pointAllFileName, pointFileName);
	readAll(busAllFileName, busFileName);
	for (int i = 0; i < pointCount; i++) {
		readPoint(pointFileName[i], &allPoint[i]);
		strcpy(allPointName[i], allPoint[i].name);
		allPointId[i] = allPoint[i].id;
	}
	
	for (int i = 0; i < busCount; i++) {
		busRoute[i] = createLink(busFileName[i]);
		char temp[10];
		strcpy(temp, busRoute[i]->name);
		char **contain;
		contain = (char**)malloc(sizeof(char*));
		splitComma(temp, contain);
		strcpy(busName[i], contain[0]);
		strcpy(temp, contain[1]);
		busPrice[i] = atof(temp);
	}
	printf("初始化完成!!!\n");
}
//根据名称找id
int findID_byName(char *s) {
	int id = -1;
	for (int i = 0; i < pointCount; i++) {
		if (equal_f(allPointName[i], s)) {
			id = allPointId[i];
			break;
		}
	}
	return id;
}
//写入demo文件
void write_demo(){
	FILE *f=fopen("D:/study/za/dataStructure/demo.txt","w+");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		fprintf(f,"%d\n",pointCount);
		fprintf(f,"%d\n",busCount);
	}
	fclose(f);
}
//根据id找站点
Point findPoint(int id){
	Point p;
	for(int i=0;i<pointCount;i++){
		if(id==allPoint[i].id){
			p=allPoint[i];
		}
	}
	return p;
}
int method_f(Neighbour *n){
	int method=equal_f(n->route,"z");
	return method;
}
//新增公交线路
void addBus() {
	char busname[10];
	float busPrice_f;
	char busPrice_s[10];
	char input[200];
	char **pointName;
	pointName = (char**)malloc(sizeof(char*));
	int a = 0;
	printf("请输入公交线路名称：");
	scanf("%s", busname);
	//判断公交路线名是否存在
	while (1) {
		a=0;
		for (int i = 0; i < busCount; i++) {
			printf("%s",busName[i]);
			if (equal_f(busname,busName[i])) {
				printf("该公交线路名称已存在，请重新输入");
				a=1;
				break;
			}
		}
		if(!a)
			break;
		printf("请输入公交线路名称：");
		scanf("%s", busname);
	}
	printf("请输入公交线路价格：");
	scanf("%f", &busPrice_f);
	printf("请依次输入公交站点\n");
	scanf("%s", input);
	//将输入的站点分割
	int count = splitComma(input, pointName);
	int flag = 1;
	int i = 0;
	Neighbour *n;
	int location[MAXSIZE];
	while (i < count) {
		location[i]=findID_byName(pointName[i]);
		if (location[i] == -1) {
			//若有不存在的站点则退出
			printf("不存在%s", pointName[i]);
			flag = 0;
			break;
		}
		i++;
	}
	i = 0;
	int flag3 = 1;
	while (flag && i < count - 1) {
		//开始判断能否到达下一站
		n=find_Neighbour(findID_byName(pointName[i+1]),findPoint(findID_byName(pointName[i])));
		if (n == NULL) {
			//TODO
			flag3 = 0;
			printf("%s%s请重新规划路线\n", pointName[i], pointName[i + 1]);
			break;
		}
		i++;
	}
	if (flag3 && flag) {
		//写入文件
		char newFile[200];
		char first[10];
		sprintf(busPrice_s, "%.2f", busPrice_f);
		strcpy(first, busname);
		strcat(first, ",");
		strcat(first, busPrice_s);
		strcpy(newFile, "D:/study/za/dataStructure/bus/");
		strcat(newFile, busname);
		strcat(newFile, ".txt");
		
		busRoute[busCount++] = createLink(newFile);
		for(i=0;i<count-1;i++){
			//TODO
			Neighbour *nt2 =find_Neighbour(findID_byName(pointName[i]), allPoint[locate_int(findID_byName(pointName[i+1]),allPointId,pointCount)]);
			Neighbour *nt1 =find_Neighbour(findID_byName(pointName[i+1]), allPoint[locate_int(findID_byName(pointName[i]),allPointId,pointCount)]);
			if(equal_f(nt1->route,"z")){
				//TODO
				strcpy(nt1->route, busname);
				strcpy(nt2->route, busname);
			}
			else{
				strcat(strcat(nt1->route,","),busname);
				strcat(strcat(nt2->route,","),busname);
			}
			char name1[10];
			char name2[10];
			sprintf(name1,"%d",findID_byName(pointName[i]));
			sprintf(name2,"%d",findID_byName(pointName[i+1]));
			char fileN1[200];
			char fileN2[200];
			strcpy(fileN1,fileName);
			strcpy(fileN2,fileName);
			strcat(strcat(strcat(fileN1,"/point/"),name1),".txt");
			strcat(strcat(strcat(fileN2,"/point/"),name2),".txt");
			write_Point(fileN1,findPoint(findID_byName(pointName[i])));
			write_Point(fileN2,findPoint(findID_byName(pointName[i+1])));
		}
		
		//写入demo
		write_demo();
		append(busAllFileName, newFile);
		//写入公交文件
		append(newFile, first);
		i = 0;
		while (i < count) {
			//TODO
			append(newFile, pointName[i]);
			i++;
		}
	}
	printf("新增公交线路已完成！！！");
}
//修改已有公交线路
//还有改名称后公交线路里面的名称也要改掉；
void alterPoint() {
	char name[10];
	char newName[10];
	int location;
	printf("请输入要修改的站点名称：");
	scanf("%s", name);
	while(findID_byName(name)==-1){
		//TODO
		printf("未找到站点，请重新输入：");
		scanf("%s",name);
	}
	//save the location of the point that needs to be changed
	location = locate_int(findID_byName(name),allPointId,pointCount);
	//save the first neighbour node
	Neighbour *n=findPoint(findID_byName(name)).first;
	printf("是否要修改名称？[Y/N]:");
	char ins;
	scanf("%c",&ins);
	getchar();
	//need to change the name of the point
	if(ins == 'Y'){
		//TODO
		printf("请输入新名称：");
		scanf("%s",newName);
		// preserve the old name
		char oldName[10];
		strcpy(oldName, allPointName[location]);
		for (int i = 0; i < busCount; i++) {
			int need=0;
			LNode* p = (LNode*)malloc(sizeof(LNode));
			p = busRoute[i]->next;
			while (p != NULL) {
				// judge if there is a need to change the bus route
				if (equal_f(p->name, oldName)) {
					need = 1;
					// modify the name that corresponds to it
					strcpy(p->name, newName);
				} 
				p = p->next;
			}
			// if there is a need to change the bus route
			if(need){
				char head[20];
				strcpy(head,busRoute[i]->name);
				char **contain=(char**)malloc(sizeof(char*));
				splitComma(head,contain);
				char *fileN = edit_bus_file_name(contain[0]);
				// write to the file of bus
				write_bus(fileN,busRoute[i]);
			}
		}
		strcpy(allPointName[location],newName);
		strcpy(allPoint[location].name,newName);
	}
	// change the distance between a and b
	while(n != NULL){
		printf("是否修改%s到%s的距离？[Y/N]:",allPointName[location],findPoint(n->id).name);
		scanf(" %c",&ins);
		if(ins == 'Y'){
			//TODO
			printf("请输入新距离：");
			float dis;
			scanf("%f",&dis);
			getchar();
			Neighbour *nn=find_Neighbour(allPoint[location].id,findPoint(n->id));
			nn->distance=dis;
			char *fn=edit_point_file_name(n->id);
			write_Point(fn,findPoint(n->id));
			n->distance=dis;
		}
		n=n->next;
	}
	// wirte to the file to the point
	char idS[10];
	sprintf(idS,"%d",findID_byName(newName));
	printf("id is %s",idS);
	char *newFileN=edit_point_file_name(findID_byName(allPointName[location]));
	write_Point(newFileN,allPoint[location]);
	printf("修改站点信息成功\n");
}
//删除站点
void delPoint() {
	char name[10];
	printf("请输入站点名：");
	scanf_s("%s",name);
	//查找该站点是否存在
	while(findID_byName(name) == -1){
		//TODO
		printf("重新输入");
		scanf_s("%s",name);
	}
	//记录站点id
	int id = findID_byName(name);
	int location = locate_int(id,allPointId,pointCount);
	allPointId[location] = -1;
	strcpy(allPointName[location],"null");
	//记录要删除的文件名
	char *delfileN = edit_point_file_name(id);
	//从all文件中删去文件名
	FILE *f=fopen(pointAllFileName,"w+");
	for(int i=0;i<pointCount;i++){
		if(equal_f(pointFileName[i],delfileN) != 1){
			fprintf(f,"%s\n",pointFileName[i]);
		}
	}
	//删除文件
	remove(delfileN);
	//对删除站点的邻居站点进行修改
	Neighbour *n = allPoint[location].first;
	//依次修改邻居站点
	while(n != NULL){
		//delpoint作为point的邻居节点，找出他的前一个和后一个邻居节点
		Neighbour *front,*rear;
		//找出point的第一个邻居节点
		Neighbour *t = allPoint[locate_int(n->id,allPointId,pointCount)].first;
		//找出delpoint对应的邻居节点
		Neighbour *nt =find_Neighbour(id, allPoint[locate_int(n->id,allPointId,pointCount)]);
		//如果delpoint对应的邻居节点是point的首个邻居节点
		if(nt->id == t->id){
			//point的首个邻居节点指向delpoint对应的邻居节点的下一个邻居节点
			allPoint[locate_int(n->id,allPointId,pointCount)].first = nt->next;
		}
		else{
			front = NULL;
			rear = nt->next;
			//找出point邻居节点中next指向delpoint对应的邻居节点
			while(t->id != nt->id){
				//TODO
				front = t;
				t = t->next;
			}
			front->next = rear;
		}
		//修改delpoint的邻居站点的point文件
		char *pointFN = edit_point_file_name(allPoint[locate_int(n->id,allPointId,pointCount)].id);
		write_Point(pointFN, allPoint[locate_int(n->id,allPointId,pointCount)]);
		n = n->next;
	}
	//修改存在delpoint的公交线路
	LNode *del = (LNode*)malloc(sizeof(LNode));		
	for(int i=0;i<busCount;i++){
		int flag = 0;
		del = busRoute[i]->next;
		//判断该线路内是否有delpoint
		while(del!=NULL){
			if(equal_f(del->name,name)){
				flag = 1;
				break;
			}
			del = del->next;
		}
		if(flag){
			//TODO
			LNode *temp = del->prior;
			del->prior->next = del->next;
			del->next->prior = temp;
			char *fileBN = edit_bus_file_name(busName[i]);
			write_bus(fileBN, busRoute[i]);
		}
	}
	pointCount--;
	//向文件中重新写入站点数
	write_demo();
	printf("删除站点成功");
}
void add_neighbor(char *neighbourName,Point *p){
	while(findID_byName(neighbourName) == -1){
		//TODO
		printf("error");
		scanf("%s",neighbourName);
	}
	Neighbour *n=(Neighbour*)malloc(sizeof(Neighbour));
	Neighbour *n2=(Neighbour*)malloc(sizeof(Neighbour));
	n->id = findID_byName(neighbourName);
	strcpy(n->route,"z");
	strcpy(n2->route,"z");
	printf("请输入距离");
	float d;
	scanf("%f",&d);
	getchar();
	n2->distance=d;
	n2->id = p->id;
	n2->next = allPoint[(locate_int(n->id,allPointId,pointCount))].first; 
	allPoint[(locate_int(n->id,allPointId,pointCount))].first = n2;
	n->distance=d;
	n->next=p->first;
	p->first=n;
	char *fileN = edit_point_file_name(n->id);
	write_Point(fileN,allPoint[(locate_int(n->id,allPointId,pointCount))]);
}
//新增站点
void addPoint() {
	char name[10];
	printf("请输入站点名：");
	scanf_s("%s",name);
	while(findID_byName(name) != -1){
		//TODO
		printf("重新输入");
		scanf_s("%s",name);
	}
	allPoint[pointCount].id=allPoint[pointCount-1].id+1;
	allPointId[pointCount]=allPoint[pointCount].id;
	strcpy(allPoint[pointCount].name,name);
	strcpy(allPointName[pointCount],name);
	char neighbourName[10];
	char choice='Y';
	do{
		//TODO
		printf("请输入邻居名称");
		scanf("%s",neighbourName);
		add_neighbor(neighbourName,&allPoint[pointCount]);
		printf("是否继续添加邻居?[Y/N]");
		scanf("%c",&choice);
	}while(choice != 'N');
	char *newFile;
	char allFile[200];
	strcpy(allFile,fileName);
	strcat(allFile,"/point/all.txt");
	newFile = edit_point_file_name(allPointId[pointCount]);
	write_Point(newFile,allPoint[pointCount]);
	append(allFile,newFile);
	printf("error");
	pointCount++;
	write_demo();
	printf("添加站点成功");
}

//查询经过该点的所有公交路线
void point_Bus() {
	char temp[10];
	int equal;
	printf("请输入站点名:");
	scanf("%s", temp);
	for (int i = 0; i < pointCount; i++) {
		equal = strcmp(temp, allPointName[i]);
		if (equal == 0) {
			break;
		}
	}
	int find_if = 0;
	if (equal != 0) {
		printf("未找到站点\n");
		return;
	} else {
		for (int i = 0; i < busCount; i++) {
			LNode* p = (LNode*)malloc(sizeof(LNode));
			p = busRoute[i]->next;
			while (p != NULL) {
				int equal_2 = equal_f(p->name, temp);
				if (equal_2) {
					find_if = 1;
					printBus(busRoute[i]);
					break;
				} else {
					p = p->next;
				}
			}
		}
		if (!find_if) {
			printf("没有经过该点的公交\n");
		}
	}
}
//所有公交路线
void allBus(){
	for(int i=0;i<busCount;i++){
		printBus(busRoute[i]);
	}	
}
//所有可达路线
int allRoute(wayNode *allWay[10],int start,int end) {
	for (int i = 0; i < 10; i++) {
		//TODO
		allWay[i] = createWay();
	}
	float time[10];
	Neighbour *n;
	Point p1, p2, p;
	int  i = 0, routeCount = 0;
	int flag = 0;
	int start1_num = 0;
	int end1_num = 0;
	int start2_num[10];
	int end2_num[10];
	int start_1[10], end_1[10];
	start_1[0] = start;
	end_1[0] = end;
	int start_2[10][10], end_2[10][10];
	p1 = findPoint(start);
	p2 = findPoint(end);
	char startN[10];
	char endN[10];
	strcpy(startN,p1.name);
	strcpy(endN,p2.name);
	for (i = 0; i < 10; i++) {
		allWay[i]->next = NULL;
		strcpy(allWay[i]->name, p1.name);
		allWay[i]->id = p1.id;
	}
	i = 0;
	p2 = findPoint(end);
	n = p1.first;
	//起点第一次
	while (n != NULL) {
		//TODO
		start_1[++i] = n->id;
		n = n->next;
	}
	start1_num = i;
	for (; i >= 1; i--) {
		
		if (start_1[i] == end) {
			//TODO
			Neighbour *n = find_Neighbour(end, p1);
			time[routeCount] = method_f(n);
			insert_wayNode(allWay[routeCount], n->id, endN, n->route);
			printWay(allWay[routeCount]);
			start_1[i] = -1;
			routeCount++;
			break;
		}
	}
	int same[10];
	//从终点的搜索不可能有起点
	i = 0;
	//终点第一次
	n = p2.first;
	while (n != NULL) {
		//TODO
		if(n->id!=start){
			//TODO
			end_1[++i] = n->id;
		}
		n = n->next;
	}
	//2条
	end1_num = i;
	int same_num = findSame(start_1, end_1, same, start1_num + 1, end1_num + 1);
	for (i = 0; i < same_num; i++) {
		//TODO
		Point pt = findPoint(same[i]);
		Neighbour *nt = find_Neighbour(same[i], p1);
		insert_wayNode(allWay[routeCount], same[i], pt.name, nt->route);
		time[routeCount] = method_f(nt);
		nt = find_Neighbour(end, pt);
		insert_wayNode(allWay[routeCount], end, endN, nt->route);
		time[routeCount] += method_f(nt);
		printWay(allWay[routeCount]);
		routeCount++;
		for (int j = 0; j < start1_num; j++) {
			//TODO
			if (start_1[j] == same[i]) {
				//TODO
				start_1[j] = -1;
				break;
			}
		}
		for (int j = 0; j < end1_num; j++) {
			//TODO
			if (end_1[j] == same[i]) {
				//TODO
				end_1[j] = -1;
				break;
			}
		}
	}
	//找起点的邻居节点的邻居节点
	for (i = 1; i <= start1_num; i++) {
		//TODO
		int j = 0;
		if (start_1[i] != -1) {
			//TODO
			p = findPoint(start_1[i]);
			n = p.first;
			start_2[flag][j++] = start_1[i];
			while (n != NULL) {
				//TODO
				if (n->id != start) {
					start_2[flag][j++] = n->id;
				}
				n=n->next;
			}
			start2_num[flag] = j;
			flag++;
		}
	}
	int cnt=0;
	int find[10];
	for (i = 0; i < flag; i++) {
		//TODO
		same_num = findSame(start_2[i], end_1, same, start2_num[i], end1_num + 1);
		for (int j = 0; j < same_num; j++) {
			//TODO
			Point pt = findPoint(start_2[i][0]);
			Neighbour *nt = find_Neighbour(start_2[i][0], p1);
			insert_wayNode(allWay[routeCount], start_2[i][0], pt.name, nt->route);
			time[routeCount] = method_f(nt);
			nt = find_Neighbour(same[j], pt);
			pt = findPoint(same[j]);
			insert_wayNode(allWay[routeCount], same[j], pt.name, nt->route);
			time[routeCount] += method_f(nt);
			nt = find_Neighbour(end, pt);
			insert_wayNode(allWay[routeCount], end, endN, nt->route);
			time[routeCount] += method_f(nt);
			printWay(allWay[routeCount++]);
			find[cnt++]=same[j];
		}
	}
	for(int m=0;m<flag;m++){
		//TODO
		for(int n=0;n<start2_num[m];n++){
			for(int k=0;k<cnt;k++){
				if(find[k]==start_2[m][n]){
					start_2[m][n]=-1;
				}
			}
		}
	}
	int flag2 = 0;
	for (i = 1; i <= end1_num; i++) {
		//TODO
		int j = 0;
		if (end_1[i] != -1) {
			p = findPoint(end_1[i]);
			n = p.first;
			end_2[flag2][j++] = end_1[i];
			while (n != NULL) {
				
				if (n->id != end) {
					end_2[flag2][j++] = n->id;
				}
				n = n->next;
			}
			end2_num[flag2] = j;
			flag2++;
		}
	}
	for (i = 0; i < flag; i++) {
		for (int j = 0; j < flag2; j++) {
			same_num = findSame(start_2[i], end_2[j], same, start2_num[i], end2_num[j]);
			
			for (int k = 0; k < same_num; k++) {
				Neighbour *nt = find_Neighbour(start_2[i][0], p1);
				Point pt = findPoint(start_2[i][0]);
				insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route);
				time[routeCount] = method_f(nt);
				nt = find_Neighbour(same[k], pt);
				pt = findPoint(same[k]);
				insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route);
				time[routeCount] += method_f(nt);
				nt = find_Neighbour(end_2[j][0], pt);
				pt = findPoint(end_2[j][0]);
				insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route);
				time[routeCount] += method_f(nt);
				nt = find_Neighbour(end, pt);
				insert_wayNode(allWay[routeCount], nt->id, endN, nt->route);
				time[routeCount] += method_f(nt);
				printWay(allWay[routeCount++]);
			}
		}
	}
	return routeCount;
}

//最短路线
void shortRoute(Point start, wayNode *allWay[pointCount]) {
	int i;
	Neighbour *n;
	n = start.first;
	int FindPoint[pointCount];
	float dist[pointCount];
	for (i = 0; i < pointCount; i++) {
		allWay[i] = (wayNode*)malloc(sizeof(wayNode));
		FindPoint[i] = 0;
		dist[i] = MAX;
		allWay[i]->id = start.id;
		strcpy(allWay[i]->name, start.name);
		allWay[i]->next = NULL;
	}
	while (n != NULL) {
		dist[locate_int(n->id, allPointId, pointCount)] = n->distance;
		Point pName = findPoint(n->id);
		insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
		n = n->next;
	}
	FindPoint[locate_int(start.id, allPointId, pointCount)] = 1;
	int v = locate_int(start.id, allPointId, pointCount);
	for (i = 0; i < pointCount - 1; i++) {
		int min = MAX;
		int u = v;
		for (int j = 0; j < pointCount; j++) {
			if (!FindPoint[j] && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		FindPoint[u] = 1;
		Point p = findPoint(allPointId[u]);
		n = p.first;
		while (n != NULL) {
			if (n->distance + dist[u] < dist[locate_int(n->id, allPointId, pointCount)] && !FindPoint[locate_int(n->id, allPointId, pointCount)]) {
				dist[locate_int(n->id, allPointId, pointCount)] = n->distance + dist[u];
				copy_way(allWay[u], allWay[locate_int(n->id, allPointId, pointCount)]);
				Point pName = findPoint(n->id);
				insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
			}
			n = n->next;
		}
	}
}
//最少时间
void leastTime(Point start, wayNode *allWay[pointCount]) {
	int i;
	Neighbour *n;
	n = start.first;
	int FindPoint[pointCount];
	float time[pointCount];
	for (i = 0; i < pointCount; i++) {
		
		allWay[i] = (wayNode*)malloc(sizeof(wayNode));
		FindPoint[i] = 0;
		time[i] = MAX;
		allWay[i]->id = start.id;
		strcpy(allWay[i]->name, start.name);
		allWay[i]->next = NULL;
	}
	while (n != NULL) {

		time[locate_int(n->id, allPointId, pointCount)] = method_f(n);
		Point pName = findPoint(n->id);
		insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
		n = n->next;
	}
	FindPoint[locate_int(start.id, allPointId, pointCount)] = 1;
	int v = locate_int(start.id, allPointId, pointCount);
	for (i = 0; i < pointCount - 1; i++) {
		int min = MAX;
		int u = v;
		for (int j = 0; j < pointCount; j++) {

			if (!FindPoint[j] && time[j] < min) {
				u = j;
				min = time[j];
			}
		}
		FindPoint[u] = 1;
		Point p = findPoint(allPointId[u]);
		n = p.first;
		while (n != NULL) {
			float x = method_f(n);
		
			if (x + time[u] < time[locate_int(n->id, allPointId, pointCount)] && !FindPoint[locate_int(n->id, allPointId, pointCount)]) {
				
				time[locate_int(n->id, allPointId, pointCount)] = x + time[u];
				copy_way(allWay[u], allWay[locate_int(n->id, allPointId, pointCount)]);
				Point pName = findPoint(n->id);
				insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
			}
			n = n->next;
		}
	}
}
//最少换乘
void least_Change(int start,int end) {
	wayNode *w = createWay();
	wayNode *leastChangeWay = createWay();
	int leastChaneCnt = MAX;
	char routeT1[10];
	char routeT2[10];
	wayNode *change[10];
	int count = allRoute(change,start,end);
	int changeCount[count];
	for (int i = 0; i < count; i++) {
		//TODO
		int cnt = 0;
		w = change[i]->next;
		while (w->next != NULL) {
			//TODO
			char **ss1;
			char **ss2;
			ss1 = (char**)malloc(sizeof(char*));
			ss2 = (char**)malloc(sizeof(char*));
			strcpy(routeT2, w->next->route);
			strcpy(routeT1, w->route);
			int cnt1 = splitComma(routeT1, ss1);
			int cnt2 = splitComma(routeT2, ss2);
			int flag = 0;
			for (int j = 0; j < cnt1; j++) {
				//TODO
				for (int k = 0; k < cnt2; k++) {
					if (equal_f(ss1[j], ss2[k])) {
						//TODO
						flag = 1;
						break;
					}
				}
				if (flag)
					//TODO
					break;
			}
			if (!flag)
				cnt++;
			w = w->next;
		}
		changeCount[i] = cnt;
		if (changeCount[i] < leastChaneCnt) {
			//TODO
			copy_way(change[i], leastChangeWay);;
		}
	}
	printWay(leastChangeWay);
}
void Dijkstra(Point start, wayNode *allWay[pointCount]) {
	int i;
	Neighbour *n;
	n = start.first;
	int FindPoint[pointCount];
	float dist[pointCount];
	// init the way and the distance from start to other points
	for (i = 0; i < pointCount; i++) {
		allWay[i] = (wayNode*)malloc(sizeof(wayNode));
		FindPoint[i] = 0;
		dist[i] = MAX;
		allWay[i]->id = start.id;
		strcpy(allWay[i]->name, start.name);
		allWay[i]->next = NULL;
	}
	// assign corresponding data to the neighbour of the starting point
	while (n != NULL) {
		dist[locate_int(n->id, allPointId, pointCount)] = n->distance;
		Point pName = findPoint(n->id);
		insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
		n = n->next;
	}
	// the start has been found
	FindPoint[locate_int(start.id, allPointId, pointCount)] = 1;
	int v = locate_int(start.id, allPointId, pointCount);
	// seek the shortest path from start to each of the other points in turn
	for (i = 0; i < pointCount - 1; i++) {
		int min = MAX;
		int u = v;
		// seek the samllest distance 
		for (int j = 0; j < pointCount; j++) {
			if (!FindPoint[j] && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		// set findPoint[u] equal to be 1
		FindPoint[u] = 1;
		Point p = findPoint(allPointId[u]);
		n = p.first;
		/* 
		  Start from the point with the shortest distance found this time to 
		  the neighbour point which the shortest route has not yet been found
		  Determine whether the new distance is smaller than the original distance. 
		  If it is smaller, modify the path and distance
		 */
		while (n != NULL) {
			if (n->distance + dist[u] < dist[locate_int(n->id, allPointId, pointCount)] && !FindPoint[locate_int(n->id, allPointId, pointCount)]) {
				dist[locate_int(n->id, allPointId, pointCount)] = n->distance + dist[u];
				copy_way(allWay[u], allWay[locate_int(n->id, allPointId, pointCount)]);
				Point pName = findPoint(n->id);
				insert_wayNode(allWay[locate_int(n->id, allPointId, pointCount)], n->id, pName.name, n->route);
			}
			n = n->next;
		}
	}
}
//环线
void cycle(){
	int count=0;
	for(int i=0;i<busCount;i++){
		//TODO
		LNode* p=(LNode*)malloc(sizeof(LNode));
		p=busRoute[i];
		p=p->next;
		while(p->next!=NULL){
			//TODO
			int e=equal_f(p->name,p->next->name);
			if(e){
				printf("%s是环线",busRoute[i]->name);
				count++;
				break;
			}
			p=p->next;
		}
	}
	if(!count)
		printf("无环线\n");
	else
		printf("共有%d条环线\n",count);
}
//选择
void select(int n){
	switch (n) {
	case 1:
		//新增公交线路
		addBus();
		break;
	case 2:
		//修改已有公交线路
		alterPoint();
		break;
	case 3:
		//删除公交线路站点
		delPoint();
		break;
	case 4:
		//新增站点
		addPoint();
		break;
	case 5:
		//查询经过该点的所有公交路线
		point_Bus();
		break;
	case 6:
		//所有公交路线
		allBus();
		break;
	case 7:
		//所有可达路线
		{
			int start,end;
			char endN[10];
			char startN[10];
			printf("请输入起点和终点：");
			scanf("%s %s", startN, endN);
			while (1) {
				start = findID_byName(startN);
				end = findID_byName(endN);
				if (start == end || start == -1 || end == -1) {
					//TODO
					printf("error\n");
					printf("请输入起点和终点：");
					scanf("%s %s", startN, endN);
				} else
					break;
			}
			wayNode *allWay[10];
			allRoute(allWay,start,end);
			break;
		}
	case 8:
		{
			int start,end;
			char endN[10];
			char startN[10];
			printf("请输入起点和终点：");
			scanf("%s %s", startN, endN);
			while (1) {
				start = findID_byName(startN);
				end = findID_byName(endN);
				if (start == end || start == -1 || end == -1) {
					//TODO
					printf("error\n");
					printf("请输入起点和终点：");
					scanf("%s %s", startN, endN);
				} else
					break;
			}
			wayNode *allWayDis[pointCount];
			wayNode *allWayTime[pointCount];
			//最短路线
			//Point p=findPoint(start);
			shortRoute(findPoint(start),allWayDis);
			printWay(allWayDis[locate_int(end,allPointId,pointCount)]);
			//最少时间
			leastTime(findPoint(start),allWayTime);
			printWay(allWayTime[locate_int(end,allPointId,pointCount)]);
			//最少换乘
			least_Change(start,end);
		}
		break;
	case 9:
		//Dijkstra
		{
			wayNode *allWay[pointCount];
			int start;
			char startN[10];
			printf("请输入起点：");
			scanf("%s", startN);
			while (1) {
				start = findID_byName(startN);
				if ( start == -1 ) {
					printf("error\n");
					printf("请输入起点：");
					scanf("%s", startN);
				} else
					break;
			}
			shortRoute(findPoint(start),allWay);
			for(int i=0;i<pointCount;i++){
				//TODO
				if(locate_int(start,allPointId,pointCount)!=i){
					//TODO
					printWay(allWay[i]);
				}
			}
		}
		break;
	case 10:
		//环线
		cycle();
		break;
	case -1:
		//exit
		printf("退出完成\n");
		break;
	default:
		//error
		printf("！！！！错误指令！！！！\n");
		break;
	}
}
//管理员
void admin(){
	adminMenu();
	int insturct_2;
	scanf("%d",&insturct_2);
	//选择操作
	while(insturct_2!=-1){
		//TODO
		select(insturct_2);
		adminMenu();
		printf("请输入操作：");
		scanf("%d",&insturct_2);
	}
}
//学生端
void stu(){	
	stuMenu();
	int insturct_2;
	printf("请输入操作:");
	scanf("%d",&insturct_2);
	if(insturct_2!=-1){
		insturct_2+=4;
	}
	//选择操作
	while(insturct_2!=-1){
		select(insturct_2);
		stuMenu();
		printf("请输入操作：");
		scanf("%d",&insturct_2);
		if(insturct_2!=-1){
			insturct_2+=4;
		}
	}
}
int main()
{
	printf("欢迎使用!\n\n");
	loginInter();
	int instruct_1;
	scanf("%d",&instruct_1);
	//登录界面选择操作
	while(instruct_1 != -1){
		//选择登录
		if(instruct_1 == 1){
			int access;
			char name[20];
			printf("请输入用户名：");
			scanf("%s",name);
			//能否登录
			access=login(name);
			//登录成功
			if(access != -1){
				//学生
				init();
				if(access == 0){
					stu();
					loginInter();
				}
				//管理员
				else if(access == 1){
					admin();
					loginInter();
				}
			}
			//登陆失败
			else{
				printf("登录失败,输入\"2\"注册新账号\n");
			}
		}
		//选择注册
		else if(instruct_1 == 2){
			registe();
			printf(",输入\"1\"登录账号\n");
		}
		//其他
		else
		{	
			printf("错误指令");
		}
		scanf("%d", &instruct_1);		
	}
	printf("欢迎再次使用");
	return 0;
}
