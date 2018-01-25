/**************************************************************************************************************
                     程序设计：万年历
                     程序功能：
					 			1.  查询当前日期，从系统时间读入数据在显视频上显示 
					 			    并打印出当年的年历表，并把年历写如文件 
								2.  指定年份查询，从键盘读入一个年份，在显视频上打印
								    该年的年历，提供选择是否把该年的年历表写到文件	  
								3.  查询制定年份的1月1好是星期几，从键盘读入年份、
								    在显示频上进行显示
								4.  查询节日，提供选择可选择公历节日和农历节日
								5.	公历转农历，从键盘上读取一个日期，进行转换
								    在显示频上进行反馈
						
						使用语言：C
						编程环境：DEV 
						小组成员：杨秉茜 苏晨晨 宋友
						时间：2017年3月6号到9号 
										 
*************************************************************************************************************/
#include<stdio.h>                                       //包含stdio头文件
#include<conio.h>                                       //包含conio头文件
#include<stdlib.h>                                      //包含stdlib头文件
#include<string.h>										//包含string头文件	
#include<time.h>                                        //包含time头文件 
#define PF printf                                       //宏定义输出printf 
#define LEAP(y) !(y%(y%100?4:400))                      //宏定义判断闰年 
#define EP PF("%s%s%.10s%s%s*",s,k,k,k,k)               //宏定义显示界面
FILE *fp;
int year_time,month_time,day_time;                      //申明全局变量 
//int lunar_year,lunar_month,lunar_day;
//void write_date(int year,int month,char array[3*7*6]);
/**********************************函数申明*****************************************************************/
int The_week(int year,int month,int day);               //判断某天是星期几 
void print_month(int year,int month,char array[3*7*6]); //输出打印某个月份 
void print_halfyear(int year,int month);                //输出打印半年的年历 
void Get_time();                                        //获取系统时间 
void print_hello();                                     //欢迎界面，系统初始化等 
void search_year();                                     //查找年份函数 
void search_day();                                      //查找天函数 
void file_init();                                       //文件指针初始化函数 
void file_write_month(int year,int month,char array[3*7*6]);
 														//在文件中写入月历  			
void file_write_halfyear(int year,int month);           //在文件中写入半年的年历 
int LunarCalendar(int year,int month,int day);          //农历函数初始化 
void lunar(int year,int month,int day);                 //农历函数 
void lunar_holiday(int year,int month,int day);         //农历假日函数 
void calendar_holiday();                                //公历假日函数 
void select_lunar_holiday(int month,int day);           //选择农历假日函数 
void lunar_holiday_print(int year,int month);           //打印农历假日函数 
void draw_yearlogo(int year);                           //输出打印年份logo 
void write_yearlogo(int year);                          //在文件中写如年份logo
void calendar_to_lunar_init(int year,int month,int day);//公历转农历函数初始化   
void calendar_to_lunar();                               //公历转农历函数 
 


/**********************************the week***************************************/
//函数功能：算出给定日期是星期几

int The_week(int year,int month,int day)                
{
    int i,y1,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    days[2]=28+LEAP(year);
    for(i=1;i<month;i++)
		day+=days[i];
    y1=year-1;
    day+=y1+y1/4-y1/100+y1/400;                                      //星期算法
    return day%7;
}
/*********************************************************************************/

/***********************************print_month***********************************/
//函数功能：对指定年份的指定月份进行打印
void print_month(int year,int month,char array[3*7*6])               //显示数组部分
{
    char *pa;
    int i,week,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};       //月份天数
    days[2]=28+LEAP(year);									         //算出闰年二月的天数
    week = The_week(year,month,1);                                   //算出某年某月1号的是星期几    
    week = week?week-1:week+6;                                       //得到星期
    pa = array+3*week;                                               //确定指针初始（1号）位置
    for(i=1;i<=3*7*6;i++)
		array[i-1]=' ';                                              
    for(i=1;i<=days[month];i++,pa+=3)                                //1号以前的日期用空格填补，之后没输出一个日期，指针加3（指向下一个显示位）
		sprintf(pa,"%3d",i);                                         //打印当前指针所指的日期 
    *pa=' ';										                 
}
/***********************************************************************************/


