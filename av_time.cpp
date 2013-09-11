#include<stdio.h>
#include<windows.h>
int main(int argc,char *argv[])
{
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
    } 
    else
        WaitForSingleObject(pi.hProcess,INFINITE);  //�ȴ��ӽ������н��� 
    GetSystemTime(&time2);  //����ӽ��̽���ʱ�� 
    printf("���̿�ʼʱ�䣺");
    printf("%d.%d.%d %d:%d:%d:%d\n",time1.wYear,time1.wMonth,time1.wDay,time1.wHour,time1.wMinute,time1.wSecond,time1.wMilliseconds);
    printf("���̽���ʱ�䣺");
    printf("%d.%d.%d %d:%d:%d:%d\n",time2.wYear,time2.wMonth,time2.wDay,time2.wHour,time2.wMinute,time2.wSecond,time2.wMilliseconds);
    printf("��������ʱ�䣺"); 
    printf("%d:%d:%d:%d\n",time2.wHour-time1.wHour,time2.wMinute-time1.wMinute,time2.wSecond-time1.wSecond,time2.wMilliseconds-time1.wMilliseconds);
}
