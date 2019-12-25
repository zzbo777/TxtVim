#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 240
#define NOT_FOUND -1
//函数声明    
void PrintWord(void);    //输出文本的内容 
void scanf_load();       //从键盘录入文本 
void file_load();        //把文本文件的内容读到线性表中
void findstr();          //查找字符串 
void delete1(int linenum);//删除一行
void delete2(int linenum,int position,int lenth);//删除莫一行,莫列，定长的内容 
void insert1();           // 插入一行文字
void insert2(char str[], int linenum, int position);//插入文字到文本莫一行莫一列
void replace();          //替换
void Mainmenu();          //主菜单
void menu1();                //文件录入方式菜单
void menu2();               //文本内容处理菜单
void menu_move();          //移动菜单 
int Index_BF(struct line *info,char *);
//定义结构体
struct line
{
	char text[MAX];      //该行的内容 
	int num;                 //用来记录行号
	struct line *prior;      //用来指向前一行
	struct line *next;       //用来指向下一行
 };
struct line *start;          //指向线性表的第一行
struct line *last;           //指向线性表的最后一行

//主函数 
int main()
{	
	Mainmenu();
	return 0;	
}
// 	输出链表的内容 
void PrintWord()
{
	struct line *p = start;
	while(p != last)
	{
		printf("\n\t\t第%d行|%s",p->num,p->text);
		p = p->next;
	}
	//这是只有一行的输出
	printf("\n\t\t第%d行|%s",last->num,last->text);
	printf("\n");
}
//把文本文件的内容读到线性表中
void file_load()
{
	struct line *info,*temp;   //行指针，info指向当前行，temp指向info的前驱行 
	char ch;
	temp = NULL;
	int linenum,i=0;	   //行计数器,行字符数组下标 
	FILE *fp;          //文件指针 
	char name[20];
	printf("请输入要打开文件名字（例如c:\a.txt）");
	scanf("%s",name);		
	while ((fp=fopen(name,"r"))==NULL)
	{
			printf("\n打开文件失败，请重新输入要打开的文件名：");
			scanf("%s",name);
    }
	start = (struct line*)malloc(sizeof(struct line));     //生成一行的结点空间 
	info = start;
	linenum = 1;
	
	while((ch = fgetc(fp)) != EOF)
	{     
			i = 0;
			info->text[i] = ch;
			i++;
			while((ch = fgetc(fp)) != '\n')      //从文件中读到一行字符到线性表中 
			{	
				info->text[i] = ch;
				i++;
			}
	info->num = linenum++;
	info->next = (struct line*)malloc(sizeof(struct line));
	if (!info->next)
	{
		printf("\n\t\t内存不足"); 
		getchar();
		exit(0);
	}

	temp = info;
	info = info->next;
	info->prior = temp;
 	} 
 	last = info->prior;
 	printf("\t\t文件读入完毕\n"); 
 	fclose(fp);
 	
}

//从键盘录入文本 
void scanf_load()
{	
	struct line *info,*temp;                 //行指针，info指向当前行，temp指向info的前驱行 
	char ch;
	temp = NULL;
	int linenum,i;							   //行计数器,行字符数组下标 
	FILE *fp;                                 //文件指针 
	temp = NULL;
	start = (struct line*)malloc(sizeof(struct line));     //生成一行的结点空间 
	info = start;//当前是第一行
	linenum = 1;
	printf("\t\t请从键盘录入文本(输入时回车换行，输入结束后在新的一行输入#结束录入)\n\t\t"); 
	while((ch = getchar()) !='#')
	{
			i = 0;
			info->text[i] = ch;
			i++;
			while((ch = getchar()) != '\n')      //从键盘读到一行字符到线性表中 
			{				
				info->text[i] = ch;
				i++;			
			}//此循环结束表明第一行输入结束，然后执行下面的代码
		printf("\t\t");		
		info->text[i] = '\0';
		info->num = linenum++;//开辟第二行
		info->next = (struct line*)malloc(sizeof(struct line));//下一行分配空间
		info->prior = temp;
		temp = info;//当前行赋给前驱行
		info = info->next;//下一行赋给当前行
 	} //输入结束了
 	temp->next = NULL;
 	last = temp;
 	free(info);
 	start->prior = NULL;
}