void print_halfyear(int year,int month)                              //输出半年的年历表
{
    int i,j;
    char ary[6][7*3],bry[6][7*3],cry[6][7*3];                        //定义三个数组（月份数组）；并排输出三个月份
    char const *k="                    ",*s="\n    *";               //显示界面提示信息
    char const *xs="********************************";               //显示界面提示信息
    PF("%s%s %04d %s*",s,xs,year,xs);                                //显示界面提示信息
    for(i=1;i<=2;i++,month+=3)
    {
       EP;	
	   char const month_name[][6]={{},{"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},
	   								{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"}};													     		   //显示界面提示信息
       PF("%s%.10s%s%.20s%s%.20s%s%.11s*",s,k,month_name[month],k,month_name[month+1],k,month_name[month+2],k);
																			   //month小于10时从month月开始显示输出三个月的月历			
       EP;																       //显示界面提示信息
       PF("%s  MO TU WE TH FR SA SU   MO TU WE TH FR SA SU   MO TU WE TH FR SA SU  *",s);
																			   //星期格式框架
       print_month(year,month ,ary[0]);									       //输出月份	
       print_month(year,month+1,bry[0]);								       //输出月份
       print_month(year,month+2,cry[0]);									   //输出月份	
       for(j=0;j<6;j++)                                                        
       {
          PF("%s %.21s  %.21s  %.21s  *",s,ary[j],bry[j],cry[j]);
       }
	   EP;
    }
    PF("%s%s******%s*",s,xs,xs);
}

/*******************************************Get_time***********************************************/
void Get_time()                                                      //获取系统时间 
{       
	int sysyear = 0;
    int sysmonth=0;
    int sysday=0;
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    sysyear = timenow->tm_year+1900;
    sysmonth=timenow->tm_mon+1;
    sysday=timenow->tm_mday;
    printf("\n\n\n\n\t\t\t\t        ||=======================================||\n");
																	  //格式化打印 
    printf("\t\t\t\t        ||系统当前时间:%d-%d-%d                  ||\n",sysyear,sysmonth,sysday);
    //printf("这是今年的年历：");   
	 year_time=sysyear;month_time=sysmonth;day_time=sysday;    
}
/***************************************************************************************************/
void print_hello()													  //欢迎界面				
{
	printf("\n\n\n"); 
	printf("			  ##      ##    #########     ##            ##           ##########   \n");
	printf("			  ##      ##    ##            ##            ##           ##      ##   \n");
	printf("			  ##########    #######       ##            ##           ##      ##   \n");
	printf("			  ##      ##    ##            ##            ##           ##      ##   \n");
	printf("			  ##      ##    ##########    ##########    ##########   ##########   \n\n\n"); 
	/***************************菜单界面***************************************/ 
	printf("\t\t\t\t\t__________________________________________\n");
	printf("\t\t\t\t\t##########################################\n"); 
	printf("\t\t\t\t\t-————————————————————-\n\n");
    printf("\t\t\t\t\t|*|你好，欢迎来到万年历小程序          |*|\n\a");
    printf("\t\t\t\t\t|*|设计人：杨秉茜 苏晨晨 宋友          |*|\n\n");   
    printf("\t\t\t\t\t|*|请选择功能：                        |*|\n");
	printf("\t\t\t\t\t|*|查询当前日期请输入 1；              |*|\n");
	printf("\t\t\t\t\t|*|查询指定的年历请输入 2；            |*|\n");
	printf("\t\t\t\t\t|*|查询指定年份元旦是周几请输入 3；    |*|\n");
	printf("\t\t\t\t\t|*|查询节日请输入 4；                  |*|\n");
	printf("\t\t\t\t\t|*|公历转农历请输入 5;                 |*|\n"); 
   	printf("\t\t\t\t\t|*|退出程序请输入 6；                  |*|\n");
	printf("\t\t\t\t\t__________________________________________\n\n");
	
}
/*****************************************************************************************************/

void search_year()
{
	int year;
	int y;
	
    printf("\t\t\t\t\t是否打印当年的年历表？\n");                //选择是否生成文件 
    printf("\t\t\t\t\t如果是请输入1;否按任意键跳过。\n\n\n");
    scanf("%d",&y);
   	if(y==1)
	{
		printf("\t\t\t\t\t请在程序所在目录下找calendar文件\n");
		fp = fopen("calendar.txt","w+");
		if(fp==0)
			{
				printf("file error\n");
				exit(1);	
			} 
	}
    do
    {
       PF("\t\t\t\t\tPlease input a year which you want to search: ");            
	   													 //提示输入年份 
       scanf("%d",&year);                                //读入年份
    }while(year<=0||year>9999);
    
 
	draw_yearlogo(year);
	if(y==1)
		write_yearlogo(year);                            //写入年份logo 
    print_halfyear(year,1);                              //上半年
	if(y==1)
		file_write_halfyear(year,1);
	getch();
    PF("\n");
    print_halfyear(year,7);                              //下半年
    
	if(y==1)
		file_write_halfyear(year,7);
	//fclose(fp);   
    getch();
    PF("\n\n\n");
    fclose(fp);
} 
/**********************************************************************************/
void search_day()
{
	int year,i;
	char const *week_day;
	do
    {
       PF("\t\t\t\t\tPlease input a year which you want to search: \n");            
	   													 //提示输入年份 
       scanf("%d",&year);                                //读入年份
    }while(year<=0||year>9999);
    i=The_week(year,1,1);
    
    switch(i)                                            //英文输出星期 
     {
    	case 1:
    		{week_day = "monday";break;}
    	case 2:
    		{week_day = "tuesday";break;}
    	case 3:
    		{week_day = "Wednesday";break;}				
    	case 4:
    		{week_day = "Thursday";break;}		
    	case 5:
    		{week_day = "Friday";break;}	
    	case 6:
    		{week_day = "Saturday";break;}			
    	case 7:
    		{week_day = "Sunday";break;}	 	
	}
    printf("\t\t\t\t\t这年的1月1号是%s。",week_day);
}
/********************************************file**************************************************/
void file_init()                                         //文件指针初始化 
{
	fp = fopen("date.txt","w+");                         //以新建形式创立一个带写入文件文件名：date 
	char ch;
	if(fp==0)
		{
			printf("file error\n");
			exit(1);	
		} 
} 
/****************************************************************************************************/
void file_write_month(int year,int month,char array[3*7*6])
{ 																			//在文件中写入某月的月历	
	int i,week,longth,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};       //月份天数
    days[2]=28+LEAP(year);									                //算出闰年二月的天数
    week = The_week(year,month,1);                                          //算出某年某月1号的是星期几    
    week = week?week-1:week+6;                                              //得到星期
    //fp = array[0]+3*week;
    array = array + 3*week;
    //strcat(array,fp);
	//longth = array[0]+(week);    
	fseek(fp,longth,1);		                                                //指针没有移位导致文件打印时出现bug！！！  
	for(i=1;i<3*7*6;i++)
		array[i-1]=' ';
	for(i=1;i<days[month];i++,fseek(fp,0,1))
		fprintf(fp,"%3d",i);
	fprintf(fp,"%s"," ");			
}

void file_write_halfyear(int year,int month)
{																		    //在文件中写入某年半年的年历 
	int i,j;
	char const month_name[][5]={{},{"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},
								{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"}};
																		    //定义月份名数组 
	char ary[6][7*3],bry[6][7*3],cry[6][7*3];
	char const *k="                    ",*s="\n    *";                      //显示界面提示信息
    //char const *xs="********************************";                    //显示界面提示信息
	char const *xs="________________________________";						//格式化显示				   
    fprintf(fp,"%s%s %04d %s*",s,xs,year,xs);                               //显示界面提示信息
    for(i=1;i<=2;i++,month+=3)
    {
       //EP;														     		   //显示界面提示信息
       fprintf(fp,"%s%.10s%s%.20s%s%.20s%s%.11s*",s,k,month_name[month],k,month_name[month+1],k,month_name[month+2],k);
																			   //month小于10时从month月开始显示输出三个月的月历			
       //EP;																       //显示界面提示信息
       fprintf(fp,"%s  MO TU WE TH FR SA SU   MO TU WE TH FR SA SU   MO TU WE TH FR SA SU  *",s);		
	   																			   //星期格式框架
       //file_write_month(year,month  ,ary[0]);									   //输出月份	
       //file_write_month(year,month+1,bry[0]);								       //输出月份
       //file_write_month(year,month+2,cry[0]);									   //输出月份	
       for(j=0;j<6;j++)                                                        
       {
          fprintf(fp,"%s %.21s  %.21s  %.21s  *",s,ary[j],bry[j],cry[j]);		   //格式化显示
       }
	   //EP;
    }
    //PF("%s%s******%s*",s,xs,xs);
}

/**************************************************************************************************/
/*                                         农历部分												  */
//本部分代码来源于网络
//////////////////////////////////////////////////////////////////////////////////////////////////// 
unsigned int LunarCalendarDay;  
unsigned int LunarCalendarTable[199] =  
{  
    0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/  
    0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/  
    0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/  
    0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/  
    0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/  
    0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/  
    0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/  
    0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/  
    0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/  
    0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/  
    0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/  
    0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/  
    0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/  
    0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/  
    0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/  
    0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/  
    0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/  
    0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/  
    0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/  
    0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/  
};  
int MonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};  
int LunarCalendar(int year,int month,int day)  
{  
    int Spring_NY,Sun_NY,StaticDayCount;  
    int index,flag;  
    //Spring_NY 记录春节离当年元旦的天数。  
    //Sun_NY 记录阳历日离当年元旦的天数。  
    if ( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)  
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;  
    else  
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;  
    Sun_NY = MonthAdd[month-1] + day - 1;  
    if ( (!(year % 4)) && (month > 2))  
        Sun_NY++;  
    //StaticDayCount记录大小月的天数 29 或30  
    //index 记录从哪个月开始来计算。  
    //flag 是用来对闰月的特殊处理。  
    //判断阳历日在春节前还是春节后  
    if (Sun_NY >= Spring_NY)//阳历日在春节后（含春节那天）  
    {  
        Sun_NY -= Spring_NY;  
        month = 1;  
        index = 1;  
        flag = 0;  
        if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)  
            StaticDayCount = 29;  
        else  
            StaticDayCount = 30;  
        while (Sun_NY >= StaticDayCount)  
        {  
            Sun_NY -= StaticDayCount;  
            index++;  
                   if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) )  
            {  
                flag = ~flag;  
                if (flag == 0)  
                    month++;  
            }  
            else  
                month++;  
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)  
                StaticDayCount=29;  
            else  
                StaticDayCount=30;  
        }  
        day = Sun_NY + 1;  
    }  
    else //阳历日在春节前  
    {  
        Spring_NY -= Sun_NY;  
        year--;  
        month = 12;  
        if ( ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)  
            index = 12;  
        else  
            index = 13;  
        flag = 0;  
        if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)  
            StaticDayCount = 29;  
        else  
            StaticDayCount = 30;  
        while (Spring_NY > StaticDayCount)  
        {  
            Spring_NY -= StaticDayCount;  
            index--;  
            if (flag == 0)  
                month--;  
            if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))  
                flag = ~flag;  
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)  
                StaticDayCount = 29;  
            else  
                StaticDayCount = 30;  
        }  
        day = StaticDayCount - Spring_NY + 1;  
    }  
    LunarCalendarDay |= day;  
    LunarCalendarDay |= (month << 6);  
    if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))  
        return 1;  
    else  
        return 0;  
	
} 


