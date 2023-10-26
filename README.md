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