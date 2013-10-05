#include <stdio.h>
#include <iostream>
#include<windows.h>

using namespace std;

int main(int argc,char *argv[])
{
	if (argc != 2)
	{
		cout << "usage:\n \tav_time.exe application_name\n";
		return 0;
	}

    SYSTEMTIME time1,time2;   //进程开始和结束时间 
    STARTUPINFO si = { sizeof(si) };     //指定新进程的主窗口特性 
    PROCESS_INFORMATION pi;   //返回有关新进程及其主线程信息 
    si.dwFlags = STARTF_USESHOWWINDOW;   // 指定wShowWindow成员有效
    si.wShowWindow = TRUE;    // 此成员设为TRUE的话则显示新建进程的主窗口

    GetSystemTime(&time1);  //获得进程开始时间 
    BOOL bCreateOK = CreateProcess(
            argv[1],       //新进程将使用的可执行文件 
            NULL,          //传递给新进程的命令行字符串 
            NULL,          //默认的进程安全性
            NULL,          //默认的线程安全性
            FALSE,         //不继承调用进程的打开句柄
            0,             //创建标志
            NULL,          //新的环境
            NULL,          //当前目录
            &si,           //启动信息，指向新进程主窗口外观
            &pi ) ;        //返回进程和主线程句柄
    if(!bCreateOK)  //创建进程失败 
    {
        printf("create process fail!\n");
		return 0;
    } 
    else
        WaitForSingleObject(pi.hProcess,INFINITE);  //等待子进程运行结束 

	// 计算进程运行时间
	FILETIME creationTime;// 100 纳秒为精度
	FILETIME exitTime;
	FILETIME kernelTime;
	FILETIME userTime;
	GetProcessTimes(pi.hProcess, &creationTime, &exitTime, &kernelTime, &userTime);
	cout << "real time: " << exitTime.dwHighDateTime-creationTime.dwHighDateTime 
		<< (exitTime.dwLowDateTime-creationTime.dwLowDateTime)*0.0001f << "ms\n"
		<< "user time: " << userTime.dwHighDateTime << userTime.dwLowDateTime*0.0001f << "ms\n"
		<< "kernel time: " << kernelTime.dwHighDateTime << kernelTime.dwLowDateTime*0.0001f << "ms\n";
}
