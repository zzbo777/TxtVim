#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>//键盘上输入或输出预处理操作
#include<windows.h>
#define Link_Size 100
int NUM,C,N,ROW;
char filename[20];
void save();
void Open();
typedef struct list
{
    char data[80];
    int length;
    struct list *next;
    struct list *pre;
    int row;
} LinkList;
LinkList *head;
void WellcomeWord()
{
    system("cls"); //清屏操作，在include（stdlib）头文件中
    printf("\t\t           欢迎使用简单的文本编辑器           \n\n");
}
LinkList *CreatWord()
{
    ROW=0;
    LinkList *temp;
    char ch;
    int i,j;
    head->next=(LinkList *)malloc(sizeof(LinkList));
    head->pre=NULL;
    temp=head->next;
    temp->pre=NULL;
    temp->length=0;
    for(i=0; i<80; i++)
        temp->data[i]='\0';
    printf("开始创建文本，请输入文章（输入#号结束）:\n");
    for(j=0; j<Link_Size; j++)
    {
        for(i=0; i<80; i++)
        {
            ch=getchar();
            temp->data[i]=ch;
            temp->length++;
            if(temp->data[i] =='\n')
            {
                ROW++;
            }
            if(ch=='#')
            {
                NUM=j;
                break;
            }
        }
        if(ch=='#')
        {
            temp->length=i;
            temp->next=NULL;
            break;
        }
        temp->next=(LinkList *)malloc(sizeof(LinkList)) ;
        temp->next->pre=temp;
        temp=temp->next;
        for(i=0; i<80; i++)
            temp->data[i]='\0';
    }
    temp->row=NUM+1;
    system("cls");
    return temp;
}
void PrintWord()
{
    int i,j;
    LinkList *p;
    p=head->next;
    system("cls");
    WellcomeWord();
    printf("\n当前文章的内容是:\n");
    for(j=0; j<=NUM&&p!=NULL; j++)
    {
        for(i=0; (i<80)&&(p->data[i])!='#'; i++)
        {
            printf("%c",p->data[i]);
        }
        p=p->next;
    }
    printf("\n当前文章的行数是:%d",ROW);
}
void CountWord()
{
    LinkList *temp;
    char ch;
    int i,j,t;
    int WORD=0,word=0,space=0,num=0,punct=0,sum=0;
    temp=head->next;
    for(j=0; j<=NUM; j++)
    {
        for(i=0; (i<80)&&(temp->data[i])!='#'; i++)
        {
            ch=temp->data[i];
            if((ch>='A')&&(ch<='Z'))
                WORD++;
            else if((ch>='a')&&(ch<='z'))
                word++;
            else if((ch>='0')&&(ch<='9'))
                num++;
            else if(ch==' ')
                space++;
            else if(ch==33||ch==34||ch==39||ch==44||ch==46||ch==58||ch==59||ch==63)
            {
                punct++;
            }
        }
        sum=WORD+word+num;
    }
    while(1)
    {
        printf("\n");
        WellcomeWord();
        printf("\t\t**********************************************\n");
        printf("\t\t*              文章内容统计菜单              *\n");
        printf("\t\t*         1、文章中大写字母的个数            *\n");
        printf("\t\t*         2、文章中小写字母的个数            *\n");
        printf("\t\t*         3、文章中数字的个数                *\n");
        printf("\t\t*         4、文章中标点符号的个数            *\n");
        printf("\t\t*         5、文章中空格的个数                *\n");
        printf("\t\t*         6、文章中所有字数                  *\n");
        printf("\t\t*         7、退出返回主菜单                  *\n");
        printf("\t\t**********************************************\n");
        printf("\t\t请选择需统计项目: ");
        scanf("%d",&t);
        switch(t)
        {
        case 1:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中大写字母的个数:%d\n",WORD);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        case 2:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中小写字母的个数:%d\n",word);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        case 3:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中数字的个数:%d\n",num);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        case 4:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中标点符号的个数:%d\n",punct);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        case 5:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中空格的个数:%d\n",space);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        case 6:
            system("cls");
            WellcomeWord();
            printf("\n\t\t文章中所有字数:%d\n",sum);
            printf("按回车键继续·····");
            getchar();
            getchar();
            system("cls");
            break;
        }
        if(t==7)
        {
            system("cls");
            break;
        }
    }
}
void SearchWord(char *str1,LinkList* temp)
{
    char Data[20] ;
    int i,j,k=0,sum=0;
    int l=1;
    temp=head->next;
    strcpy(Data,str1);
    for(i=0; i<=NUM; i++)
    {
        for(j=0; j<80; j++)
        {
            if((temp->data[j])==Data[k])
                k++;
            else if(Data[k]!='\0')
            {
                j=j-k;
                k=0;
            }
            if(Data[k]=='\0')
            {
                sum++;
                j=j-k+1;
                printf("\t\t第%d次出现在第%d行第%d列\n",l,i+1,j+1);
                l++;

                k=0;
                continue;
            }
        }
        temp=temp->next;
    }
    printf("\t\t\t字符串总共出现次数为:%d\n\n",sum);
    C=sum;
    N=i*80+j;
}
void DeleteWord(char *str2)
{
    char Data[20];
    LinkList *temp,*term;
    int i,j,k,m,y,num;
    strcpy(Data,str2);
    for(y=0; y<C; y++)
    {
        num=80;
        k=0,m=0;
        temp=head;
        for(i=0; i<=NUM; i++)
        {
            term=temp;
            temp=temp->next;
            for(j=0; j<80; j++)
            {
                if((temp->data[j])==Data[k])
                    k++;
                else if(Data[k]!='\0')
                {
                    j=j-k;
                    k=0;
                }
                if(Data[k]=='\0')
                {
                    num=j;
                    break;
                }
            }
            if(num<80)
                break;
        }
        for(; i<=NUM; i++)
        {
            for(; j<80; j++)
            {
                if(j+1<k)
                {
                    term->data[80-k+num]=temp->data[j+1];
                }
                else
                    temp->data[j-k+1]=temp->data[j+1];
            }
            term=temp;
            temp=temp->next;
            j=0;
        }
    }
}
char *strrpc(char *str,char *oldstr,char *newstr,int *count)
{
    char bstr[strlen(str)];//转换缓冲区
    memset(bstr,0,sizeof(bstr));

    for(int i = 0; i < strlen(str); i++)
    {
        if(!strncmp(str+i,oldstr,strlen(oldstr))) //查找目标字符串
        {
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
            (*count)++;
        }
        else
        {
            strncat(bstr,str + i,1);//保存一字节进缓冲区
        }
    }

    strcpy(str,bstr);
    return str;
}
LinkList * Replaceword(LinkList *temp)
{
    char *sour=(char *)malloc(sizeof(char)*80);
    char *des=(char *)malloc(sizeof(char)*80);
    int *count=(int *)malloc(sizeof(int)) ;
    *count=0;
    LinkList *head=temp;
    fflush(stdin);
    printf("请输入源字符串:");
    scanf("%s",sour);
    printf("\n请输入目的字符串:");
    scanf("%s",des);
    while(temp)
    {
        strcpy(temp->data,strrpc(temp->data,sour,des,count));
        temp=temp->next;
    }
    head->length-=(*count)*(strlen(sour)-strlen(des));
    temp=head;
    while(temp->data==NULL)
    {
        (head->row)--;
        head=head->next;
        temp=temp->next;
    }
    temp=head;
    while(temp)
    {
        if(temp->next&&temp->next->data==NULL)
        {
            temp->next=temp->next->next;
        }
        else
        {
            temp=temp->next;
        }
    }
    return head;
}
LinkList * MoveWord(LinkList *temp)
{
    int row,pos;
    char *s=(char *)malloc(sizeof(char)*80);
    LinkList *h=temp;
    printf("请输入要移动的字符串,其所在行,要移动到的位置，用空格隔开\n");
    fflush(stdin);
    scanf("%s %d %d",s,&row,&pos);
    if(row<0||row>temp->length)
    {
        printf("行号有误！");
        return temp;
    }
    while(--row>0)
    {
        h=h->next;
    }
    if(strstr(h->data,s)==NULL)//看s是否在data里面
    {
        printf("该行不含此字符串！");
        return temp;
    }
    else
    {
        if(strlen(h->data)<strlen(s)+pos-1||pos<1)
        {
            printf("输入位置有误！");
            return temp;
        }
        else
        {
            char *tem=strstr(h->data,s);

            int p=-((&(h->data[0]))-(&(*tem)));
            //printf("%d %d %d %d",&(h->data[0]),&(*tem),p,strlen(s));
            if(p==pos)
            {
                return temp;
            }
            else if(p>pos)
            {
                char tem[p-pos];
                for(int i=0; i<p-pos; i++)
                {
                    tem[i]=h->data[pos+i];
                }
                tem[p-pos]='\0';
                //	printf("  %s",tem);
                for(int i=0; i<=strlen(s); i++)
                {
                    h->data[pos+i]=s[i];
                }
                for(int i=0; i<p-pos; i++)
                {
                    h->data[pos+strlen(s)+i]=tem[i];
                }
                return temp;
            }
            else if(p<pos)
            {
                ;
            }
        }
    }
}
LinkList * InsertWord(char *str1,LinkList *temp)
{
    int h,q;

    printf("\n\t\t当前文章内容为:");
    PrintWord();
    printf("\n\t\t请输入要插入的行:");
    scanf("%d",&h);
    printf("\n\t\t请输入要插入的列:");
    scanf("%d",&q);
    int i=(h-1)*80+q;
    LinkList *a;
    int n=strlen(str1);
    int m ;
    int insertRow=i/80+1;
    int row=temp->row;
    int j;
    if(insertRow==row)
    {
        for(m=temp->length-1; m>=(i%80)&&n>0; m--)
            temp->data[m+n]=temp->data[m];
        for(m=(i%80),j=0; m<n+(i%80); m++,j++)
        {
            temp->data[m]=str1[j];
        }
    }
    else
    {
        int r=0;
        for(int p=insertRow; p<row; p++)
        {
            if(p == insertRow)
                r=0;
            else
                r=n;
            for(m=temp->length-1-r; m>=0&&n>0; m--)
                temp->data[m+n]=temp->data[m];
            a=temp;
            temp = temp->pre;
            temp->length = 80;
            for(m = temp->length-n,j=0; m<temp->length; m++,j++)
                a->data[j]=temp->data[m];
        }
        for(m=temp->length-n-1; m>=(i%80); m--)
            temp->data[m+n]=temp->data[m];
        for(m=(i%80),j=0; m<(i%80)+n; m++,j++)
            temp->data[m] =str1[j];
    }
    return temp;
}