void lunar(int year,int month,int day)  
{  
    const char *ChDay[] = {"*","初一","初二","初三","初四","初五",  
                           "初六","初七","初八","初九","初十",  
                           "十一","十二","十三","十四","十五",  
                           "十六","十七","十八","十九","二十",  
                           "廿一","廿二","廿三","廿四","廿五",  
                           "廿六","廿七","廿八","廿九","三十"  
                          };  
    const char *ChMonth[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};  
    struct tm * Local;  
    long t;  
    //int year,month,day;  
    char str[13] = "";  
#if 0  
    t = time(NULL);  
    Local = localtime(&t);  
    year = Local->tm_year + 1900;  
    month = Local->tm_mon + 1;  
    day = Local-> tm_mday;	        
#endif  
    printf("\t\t\t\t        ||今天是：%d年%d月%d日\t农历: ",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        strcat(str,"闰");  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
    }  
    else  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    strcat(str,"月");  
	    strcat(str,ChDay[LunarCalendarDay & 0x3F]);
		strcat(str,"   ||");  
		puts(str);  
	    getchar(); 	 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************************************************************************/
void lunar_holiday(int year,int month,int day)  
{  
    const int Day[] = {0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,20,21,22,
	23,24,25,26,27,28,29,30,31};                     //月份天数数组 
    const int Month[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};  
    struct tm *Local;  
    long t;  
    //int year,month,day;  
    //char str[13] = "";  
#if 0  
    t = time(NULL);  
    Local = localtime(&t);  
    year = Local->tm_year + 1900;  
    month = Local->tm_mon + 1;  
    day = Local-> tm_mday;        
#endif  
    /*lunar_year=year;
    lunar_month=month;
    lunar_day=day;*/
	//printf("今天是：%d年%d月%d日\t农历：",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        //strcat(str,"闰");  
        //strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
       // lunar_month=Month[(LunarCalendarDay & 0x3C0) >> 6];  
    }  
    //else  
        //strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    //strcat(str,"月");  
	    //strcat(str,ChDay[LunarCalendarDay & 0x3F]);  
	    //puts(str);  
	    //getchar();
	    //lunar_month=(int)Month[(LunarCalendarDay & 0x3C0) >> 6];
	    //lunar_day=(int)Day[LunarCalendarDay & 0x3F];	
}