//文件保存
void save()
{
    system("cls");
	FILE *fp;
    line *info=start;
	int i=0;
    char name[20];
	printf("\n请输入保存地址(例如: c:\\a.txt):");
	scanf("%s",name);
		while ((fp=fopen(name,"w+"))==NULL)
		{
			printf("文件不存在，请重新输入文件名：");
			scanf("%s",name);
		} 
	while(info)
	{   
        while(info->text[i]!='\n')  
		{fprintf(fp,"%c",info->text[i]);
		 i++;
		}
		info = info->next;
		i = 0;
	}
	    
        fclose(fp);
		printf("\n文件保存成功\n");	

}
//BF算法
int Index_BF(struct line *info,char *str){
	int i=1,j=1;
	//printf("test\n");
	while(i<=strlen(info->text)&&j<=strlen(str)){//两串均未达到末尾
		if(info->text[i]==str[j]){
			++i;++j;//继续比较
		}else{
		i=i-j+2;j=1;//指针后腿重新匹配
		}
	}
	//printf("2test\n");
	if(j>strlen(str))
		return i-strlen(str);//匹配成功
	else
		return 0;//匹配失败
}

 //查找字符串 
void findstr(){

	PrintWord();
	char str[MAX];
	getchar();
	printf("\t\t 输入想要查找的字符串：");
	gets(str);
	printf("\t\t|>>________________________________________________<<|\n");
  	struct line *info;
	//int i = 0, find_len, found = 0, position;
	//char substring[MAX];
	info = start;
	//int find_num = 0;             //匹配到的次数 
	//find_len = strlen(str);
	while (info)   //查询
	{	
		//下面采用BF算法实现字符串匹配
		if(Index_BF(info,str))
			printf("\t\t出现在%d行%d列\n",info->num,Index_BF(info,str));
		else
			printf("\t\t内容不存在\n");

		/*i = 0;  //行间循环
		while (i <= (strlen(info->text) - find_len))  //行内查找循环
		{	int k=0;
			
			for(int j=i;j<i+find_len;j++)   // 行内的字符串从第一个开始按定长find_len赋给substring 
			{	
				substring[k] = info->text[j]; 
				k++;
			}
			if (strcmp(substring,str) == 0)
			{	
				find_num++;
			
				printf("\t\t|第%d次出现在：%d行%d列\n",find_num,info->num,(i+1+1)/2);
				found = 1;
			}
				i++;
		}*/
		info = info->next;
	}
	/*if (found)  //查找成功
		printf("\t\t|\t\t该内容出现的总次数为%d\n",find_num);
	else   //查找不成功
		printf("\t\t该内容不存在\n");*/
	printf("\t\t|>>________________________________________________<<|\n");
	
}

//删除一行
void delete1(int line_num)
{	
	struct line * info, *p;
	info = start;
	while ((info->num < line_num) && info)  //寻找要删除的行 
		info = info->next;
	if (info == NULL)
		printf("该行不存在");
	else
	{
		p = info->next;     //指向要删除的行后面一行 
		if (start == info) //如果删除的是第一行
		{
			start = info->next;
			if (start)  //如果删除后，不为空
				start->prior = NULL;
			else  //删除后为空
				last = NULL;
		}
		else
		{
			info->prior->next = info->next;  //指定行的上一行指向指定行的下一行
			if (info != last) //如果不是最后一行
				info->next->prior = info->prior;  //修改其下一行的指向头的指针 
			else  //如果是最后一行，修改尾指针
				last = info->prior;
		}
		free(info);
		while (p) //被删除行之后的行号减一 
		{
			p->num = p->num - 1;
			p = p->next;
		}

	}

}

