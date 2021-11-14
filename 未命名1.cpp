/*sigactionϵͳ���õ�ʹ�÷�����sigaction�����Ĺ����Ǽ����޸����ƶ��ź�������Ĵ�������������ȫ����signal����*/
/*��һ���˽��źŴ�����*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int g_iSeq=0;

void SignHandlerNew(int iSignNo,siginfo_t *pInfo,void *pReserved)
{
    int iSeq=g_iSeq++;
    printf("%d Enter SignHandlerNew,signo:%d.\n",iSeq,iSignNo);
    sleep(3);      /*˯��3����*/
    printf("%d Leave SignHandlerNew,signo:%d\n",iSeq,iSignNo);
}
 
int main(void)
{
    char szBuf[20];      /*���뻺����������Ϊ20*/
    int iRet;
    struct sigaction act;   /*�����źŴ������Ľṹ��*/
    act.sa_sigaction=SignHandlerNew;  /*ָ���źŴ�����*/
    act.sa_flags=SA_SIGINFO;   /*�����źŴ�������sa_sigactionָ��*/
    sigemptyset(&act.sa_mask);
    /*�źż�����������act.sa_mask��ָ����źż���գ�*/
    /*���������κ��ź�*/
    sigaction(SIGINT,&act,NULL);   /*ע��SIGINT�ź�*/
    sigaction(SIGQ,UIT,&act,NULL);  /* ע��SIGQUIT�ź�*/
    do{
       iRet=read(STDIN_FILENO,szBuf,sizeof(szBuf)-1);  /*�ӱ�׼�����������*/
       if(iRet<0)
       {
           perror("read fail.");
           break;   /* read�����˳�*/
       }
       szBuf[iRet]=0;
       printf("Get: %s",szBuf);    /*��ӡ�ն�������ַ���*/
       }while(strcmp(szBuf,"quit\n")!=0);   /*����"quit"ʱ�˳�����*/
     return 0;
}