//                                        节假日查询部分 


////////////////////////////////////////////////////////////////////////////////////////////////////\
//公历查询部分
void calendar_holiday()  
{																	//公历假日 
	int year,month;
    do
    {
        printf("\t\t\t\t\t请输入您想要查询节日的年份和月份\n:");
        scanf("%d%d",&year,&month);
    }while((month<1||month>12)||(year<1||year>9999));
    printf("\t\t\t\t\t%d年%d月的节日有：\n\n",year,month);
    switch(month)
    {
        case 1:     printf("\t\t\t\t\t1月1日元旦(New Year's Day)\n");
                    printf("1月最后一个星期日国际麻风节\n");
                    printf("\n\n\n");
                    break;
		case 2:	    printf("\t\t\t\t\t2月2日  世界湿地日(World Wetlands Day)\n");
				    printf("\t\t\t\t\t2月14日 情人节(Valentine's Day)\n");
            		printf("\n\n\n");     
				    break;
        case 3:     printf("\t\t\t\t\t3月3日  全国爱耳日\n");
				    printf("\t\t\t\t\t3月5日  青年志愿者服务日\n");
				    printf("\t\t\t\t\t3月8日  国际妇女节(International Women' Day)\n");
				    printf("\t\t\t\t\t3月9日  保护母亲河日\n");
                    printf("\t\t\t\t\t3月12日 中国植树节(China Arbor Day)\n");
                    printf("\t\t\t\t\t3月14日 白色情人节(White Day)\n");
                    printf("\t\t\t\t\t3月14日 国际警察日(International Policemen' Day)\n");
                    printf("\t\t\t\t\t3月15日 世界消费者权益日(World Consumer Right Day)\n");
				    printf("\t\t\t\t\t3月21日 世界森林日(World Forest Day)\n");
                    printf("\t\t\t\t\t3月21日 世界睡眠日(World Sleep Day)\n");
                    printf("\t\t\t\t\t3月22日 世界水日(World Water Day)\n");
                    printf("\t\t\t\t\t3月23日 世界气象日(World Meteorological Day)\n");
					printf("\t\t\t\t\t3月24日 世界防治结核病日(World Tuberculosis Day)\n");
                    printf("\t\t\t\t\t3月最后一个完整周的星期一中小学生安全教育日\n");
					printf("\n\n\n");
					break;
		case 4:     printf("\t\t\t\t\t4月1日  愚人节(April Fools' Day)\n");
                    printf("\t\t\t\t\t4月5日  清明节(Tomb-sweeping Day)\n");
                    printf("\t\t\t\t\t4月7日  世界卫生日(World Health Day)\n");
                    printf("\t\t\t\t\t4月22日 世界地球日(World Earth Day)\n");
                    printf("\t\t\t\t\t4月26日 世界知识产权日(World Intellectual Property Day)\n");
					printf("\n\n\n");
					break;
	    case 5:     printf("\t\t\t\t\t5月1日  国际劳动节(International Labour Day)\n");
                    printf("\t\t\t\t\t5月3日  世界哮喘日(World Asthma Day)\n");
                    printf("\t\t\t\t\t5月4日  中国青年节(Chinese Youth Day)\n");
                    printf("\t\t\t\t\t5月8日  世界红十字日(World Red-Cross Day)\n");
                    printf("\t\t\t\t\t5月12日 国际护士节(International Nurse Day)\n");
                    printf("\t\t\t\t\t5月15日 国际家庭日(International Family Day)\n");
                    printf("\t\t\t\t\t5月17日 世界电信日(World Telecommunications Day)\n");
                    printf("\t\t\t\t\t5月20日 全国学生营养日\n");
                    printf("\t\t\t\t\t5月23日 国际牛奶日(International Milk Day)\n");
                    printf("\t\t\t\t\t5月31日 世界无烟日(World No-Smoking Day)\n");
                    printf("\t\t\t\t\t5月第二个星期日母亲节(Mother's Day)\n");
                    printf("\t\t\t\t\t5月第三个星期日全国助残日\n");
					printf("\n\n\n");
					break;
		case 6:     printf("\t\t\t\t\t6月1日  国际儿童节(International Children's Day)\n");
                    printf("\t\t\t\t\t6月5日  世界环境日(International Environment Day)\n");
                    printf("\t\t\t\t\t6月6日  全国爱眼日\n");
                    printf("\t\t\t\t\t6月17日 世界防治荒漠化和干旱日(World Day to combat desertification)\n");
                    printf("\t\t\t\t\t6月23日 国际奥林匹克日(International Olympic Day)\n");
                    printf("\t\t\t\t\t6月25日 全国土地日\n");
                    printf("\t\t\t\t\t6月26日 国际禁毒日(International Day Against Drug Abuse and Illicit Trafficking)\n");
                    printf("\t\t\t\t\t6月第三个星期日父亲节(Father's Day)\n");
					printf("\n\n\n");
					break;
			case 7: printf("\t\t\t\t\t7月1日  中国共产党诞生日(Anniversary of the Founding of the Chinese Communist Party)\n");
                    printf("\t\t\t\t\t7月1日  国际建筑日(International Architecture Day)\n");
                    printf("\t\t\t\t\t7月7日  中国人民抗日战争纪念日\n");
                    printf("\t\t\t\t\t7月11日 世界人口日(World Population Day)\n");
					printf("\n\n\n");
					break;
			case 8: printf("\t\t\t\t\t8月1日  中国人民解放军建军节(Army Day)\n");
                    printf("\t\t\t\t\t8月12日 国际青年节(International Youth Day)\n");
					printf("\n\n\n");
					break;
			case 9: printf("\t\t\t\t\t9月8日  国际扫盲日(International Anti-illiteracy Day)\n");
                    printf("\t\t\t\t\t9月10日 中国教师节(Teacher's Day)\n");
                    printf("\t\t\t\t\t9月16日 中国脑健康日\n");
                    printf("\t\t\t\t\t9月16日 国际臭氧层保护日(International Day for the Preservation of the Ozone Layer)\n");
                    printf("\t\t\t\t\t9月20日 全国爱牙日\n");
                    printf("\t\t\t\t\t9月21日 世界停火日(World Cease-fire Day)\n");
                    printf("\t\t\t\t\t9月27日 世界旅游日(World Tourism Day)\n");
                    printf("\t\t\t\t\t9月第三个星期二国际和平日(International Peace Day)\n");
                    printf("\t\t\t\t\t9月第三个星期六全国国防教育日\n");
                    printf("\t\t\t\t\t9月第四个星期日国际聋人节(International Day of the Deaf)\n");
					printf("\n\n\n");
					break;
		    case 10:printf("\t\t\t\t\t10月1日  中华人民共和国国庆节(National Day)\n");
                    printf("\t\t\t\t\t10月1日  国际音乐日(International Music Day)\n");
                    printf("\t\t\t\t\t10月1日  国际老年人日(International Day of Older Persons)\n");
                    printf("\t\t\t\t\t10月4日  世界动物日(World Animal Day)\n");
                    printf("\t\t\t\t\t10月5日  世界教师日(World Teachers' Day)（联合国教科文组织确立）\n");
                    printf("\t\t\t\t\t10月8日  全国高血压日\n");
                    printf("\t\t\t\t\t10月9日  世界邮政日(World Post Day)\n");
                    printf("\t\t\t\t\t10月10日 世界精神卫生日(World Mental Health Day)\n");
                    printf("\t\t\t\t\t10月14日 世界标准日(World Standards Day)\n");
                    printf("\t\t\t\t\t10月15日 国际盲人节(International Day of the Blind)\n");
                    printf("\t\t\t\t\t10月15日 世界农村妇女日(World Rural Women's Day)\n");
                    printf("\t\t\t\t\t10月16日 世界粮食日(World Food Day)\n");
                    printf("\t\t\t\t\t10月17日 国际消除贫困日(International Day for the Eradication of Poverty)\n");
                    printf("\t\t\t\t\t10月24日 联合国日(United Nations Day)\n");
                    printf("\t\t\t\t\t10月24日 世界发展新闻日(World Development Information Day)\n");
                    printf("\t\t\t\t\t10月28日 中国男性健康日\n");
                    printf("\t\t\t\t\t10月29日 国际生物多样性日(International Biodiversity Day)\n");
                    printf("\t\t\t\t\t10月31日 万圣节(Halloween)\n");
                    printf("\t\t\t\t\t10月的第一个星期一世界住房日(World Habitat Day)\n");
                    printf("\t\t\t\t\t10月的第二个星斯一加拿大感恩节(Thanksgiving Day)\n");
                    printf("\t\t\t\t\t10月第二个星期三国际减轻自然灾害日(International Day for Natural Disaster Reduction)\n");
                    printf("\t\t\t\t\t10月第二个星期四世界爱眼日(World Sight Day)\n");
					printf("\n\n\n");
					break;
			case 11:printf("\t\t\t\t\t11月8日  中国记者节\n");
                    printf("\t\t\t\t\t11月9日  消防宣传日\n");
                    printf("\t\t\t\t\t11月14日 世界糖尿病日(World Diabetes Day)\n");
                    printf("\t\t\t\t\t11月17日 国际大学生节\n");
                    printf("\t\t\t\t\t11月25日 国际消除对妇女的暴力日(International Day For the elimination of Violence against Women)\n");
                    printf("\t\t\t\t\t11月最后一个星期四美国感恩节(Thanksgiving Day)\n");
                    printf("\n\n\n");
					break;
			case 12:printf("\t\t\t\t\t12月1日  世界爱滋病日(World AIDS Day)\n");
                    printf("\t\t\t\t\t12月3日  世界残疾人日(World Disabled Day)\n");
                    printf("\t\t\t\t\t12月4日  全国法制宣传日\n");
                    printf("\t\t\t\t\t12月9日  世界足球日(World Football Day)\n");
                    printf("\t\t\t\t\t12月25日 圣诞节(Christmas Day)\n");
					printf("\t\t\t\t\t12月29日 国际生物多样性日(International Biological Diversity Day)\n");
					printf("\n\n\n");
					break;
    }
} 


