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

 ```c
//最少换乘
void least_Change(int start,int end) {
    wayNode *w = createWay();
    wayNode *leastChangeWay = createWay();
    int leastChaneCnt = MAX;
    char routeT1[20];
    char routeT2[20];
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
            copy_way(change[i], leastChangeWay);
        }
    }
    printWay(leastChangeWay);
}
 ```

 ```java
// This file is auto-generated, don't edit it. Thanks.
package com.aliyun.sample;

import com.aliyun.tea.*;
import com.aliyun.iot20180120.*;
import com.aliyun.iot20180120.models.*;
import com.aliyun.teaopenapi.*;
import com.aliyun.teaopenapi.models.*;
import com.aliyun.teautil.*;
import com.aliyun.darabonba.env.*;
import com.aliyun.teaconsole.*;
import com.aliyun.darabonbastring.*;
import com.aliyun.darabonbanumber.*;
import com.aliyun.darabonba.array.*;

public class Sample {

    /**
     * 初始化IoT(Iot20180120)客户端
     */
    public static com.aliyun.iot20180120.Client initialization() throws Exception {
        Config config = new Config()
                .setRegionId("cn-shanghai")
                .setAccessKeyId(com.aliyun.darabonba.env.EnvClient.getEnv("ACCESS_KEY_ID"))
                .setAccessKeySecret(com.aliyun.darabonba.env.EnvClient.getEnv("ACCESS_KEY_SECRET"));
        return new com.aliyun.iot20180120.Client(config);
    }

    /**
     * 入参校验
     * param:pProductKey 产品KEY
     * param:pDeviceName 设备名称
     * param:pTopic 消息Topic
     * return 校验通过:true 校验失败:false
     */
    public static Boolean checkParameters(String pProductKey, String pDeviceName, String pTopic) throws Exception {
        if (com.aliyun.teautil.Common.empty(pProductKey)) {
            com.aliyun.teaconsole.Client.log("==========入参[ProductKey]不能为空==========");
            return false;
        }

        if (com.aliyun.teautil.Common.empty(pDeviceName)) {
            com.aliyun.teaconsole.Client.log("==========入参[DeviceName]不能为空==========");
            return false;
        }

        if (com.aliyun.teautil.Common.empty(pTopic)) {
            com.aliyun.teaconsole.Client.log("==========入参[Topic]不能为空==========");
            return false;
        }

        // 入参校验通过
        return true;
    }

    /**
     * 获取主处理main的入参元素值，未设置时返回空字符串。
     * param:主处理main的入参数组
     * param:主处理main的入参下标
     * return:指定下标对应的具体入参内容，未设置则返回空字符串。
     */
    public static String getArg(java.util.List<String> args, Integer pIndex) throws Exception {
        Long length = com.aliyun.darabonbanumber.Client.itol(com.aliyun.darabonba.array.Client.size(args));
        if (com.aliyun.darabonbanumber.Client.gt(length, com.aliyun.darabonbanumber.Client.itol(pIndex))) {
            return args.get(pIndex);
        }

        return "";
    }

    /**
     * 调用Iot20180120客户端发送请求
     * 1.SubscribeTopic 为指定设备订阅Topic
     */
    public static SubscribeTopicResponseBody subscribeTopicSample(com.aliyun.iot20180120.Client client, String pIotInstanceId, String pProductKey, String pDeviceName, String pTopic) throws Exception {
        // 要订阅的Topic，最多订阅10个Topic。
        // Topic的操作权限必须为订阅或发布和订阅。
        java.util.List<String> arrTopic = com.aliyun.darabonbastring.Client.split(pTopic, ",", 10);
        SubscribeTopicRequest request = new SubscribeTopicRequest()
                .setIotInstanceId(pIotInstanceId)
                .setProductKey(pProductKey)
                .setDeviceName(pDeviceName)
                .setTopic(arrTopic);
        try {
            com.aliyun.teaconsole.Client.log("-----------1.SubscribeTopic 为指定设备订阅Topic-----------");
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(request)));
            SubscribeTopicResponse response = client.subscribeTopic(request);
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(response.body)));
            return response.body;
        } catch (TeaException error) {
            com.aliyun.teaconsole.Client.log(error.message);
            return new SubscribeTopicResponseBody()
                    .setSuccess(false);
        } catch (Exception _error) {
            TeaException error = new TeaException(_error.getMessage(), _error);
            com.aliyun.teaconsole.Client.log(error.message);
            return new SubscribeTopicResponseBody()
                    .setSuccess(false);
        }        
    }

    /**
     * 调用Iot20180120客户端发送请求
     * 2.查询设备已订阅的Topic列表：QueryDeviceSubTopic
     */
    public static QueryDeviceSubTopicResponseBody queryDeviceSubTopicSample(com.aliyun.iot20180120.Client client, String pIotInstanceId, String pProductKey, String pDeviceName) throws Exception {
        QueryDeviceSubTopicRequest request = new QueryDeviceSubTopicRequest()
                .setIotInstanceId(pIotInstanceId)
                .setProductKey(pProductKey)
                .setDeviceName(pDeviceName);
        try {
            com.aliyun.teaconsole.Client.log("-----------2.查询设备已订阅的Topic列表：QueryDeviceSubTopic-----------");
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(request)));
            QueryDeviceSubTopicResponse response = client.queryDeviceSubTopic(request);
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(response.body)));
            return response.body;
        } catch (TeaException error) {
            com.aliyun.teaconsole.Client.log(error.message);
            return new QueryDeviceSubTopicResponseBody()
                    .setSuccess(false);
        } catch (Exception _error) {
            TeaException error = new TeaException(_error.getMessage(), _error);
            com.aliyun.teaconsole.Client.log(error.message);
            return new QueryDeviceSubTopicResponseBody()
                    .setSuccess(false);
        }        
    }

    /**
     * 调用Iot20180120客户端发送请求
     * 3.通过自定义Topic向设备发布消息：Pub
     */
    public static PubResponseBody pubSample(com.aliyun.iot20180120.Client client, String pIotInstanceId, String pProductKey, String pDeviceName, String pTopicName) throws Exception {
        // 要发送的消息主体。
        // 您需要将消息原文转换成二进制数据，并进行Base64编码，从而生成消息主体。
        // 原文：test-ColeSample-PubRequest-MessageContent
        String strMessageContent = "dGVzdC1Db2xlU2FtcGxlLVB1YlJlcXVlc3QtTWVzc2FnZUNvbnRlbnQ=";
        PubRequest request = new PubRequest()
                .setIotInstanceId(pIotInstanceId)
                .setProductKey(pProductKey)
                .setDeviceName(pDeviceName)
                .setMessageContent(strMessageContent)
                .setTopicFullName(pTopicName)
                .setQos(0);
        try {
            com.aliyun.teaconsole.Client.log("-----------3.通过自定义Topic向设备发布消息：Pub-----------");
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(request)));
            PubResponse response = client.pub(request);
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(response.body)));
            return response.body;
        } catch (TeaException error) {
            com.aliyun.teaconsole.Client.log(error.message);
            return new PubResponseBody()
                    .setSuccess(false);
        } catch (Exception _error) {
            TeaException error = new TeaException(_error.getMessage(), _error);
            com.aliyun.teaconsole.Client.log(error.message);
            return new PubResponseBody()
                    .setSuccess(false);
        }        
    }

    /**
     * 调用Iot20180120客户端发送请求
     * 4.通过消息ID查询设备上下行消息的详情：QueryMessageInfo
     */
    public static QueryMessageInfoResponseBody queryMessageInfoSample(com.aliyun.iot20180120.Client client, String pIotInstanceId, String pUniMsgId) throws Exception {
        QueryMessageInfoRequest request = new QueryMessageInfoRequest()
                .setIotInstanceId(pIotInstanceId)
                .setUniMsgId(pUniMsgId);
        try {
            com.aliyun.teaconsole.Client.log("-----------4.通过消息ID查询设备上下行消息的详情：QueryMessageInfo-----------");
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(request)));
            QueryMessageInfoResponse response = client.queryMessageInfo(request);
            com.aliyun.teaconsole.Client.log(com.aliyun.teautil.Common.toJSONString(TeaModel.buildMap(response.body)));
            return response.body;
        } catch (TeaException error) {
            com.aliyun.teaconsole.Client.log(error.message);
            return new QueryMessageInfoResponseBody()
                    .setSuccess(false);
        } catch (Exception _error) {
            TeaException error = new TeaException(_error.getMessage(), _error);
            com.aliyun.teaconsole.Client.log(error.message);
            return new QueryMessageInfoResponseBody()
                    .setSuccess(false);
        }        
    }

    /**
     * 【主处理main】
     * param.1:IotInstanceId 实例ID
     * param.2:ProductKey 产品KEY
     * param.3:DeviceName 设备名称
     * param.4:Topic 要订阅的Topic
     */
    public static void main(String[] args_) throws Exception {
        java.util.List<String> args = java.util.Arrays.asList(args_);
        // * param.1:IotInstanceId 实例ID
        //   您可在物联网平台控制台的实例概览页面，查看当前实例的ID。
        //   若有ID值，必须传入该ID值，否则调用会失败。
        //   如何获取到实例ID:https://help.aliyun.com/document_detail/267533.htm
        //   实例的更多信息，请参见实例概述：https://help.aliyun.com/document_detail/356505.htm
        String argIotInstanceId = Sample.getArg(args, 0);
        // * param.2:ProductKey 产品KEY
        //   ProductKey是物联网平台为新建产品颁发的全局唯一标识符。
        //   您可以在物联网平台控制台或调用QueryProductList，查看当前账号下所有产品的信息。
        String argProductKey = Sample.getArg(args, 1);
        // * param.3:DeviceName 设备名称
        String argDeviceName = Sample.getArg(args, 2);
        // * param.4:Topic 要订阅的Topic
        //   最多订阅10个Topic。
        //   Topic的操作权限必须为订阅或发布和订阅。
        String argTopic = Sample.getArg(args, 3);
        // 【入参校验】
        if (!Sample.checkParameters(argProductKey, argDeviceName, argTopic)) {
            // 入参校验失败
            return ;
        }

        // 【发起客户端调用】
        com.aliyun.teaconsole.Client.log("hello world!");
        com.aliyun.iot20180120.Client client = Sample.initialization();
        com.aliyun.teaconsole.Client.log("==========A.为指定设备订阅Topic==========");
        SubscribeTopicResponseBody responseBodySubscribe = Sample.subscribeTopicSample(client, argIotInstanceId, argProductKey, argDeviceName, argTopic);
        if (!responseBodySubscribe.success) {
            com.aliyun.teaconsole.Client.log("为指定设备订阅Topic失败。");
            return ;
        }

        com.aliyun.teaconsole.Client.log("==========B.查询设备已订阅的Topic列表==========");
        QueryDeviceSubTopicResponseBody responseBodyQueryTopic = Sample.queryDeviceSubTopicSample(client, argIotInstanceId, argProductKey, argDeviceName);
        if (!responseBodyQueryTopic.success) {
            com.aliyun.teaconsole.Client.log("查询设备已订阅的Topic列表失败。");
            return ;
        }

        java.util.List<QueryDeviceSubTopicResponseBody.QueryDeviceSubTopicResponseBodyTopicList> arrTopicList = responseBodyQueryTopic.topicList;
        for (QueryDeviceSubTopicResponseBody.QueryDeviceSubTopicResponseBodyTopicList modelTopicInfo : arrTopicList) {
            com.aliyun.teaconsole.Client.log("==========C.通过自定义Topic向设备发布消息==========");
            String strTopicName = modelTopicInfo.topicName;
            PubResponseBody responseBodyPub = Sample.pubSample(client, argIotInstanceId, argProductKey, argDeviceName, strTopicName);
            if (!responseBodyPub.success) {
                com.aliyun.teaconsole.Client.log("通过自定义Topic向设备发布消息失败。");
            } else {
                com.aliyun.teaconsole.Client.log("==========D.通过消息ID查询设备消息的详情==========");
                // 物联网平台为消息生成的唯一标识ID
                // 您可登录物联网平台控制台(https://iot.console.aliyun.com/lk/monitor/log)，在监控运维 > 日志服务页面，获取消息ID信息。
                String strMsgId = responseBodyPub.messageId;
                QueryMessageInfoResponseBody responseBody = Sample.queryMessageInfoSample(client, argIotInstanceId, strMsgId);
                if (!responseBody.success) {
                    com.aliyun.teaconsole.Client.log("通过消息ID查询设备消息的详情失败。");
                }

            }

        }
    }
}
 ```