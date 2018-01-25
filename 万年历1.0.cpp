/**************************************************************************************************************
                     ������ƣ�������
                     �����ܣ�
					 			1.  ��ѯ��ǰ���ڣ���ϵͳʱ���������������Ƶ����ʾ 
					 			    ����ӡ���������������������д���ļ� 
								2.  ָ����ݲ�ѯ���Ӽ��̶���һ����ݣ�������Ƶ�ϴ�ӡ
								    ������������ṩѡ���Ƿ�Ѹ����������д���ļ�	  
								3.  ��ѯ�ƶ���ݵ�1��1�������ڼ����Ӽ��̶�����ݡ�
								    ����ʾƵ�Ͻ�����ʾ
								4.  ��ѯ���գ��ṩѡ���ѡ�������պ�ũ������
								5.	����תũ�����Ӽ����϶�ȡһ�����ڣ�����ת��
								    ����ʾƵ�Ͻ��з���
						
						ʹ�����ԣ�C
						��̻�����DEV 
						С���Ա������� �ճ��� ����
						ʱ�䣺2017��3��6�ŵ�9�� 
										 
*************************************************************************************************************/
#include<stdio.h>                                       //����stdioͷ�ļ�
#include<conio.h>                                       //����conioͷ�ļ�
#include<stdlib.h>                                      //����stdlibͷ�ļ�
#include<string.h>										//����stringͷ�ļ�	
#include<time.h>                                        //����timeͷ�ļ� 
#define PF printf                                       //�궨�����printf 
#define LEAP(y) !(y%(y%100?4:400))                      //�궨���ж����� 
#define EP PF("%s%s%.10s%s%s*",s,k,k,k,k)               //�궨����ʾ����
FILE *fp;
int year_time,month_time,day_time;                      //����ȫ�ֱ��� 
//int lunar_year,lunar_month,lunar_day;
//void write_date(int year,int month,char array[3*7*6]);
/**********************************��������*****************************************************************/
int The_week(int year,int month,int day);               //�ж�ĳ�������ڼ� 
void print_month(int year,int month,char array[3*7*6]); //�����ӡĳ���·� 
void print_halfyear(int year,int month);                //�����ӡ��������� 
void Get_time();                                        //��ȡϵͳʱ�� 
void print_hello();                                     //��ӭ���棬ϵͳ��ʼ���� 
void search_year();                                     //������ݺ��� 
void search_day();                                      //�����캯�� 
void file_init();                                       //�ļ�ָ���ʼ������ 
void file_write_month(int year,int month,char array[3*7*6]);
 														//���ļ���д������  			
void file_write_halfyear(int year,int month);           //���ļ���д���������� 
int LunarCalendar(int year,int month,int day);          //ũ��������ʼ�� 
void lunar(int year,int month,int day);                 //ũ������ 
void lunar_holiday(int year,int month,int day);         //ũ�����պ��� 
void calendar_holiday();                                //�������պ��� 
void select_lunar_holiday(int month,int day);           //ѡ��ũ�����պ��� 
void lunar_holiday_print(int year,int month);           //��ӡũ�����պ��� 
void draw_yearlogo(int year);                           //�����ӡ���logo 
void write_yearlogo(int year);                          //���ļ���д�����logo
void calendar_to_lunar_init(int year,int month,int day);//����תũ��������ʼ��   
void calendar_to_lunar();                               //����תũ������ 
 


/**********************************the week***************************************/
//�������ܣ�����������������ڼ�

int The_week(int year,int month,int day)                
{
    int i,y1,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    days[2]=28+LEAP(year);
    for(i=1;i<month;i++)
		day+=days[i];
    y1=year-1;
    day+=y1+y1/4-y1/100+y1/400;                                      //�����㷨
    return day%7;
}
/*********************************************************************************/

/***********************************print_month***********************************/
//�������ܣ���ָ����ݵ�ָ���·ݽ��д�ӡ
void print_month(int year,int month,char array[3*7*6])               //��ʾ���鲿��
{
    char *pa;
    int i,week,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};       //�·�����
    days[2]=28+LEAP(year);									         //���������µ�����
    week = The_week(year,month,1);                                   //���ĳ��ĳ��1�ŵ������ڼ�    
    week = week?week-1:week+6;                                       //�õ�����
    pa = array+3*week;                                               //ȷ��ָ���ʼ��1�ţ�λ��
    for(i=1;i<=3*7*6;i++)
		array[i-1]=' ';                                              
    for(i=1;i<=days[month];i++,pa+=3)                                //1����ǰ�������ÿո����֮��û���һ�����ڣ�ָ���3��ָ����һ����ʾλ��
		sprintf(pa,"%3d",i);                                         //��ӡ��ǰָ����ָ������ 
    *pa=' ';										                 
}
/***********************************************************************************/