//农历查询部分： 
/*函数说明：以公历输入月份 以农历节假日输出这个月有的节日；                                       */
void select_lunar_holiday(int month,int day)
{
	switch(month)
	{
		case 1:
		{
			if(day==1)
				printf("\t\t\t\t\t春节\n"); 
				if(day==2)
				printf("\t\t\t\t\t春节\n");
				if(day==3)
				printf("\t\t\t\t\t春节\n");
			if(day==15)
				printf("\t\t\t\t\t元宵节\n");
		
		//		printf("\n\n\n");
			break; 
		} 
		case 2:
		{
			if(day==2)
			{
				printf("\t\t\t\t\t春龙节（龙抬头）\n"); 
			}
		//	printf("\n\n\n");	
			break;
		}
		case 4:
		{
			if(day==3)
			{
				printf("\t\t\t\t\t寒食节\n"); 
			}
			if(day==5||day==6)
			{
				printf("\t\t\t\t\t清明节\n");
			}
		//	printf("\n\n\n");	
			break;
		}	
		case 5:
		{
			if(day==5)
			{
				printf("\t\t\t\t\t端午节\n"); 
			}	
		//	//printf("\n\n\n");
			break;
		}
		case 7:
		{
			if(day==7)
			{
				printf("\t\t\t\t\t七夕\n");
			}
			if(day==15)
			{
				printf("\t\t\t\t\t中元节\n");
			}
		//	printf("\n\n\n");
			break;	
		} 
		case 8:
		{
			if(day==15)
			{
				printf("\t\t\t\t\t中秋节\n");
			}	
		//	printf("\n\n\n");
			break;
		} 
		case 9:
		{
			if(day==9)
			{
				printf("\t\t\t\t\t重阳节\n");
			}	
		//	printf("\n\n\n");
			break;
		} 
		case 12:
		{
			if(day==8)
			{
				printf("\t\t\t\t\t腊八节\n");
			}
			if(day==23)
			{
				printf("\t\t\t\t\t小年\n");
			}
			if(day==30)
			{
				printf("\t\t\t\t\t除夕\n");
			}
		//	printf("\n\n\n");	
			break;
			
		}
		/*case 3 :
		printf("\t\t\t\t\t本月没有传统节日！！！！\n");break;  
		case 6 :
		printf("\t\t\t\t\t本月没有传统节日！！！！\t");break;    
		case 10 :
		printf("\t\t\t\t\t本月没有传统节日！！！！\t");break;    
		case 11 :
		printf("\t\t\t\t\t本月没有传统节日！！！！\t");break;
	 */
	 
	}
	//getch();
}

