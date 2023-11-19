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
 ```python
import base64                   # 图片/音频转base64流
import threading
import time
import numpy as np              # 随机数生成
from PySide2.QtCore import QFile
from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QFileDialog, QMainWindow
import aliyun                   # 自己定义
import 录音
# 随机数信息初始化，全局变量
data_random = [0]
data_normal = [0]
data_posong = [0]
 
 
class UI:
    def __init__(self):
        # 从文件中加载UI定义
        qfile_Server = QFile("send.ui")
        qfile_Server.open(QFile.ReadOnly)
        qfile_Server.close()
        # 从 UI 定义中动态 创建一个相应的窗口对象
        self.ui = QUiLoader().load(qfile_Server)
        self.ui.senddata.clicked.connect(self.senddata)
        self.ui.sendpicture.clicked.connect(self.sendpicture)
        self.ui.luying.clicked.connect(self.luying_thread)
        self.ui.music.clicked.connect(self.sendmusic)
 
    # 开启录音线程
    def luying_thread(self):
        thread = threading.Thread(target=self.luying)
        thread.setDaemon(True)
        thread.start()
 
    # 进行录音，并发送至阿里云
    def luying(self):
        self.ui.luying.setEnabled(False)
        timeluying = self.ui.time.currentText()
 
        thread = threading.Thread(target=lambda: 录音.luying(self, int(timeluying)))
        thread.setDaemon(True)
        thread.start()
 
        time.sleep(int(timeluying)+1)
 
        f = open('luying.mp3', 'rb')
        # base64编码
        base64_data = base64.b64encode(f.read())
        f.close()
        '''注意编码类型问题，byte->string '''
        base64_data = base64_data.decode()
        aliyun.senddata(data_random, data_normal, data_posong, '', base64_data)
        self.ui.luying.setEnabled(True)
 
    # 向阿里云发送随机数数据
    def senddata(self):
        # 获取UI界面数据
        junyunmin = self.ui.min.text()
        junyunmax = self.ui.max.text()
        zhentaijunzhi = self.ui.zhentaijunzhi.text()
        zhentaibiaozhuncha = self.ui.zhentaibiaozhuncha.text()
        posong = self.ui.posong.text()
        # 生成随机数
        global data_random
        global data_normal
        global data_posong
        data_random = [round(np.random.uniform(float(junyunmin), float(junyunmax)), 2) for i in range(512)]  # 均匀分布
        data_normal = [round(np.random.normal(float(zhentaijunzhi), float(zhentaibiaozhuncha)), 2) for i in range(512)]  # 正态分布
        data_posong = [round(np.random.poisson(float(posong)), 2) for i in range(512)]  # 泊松分布
        # 向阿里云发送数据
        aliyun.senddata(data_random, data_normal, data_posong, '', '')
 
    # 向阿里云发送图片
    def sendpicture(self):
        FileDirectory = QFileDialog.getOpenFileName(QMainWindow(), "选择文件")
        f = open(FileDirectory[0], 'rb')
        # base64编码
        base64_data = base64.b64encode(f.read())
        f.close()
        '''注意编码类型问题，byte->string '''
        base64_data = base64_data.decode()
        aliyun.senddata(data_random, data_normal, data_posong, base64_data, '')
 
    # 向阿里云发送音频
    def sendmusic(self):
        FileDirectory = QFileDialog.getOpenFileName(QMainWindow(), "选择文件")
        f = open(FileDirectory[0], 'rb')
        # base64编码
        base64_data = base64.b64encode(f.read())
        f.close()
        '''注意编码类型问题，byte->string '''
        base64_data = base64_data.decode()
        aliyun.senddata(data_random, data_normal, data_posong, '', base64_data)
 
 
# 登陆界面
class Denlu:
    def __init__(self):
        # 从文件中加载UI定义
        qfile = QFile("denlu.ui")
        qfile.open(QFile.ReadOnly)
        qfile.close()
        # 从 UI 定义中动态 创建一个相应的窗口对象
        self.ui = QUiLoader().load(qfile)
        self.ui.acknowledge.clicked.connect(self.acknowledge)
        self.ui.delete_2.clicked.connect(self.ui.close)
 
    # 确认按钮程序
    def acknowledge(self):
        name = self.ui.name.text()
        password = self.ui.password.text()
        if name == '2537148609' and password == '12345678':
            self.state = UI()
            self.state.ui.show()
            self.ui.close()
        elif name == '' or password == '':
            self.ui.Error.setText('Error! Do not enter a user name or password')
        else:
            self.ui.Error.setText('Error! Incorrect user name or password')
 
 
app = QApplication([])
denlu = Denlu()
denlu.ui.show()
# 循环执行
app.exec_()

import paho.mqtt.client as mqtt		# mqtt阿里云
import time							# 延时库
import hashlib						# 哈希计算
import hmac							# 密钥认证
# 把我们自己对应的三元组填进去即可
 
options = {
	'productKey': 'productKey',
	'deviceName': 'deviceName',
	'deviceSecret': 'deviceSecret',
	'regionId': 'cn-shanghai'
}
 
HOST = options['productKey'] + '.iot-as-mqtt.'+options['regionId']+'.aliyuncs.com'
PORT = 1883
PUB_TOPIC = "/sys/" + options['productKey'] + "/" + options['deviceName'] + "/thing/event/property/post"
 
 
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))
 
 
def hmacsha1(key, msg):
	return hmac.new(key.encode(), msg.encode(), hashlib.sha1).hexdigest()
 
 
def getAliyunIoTClient():
	timestamp = str(int(time.time()))
	CLIENT_ID = "paho.py|securemode=3,signmethod=hmacsha1,timestamp="+timestamp+"|"
	CONTENT_STR_FORMAT = "clientIdpaho.pydeviceName"+options['deviceName']+"productKey"+options['productKey']+"timestamp"+timestamp
	# set username/password.
	USER_NAME = options['deviceName']+"&"+options['productKey']
	PWD = hmacsha1(options['deviceSecret'], CONTENT_STR_FORMAT)
	client = mqtt.Client(client_id=CLIENT_ID, clean_session=False)
	client.username_pw_set(USER_NAME, PWD)
	return client
 
 
# 发送数据
def senddata(data_random, data_normal, data_posong, dase64_data, music):
	client = getAliyunIoTClient()
	client.on_message = on_message
 
	client.connect(HOST, 1883, 300)
	# 以json结构发送数据
	payload_json = {
		'id': int(time.time()),
		'params': {
			'junyundata': data_random,
			'normaldata': data_normal,
			'posongdata': data_posong,
			'Image': dase64_data,
			'music': music,
		},
		'method': "thing.event.property.post"
	}
 
	client.publish(PUB_TOPIC, payload=str(payload_json), qos=1)
	client.loop_start()
	time.sleep(1)

    import base64               # 图片/音频转base64流
import threading            # 多线程
from PySide2.QtCore import QFile
from PySide2.QtGui import QPixmap       # 加载图像
from PySide2.QtUiTools import QUiLoader
from PySide2.QtWidgets import QApplication, QGraphicsScene, QGraphicsPixmapItem     # 加载图像
from linkkit import linkkit         # 阿里云aliyun-iot-linkkit库
import time         # python延时库
import json         # 发送json数据
import 折线图        # 自己定义
from selenium import webdriver  # 用浏览器打开html
import os
 
# 三元组信息
ProductKey = "ProductKey"        # 阿里云物联网ProductKey
DeviceName = "DeviceName"        # 阿里云物联网DeviceName
DeviceSecret = "DeviceSecret"     # 阿里云物联网DeviceSecret
# 随机数信息初始化，全局变量
data_random = [0]
data_normal = [0]
data_posong = [0]
 
 
class UI:
    def __init__(self):
        # 从文件中加载UI定义
        qfile_Server = QFile("receive.ui")
        qfile_Server.open(QFile.ReadOnly)
        qfile_Server.close()
        # 从 UI 定义中动态 创建一个相应的窗口对象
        self.ui = QUiLoader().load(qfile_Server)
        self.ui.tuxian.clicked.connect(lambda: self.receivedata(data_random, data_normal, data_posong))
        self.ui.picture.clicked.connect(self.showImage)
        self.ui.music.clicked.connect(self.openmusic)
 
    # 播放音乐
    def openmusic(self):
        self.ui.isOK1.setText('')
 
        thread = threading.Thread(target=lambda: os.system('yuying.mp3'))
        thread.setDaemon(True)
        thread.start()
 
    # 接收随机数数据并生成折线图
    def receivedata(self, data_random, data_normal, data_posong):
        self.ui.isOK2.setText('')
        self.ui.music.setEnabled(False)
        print(data_random, data_normal, data_posong, sep='\n')
        start = self.ui.start.text()
        number_of_interval = self.ui.number_of_interval.currentText()
        length = self.ui.length.currentText()
        折线图.getzhexian(data_random, data_normal, data_posong, float(start), int(number_of_interval), int(length))
        # 设置数据守护线程
        thread1 = threading.Thread(target=self.keepdriver)
        thread1.setDaemon(True)
        thread1.start()
 
    # 使html在游览器上循环出现
    def keepdriver(self):
        driver = webdriver.Edge()
        while (True):
            driver.get('file://C://Users//hp//Desktop//Python//云接入课设//Lib//zhexian.html')
            driver.maximize_window()
            time.sleep(1000)
 
    # 展示图片
    def showImage(self):
        self.ui.isOK.setText('')
        self.ui.music.setEnabled(False)
        # 将词云图加载到UI.ui界面
        self.ui.GraphView.scene_img = QGraphicsScene()
        self.imgShow = QPixmap()
        self.imgShow.load('mypicture.png')
        self.imgShowItem = QGraphicsPixmapItem()
        self.imgShowItem.setPixmap(QPixmap(self.imgShow))
        self.ui.GraphView.scene_img.addItem(self.imgShowItem)
        self.ui.GraphView.setScene(self.ui.GraphView.scene_img)
        self.ui.GraphView.fitInView(QGraphicsPixmapItem(QPixmap(self.imgShow)))
 
    # 接收阿里云的数据
    def on_topic_message(self, topic, payload, qos, userdata):
        # 拿到接收来的数据
        data = str(payload)[2:-1]
        dataDict = json.loads(data)
        global data_random
        global data_normal
        global data_posong
        # 多层解析
        data_random = dataDict["junyundata"]
        data_normal = dataDict["normaldata"]
        data_posong = dataDict["posongdata"]
        base64_data = dataDict['Image']
        base64_data1 = dataDict['music']
        self.ui.music.setEnabled(True)
        if base64_data != '':
            # 进行base64解码工作 base64->数组
            image_decode = base64.b64decode(base64_data)
            with open('mypicture.png', 'wb') as f:
                f.write(image_decode)
            self.ui.isOK.setText('OK')
        elif base64_data1 != '':
            # 进行base64解码工作 base64->数组
            image_decode1 = base64.b64decode(base64_data1)
            with open('yuying.mp3', 'wb') as f:
                f.write(image_decode1)
            self.ui.isOK1.setText('OK')
        else:
            self.ui.isOK2.setText('OK')
        print("OK")
 
 
# 订阅Topic
def on_subscribe_topic(mid, granted_qos, userdata):  # 订阅topic
    print("on_subscribe_topic mid:%d, granted_qos:%s" %
          (mid, str(','.join('%s' % it for it in granted_qos))))
 
 
# 登陆界面
class Denlu:
    def __init__(self):
        # 从文件中加载UI定义
        qfile = QFile("denlu.ui")
        qfile.open(QFile.ReadOnly)
        qfile.close()
        # 从 UI 定义中动态 创建一个相应的窗口对象
        self.ui = QUiLoader().load(qfile)
        self.ui.acknowledge.clicked.connect(self.acknowledge)
        self.ui.delete_2.clicked.connect(self.ui.close)
 
    # 确认按钮程序
    def acknowledge(self):
        name = self.ui.name.text()
        password = self.ui.password.text()
        if name == '2537148609' and password == '12345678':
            self.state = UI()
            self.state.ui.show()
            # 注册当接受到云端发送的数据的时候的方法
            lk.on_topic_message = self.state.on_topic_message
            self.ui.close()
        elif name == '' or password == '':
            self.ui.Error.setText('Error! Do not enter a user name or password')
        else:
            self.ui.Error.setText('Error! Incorrect user name or password')
 
 
app = QApplication([])
denlu = Denlu()
denlu.ui.show()
 
# 初始化连接参数，阿里云三码设置
lk = linkkit.LinkKit(
    host_name="cn-shanghai",    # 当前设备服务器(上海-华东二)
    product_key=ProductKey,  # 当前设备product_key
    device_name=DeviceName,  # 当前设备device_name
    device_secret=DeviceSecret)  # 当前设备device_secret
 
# //注册云端订阅的方法
lk.on_subscribe_topic = on_subscribe_topic
 
# 连接阿里云的函数（异步调用）
lk.connect_async()
time.sleep(1)       # 延时设置
 
# //订阅这个topic，不需要写prodect_key和device_name
rc, mid = lk.subscribe_topic(lk.to_full_topic("user/get"))
 
# 循环执行
app.exec_()

import pyecharts.options as opts
from pyecharts.charts import Line       # 折线图
 
 
# 用pyecharts生成图线html
def zhexian(data_normal, data_random, data_posong):
    x1=[];y1=[];y2=[];y3=[]
    for i in data_normal:
        [left, right] = i[0].split('~')
        x1.append(left)
        y1.append(round(i[1], 1))
    for i in data_random:
        y2.append(round(i[1], 1))
    for i in data_posong:
        y3.append(round(i[1], 1))
    line = (
            Line()
            .add_xaxis(xaxis_data=x1)
            .add_yaxis(series_name="泊松分布", y_axis=y3, is_smooth=True)
            .add_yaxis(series_name="均匀分布", y_axis=y2, is_smooth=True)
            .add_yaxis(series_name="正态分布", y_axis=y1, is_smooth=True)
            .set_global_opts(title_opts=opts.TitleOpts(title="Line图"), yaxis_opts=opts.AxisOpts(name='概率'),
                             xaxis_opts=opts.AxisOpts(name='数据大小'))
    ).render('zhexian.html')
 
 
# 分区切片
def interval_statistics(data, intervals):
    result = []
    if len(data) == 0:
        return
    for num in data:
        for interval in intervals:
            lr = tuple(interval.split('~'))
            left, right = float(lr[0]), float(lr[1])
            if left <= num <= right:
                intervals[interval] += 1
    for key, value in intervals.items():
        result.append([key, value * 100.000 / len(data)])
    return result
 
 
# 数据分区切片，计算频率
def getzhexian(data_random, data_normal, data_posong, start, number_of_interval, length):
    start = start  # 区间左端点
    number_of_interval = number_of_interval  # 区间个数
    length = length  # 区间长度
    intervals = {'{:.3f}~{:.3f}'.format(length*x+start, length*(x+1)+start): 0 for x in range(number_of_interval)}  # 生成区间
    data_random = interval_statistics(data_random, intervals)
    intervals = {'{:.3f}~{:.3f}'.format(length * x + start, length * (x + 1) + start): 0 for x in range(number_of_interval)}
    data_normal = interval_statistics(data_normal, intervals)
    intervals = {'{:.3f}~{:.3f}'.format(length * x + start, length * (x + 1) + start): 0 for x in range(number_of_interval)}
    data_posong = interval_statistics(data_posong, intervals)
    zhexian(data_normal, data_random, data_posong)
 ```