//删除莫一行,莫列，定长的内容 
void delete2(int line_num,int position,int lenth)
{	
	
	struct line *info=start;
	char rest_str[MAX];
	if(line_num == 1)
	info = start;
	else
	for(int i=1;i<line_num;i++)     	 //让info指向删除内容所在行 
	info = info->next;      
	if (info == NULL)
		printf("该行没有字符！n");
	else
	{
		if (strlen(info->text) <= (position + lenth))  //本行的字符长度<=待删除的列号+删除长度，直接在当前位置插入'\0'
			info->text[position] = '\0';
		else
		{	int i;
			for(i = position-1;info->text[i+lenth]!='\0';i++)
			info->text[i]=info->text[i+lenth];
			info->text[i]='\0';
		}
	}
}


// 插入一行文字
void insert1()
{	
	int linenum; 
	printf("\t\t输入插入位置的行号：");
	scanf("%d", &linenum);
	struct line * info, * q, * p;
	p = start;
	q = NULL;

	while (p && p->num != linenum)               
	{
		q = p;				//插入行前面一行 
		p = p->next;	   //插入行后面一行
	}

	if (p == NULL && (q->num + 1) != linenum)	//指定行不存在，不能插入
	{
		printf("\t\t输入的行号不存在");
	}

	else // 指定行存在，进行插入
	{
		info = (struct line *)malloc(sizeof(struct line));
		printf("\t\t输入要插入的字符串:");
		scanf("%s", info->text);
		info->num = linenum;
		if (linenum == 1)  			  //插入在第一行
		{
			info->next = p;
			p->prior = info;
			info->prior = NULL;
			start = info;
		}

		else if (q->num != linenum)  //插入在最后一行
		{
			q->next = info;
			info->next = p;
			info->prior = q;
		}

		else     //插入在其他行
		{
			q->next = info;
			info->next = p;
			p->prior = info;
			info->prior = q;
		}

		while (p)   //如果不是插入在最后一行，插入行后面的行号都加1
		{
			p->num = p->num + 1;
			p = p->next;
		}

	}

}

//插入文字到文本莫一行莫一列
void insert2(char str[], int linenum, int position)
{
	
	struct line * info;
	int len, i;
	int lenth;
	char rest_str[MAX],kongge[2] = { " " };
	info = start;
	while (info && info->num != linenum)   //查询要插入的行
	{
		info = info->next;
	}
	if (info == NULL)
		printf("不存在该行！\n");
	else if (position < 0)
		printf("不存在该列！\n");
	else    //如果行和列都存在，则进行插入
	{
		lenth = strlen(info->text);
		if (lenth < position)	//插入列大于本行文件列数
		{
			len = position - lenth - 1;
			for (i = 0; i < len; i++)
			strcat(info->text, kongge);   //将空余的部分插入空格符
			strcat(info->text, str);    //插入字符到列的未尾
		}

		else   //插入列在本行文字的中间
		{
			strcpy(rest_str, &info->text[position - 1]);
			strcpy(&info->text[position - 1], str);
			strcat(info->text, rest_str);
		}
	}
} 
 
//替换
void replace()
{
	PrintWord();
	char str[MAX];
	printf("\t\t输入想要替换的字符串：\t\t");
	scanf("%s",&str);
	char replace[MAX]; 
	printf("\t\t替换为："); 
	scanf("%s",&replace);
  	struct line *info;
	int i = 0, find_len, found = 0, position;
	char bijiao[MAX];
	info = start;
	int find_num = 0;             //匹配到的次数 
	find_len = strlen(str);
	while (info)   //查询
	{	
		
		i = 0;  //行间循环
		while (i <= (strlen(info->text) - find_len))  //行内查找循环
		{	int k=0;
			
			for(int j=i;j<i+find_len;j++)   // 行内的字符串从第一个开始按定长find_len赋给substring 
			{	
				bijiao[k] = info->text[j]; 
				k++;
			}
			if (strcmp(bijiao,str) == 0)
			{	
				find_num++;
				delete2(info->num,i+1,find_len);
				insert2(replace,info->num,i+1);
				found = 1;
			}
				i++;
		}
		info = info->next;
	}
	if (found)  //查找成功
		printf("\t\t该内容替换的总次数为%d\n",find_num);
	else   //查找不成功
		printf("\t\t该内容不存在\n");
	printf("\t\t经过替换后的内容为：\n");
	PrintWord();
	
	
 } 

