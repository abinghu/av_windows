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

    SYSTEMTIME time1,time2;   //���̿�ʼ�ͽ���ʱ�� 
    STARTUPINFO si = { sizeof(si) };     //ָ���½��̵����������� 
    PROCESS_INFORMATION pi;   //�����й��½��̼������߳���Ϣ 
    si.dwFlags = STARTF_USESHOWWINDOW;   // ָ��wShowWindow��Ա��Ч
    si.wShowWindow = TRUE;    // �˳�Ա��ΪTRUE�Ļ�����ʾ�½����̵�������

    GetSystemTime(&time1);  //��ý��̿�ʼʱ�� 
    BOOL bCreateOK = CreateProcess(
            argv[1],       //�½��̽�ʹ�õĿ�ִ���ļ� 
            NULL,          //���ݸ��½��̵��������ַ��� 
            NULL,          //Ĭ�ϵĽ��̰�ȫ��
            NULL,          //Ĭ�ϵ��̰߳�ȫ��
            FALSE,         //���̳е��ý��̵Ĵ򿪾��
            0,             //������־
            NULL,          //�µĻ���
            NULL,          //��ǰĿ¼
            &si,           //������Ϣ��ָ���½������������
            &pi ) ;        //���ؽ��̺����߳̾��
    if(!bCreateOK)  //��������ʧ�� 
    {
        printf("create process fail!\n");
		return 0;
    } 
    else
        WaitForSingleObject(pi.hProcess,INFINITE);  //�ȴ��ӽ������н��� 

	// �����������ʱ��
	FILETIME creationTime;// 100 ����Ϊ����
	FILETIME exitTime;
	FILETIME kernelTime;
	FILETIME userTime;
	GetProcessTimes(pi.hProcess, &creationTime, &exitTime, &kernelTime, &userTime);
	cout << "real time: " << exitTime.dwHighDateTime-creationTime.dwHighDateTime 
		<< (exitTime.dwLowDateTime-creationTime.dwLowDateTime)*0.0001f << "ms\n"
		<< "user time: " << userTime.dwHighDateTime << userTime.dwLowDateTime*0.0001f << "ms\n"
		<< "kernel time: " << kernelTime.dwHighDateTime << kernelTime.dwLowDateTime*0.0001f << "ms\n";
}