void lunar_holiday_print(int year,int month) 
{
	int i,year_holiday,month_holiday,day_holiday;
	int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	days[2]=28+LEAP(year);
    for(i=1;i<days[month];i++)
    {
    	//lunar_holiday(year,month,i);           //输入一个公历日期查询所对应的农历
    	//month_holiday=lunar_month;
    	//day_holiday=lunar_day;
    	select_lunar_holiday(month,i);
	}
} 

void calendar_to_lunar_init(int year,int month,int day)  
{  
    const char *ChDay[] = {"*","初一","初二","初三","初四","初五",  
                           "初六","初七","初八","初九","初十",  
                           "十一","十二","十三","十四","十五",  
                           "十六","十七","十八","十九","二十",  
                           "廿一","廿二","廿三","廿四","廿五",  
                           "廿六","廿七","廿八","廿九","三十"  
                          };  
    const char *ChMonth[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};  
    struct tm * Local;  
    long t;  
    //int year,month,day;  
    char str[13] = "";  
#if 0  
    t = time(NULL);  
    Local = localtime(&t);  
    year = Local->tm_year + 1900;  
    month = Local->tm_mon + 1;  
    day = Local-> tm_mday;        
#endif  
    printf("\t\t\t\t        公历：%d年%d月%d日\t农历: ",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        strcat(str,"闰");  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
    }  
    else  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    strcat(str,"月");  
	    strcat(str,ChDay[LunarCalendarDay & 0x3F]);
		//strcat(str,"   ||");  
		puts(str);  
	    getchar(); 	 
}
/*********************************************公历转农历部分********************************************/
void calendar_to_lunar() 
{
	int year,month,day,select;
	int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	do
	{
		printf("\t\t\t\t\t公历转农历：\n");
	    printf("\t\t\t\t\t请输入日期：\n");
		scanf("%d%d%d",&year,&month,&day);
		days[2]=28+LEAP(year);
		printf("\t\t\t\t\t下面是转换结果：\n");
		calendar_to_lunar_init(year,month,day);
		printf("\n");
		printf("\t\t\t\t\t是否继续输入转换 \n");
		printf("\t\t\t\t\t如果是请输入 1\n");
		scanf("%d",&select);
		getch();
		system("cls");		 
    }while(select==1);
}