void print_halfyear(int year,int month)                              //��������������
{
    int i,j;
    char ary[6][7*3],bry[6][7*3],cry[6][7*3];                        //�����������飨�·����飩��������������·�
    char const *k="                    ",*s="\n    *";               //��ʾ������ʾ��Ϣ
    char const *xs="********************************";               //��ʾ������ʾ��Ϣ
    PF("%s%s %04d %s*",s,xs,year,xs);                                //��ʾ������ʾ��Ϣ
    for(i=1;i<=2;i++,month+=3)
    {
       EP;	
	   char const month_name[][6]={{},{"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},
	   								{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"}};													     		   //��ʾ������ʾ��Ϣ
       PF("%s%.10s%s%.20s%s%.20s%s%.11s*",s,k,month_name[month],k,month_name[month+1],k,month_name[month+2],k);
																			   //monthС��10ʱ��month�¿�ʼ��ʾ��������µ�����			
       EP;																       //��ʾ������ʾ��Ϣ
       PF("%s  MO TU WE TH FR SA SU   MO TU WE TH FR SA SU   MO TU WE TH FR SA SU  *",s);
																			   //���ڸ�ʽ���
       print_month(year,month ,ary[0]);									       //����·�	
       print_month(year,month+1,bry[0]);								       //����·�
       print_month(year,month+2,cry[0]);									   //����·�	
       for(j=0;j<6;j++)                                                        
       {
          PF("%s %.21s  %.21s  %.21s  *",s,ary[j],bry[j],cry[j]);
       }
	   EP;
    }
    PF("%s%s******%s*",s,xs,xs);
}

/*******************************************Get_time***********************************************/
void Get_time()                                                      //��ȡϵͳʱ�� 
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
																	  //��ʽ����ӡ 
    printf("\t\t\t\t        ||ϵͳ��ǰʱ��:%d-%d-%d                  ||\n",sysyear,sysmonth,sysday);
    //printf("���ǽ����������");   
	 year_time=sysyear;month_time=sysmonth;day_time=sysday;    
}
/***************************************************************************************************/
void print_hello()													  //��ӭ����				
{
	printf("\n\n\n"); 
	printf("			  ##      ##    #########     ##            ##           ##########   \n");
	printf("			  ##      ##    ##            ##            ##           ##      ##   \n");
	printf("			  ##########    #######       ##            ##           ##      ##   \n");
	printf("			  ##      ##    ##            ##            ##           ##      ##   \n");
	printf("			  ##      ##    ##########    ##########    ##########   ##########   \n\n\n"); 
	/***************************�˵�����***************************************/ 
	printf("\t\t\t\t\t__________________________________________\n");
	printf("\t\t\t\t\t##########################################\n"); 
	printf("\t\t\t\t\t-����������������������������������������-\n\n");
    printf("\t\t\t\t\t|*|��ã���ӭ����������С����          |*|\n\a");
    printf("\t\t\t\t\t|*|����ˣ������ �ճ��� ����          |*|\n\n");   
    printf("\t\t\t\t\t|*|��ѡ���ܣ�                        |*|\n");
	printf("\t\t\t\t\t|*|��ѯ��ǰ���������� 1��              |*|\n");
	printf("\t\t\t\t\t|*|��ѯָ�������������� 2��            |*|\n");
	printf("\t\t\t\t\t|*|��ѯָ�����Ԫ�����ܼ������� 3��    |*|\n");
	printf("\t\t\t\t\t|*|��ѯ���������� 4��                  |*|\n");
	printf("\t\t\t\t\t|*|����תũ�������� 5;                 |*|\n"); 
   	printf("\t\t\t\t\t|*|�˳����������� 6��                  |*|\n");
	printf("\t\t\t\t\t__________________________________________\n\n");
	
}
/*****************************************************************************************************/

void search_year()
{
	int year;
	int y;
	
    printf("\t\t\t\t\t�Ƿ��ӡ�����������\n");                //ѡ���Ƿ������ļ� 
    printf("\t\t\t\t\t�����������1;�������������\n\n\n");
    scanf("%d",&y);
   	if(y==1)
	{
		printf("\t\t\t\t\t���ڳ�������Ŀ¼����calendar�ļ�\n");
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
	   													 //��ʾ������� 
       scanf("%d",&year);                                //�������
    }while(year<=0||year>9999);
    
 
	draw_yearlogo(year);
	if(y==1)
		write_yearlogo(year);                            //д�����logo 
    print_halfyear(year,1);                              //�ϰ���
	if(y==1)
		file_write_halfyear(year,1);
	getch();
    PF("\n");
    print_halfyear(year,7);                              //�°���
    
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
	   													 //��ʾ������� 
       scanf("%d",&year);                                //�������
    }while(year<=0||year>9999);
    i=The_week(year,1,1);
    
    switch(i)                                            //Ӣ��������� 
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
    printf("\t\t\t\t\t�����1��1����%s��",week_day);
}
/********************************************file**************************************************/
void file_init()                                         //�ļ�ָ���ʼ�� 
{
	fp = fopen("date.txt","w+");                         //���½���ʽ����һ����д���ļ��ļ�����date 
	char ch;
	if(fp==0)
		{
			printf("file error\n");
			exit(1);	
		} 
} 
/****************************************************************************************************/
void file_write_month(int year,int month,char array[3*7*6])
{ 																			//���ļ���д��ĳ�µ�����	
	int i,week,longth,days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};       //�·�����
    days[2]=28+LEAP(year);									                //���������µ�����
    week = The_week(year,month,1);                                          //���ĳ��ĳ��1�ŵ������ڼ�    
    week = week?week-1:week+6;                                              //�õ�����
    //fp = array[0]+3*week;
    array = array + 3*week;
    //strcat(array,fp);
	//longth = array[0]+(week);    
	fseek(fp,longth,1);		                                                //ָ��û����λ�����ļ���ӡʱ����bug������  
	for(i=1;i<3*7*6;i++)
		array[i-1]=' ';
	for(i=1;i<days[month];i++,fseek(fp,0,1))
		fprintf(fp,"%3d",i);
	fprintf(fp,"%s"," ");			
}