//文件录入方式菜单
void menu1()
{	
	printf("\t\t|请选择录入方式    1：从键盘输入     2：从文件录入   |\n\t\t");
	int i;
	scanf("%d",&i);
	getchar();
		if(i>2||i<1)    
	{   
		printf("\t\t对不起，请输入正确的功能序号!\n");
	}
	switch(i)
	{
		case 1:
			scanf_load();
			system("cls"); 
			break;
		case 2:
			file_load();
			system("cls"); 
			break;				 
 	} 
}

//移动菜单 
void menu_move()
{	
	
	int choice;
	printf("\n\t\t|______________移动操作___________________|\n");
	printf("\n\t|----->1.      向下移动一行         <-----------|\n");
	printf("\t\t|----->2.      向上移动一行         <-----------|\n");
	printf("\t\t|----->3.      向右移动一列         <-----------|\n");
	printf("\t\t|----->4.      向左移动一列         <-----------|\n");
	printf("\t\t|----->5.      返回上级菜单         <-----------|\n");
	printf("\t\t请选择");
	scanf("%d",&choice); 
	int line_num,number;
	char str[2];
	switch (choice)
			{
			case 1:   // 向下移动一行
				
				printf("\t\t输人要移动的字符串所在行号：");
				scanf("%d", &line_num);
				struct line *info,*p;                    //新建一行空行 
				info = (struct line *)malloc(sizeof(struct line));
				info->text[0] = ' ';
				info->text[1] = '\0';
				info->num = line_num;
				if (line_num == 1)    //插入在首行
				{	
					info->next = start;
					start->prior = info;
					start = info;
					start->prior = NULL;
					p=start->next;
				}
				else  //插入在其他行
		        {
		       	p=start;
		    	while (p->num != line_num)
					p = p->next;                    //令p指向插入行 
				info->next=p;
				info->prior=p->prior;
				p->prior->next=info;
				p->prior = info;}
				while (p)   //插入行后面的行号都加1
				 {
					p->num = p->num + 1;
					p = p->next;
				 }
				break;
			case 2:   //向上移动一行
				printf("\t\t输入要移动的字符串所在行号：");
				scanf("%d",&line_num);
				delete1(line_num-1);
				break;
			case 3:   //向右移动一列
				printf("\t\t输人要移动的字符串所在行号：");
				scanf("%d", &line_num);
				printf("\t\t输入要移动的字符串所在列号：");
				scanf("%d", &number);
				str[0] = ' ';
				str[1] = '\0';
				insert2(str, line_num, number);
				break;
			case 4:   //向左移动
				printf("\t\t输入要移动的字符串所在行号：");
				scanf("%d", &line_num);
				printf("\t\t输入要移动的字符串所在列号：");
				scanf("%d", &number);
				if (number <= 0)
					printf("\t\t该列不存在");
				else
					delete2(line_num, number - 2, 1);
				break;
			case 5:   //退出移动
				break;

} 
	
}

