# UJS_BusMap
江苏大学2021数据结构与算法课程设计
# 审判我的代码

----------

## 题目

-----------

![](D:\study\studyNote\picture\数据结构\map.jpg)

> 以上是一份江大手绘地图，请你为2022级新生定制一个线路问询交互系统，请从地图中选择至少15个的江苏大学重要地点，其中需要包含校内公交站点和非公交站点，至少5条校车路线，这样可以设计出换乘路线，如果校内没有开通可以自行设计校车路线。

## 实现

-----------

### 规划

-------

#### 路线

-------

#### 整体架构

-------

![](F:/algorithms/规划/整体架构.png "")

#### 数据结构

---------

```C   
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

```

### 初始化

-------

### 查询

---------

#### 查询公交线路

-------

#### 最优路线规划

-----------

##### 最短时间

##### 最短距离

##### 最少换乘

##### Dijkstra

### 修改

----------

#### 新增一条公交线路

------

#### 修改站点信息

-----------

#### 新增站点

----------

#### 删除站点

--------------

## 感想 


```C

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

const uint8_t PROGMEM myImage[] = {
  // 在这里插入你的单色位图数据
};

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 5);  // SDA引脚连接到D2（GPIO4），SCL引脚连接到D1（GPIO5）

  if(!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("SSD1306分辨率未找到，请确认是否正确连接。"));
    while (true);
  }
  display.display();  // 清空显示

  delay(1000);
}

void loop() {
  // 清空显示
  display.clearDisplay();

  // 显示图片
  display.drawBitmap(0, 0, myImage, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

  // 更新显示
  display.display();

  delay(1000);  // 显示图片一秒钟
}
```  

```C
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
 ```