/**********************************************year_logo_print*******************************************/
//函数说明：打印年份

void draw_yearlogo(int year)
{
    int i,j,k;
    int a,b,c,d;
    const char Logo[12][7][10]=
						 {
						 {"* * * *","*     *","*     *","*     *","* * * *"},//0
                         {"  ***  "," ** *  ","  * *  ","  * *  "," ***** "},//1
                         {" * * * ","     * "," * * * "," *     "," * * * "},//2
                         {" * * * ","     * "," * * * ","     * "," * * * "},//3
                         {" *   * "," *   * "," * * * ","     * ","     * "},//4
                         {" * * * "," *     "," * * * ","     * "," * * * "},//5
                         {" * * * "," *     "," * * * "," *   * "," * * * "},//6
                         {" * * * ","     * ","     * ","     * ","     * "},//7
                         {" * * * "," *   * "," * * * "," *   * "," * * * "},//8
                         {" * * * "," *   * "," * * * ","     * "," * * * "},//9
                         };
    a=year/1000;
    b=year/100%10;
    c=year/10%10;
    d=year%10;
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[a][0][j]);
    }
	printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[b][0][j]);
    }
	printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[c][0][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[d][0][j]);
    }
    printf("\n");
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[a][1][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[b][1][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[c][1][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[d][1][j]);
    }
    printf("\n");
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[a][2][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[b][2][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[c][2][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[d][2][j]);
    }
    printf("\n");
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[a][3][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[b][3][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[c][3][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[d][3][j]);
    }
    printf("\n");
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[a][4][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[b][4][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[c][4][j]);
    }
    printf("\t    ");
    for(j=0;j<7;j++)
    {
        printf("%c",Logo[d][4][j]);
    }
    printf("\n");
}
/**********************************************year_logo_write*******************************************/
//函数说明：打印年份

void write_yearlogo(int year)
{
    int i,j,k;
    int a,b,c,d;
    //char ch;
    const char Logo[12][7][10]=
						 {
						 {"* * * *","*     *","*     *","*     *","* * * *"},//0
                         {"  ***  "," ** *  ","  * *  ","  * *  "," ***** "},//1
                         {" * * * ","     * "," * * * "," *     "," * * * "},//2
                         {" * * * ","     * "," * * * ","     * "," * * * "},//3
                         {" *   * "," *   * "," * * * ","     * ","     * "},//4
                         {" * * * "," *     "," * * * ","     * "," * * * "},//5
                         {" * * * "," *     "," * * * "," *   * "," * * * "},//6
                         {" * * * ","     * ","     * ","     * ","     * "},//7
                         {" * * * "," *   * "," * * * "," *   * "," * * * "},//8
                         {" * * * "," *   * "," * * * ","     * "," * * * "},//9
                         };
    a=year/1000;
    b=year/100%10;
    c=year/10%10;
    d=year%10;
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
    	//ch=Logo[a][0][j];
        fputc(Logo[a][0][j],fp);
    }
	fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[b][0][j],fp);
    }
	fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[c][0][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[d][0][j],fp);
    }
    fputs("\n",fp);
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[a][1][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[b][1][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[c][1][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[d][1][j],fp);
    }
    fputs("\n",fp);
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[a][2][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[b][2][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[c][2][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[d][2][j],fp);
    }
    fputs("\n",fp);
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[a][3][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[b][3][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[c][3][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[d][3][j],fp);
    }
    fputs("\n",fp);
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[a][4][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[b][4][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[c][4][j],fp);
    }
    fprintf(fp,"%s","\t    ");
    for(j=0;j<7;j++)
    {
        fputc(Logo[d][4][j],fp);
    }
    fputs("\n",fp);
}

 
 
/***************************************************************************************************/ 
////////////////////////////////////////////////main/////////////////////////////////////////////////
/***************************************************************************************************/
int main( )
{   
	int select;
    do
    { 
        print_hello();
		do
		{
			scanf("%d",&select);
	    }while(select<0||select>6);
		switch(select)
	    {
	    	case 1:
	    		{
	    			int year,month,day;
	    			Get_time();
	    			year=year_time,month=month_time,day=day_time;
	    			LunarCalendar(year,month,day);
	    			lunar(year,month,day);
	    			printf("\t\t\t\t        ||=======================================||\n\n\n");
	    			getch();
					printf("\n\t\t\t\t\t这是今年的年历\n");
	    			
					file_init(); 
					draw_yearlogo(year);
					write_yearlogo(year);  
				    print_halfyear(year,1);                              //上半年
					file_write_halfyear(year,1);
					//getch();
				    PF("\n");
				    print_halfyear(year,7);                              //下半年
				    file_write_halfyear(year,7);
					fclose(fp);   
				    getch();
				    getch();
				    PF("\n");
				    system("cls");
				    break;
				}
			case 2:
			    
			    	search_year();
			    	system("cls");
			    	break;
					
			case 3:
			    
					search_day();
					getch(); 
					system("cls");
					break;	
				
			case 4:	
			{
				int select_lunar;
				printf("\n\n\t\t\t\t\t查询公历节日请输入 1；\n"); 
				printf("\t\t\t\t\t查询农历节日请输入 2；\n");
				scanf("%d",&select_lunar); 
				switch(select_lunar)
				{	
					case 1:
					{
						calendar_holiday();	
						getch();
						break;	
					}
					case 2:
					{
						int year,month;
						printf("\t\t\t\t\t请输入年份及月份：");
						scanf("%d %d",&year,&month);
					    lunar_holiday_print(year,month);
					    getch();
						break;	
					}
				} 
			getch();
			system("cls");
			break;
			}
			case 5:				
				calendar_to_lunar();
				getch();
				system("cls");
				break;
		}
	}while(select!=6);
		
	return 0;
}

/****************************************************end**************************************************************/

 
