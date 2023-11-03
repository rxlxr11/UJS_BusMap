
#include "user.h"
#include "cilent.h"
#include "admin.h"
//初始化
void init() {
    printf("初始化中请稍后...\n");
    FILE *f;
    f = fopen(DEMOFILE, "r");
    if (f == NULL) {
        printf("demo error");
        exit(0);
    } else {
        fscanf(f,"%d\n",&point_Num);
        fscanf(f, "%d\n", &bus_Num);
    }
    fclose(f);

    pointFileName = (char**)malloc(25 * sizeof(char*));
    busFileName = (char**)malloc(10 * sizeof(char*));
    readAll(POINTALLFILENAME, pointFileName);
    readAll(BUSALLFILENAME, busFileName);
    for (int i = 0; i < point_Num; i++) {
        readPoint(pointFileName[i], &allPoint[i]);
        strcpy(allPointName[i], allPoint[i].name);
        //printf("%s%s\n",allPointName[i],allPoint[i].name);
        allPointId[i] = allPoint[i].id;
    }

    for (int i = 0; i < bus_Num; i++) {
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
            char endN[20];
            char startN[20];
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
            char endN[20];
            char startN[20];
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
            wayNode *allWayDis[point_Num];
            wayNode *allWayTime[point_Num];
            //最短路线
            //Point p=findPoint(start);
            shortRoute(findPoint(start),allWayDis);
            printf("路程最短的路线为\n");
            printWay(allWayDis[locate_int(end,allPointId,point_Num)]);
            //最少时间
            leastTime(findPoint(start),allWayTime);
            printf("用时最少的路线为\n");
            printWay(allWayTime[locate_int(end,allPointId,point_Num)]);
            //最少换乘
            //least_Change(start,end);
        }
            break;
        case 9:
            //Dijkstra
        {
            wayNode *allWay[point_Num];
            int start;
            char startN[20];
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
            for(int i=0;i<point_Num;i++){
                //TODO
                if(locate_int(start,allPointId,point_Num)!=i){
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
int main(){
    setbuf(stdout,NULL);
    printf("欢迎使用!\n\n");
    loginInter();
    int instruct_1;
    scanf("%d",&instruct_1);
    //登录界面选择操作
    while(instruct_1 != -1){
        //选择登录
        if(instruct_1 == 1){
            int access;
            user *u;
            char name[20];
            for(int i = 3 ; i>0 ;i-- ){
                printf("请输入用户名：");
                scanf("%s",name);
                u = user_exist(name);
                if(u!=NULL){
                    break;
                }
                printf("用户名错误还有%d次机会\n",i-1);
            }

            //能否登录
            access=login(u);
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