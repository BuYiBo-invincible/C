#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

const int MAXRESOURCE = 10;//最大资源类数

const int MAXPROCESS = 10;//最大进程数

int process;//进程数

int resourceForProcess;//进程所需资源类数

int pid;//进程ID

int Available[MAXRESOURCE] = {0};//每类资源可用量

int Claim[MAXPROCESS][MAXRESOURCE] = {0};//进程i最大需要j类资源数量(最大需求矩阵)

int Allocation[MAXPROCESS][MAXRESOURCE] = {0};//进程i已经占有的j类资源的数量(已分配资源矩阵)

int Need[MAXPROCESS][MAXRESOURCE] = {0};//进程i尚需j类资源的数量(需求矩阵)

int Request[MAXRESOURCE] = {0};//进程对i资源的请求数量

int Work[MAXPROCESS] = {0};//记录模拟执行中资源的回收情况，初值为Available[M]的值。

                      //目前可提供给进程继续运行使用的各类资源(空闲的)数目

int Finish[MAXPROCESS] = {0};//进程i 是否能够成功执行。初始值为FALSE 当有资源可以分配时 赋值为TRUE并分配资源。

int securitySequence[MAXPROCESS]  = {0};//安全序列

//初始化
void init(){
    int i,j,data;
    char input;
    printf("请输入进程数：\n");
    scanf("%d",&process);
    printf("请输入资源种类数：\n");
    scanf("%d",&resourceForProcess);
    printf("请输入各类资源可用总数：\n");
    for (i = 0; i < resourceForProcess; i++)
        scanf("%d",&Available[i]);
    printf("请输入各进程对各类资源的需求量：\n");
    //进程i
    for (i = 0; i < process; i++){
        //资源j
        for (j = 0; j < resourceForProcess; j++){
            printf("进程P%d对资源R%d的需求:\n",i,j);
            while (scanf("%d",&data)){
                if(data < 0)
                    printf("非法输入！请重新输入\n");
                else{
                    if (data > Available[j])
                        printf("大于可用资源数！请重新输入\n");
                    else{
                        Claim[i][j] = data;
                        break;
                    }
                    
                }
            }
        }
    }
    printf("是否输入分配矩阵?(y/n)\n");
    while (scanf("%c",&input)){
        if(input == 'n'){
            break;
        }
        else if(input == 'y'){
            for(i = 0; i<process; i++){
                for(j = 0; j<resourceForProcess; j++){
                    printf("请输入进程P%d对资源R%d的已分配情况：\n",i,j);
                    while (scanf("%d",&data)){
                        if(data < 0)
                            printf("非法输入！请重新输入\n");
                        else{
                            if(data > Claim[i][j])
                                printf("大于所需资源数！请重新输入\n");
                            else if (data > Available[j])
                                printf("大于可用资源数！请重新输入\n");
                            else{
                                Allocation[i][j] = data;
                                Available[j] -= data;
                                break;
                            }

                        }
                    }                    
                }
            }
            break;
        }
        else
            printf("\n");
    }
    //Need 初始化
    for(i = 0; i < process; i++){
        for(j = 0; j < resourceForProcess; j++){
            Need[i][j] = Claim[i][j] - Allocation[i][j];
        }
    }
}

//打印当前系统分配状态
void print_info(){
    int i,j,k = 0;
    printf("process       claim         allocation          need          available \n");
    for(i = 0;i<4; i++){
        printf("\t      ");
        for(j = 0;j < resourceForProcess; j++){
            printf("%d  ",k++);   
        }
        k = 0;
    }
    printf("\n--------------------------------------------------------------------------------------\n");
    printf("\n");
    for(i = 0; i < process;i++){
        printf("P%d",i+1);
        printf("           ");
        for(j = 0; j < resourceForProcess;j++){
            printf("%d  " , Claim[i][j]);
        }
        printf("        ");
        for(j = 0; j < resourceForProcess;j++){
            printf("%d  " , Allocation[i][j]);
        }
        printf("        ");
        for(j = 0; j < resourceForProcess;j++){
            printf("%d  " , Need[i][j]);
        }
        printf("         ");
        if(i == process-1)
            for(j = 0; j < resourceForProcess;j++)
                printf("%d  " , Available[j]); 
        printf("\n\n");

    }
}

