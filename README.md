# 使用说明

## 1. 认识项目结构

tcpserver.cpp文件是服务器源码，SocketTCPServer.exe是其编译后的可执行文件。TcpClientGUI是客户端的可视化源码，基于QT实现，其编译后的可执行文件是TcpClientGUI.exe。

## 2.系统概述

### 2.1运行环境及编译

本软件服务端程序"SocketTCPServer.exe"在Visual Studio2022的MSVC编译器编译以及运行,可以在windows操作系统下运行。**使用时请先启动服务端程序"SocketTCPServer.exe"。**

本软件chat flymessage的客户端程序有两个版本：命令行版本以及GUI图形化版本。命令行版本"SocketTCPUDP.exe"在Visual Studio2022的MSVC编译器编译以及运行。GUI图形化窗口的版本"TcpclientGUI.exe"在Qt Creator的MSVC2019编译器以及一些Qt的支持库的环境下编译并且运行。这两个版本的程序都可在windows操作系统下运行。值得注意的是，你可以登录GUI图形化版本的程序去与同样使用GUI图形化版本的用户通信，**也同样可以与使用命令行版本的用户相互聊天通信。**

### 2.2使用方法

使用方法见第四条用户使用手册。

### 2.3实现环境

实现环境在2.1的运行环境及编译的介绍中。

### 2.4程序文件列表

服务器端程序"SocketTCPServer.exe"的文件列表是：

<img src="https://jobsearchimagedir.oss-cn-shanghai.aliyuncs.com/1.png?Expires=1707360612&OSSAccessKeyId=TMP.3KiAwUNxsZVjFhqeEtjQRUudK1ogysiQMafWKugvi2FssbjzxD4o3QYAaRJUjG8waoaK5MFnSjuuqdWNZVkEmqMfN8BuMr&Signature=NM8tZmgi9azZrsyr6XFbQzgOfUs%3D" />

命令行版本的客户端程序"SocketTCPUDP.exe"的文件列表是：

<img src="https://jobsearchimagedir.oss-cn-shanghai.aliyuncs.com/2.png?Expires=1707360670&OSSAccessKeyId=TMP.3KiAwUNxsZVjFhqeEtjQRUudK1ogysiQMafWKugvi2FssbjzxD4o3QYAaRJUjG8waoaK5MFnSjuuqdWNZVkEmqMfN8BuMr&Signature=Ri5IB%2FUQlpsWdvCuxGndfg2SAlI%3D" />

GUI图形化版本的客户端程序"TcpClientGUI.exe"的文件列表是：

<img src="https://jobsearchimagedir.oss-cn-shanghai.aliyuncs.com/4.png?Expires=1707360709&OSSAccessKeyId=TMP.3KiAwUNxsZVjFhqeEtjQRUudK1ogysiQMafWKugvi2FssbjzxD4o3QYAaRJUjG8waoaK5MFnSjuuqdWNZVkEmqMfN8BuMr&Signature=VzMmUJz2zF8L2jAGYO8lqV6IwzE%3D" />

<img src="https://jobsearchimagedir.oss-cn-shanghai.aliyuncs.com/5.png?Expires=1707360740&OSSAccessKeyId=TMP.3KiAwUNxsZVjFhqeEtjQRUudK1ogysiQMafWKugvi2FssbjzxD4o3QYAaRJUjG8waoaK5MFnSjuuqdWNZVkEmqMfN8BuMr&Signature=4rILfrVk3r2x8tujzdPkZF%2FbE3c%3D" />

<img src="https://jobsearchimagedir.oss-cn-shanghai.aliyuncs.com/3.png?Expires=1707360769&OSSAccessKeyId=TMP.3KiAwUNxsZVjFhqeEtjQRUudK1ogysiQMafWKugvi2FssbjzxD4o3QYAaRJUjG8waoaK5MFnSjuuqdWNZVkEmqMfN8BuMr&Signature=7%2BiG64oGHywItDmoHwjI3hXNlzo%3D" />

## 3.主要数据结构

本软件实现存储在线用户和合法用户运用的是维护了2个vector向量。本软件使用了多线程的技术，有$n$个客户端，在服务端程序中就有$n+1$个线程。

## 4.主要算法描述

本软件实现查询是否是在线用户以及在登录时判断是否是合法用户运用的是在vector数据结构中的顺序查找。

## 5.用户使用手册

### 1.登录界面

输入username和password，如果输入的不是合法用户就重新输入。输入后点击login按钮登录。

点击quit按钮退出界面。

### 2.聊天chatpage界面

点击fresh onlinue user按钮更新查询当前在线的用户。点击SC进入选择输入要聊天的用户界面。输入用户后，在输入要聊天的用户界面点击Enter发送请求。消息提示connect success表示连接成功，否则连接失败，请重新上两步的操作。

连接成功后在消息输入框输入消息，并点击Send按钮发送。

点击RC按钮终止当前对这个用户的聊天，之后可以重新选择用户（点击SC）或者点击Return退出登录，换一个账号登录。



