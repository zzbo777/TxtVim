#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAXSIZE 256   //定义串的长度
#define ERR_NOMEMORY -1
char source_str[STRING_MAXSIZE]; //将文件内资源以字符串存于此变量
int len;    //存储原始字符串的长度
//定义数据存储的结构，以链结构存储
typedef struct LNode
{
    char data;
    struct LNode *next;
} LNode,*LinkList;
LinkList L = 0;         //定义全局变量字符串的起始指针
void   menu();          //菜单显示函数，显示菜单，无传递参数，
//接调用
LinkList Init(char Init_str);  //初始化函数，将资源转化为所定义的连//式结构，传入参数为所要初始化的文本，//返回值为LinkList类型的头指针。
int Input(char input_string[]); //插入函数，在默认在文本末尾插入文本，//传入参量为所要插入的文本信息，返回//值为修改后的文本信息。
void Output();  //输出函数，输出文本所包含的信息，无//传入参量，无返回值
int Search(char search_str[]);  //查找函数，查找相应的字符串函数传入//参量为指定的查找文本信息，返回查找//到的参数。
void Replace(char bereplaced_str[],char replace_str[]);                      //替换函数，替换相应文本信息，传入参//量为被替换的文本信息，以及替换的文//本信息。
void Insert(char insert_str[],int location);
//插入函数，在指定位置插入指定信息，//传入参量为需要插入的文本信息，以及//插入的相关位置。
void Move(char bemoved_str[],int location);
//块移动函数，将文本信息中的指定信息//移动到指定位置，传入参量为需要移动//的文本块以及指定的移动位置。
void Delete(char delete_str[]);        //删除函数，删除相应的文本信息，传入//参数为指定的被删除的文本
void Display(int len_dis);    //显示函数，传入参量为所要显示的文本//长度。
void save();    //存盘函数，将所改变的文本存入到磁盘//中，无传入参数，无返回参数
void delay();       //延时函数
int StringLength( LinkList S );  //求串长函数，传入参数为要求的串的长//度，返回参数为文本的长度
void statistics();            //统计行数，无传入参数，无返回值。
void KMPGetNext(char *T,int n2,int nextval[]);
int KMPIndex(char *S,int n1,char *T,int n2); //KMP算法，求文本的位置
void KMPGetNext(char *T,int n2,int nextval[])
//求子串T的next函数修正值并存入数组nextval
{
    int j=1,k=0;
    nextval[0]=-1;
    while(j<n2)
    {
        if(k==0||T[k]==T[j])
        {
            nextval[j]=T[k]==T[j]?nextval[k]:k;
            j++;
            k++;
        }
        else
            k=nextval[k];
    }
}
int KMPIndex(char *S,int n1,char *T,int n2)
//利用子串T的next函数求T在主串S中的位置
{
    int i=0,j=0;
    int *next=(int *)malloc(n2*sizeof(int));
    if(!next)
        return ERR_NOMEMORY ;
    KMPGetNext(T,n2,next);
    while(i<n1&&j<n2)
    {
        if(j==-1||S[i]==T[j])            //继续比较后继字符
        {
            i++;
            j++;
        }
        else                            //模式串向右移动
            j=next[j];
    }
    free(next);
    return (j>=n2?i-n2:-1);
}
int Search(char search_str[])
{
    char s[STRING_MAXSIZE];
    int i=0;
    int search_loc,search_len,s_len;
    LNode *p;
    p=L->next;
    while(p)                                //获取修改后的文本信息
    {
        s[i++]=p->data;
        p=p->next;
    }
    s_len=strlen(s);
    search_len=strlen(search_str);
    if(search_len <= s_len)
    {
        search_loc = KMPIndex(s,s_len,search_str,search_len);        //利用KMP算法获取查找的位置
        return search_loc;
    }
    else
    {
        return -1;                            //未找到
    }
}
int Replace(char replaced_str[],char replace_str[])
{
    int j=0;
    int replaced_str_loc,replaced_str_len,reped_len,source_str_len;
    LNode *p,*s,*z,*w;
    replaced_str_len = strlen(replaced_str);  //被替换的字符的长度
    reped_len = strlen(replace_str);          //需要替换的字符的长度
    source_str_len = strlen(source_str);      //主串字符的长度
    replaced_str_loc = Search(replaced_str);  //被替换的字符的位置
    if(replaced_str_loc != -1)
    {
        LTmp = Init(replace_str);
        p = L;
        s = L;
        z = LTmp->next;
        w = LTmp;
        for(j = 0; j < replaced_str_loc; j++)
            p = p->next;
        for(j = 0; j < (replaced_str_loc + replaced_str_len); j++)
            s = s->next;
        for(j = 0; j < reped_len; j++)
            w = w->next;
        p->next = z;
        w->next = s->next;
        Display();
        return 0;
    }
    else
    {
        printf("**************************************\n");
        printf("* 主银！！您所被替换的文本不存在哦~~*\n");
        printf("**************************************\n");
    }
}
void Insert(char insert_str[],int location)
{
    int i,j,len_ins,source_str_len;
    LNode *p,*s;
    len_ins = strlen(insert_str);
    source_str_len = strlen(source_str);
    if((location <= source_str_len)&&(location >= 0))
    {
        p=L;
        j=0;
        for(i=0; i<len_ins; i++)                  //插入的次数
        {
            while(p&&j<location)
            {
                p=p->next;
                j++;
            }
            s=(LinkList)malloc(sizeof(LNode));    //生成新结点
            s->data=insert_str[i];
            s->next=p->next;
            p->next=s;
            p=p->next;
        }
        len_ins=strlen(source_str)+len_ins;
        Display();
    }
    else
    {
        ……;
    }
}
void  Move(char bemoved_str[],int location)
{
    int j,bemoved_str_loc = 0,bemoved_str_len = 0,source_str_len;
    LNode *p,*s,*w,*temp;
    bemoved_str_loc = Search(bemoved_str) + 1;
    bemoved_str_len = strlen(bemoved_str);
    source_str_len = strlen(source_str);
    if((bemoved_str_loc) > 0)
    {
        if((location <= source_str_len)&&(location >= 0))
        {
            p = L;
            s = L;
            w = L;
            for(j = 0; j < bemoved_str_loc-1; j++)
            {
                p = p->next;
            }
            temp = p->next;
            for(j = 0; j < (bemoved_str_loc + bemoved_str_len-1); j++)
                s = s->next;
            for(j = 0; j < location; j++)
                w = w->next;
            p->next = s->next;
            s->next = w->next;
            w->next = temp;
            Display();
        }
        else
        {
            ……;
        }
    }
    else
    {
        ……;
    }
}
void Delete(char delete_str[])
{
    int loc;            //记录要删除的文本的位置
    int i,j=0;
    int len_del;
    LNode *p,*q;
    p=L;
    len_del=strlen(delete_str);
    loc=Search(delete_str)+1;
    if((loc - 1) >= 0)
    {
        for(i=0; i<len_del; i++)      //要删除的结点的个数
        {
            while(p->next&&j<loc-1)    //寻找第loc[i]个元素，并令p指向其前驱
            {
                p=p->next;
                j++;
            }
            q=p->next;                    //删除结点
            if(q->next->data== 10)
                q=q->next;
            p->next=q->next;
        }
        len=strlen(source_str)-len_del;
        Display();
    }
    else
    {
        ……;
    }
}
void OpenFile()
{
    char ch,meng[33];
    int i = 0,flag = 1,copy_num;
    FILE *fp1;
    printf("你猜你要输入什么样儿滴文本路径(我看这个不错f:\\1.txt) \n");
    scanf("%s",way);
    if((fp1=fopen(way,"r"))==NULL)
    {
        while(flag)
        {
            printf("总统大人，您的文件不在磁盘里呢，是不是在U盘,再¨来一遍!\n");
            scanf("%s",way);
            fp1 = fopen(way,"r");
            if(fp1 != NULL)
                flag = 0;
            else
                flag = 1;
        }
    }
    if((fp1=fopen(way,"r")) != NULL)
    {
        while(!feof(fp1))
        {
            ch = fgetc(fp1);
            source_str[i++] = ch;
        }
        source_str[i] = '\0';
        for(i = 0; i < strlen(source_str)-1; i++)
            source_str[i] = source_str[i];
        source_str[i] = '\0';
        for(copy_num = 0; copy_num < STRING_MAXSIZE; copy_num ++)
            changed_source_str[copy_num] = source_str[copy_num];
        printf("我已经把他印在脑海里了！给你看下一个画面,不要捉急...\n");
        delay();
        fclose(fp1);
        system( "cls" ) ;
        menu();
    }
}
void delay()
{
    int i,j;
    for(i = 0; i < 55000; i++)
        for(j = 0; j < 11000; j++);
}
void save()
{
    FILE * fp2;
    fp2=fopen(way,"w");
    fprintf (fp2,"%s",changed_source_str);
    fclose (fp2);
}
int main()
{

    return 0;
}
