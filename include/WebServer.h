//
// Created by yonggeng on 3/26/22.
//

//#ifndef RUNNINGBEEF_WEBSERVER_WEBSERVER_H
//#define RUNNINGBEEF_WEBSERVER_WEBSERVER_H

#pragma once

#include "Timer.h"
#include "Epoll.h"
#include "HttpData.h"
#include "Socket.h"
#include "ParseHttpRequest.h"
#include "ParseHttpResponse.h"
#include "ThreadPool.h"
#include <functional>
#include <exception>
#include <memory>

class HttpData;
class Epoll;
class TimerManager;

extern std::string basePath;



class WebServer;

void cbfunc(WebServer * webserver,std::shared_ptr<HttpData> httpData);

class WebServer{
public:
    friend void cbfunc(WebServer & webserver,std::shared_ptr<HttpData> httpData);
    explicit WebServer(int threadNum = 8,int maxTask = 1024,int eventSize = 1024 ,int port = 8080,char * ip = NULL);
    ~WebServer();

    /*主函数*/
    void run();

    /*完成http请求和响应*/
    void do_request(std::shared_ptr<void >);

    /*服务器获取新的连接*/
    void handleConnection();

    /*分配监听事件*/
    std::vector<std::shared_ptr<HttpData>> handleEvents();

public:
    int threadNum_;/*线程个数*/
    int maxTask_;/*任务队列最大存储任务个数*/
    int eventSize_;/*监听事件数量*/
    ServerSocket serverSocket_;/*服haodi务socket*/
    std::shared_ptr<ThreadPool> threadPool_;/*线程池*/
    Epoll *epoll_;/*epoll类方法封装*/
    TimerManager  * timerManager;/*定时器管理容器*/
    std::unordered_map<int,std::shared_ptr<HttpData>> httpDataMap_;/*连接socket*/
};

//#endif //RUNNINGBEEF_WEBSERVER_WEBSERVER_H
//

