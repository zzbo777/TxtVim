#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string>
#include<iostream>
#include<conio.h>

#define Link_Size 100

int NUM,C,N;

typedef struct list
{
    char data[80];
    int length;
    struct list *next;
    struct list *pre;
    int row;
} LinkList;

int initlist(Sqlist *L)  //顺序表的初始化

LinkList *CreatWord()    //文本的输入
{
    LinkList *temp;
    char ch;
    int i,j;
    head->next=(LinkList *)malloc(sizeof(LinkList));
    head->pre=NULL;

    temp=head->next;
    temp->pre=null;
    temp->length=0;

    for(i=0; i<80; i++)
        temp->data[i]='\0';//初始化初值

    printf("开始创建文本，请输入文章（输入#号结束）：\n");
    for(j=0; j<Link_Size; j++)
    {
        for(i=0; i<80; i++)
        {
            ch=getchar();
            temp->data[i]=ch;
            temp->length++;
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
        temp->next=(LinkList *)malloc(sizeof(LinkList));
        temp->next->pre=temp;
        temp=temp->next;
        for(i=0; i<80; i++)
            temp->data[i]='\0';
    }
    temp->row=NULL+1;
    system("cls");
    return temp;

}
void PrintWord()//文本输出函数

{

    int i,j;

    LinkList *p;

    p=head->next;

    system("cls");

    //HeadWord();

    printf("\n当前文章的内容是:");

    for(j=0; j<=NUM&&p!=NULL; j++)

    {

        for(i=0; (i<80)&&(p->data[i])!='#'; i++)

        {

            printf("%c",p->data[i]);

        }

        p=p->next;

    }

}

void ReplaceWord(char *shr1,LinkList* temp)//文本的替换函数
{
    char Date1[20],Date2[20];
    int i,j,k=0,sum=0;
    int i=1;
    temp=head->next;
    strcpy(Date1,str1);//被替换内容的赋值
    strcpy(Date2,str2);//替换内容的赋值

    for(i=0; i<=NUM; i++)

    {

        for(j=0; j<80; j++)

        {

            if((temp->data[j])==Data1[k])
                k++;

            else if(Data1[k]!='\0')

            {

                j=j-k;

                k=0;

            }

            if(Data1[k]=='\0')

            {
                int n;
                n=j-k+1;
                for(m=0; m<sizeof(str2); k++)
                {
                    temp->data[n]=Date2[m];//替换值
                    n++;
                }

                l++;

                k=0;

                continue;
            }

        }

        temp=temp->next;

    }
    printf("替换后的文本内容如下：\n")；
    PrintWord();
}
void SearchWord(char *str1,LinkList* temp)//文本内容查找函数

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
void DeleteWord(char *str2)//文本内容删除函数

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
LinkList * InsertWord(LinkList *temp)//文本内容插入函数

{

    char Data[20];

    int h,l;


    printf("\n\t\t请输入要插入的字符或字符串:");

    getchar();

    gets(Data);

    printf("\n\t\t当前文章内容为:");

    PrintWord();

    printf("\n\t\t请输入要插入的行:");

    scanf("%d",&h);

    printf("\n\t\t请输入要插入的列:");

    scanf("%d",&l);

    int i=(h-1)*80+l;

    LinkList *a;

    int n=strlen(Data);

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

            temp->data[m]=Data[j];

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

            temp->data[m] =Data[j];


    }

    return temp;

}

void FileSave()//文件存入函数
{
    LinkList *s;
    s=head->next;

    FILE *fpWrite=fopen("data.txt","w");//数据存入文件
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(j=0; j<Link_Size; j++)
    {
        for(i=0; i<80; i++)
        {
            j=s->data[i];
            fprintf(fpWrite,"%d ",j);
        }
    }
    fclose(fpWrite);
    printf("数据已存入到文件中！\n");

}

void FileRead()//文件的读取
{
    LinkList *r;
    r=head->next;

    FILE *fpRead=fopen("data.txt","r");

    if(fpRead==NULL)

    {
        return 0;
    }

    for(j=0; j<Link_Size; j++)
    {
        for(i=0; i<80; i++)
        {
        fscanf(fpRead,"%d ",&s->date[i]);
        printf("%d ",s->date[i]);
    }

    printf("数据已从文件中读取成功！\n");
    getchar();//等待
}

}





void main()
{
    printf("\t\t\t*************************************************************\t\t\t\n");
    printf("\t\t\t*                                                           *\n");
    printf("\t\t\t*                       文 本 编 译 器                      *\n");
    printf("\t\t\t*                                                           *\n");
    printf("\t\t\t*************************************************************\t\t\t\n");
    printf("\t\t\t*                    可 执 行 如 下 操 作                   *\n");
    printf("\t\t\t*************************************************************\t\t\t\n");
    printf("\t\t\t* {1}：文本的输入    \t\t\t    {2}：文本的修改 *        \n");
    printf("\t\t\t* {3}：文本的删除    \t\t\t    {4}：文本的查找 *        \n");
    printf("\t\t\t* {5}：文本的替换    \t\t\t    {6}：文本的插入 *        \n");
    printf("\t\t\t* {7}：文本的移动    \t\t\t    {8}：文本的输出 *        \n");
    printf("\t\t\t* {9}：文件的存入    \t\t\t    {10}：文件的读取 *        \n");
    printf("\t\t\t*************************************************************\t\t\t\n");
    printf("\t\t\t提示：如果您是第一次使用文本编译器请选择第一选项进行内容的输入！\n");
    printf("\t\t\t请输入您的选择：\n");
    scanf("%d",&a);

    switch(a)

    {

    case 1:

        system("cls");

        CreatWord();

        printf("\t\t\t请输入需要编译的文本内容:\n");

        getchar();

        gets(str1);

        SearchWord(str1,temp);

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    /*case 2:

        system("cls");

    修改函数

        printf("\t\t\t请选择您输入修改的字符或字符串:");

        getchar();

        gets(str2);

        SearchWord(str2,temp);

        DeleteWord(str2);

        printf("\t\t\t修改后的文章为:",str2);

        PrintWord();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;*/

    case 3:

        system("cls");

        DeleteWord(temp);

        printf("\t\t\t修改后的文章为:");

        PrintWord();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    case 4:

        system("cls");

        SearchWord()

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    case 5:

        system("cls");

        ReplaceWord();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    case 6:

        system("cls");

        InsertWord();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    /*case 7://文本的移动

        system("cls");

        SearchWord()

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;
*/
    case 8:

        system("cls");

        PrintWord()；

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;

    case 9://文件的存入

        system("cls");

        FileRead();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;


    case 10://文件的读取

        system("cls");

        FileRead();

        printf("按回车键继续·····");

        getchar();

        getchar();

        system("cls");

        break;


    }

}