void file_write_halfyear(int year,int month)
{																		    //���ļ���д��ĳ���������� 
	int i,j;
	char const month_name[][5]={{},{"Jan"},{"Feb"},{"Mar"},{"Apr"},{"May"},{"Jun"},
								{"Jul"},{"Aug"},{"Sep"},{"Oct"},{"Nov"},{"Dec"}};
																		    //�����·������� 
	char ary[6][7*3],bry[6][7*3],cry[6][7*3];
	char const *k="                    ",*s="\n    *";                      //��ʾ������ʾ��Ϣ
    //char const *xs="********************************";                    //��ʾ������ʾ��Ϣ
	char const *xs="________________________________";						//��ʽ����ʾ				   
    fprintf(fp,"%s%s %04d %s*",s,xs,year,xs);                               //��ʾ������ʾ��Ϣ
    for(i=1;i<=2;i++,month+=3)
    {
       //EP;														     		   //��ʾ������ʾ��Ϣ
       fprintf(fp,"%s%.10s%s%.20s%s%.20s%s%.11s*",s,k,month_name[month],k,month_name[month+1],k,month_name[month+2],k);
																			   //monthС��10ʱ��month�¿�ʼ��ʾ��������µ�����			
       //EP;																       //��ʾ������ʾ��Ϣ
       fprintf(fp,"%s  MO TU WE TH FR SA SU   MO TU WE TH FR SA SU   MO TU WE TH FR SA SU  *",s);		
	   																			   //���ڸ�ʽ���
       //file_write_month(year,month  ,ary[0]);									   //����·�	
       //file_write_month(year,month+1,bry[0]);								       //����·�
       //file_write_month(year,month+2,cry[0]);									   //����·�	
       for(j=0;j<6;j++)                                                        
       {
          fprintf(fp,"%s %.21s  %.21s  %.21s  *",s,ary[j],bry[j],cry[j]);		   //��ʽ����ʾ
       }
	   //EP;
    }
    //PF("%s%s******%s*",s,xs,xs);
}

