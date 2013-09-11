#include<stdio.h>
#include<windows.h>
int main(int argc,char *argv[])
{
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
    } 
    else
        WaitForSingleObject(pi.hProcess,INFINITE);  //等待子进程运行结束 
    GetSystemTime(&time2);  //获得子进程结束时间 
    printf("进程开始时间：");
    printf("%d.%d.%d %d:%d:%d:%d\n",time1.wYear,time1.wMonth,time1.wDay,time1.wHour,time1.wMinute,time1.wSecond,time1.wMilliseconds);
    printf("进程结束时间：");
    printf("%d.%d.%d %d:%d:%d:%d\n",time2.wYear,time2.wMonth,time2.wDay,time2.wHour,time2.wMinute,time2.wSecond,time2.wMilliseconds);
    printf("进程运行时间："); 
    printf("%d:%d:%d:%d\n",time2.wHour-time1.wHour,time2.wMinute-time1.wMinute,time2.wSecond-time1.wSecond,time2.wMilliseconds-time1.wMilliseconds);
}