void menu(LinkList *temp)
{
    char str1[20];
    char str2[20];
    char str3[20];
    char str4[20];
    int a;
    int t;
    do
    {
        WellcomeWord();
        printf("\n");
        printf("\t\t***************************************************\n");
        printf("\t\t*                 主菜单                          *\n");
        printf("\t\t*        1、文章内容输入                          *\n");
        printf("\t\t*        2、显示当前内容                          *\n");
        printf("\t\t*        3、内容统计菜单                          *\n");
        printf("\t\t*        4、查找字符或者字符串                    *\n");
        printf("\t\t*        5、删除字符或者字符串                    *\n");
        printf("\t\t*        6、插入字符或者字符串                    *\n");
        printf("\t\t*        7、替换文章中的符串                      *\n");
        printf("\t\t*        8、移动文章中的符串                      *\n");
        printf("\t\t*        9、保存文件                              *\n");
        printf("\t\t*       10、读取文件                              *\n");
        printf("\t\t*       11、结束:                                 *\n");
        printf("\t\t*    注：第一次运行本程序时请选择1号功能          *\n");
        printf("\t\t***************************************************\n");
        printf("    请选择: ");
        scanf("%d",&t);
        if((t>11)&&(t<1))
        {
            printf("对不起，无此功能，请输入正确的功能序号!\n");
        }
        else
            switch(t)
            {
            case 1:
                system("cls");
                WellcomeWord();
                temp=CreatWord();
                break;
            case 2:
                system("cls");
                PrintWord();
                printf("\n");
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 3:
                system("cls");
                CountWord();
                break;
            case 4:
                system("cls");
                WellcomeWord();
                printf("\t\t\t请输入您需要查找的字符或字符串:");
                getchar();
                gets(str1);
                SearchWord(str1,temp);
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 5:
                system("cls");
                WellcomeWord();
                printf("\t\t\t请输入您需要删除的字符或字符串:");
                getchar();
                gets(str2);
                SearchWord(str2,temp);
                DeleteWord(str2);
                printf("\t\t\t删除 %s 后的文章为:",str2);
                PrintWord();
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 6:
                system("cls");
                WellcomeWord();
                printf("\n\t\t请输入要插入的字符或字符串:");
                getchar();
                gets(str1);
                InsertWord(str1,temp);
                printf("\t\t\t插入字符或字符串后文章为:");
                PrintWord();
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 7:
                system("cls");
                WellcomeWord();
                temp=  Replaceword(temp);
                printf("\t\t\t替换字符或字符串后文章为:");
                PrintWord();
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 8:
                system("cls");
                WellcomeWord();
                MoveWord(temp);
                fflush(stdin);
                getchar();
                printf("\t\t\t移动后的文章为:");
                PrintWord();
                printf("按回车键继续·····");
                getchar();
                getchar();
                system("cls");
                break;
            case 9:
                save();
                break;
            case 10:
                Open();
                system("pause");
                break;
            }
        if(t==11)
            exit(0);;
    }
    while(1);
}
int main()
{
    head=(LinkList *)malloc(sizeof(LinkList));
    LinkList *temp;
    menu(temp);
}
void save()
{
    LinkList *info=head->next;
    int i=0;
    FILE *fp;
    printf("\n请输入文件名称:（例如: d:\\a.txt）\n");
    gets(filename);
    gets(filename);
    if((fp=fopen(filename,"w"))==NULL)
    {
        printf("文件创建失败");
        exit(0);
    }

    for(int j=0; j<=NUM&&info!=NULL; j++)
    {
        for(int i=1; (i<80)&&(info->data[i])!='#'; i++)
        {
            fprintf(fp,"%c",info->data[i]);
        }
        info=info->next;
    }


    fclose(fp);
}
void Open()
{
    ROW=1;
    LinkList *temp;
    int i,j;
    head->next=(LinkList *)malloc(sizeof(LinkList));
    head->pre=NULL;
    temp=head->next;
    temp->pre=NULL;
    temp->length=0;
    for(i=0; i<80; i++)
        temp->data[i]='\0';

    char ch[80]={'\0'};
    FILE *fp;
    printf("输入要打开的文件名:\n");
    scanf("%s",filename);        //输入文件名
    if ((fp = fopen(filename, "r")) == NULL)
        printf("Open file Filename error!\n");
    else
    {
        for(int i=0; i<=80&&!feof(fp); i++)
        {
            fscanf(fp,"%c",&ch[i]);
        }

        printf("文本内容为：\n%s\n",ch);
    }
    //将ch数组的字符再保存到链表
    /*for(j=0; j<Link_Size; j++)
    {*/
        for(i=0; i<80; i++)
        {
            temp->data[i]=ch[i];
            temp->length++;
            if(temp->data[i] =='\n')
            {
                ROW++;
            }
            if(ch=='\0')
            {
                NUM=j;
                break;
            }
        }
        if(ch=='\0')
        {
            temp->length=i;
            temp->next=NULL;
           // break;
        }
        temp->next=(LinkList *)malloc(sizeof(LinkList)) ;
        temp->next->pre=temp;
        temp=temp->next;
        for(i=0; i<80; i++)
            temp->data[i]='\0';
    //}
    temp->row=NUM+1;
    //system("cls");
    fclose(fp);

}