/**************************************************************************************************/
/*                                         ũ������												  */
//�����ִ�����Դ������
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
    //Spring_NY ��¼�����뵱��Ԫ����������  
    //Sun_NY ��¼�������뵱��Ԫ����������  
    if ( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)  
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;  
    else  
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;  
    Sun_NY = MonthAdd[month-1] + day - 1;  
    if ( (!(year % 4)) && (month > 2))  
        Sun_NY++;  
    //StaticDayCount��¼��С�µ����� 29 ��30  
    //index ��¼���ĸ��¿�ʼ�����㡣  
    //flag �����������µ����⴦��  
    //�ж��������ڴ���ǰ���Ǵ��ں�  
    if (Sun_NY >= Spring_NY)//�������ڴ��ں󣨺��������죩  
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
    else //�������ڴ���ǰ  
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
    const char *ChDay[] = {"*","��һ","����","����","����","����",  
                           "����","����","����","����","��ʮ",  
                           "ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",  
                           "ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",  
                           "إһ","إ��","إ��","إ��","إ��",  
                           "إ��","إ��","إ��","إ��","��ʮ"  
                          };  
    const char *ChMonth[] = {"*","��","��","��","��","��","��","��","��","��","ʮ","ʮһ","��"};  
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
    printf("\t\t\t\t        ||�����ǣ�%d��%d��%d��\tũ��: ",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        strcat(str,"��");  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
    }  
    else  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    strcat(str,"��");  
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
	23,24,25,26,27,28,29,30,31};                     //�·��������� 
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
	//printf("�����ǣ�%d��%d��%d��\tũ����",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        //strcat(str,"��");  
        //strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);
       // lunar_month=Month[(LunarCalendarDay & 0x3C0) >> 6];  
    }  
    //else  
        //strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    //strcat(str,"��");  
	    //strcat(str,ChDay[LunarCalendarDay & 0x3F]);  
	    //puts(str);  
	    //getchar();
	    //lunar_month=(int)Month[(LunarCalendarDay & 0x3C0) >> 6];
	    //lunar_day=(int)Day[LunarCalendarDay & 0x3F];	
}


//                                        �ڼ��ղ�ѯ���� 