//安全状态检测
int safe_detection(){
    int i,j,index = 0;
    //标志位(是否退出寻找)
    int flag;
    //初始化work向量
    for(i = 0; i < resourceForProcess; i++){
        Work[i] = Available[i];
    }
    //初始化Finish向量
    for(i = 0; i < process; i++){
        Finish[i] = false;
    }
    while(1){
        flag = false;
        for(i = 0; i < process; i++){
            for(j = 0; j < resourceForProcess; j++)
                if(Finish[i] == true || Need[i][j] > Work[j])
                    break;
             //当前进程可以执行完成 进行资源回收     
            if( j == resourceForProcess){
                Finish[i] = true;
                flag = true;
                securitySequence[index] = i;
                index++;
                for(j = 0; j < resourceForProcess; j++){
                    Work[j] += Allocation[i][j];
                }

            }
        }
        if(flag == false) break;
    }
    for(i = 0; i < process; i++)
        if(Finish[i] == false)
            return false;//非安全状态
    return true;//安全态
}

//请求资源回滚
void rollback(){
    int i;
    for(i = 0;i < resourceForProcess; i++){
        Available[i] += Request[i];
        Allocation[pid][i] -= Request[i];
        Need[pid][i] += Request[i];
    }
}

//资源申请
int requstResource(){
    int i;
    printf("请输入请求进程号\n");
    while(scanf("%d",&pid)){
        if(pid < 0 || pid >= process)
            printf("无此进程，请重新输入！\n");
        else
            break;   
    }
    printf("请输入各资源请求数量\n");
    for(i = 0; i < resourceForProcess; i++){
        printf("对资源R%d进行资源请求：\n",i);
        scanf("%d",&Request[i]);
    }
    for(i = 0; i < resourceForProcess; i++){
        if (Request[i] > Need[pid][i]){
             printf("请求资源数大于所需资源数！已终止\n");
             return false;
        }
        else if(Request[i] > Available[i]){
             printf("请求资源数大于所需剩余资源数！已终止\n");
             return false;
        }
    }
    //预分配
    for(i = 0; i < resourceForProcess; i++){
        Available[i] -= Request[i];
        Allocation[pid][i] += Request[i];
        Need[pid][i] -= Request[i];
    }
    //安全性检测
    if(safe_detection()){
        printf("资源分配成功！\n");
        return true;
    }
    else{
        rollback();
        printf("系统不安全！资源分配失败！\n");
        return true;
    }
}




int main(int argc, char const *argv[])
{
    int input,result,i,flag = true;
    while(flag){
        printf("--------------------银行家算法--------------------\n");
        printf("1：初始化系统\n");
        printf("2：查看系统分配结果\n");
        printf("3：安全性检测\n");
        printf("4：资源请求\n");
        printf("5：退出\n");
        while(scanf("%d",&input)){
            if (input == 1){
                init();
                break;
            }
            else if(input == 2){
                print_info();
                break;
            }
            else if(input == 3){
                result = safe_detection();
                if(result == true){
                    printf("当前处于安全状态\n");
                    printf("存在安全序列：");                   
                    for(i = 0;i < process; i++ )
                        printf("P%d ",securitySequence[i]);
                    printf("\n");
                    }
                    
                else{
                    printf("当前处于不安全状态！\n");
                }
                
                break;
            }
            else if(input == 4){
                //安全性检测
                result = safe_detection();
                if(result == false){
                    printf("当前处于不安全状态 拒绝分配\n");
                    break;
                }
                requstResource();
                break;
            }
            else if(input == 5){
                flag = false;
                break;
            }
            else
                printf("非法输入！\n");
            
        }
    }
    return 0;
}