//文本内容处理菜单
void menu2()
{  
	char str1[20];
	char str2[20];
	int a;
while(1)
{	

	printf("\t\t___________________\n");
	printf("\t\t1、查找字符或字符串\n");
	printf("\t\t2、删除字符或字符串\n");
	printf("\t\t3、插入字符或字符串\n");
	printf("\t\t4、移动字符或字符串\n");
	printf("\t\t5、替换字符或字符串\n");
	printf("\t\t6、返回主菜单      \n");
	printf("\t\t7、直接退出系统    \n");
	printf("\t\t___________________\n");
	printf("\t\t    请选择:");
	scanf("%d",&a);
	switch(a)
	{
		case 1:   
	       	 system("cls"); 
	      	 
         	 findstr();
		  	 printf("\t\t按回车键继续·····");
			 getchar();
		   	 getchar();
			 system("cls");
		     break;
	   case 2:
	         system("cls"); 
	         
	         printf("\t\t|    1:删除一行文字    2:删除某一行,某列，定长的内容|\n\t\t");
	         int delete_choice;
             scanf("%d",&delete_choice);
             getchar();
             if(delete_choice == 1)
           	{
				   int linenum;
				   printf("\t\t当前文本为：\n");
				   PrintWord();
           		   printf("\t\t请输入你删除行的行号：");
			       scanf("%d",&linenum);
				   getchar(); 
           		   delete1(linenum);
			}
             else if(delete_choice == 2)
			{
				   int linenum, position,lenth;  //行，列，删除长度 
				   printf("\t\t当前文本为：\n");
				   PrintWord();
			       printf("\t\t请输入要删除内容所在行，列，删除内容字节长度，中间用空格隔开\n");
				   printf("\t\t--->注意：汉字占两个字节\n\t\t");
				   scanf("%d %d %d",&linenum,&position,&lenth);
				   position = (position*2)-1;
				   getchar();
				   delete2(linenum,position,lenth);
			}
            printf("\t\t删除后的文章为:\n");
            PrintWord();
		    printf("\t\t按回车键继续·····");
			getchar();
			getchar();
			system("cls");
		    break;
      case 3:
           
	        system("cls"); 
	        
            printf("\t\t|   1:插入一行文字      2：插入文字到文本到一行的中间|\n\t\t");
            int insert_choice;
            scanf("%d",&insert_choice);
            if(insert_choice == 1)
            {
            printf("\t\t当前文本为：\n");
			PrintWord();
			insert1();}
            else
           {
           	printf("\t\t当前文本为：\n");
			PrintWord();
		    char str[MAX]; int linenum; int position;
		    printf("\t\t输入插入位置一行号：");
			scanf("%d", &linenum);
			printf("\t\t输入插入位置-列号：");
			scanf("%d", &position);
			position = (position*2)-1;
			printf("\t\t要插入的字符串：");
			scanf("%s", str);
			insert2(str,linenum,position);
		   }
           
            printf("\t\t插入字符或字符串后文章为:\n");
            PrintWord();
		    printf("\t\t按回车键继续·····");
			getchar();
			getchar();
			system("cls");
		    break;
	 case 4:
		    system("cls");
		    			
		    menu_move();
		    printf("\t\t移动后文本内容为：\n");
			PrintWord();
		    printf("\t\t按回车键继续·····");
			getchar();
			getchar();
			system("cls");
		    break;
	 case 5: 
		    system("cls"); 

		    replace();
		    printf("\t\t按回车键继续·····");
			getchar();
			getchar();
			system("cls");
	        break;
	 case 6:
		 system("cls");
		 break;
	 case 7:
		 exit(0);
     }       
  }
}
//主菜单

void Mainmenu()
{	
	int t;
	while(1){
	printf("\n");
	printf("\t\t ____________________________________________________\n");
	printf("\t\t|                 主菜单                             |\n");
	printf("\t\t|                                                    |\n");
	printf("\t\t|---->  1、输入文章内容                              |\n");
	printf("\t\t|---->  2、进入文章内容处理菜单                      |\n");
	printf("\t\t|---->  3、显示当前文章内容                          |\n");
	printf("\t\t|---->  4、保存文本                                  |\n");
	printf("\t\t|---->  5、退出文本编辑器                            |\n");
	printf("\t\t|                                                    |\n");
	printf("\t\t|    注：第一次运行本程序时请选择功能1               |\n");
	printf("\t\t|____________________________________________________|\n");
	printf("  \t\t  请选择:");
	scanf("%d",&t);
	if(t>5||t<1)
	{   
		printf("对不起，无此功能，请输入正确的功能序号!\n");
	}
	else
	switch(t)
	{  
    	case 1:  
		     system("cls"); 		     
		     menu1();
			 printf("\t\t按回车键继续·····");
			 getchar();
			 getchar();
			 system("cls");
             break;
    	case 2:  
		     system("cls"); 
		     menu2();
			 break;
		case 3:
		     system("cls"); 
		     
			 printf("\n\t\t ____________________文章内容为______________________\n");
             PrintWord();
			 printf("\n");
			 printf("\t\t按回车键继续·····");
			 getchar();
			 getchar();
			 system("cls");
			 break;
		case 4:	 
		     save();
		     break;
		case 5:
			break;
	  }
   }
}