////////////////////////////////////////////////////////////////////////////////////////////////////\
//������ѯ����
void calendar_holiday()  
{																	//�������� 
	int year,month;
    do
    {
        printf("\t\t\t\t\t����������Ҫ��ѯ���յ���ݺ��·�\n:");
        scanf("%d%d",&year,&month);
    }while((month<1||month>12)||(year<1||year>9999));
    printf("\t\t\t\t\t%d��%d�µĽ����У�\n\n",year,month);
    switch(month)
    {
        case 1:     printf("\t\t\t\t\t1��1��Ԫ��(New Year's Day)\n");
                    printf("1�����һ�������չ�������\n");
                    printf("\n\n\n");
                    break;
		case 2:	    printf("\t\t\t\t\t2��2��  ����ʪ����(World Wetlands Day)\n");
				    printf("\t\t\t\t\t2��14�� ���˽�(Valentine's Day)\n");
            		printf("\n\n\n");     
				    break;
        case 3:     printf("\t\t\t\t\t3��3��  ȫ��������\n");
				    printf("\t\t\t\t\t3��5��  ����־Ը�߷�����\n");
				    printf("\t\t\t\t\t3��8��  ���ʸ�Ů��(International Women' Day)\n");
				    printf("\t\t\t\t\t3��9��  ����ĸ�׺���\n");
                    printf("\t\t\t\t\t3��12�� �й�ֲ����(China Arbor Day)\n");
                    printf("\t\t\t\t\t3��14�� ��ɫ���˽�(White Day)\n");
                    printf("\t\t\t\t\t3��14�� ���ʾ�����(International Policemen' Day)\n");
                    printf("\t\t\t\t\t3��15�� ����������Ȩ����(World Consumer Right Day)\n");
				    printf("\t\t\t\t\t3��21�� ����ɭ����(World Forest Day)\n");
                    printf("\t\t\t\t\t3��21�� ����˯����(World Sleep Day)\n");
                    printf("\t\t\t\t\t3��22�� ����ˮ��(World Water Day)\n");
                    printf("\t\t\t\t\t3��23�� ����������(World Meteorological Day)\n");
					printf("\t\t\t\t\t3��24�� ������ν�˲���(World Tuberculosis Day)\n");
                    printf("\t\t\t\t\t3�����һ�������ܵ�����һ��Сѧ����ȫ������\n");
					printf("\n\n\n");
					break;
		case 4:     printf("\t\t\t\t\t4��1��  ���˽�(April Fools' Day)\n");
                    printf("\t\t\t\t\t4��5��  ������(Tomb-sweeping Day)\n");
                    printf("\t\t\t\t\t4��7��  ����������(World Health Day)\n");
                    printf("\t\t\t\t\t4��22�� ���������(World Earth Day)\n");
                    printf("\t\t\t\t\t4��26�� ����֪ʶ��Ȩ��(World Intellectual Property Day)\n");
					printf("\n\n\n");
					break;
	    case 5:     printf("\t\t\t\t\t5��1��  �����Ͷ���(International Labour Day)\n");
                    printf("\t\t\t\t\t5��3��  ����������(World Asthma Day)\n");
                    printf("\t\t\t\t\t5��4��  �й������(Chinese Youth Day)\n");
                    printf("\t\t\t\t\t5��8��  �����ʮ����(World Red-Cross Day)\n");
                    printf("\t\t\t\t\t5��12�� ���ʻ�ʿ��(International Nurse Day)\n");
                    printf("\t\t\t\t\t5��15�� ���ʼ�ͥ��(International Family Day)\n");
                    printf("\t\t\t\t\t5��17�� ���������(World Telecommunications Day)\n");
                    printf("\t\t\t\t\t5��20�� ȫ��ѧ��Ӫ����\n");
                    printf("\t\t\t\t\t5��23�� ����ţ����(International Milk Day)\n");
                    printf("\t\t\t\t\t5��31�� ����������(World No-Smoking Day)\n");
                    printf("\t\t\t\t\t5�µڶ���������ĸ�׽�(Mother's Day)\n");
                    printf("\t\t\t\t\t5�µ�����������ȫ��������\n");
					printf("\n\n\n");
					break;
		case 6:     printf("\t\t\t\t\t6��1��  ���ʶ�ͯ��(International Children's Day)\n");
                    printf("\t\t\t\t\t6��5��  ���绷����(International Environment Day)\n");
                    printf("\t\t\t\t\t6��6��  ȫ��������\n");
                    printf("\t\t\t\t\t6��17�� ������λ�Į���͸ɺ���(World Day to combat desertification)\n");
                    printf("\t\t\t\t\t6��23�� ���ʰ���ƥ����(International Olympic Day)\n");
                    printf("\t\t\t\t\t6��25�� ȫ��������\n");
                    printf("\t\t\t\t\t6��26�� ���ʽ�����(International Day Against Drug Abuse and Illicit Trafficking)\n");
                    printf("\t\t\t\t\t6�µ����������ո��׽�(Father's Day)\n");
					printf("\n\n\n");
					break;
			case 7: printf("\t\t\t\t\t7��1��  �й�������������(Anniversary of the Founding of the Chinese Communist Party)\n");
                    printf("\t\t\t\t\t7��1��  ���ʽ�����(International Architecture Day)\n");
                    printf("\t\t\t\t\t7��7��  �й�������ս��������\n");
                    printf("\t\t\t\t\t7��11�� �����˿���(World Population Day)\n");
					printf("\n\n\n");
					break;
			case 8: printf("\t\t\t\t\t8��1��  �й������ž�������(Army Day)\n");
                    printf("\t\t\t\t\t8��12�� ���������(International Youth Day)\n");
					printf("\n\n\n");
					break;
			case 9: printf("\t\t\t\t\t9��8��  ����ɨä��(International Anti-illiteracy Day)\n");
                    printf("\t\t\t\t\t9��10�� �й���ʦ��(Teacher's Day)\n");
                    printf("\t\t\t\t\t9��16�� �й��Խ�����\n");
                    printf("\t\t\t\t\t9��16�� ���ʳ����㱣����(International Day for the Preservation of the Ozone Layer)\n");
                    printf("\t\t\t\t\t9��20�� ȫ��������\n");
                    printf("\t\t\t\t\t9��21�� ����ͣ����(World Cease-fire Day)\n");
                    printf("\t\t\t\t\t9��27�� ����������(World Tourism Day)\n");
                    printf("\t\t\t\t\t9�µ��������ڶ����ʺ�ƽ��(International Peace Day)\n");
                    printf("\t\t\t\t\t9�µ�����������ȫ������������\n");
                    printf("\t\t\t\t\t9�µ��ĸ������չ������˽�(International Day of the Deaf)\n");
					printf("\n\n\n");
					break;
		    case 10:printf("\t\t\t\t\t10��1��  �л����񹲺͹������(National Day)\n");
                    printf("\t\t\t\t\t10��1��  ����������(International Music Day)\n");
                    printf("\t\t\t\t\t10��1��  ������������(International Day of Older Persons)\n");
                    printf("\t\t\t\t\t10��4��  ���綯����(World Animal Day)\n");
                    printf("\t\t\t\t\t10��5��  �����ʦ��(World Teachers' Day)�����Ϲ��̿�����֯ȷ����\n");
                    printf("\t\t\t\t\t10��8��  ȫ����Ѫѹ��\n");
                    printf("\t\t\t\t\t10��9��  ����������(World Post Day)\n");
                    printf("\t\t\t\t\t10��10�� ���羫��������(World Mental Health Day)\n");
                    printf("\t\t\t\t\t10��14�� �����׼��(World Standards Day)\n");
                    printf("\t\t\t\t\t10��15�� ����ä�˽�(International Day of the Blind)\n");
                    printf("\t\t\t\t\t10��15�� ����ũ�帾Ů��(World Rural Women's Day)\n");
                    printf("\t\t\t\t\t10��16�� ������ʳ��(World Food Day)\n");
                    printf("\t\t\t\t\t10��17�� ��������ƶ����(International Day for the Eradication of Poverty)\n");
                    printf("\t\t\t\t\t10��24�� ���Ϲ���(United Nations Day)\n");
                    printf("\t\t\t\t\t10��24�� ���緢չ������(World Development Information Day)\n");
                    printf("\t\t\t\t\t10��28�� �й����Խ�����\n");
                    printf("\t\t\t\t\t10��29�� ���������������(International Biodiversity Day)\n");
                    printf("\t\t\t\t\t10��31�� ��ʥ��(Halloween)\n");
                    printf("\t\t\t\t\t10�µĵ�һ������һ����ס����(World Habitat Day)\n");
                    printf("\t\t\t\t\t10�µĵڶ�����˹һ���ô�ж���(Thanksgiving Day)\n");
                    printf("\t\t\t\t\t10�µڶ������������ʼ�����Ȼ�ֺ���(International Day for Natural Disaster Reduction)\n");
                    printf("\t\t\t\t\t10�µڶ������������簮����(World Sight Day)\n");
					printf("\n\n\n");
					break;
			case 11:printf("\t\t\t\t\t11��8��  �й����߽�\n");
                    printf("\t\t\t\t\t11��9��  ����������\n");
                    printf("\t\t\t\t\t11��14�� ����������(World Diabetes Day)\n");
                    printf("\t\t\t\t\t11��17�� ���ʴ�ѧ����\n");
                    printf("\t\t\t\t\t11��25�� ���������Ը�Ů�ı�����(International Day For the elimination of Violence against Women)\n");
                    printf("\t\t\t\t\t11�����һ�������������ж���(Thanksgiving Day)\n");
                    printf("\n\n\n");
					break;
			case 12:printf("\t\t\t\t\t12��1��  ���簮�̲���(World AIDS Day)\n");
                    printf("\t\t\t\t\t12��3��  ����м�����(World Disabled Day)\n");
                    printf("\t\t\t\t\t12��4��  ȫ������������\n");
                    printf("\t\t\t\t\t12��9��  ����������(World Football Day)\n");
                    printf("\t\t\t\t\t12��25�� ʥ����(Christmas Day)\n");
					printf("\t\t\t\t\t12��29�� ���������������(International Biological Diversity Day)\n");
					printf("\n\n\n");
					break;
    }
} 


//ũ����ѯ���֣� 
/*����˵�����Թ��������·� ��ũ���ڼ������������еĽ��գ�                                       */
void select_lunar_holiday(int month,int day)
{
	switch(month)
	{
		case 1:
		{
			if(day==1)
				printf("\t\t\t\t\t����\n"); 
				if(day==2)
				printf("\t\t\t\t\t����\n");
				if(day==3)
				printf("\t\t\t\t\t����\n");
			if(day==15)
				printf("\t\t\t\t\tԪ����\n");
		
		//		printf("\n\n\n");
			break; 
		} 
		case 2:
		{
			if(day==2)
			{
				printf("\t\t\t\t\t�����ڣ���̧ͷ��\n"); 
			}
		//	printf("\n\n\n");	
			break;
		}
		case 4:
		{
			if(day==3)
			{
				printf("\t\t\t\t\t��ʳ��\n"); 
			}
			if(day==5||day==6)
			{
				printf("\t\t\t\t\t������\n");
			}
		//	printf("\n\n\n");	
			break;
		}	
		case 5:
		{
			if(day==5)
			{
				printf("\t\t\t\t\t�����\n"); 
			}	
		//	//printf("\n\n\n");
			break;
		}
		case 7:
		{
			if(day==7)
			{
				printf("\t\t\t\t\t��Ϧ\n");
			}
			if(day==15)
			{
				printf("\t\t\t\t\t��Ԫ��\n");
			}
		//	printf("\n\n\n");
			break;	
		} 
		case 8:
		{
			if(day==15)
			{
				printf("\t\t\t\t\t�����\n");
			}	
		//	printf("\n\n\n");
			break;
		} 
		case 9:
		{
			if(day==9)
			{
				printf("\t\t\t\t\t������\n");
			}	
		//	printf("\n\n\n");
			break;
		} 
		case 12:
		{
			if(day==8)
			{
				printf("\t\t\t\t\t���˽�\n");
			}
			if(day==23)
			{
				printf("\t\t\t\t\tС��\n");
			}
			if(day==30)
			{
				printf("\t\t\t\t\t��Ϧ\n");
			}
		//	printf("\n\n\n");	
			break;
			
		}
		/*case 3 :
		printf("\t\t\t\t\t����û�д�ͳ���գ�������\n");break;  
		case 6 :
		printf("\t\t\t\t\t����û�д�ͳ���գ�������\t");break;    
		case 10 :
		printf("\t\t\t\t\t����û�д�ͳ���գ�������\t");break;    
		case 11 :
		printf("\t\t\t\t\t����û�д�ͳ���գ�������\t");break;
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
    	//lunar_holiday(year,month,i);           //����һ���������ڲ�ѯ����Ӧ��ũ��
    	//month_holiday=lunar_month;
    	//day_holiday=lunar_day;
    	select_lunar_holiday(month,i);
	}
} 

void calendar_to_lunar_init(int year,int month,int day)  
{  
    const char *ChDay[] = {"*","��һ","����","����","����","����",  
                           "����","����","����","����","��ʮ",  
                           "ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",  
                           "ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",  
                           "إһ","إ��","إ��","إ��","إ��",  
                           "إ��","إ��","إ��","إ��","��ʮ"  
                          };  
    const char *ChMonth[] = {"*","��","��","��","��","��","��","��","��","��","ʮ","ʮһ","��"};  
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
    printf("\t\t\t\t        ������%d��%d��%d��\tũ��: ",year,month,day);  
    if (LunarCalendar(year,month,day))  
    {  
        strcat(str,"��");  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
    }  
    else  
        strcat(str,ChMonth[(LunarCalendarDay & 0x3C0) >> 6]);  
	    strcat(str,"��");  
	    strcat(str,ChDay[LunarCalendarDay & 0x3F]);
		//strcat(str,"   ||");  
		puts(str);  
	    getchar(); 	 
}
/*********************************************����תũ������********************************************/
void calendar_to_lunar() 
{
	int year,month,day,select;
	int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	do
	{
		printf("\t\t\t\t\t����תũ����\n");
	    printf("\t\t\t\t\t���������ڣ�\n");
		scanf("%d%d%d",&year,&month,&day);
		days[2]=28+LEAP(year);
		printf("\t\t\t\t\t������ת�������\n");
		calendar_to_lunar_init(year,month,day);
		printf("\n");
		printf("\t\t\t\t\t�Ƿ��������ת�� \n");
		printf("\t\t\t\t\t����������� 1\n");
		scanf("%d",&select);
		getch();
		system("cls");		 
    }while(select==1);
}

/**********************************************year_logo_print*******************************************/
//����˵������ӡ���

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
//����˵������ӡ���

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
					printf("\n\t\t\t\t\t���ǽ��������\n");
	    			
					file_init(); 
					draw_yearlogo(year);
					write_yearlogo(year);  
				    print_halfyear(year,1);                              //�ϰ���
					file_write_halfyear(year,1);
					//getch();
				    PF("\n");
				    print_halfyear(year,7);                              //�°���
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
				printf("\n\n\t\t\t\t\t��ѯ�������������� 1��\n"); 
				printf("\t\t\t\t\t��ѯũ������������ 2��\n");
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
						printf("\t\t\t\t\t��������ݼ��·ݣ�");
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

 
