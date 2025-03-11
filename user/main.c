
#include "stm32f10x.h"                  // Device header
#include "delay.h"

#include "serial.h"
#include "Key.h"
#include "Timer.h"
#include "TFT_Driver.h"
#include "GUI.h"
#include <string.h>
#include <stdlib.h>
#include "Weather_ShowImage.h"
#include "W25Q64.h"
#include "Voice.h"
#include "OLED.h"

uint8_t RxData;
uint8_t Key;
uint16_t p;
uint32_t pRxstate;
uint8_t Tem_High=0;
uint8_t Tem_Low=100;
uint8_t Tem_Now;
int8_t time=0;
uint8_t rain_or_not=0;
uint8_t sun_or_not=0;
char Tem_of_day [24];
int key;
char Weather_location[]={"GET https://api.seniverse.com/v3/weather/hourly.json?key=SqkLpGgpqSHquqJSY&location=000.00:000.00&language=zh-Hans&unit=c&start=0&hours=12\r\n"};
char Get_Location[]={"GET https://api.ipdatacloud.com/v2/query?ip=125.78.207.100&key=947ae6b0d9f611ee866f00163e25360e\r\n"};
//char location[13]={"000000:000000"};
int test=0;
	int success=0;
int state=0;
int check_internet;
int i;
int TIME_GET=0;
//int m;
int e;
int WEATHER_GET;
int INTERRUPT_CHECK;
int DATA_ANAYLISE_TEMP;
char Recieve_String[1900];
char Temperature[16];
char Weather[16];
char IP[14];
char time_temp[6]={"1415"};
char Time[8]={"00.00.00"};
int get_weather_succeed=0;
int TIME_HOUR;
int TIME_MINUTE;
int Update_hour;
int Sleep_hour;

uint8_t Count;
uint16_t time_count;

void Weather_Show()
{
	
	if(time>11)
	{time=0;} 
	if(time<0)
	{time=11;} 
	
	switch(time)
	{
	
	case 0:Refresh(80,62,50,20) ;Refresh(40,15,160,80);Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "NOW");Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[0]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[0]-(Temperature[0]/10)*10));break;
		case 1:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+1h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[1]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[1]-(Temperature[1]/10)*10));break;
		case 2:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+2h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[2]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[2]-(Temperature[2]/10)*10));break;
		case 3:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+3h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[3]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[3]-(Temperature[3]/10)*10));break;
		case 4:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+4h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[4]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[4]-(Temperature[4]/10)*10));break;
		case 5:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+5h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[5]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[5]-(Temperature[5]/10)*10));break;
		case 6:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+6h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[6]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[6]-(Temperature[6]/10)*10));break;
		case 7:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+7h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[7]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[7]-(Temperature[7]/10)*10));break;
		case 8:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+8h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[8]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[8]-(Temperature[8]/10)*10));break;
		case 9:Refresh(80,62,50,20) ;Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+9h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[9]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[9]-(Temperature[9]/10)*10));break;
		case 10:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+10h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[10]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[10]-(Temperature[10]/10)*10));break;
		case 11:Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "+11h");Refresh(40,15,160,40);Gui_DrawFont_Num32(40,15,BLACK,WHITE,Temperature[11]/10);Gui_DrawFont_Num32(65,15,BLACK,WHITE,(Temperature[11]-(Temperature[11]/10)*10));break;
		
		
	}
	Gui_DrawFont_GBK16(100, 15,BLACK,WHITE, "C");
				Gui_Circle(95,15,3,BLACK);
				Gui_Circle(95,15,4,BLACK);
	//Gui_DrawFont_GBK16(1, 144,BLACK,WHITE, location);
	Gui_DrawFont_GBK16(1, 144,BLACK,WHITE, time_temp);
	
switch (Weather[time])
			{
			
				case 0:Show_Sunny(0,61);Refresh(80,85,128,135) ;Show_Sunglass(80,85);break;
				case 1:Show_Sunny(0,61);Refresh(80,85,128,135) ;Show_Sunglass(80,85);break;
				case 2:Show_Sunny(0,61);Refresh(80,85,128,135) ;Show_Sunglass(80,85);break;
				case 3:Show_Clear_Night(0,61);Refresh(80,85,128,135) ;Show_Sleep(80,85);break;
				case 4:Show_Cloudy_Day(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 5:Show_Cloudy_Day(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 6:Show_Cloudy_Night(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 7:Show_Cloudy_Day(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 8:Show_Cloudy_Night(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 9:Show_yintian(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 10:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 11:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 12:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 13:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 14:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 15:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 16:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 17:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 18:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 19:Show_Rain_Day(0,61);Refresh(80,85,128,135) ;Show_Umbrella(80,85);break;
				case 20:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 21:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 22:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 23:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 24:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 25:Show_Snowy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 32:Show_Windy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 33:Show_Windy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 34:Show_Windy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				case 35:Show_Windy(0,61);Refresh(80,85,128,135) ;Show_Cloth(80,85);break;
				
				
				
				
			}
}

void GET_TIME()
{ char TIME_TEMP[2];  
	Gui_DrawFont_GBK16(1, 96,BLACK,WHITE, "GETTING TIME");
	
	
	int temp;
USART_SendString("AT+CIPCLOSE\r\n");
	Time_back:
	Delay_ms(200);
pRxstate=0;
	 USART_SendString("AT+CIPSTART=\42TCP\42,\42api.k780.com\42,80\r\n");
	 pRxstate=0;

	
	if((Recieve_String[35]=='C'&&Recieve_String[36]=='O')||Recieve_String[35]=='A')
	{
		Delay_ms(1000);
	USART_SendString("AT+CIPSEND=150\r\n");
	Delay_ms(1000);
	
	USART_SendString("GET http://api.k780.com/?app=life.time&appkey=69973&sign=0caedc32dce9daa1e282e6639f899383&format=json\r\n");
	pRxstate=0;
	USART_SendString("GET http://api.k780.com/?app=life.time&appkey=6");
	
	Delay_ms(1000);
for(int i=0;i<100;i++)
	{
		if(Recieve_String[i]==':')
			temp=i;
	}
	
for(int u=0;u<5;u++)
	{
	time_temp[u]=Recieve_String[u+temp+13];
	
	}
	if(time_temp[1]=='e')
	{
		for(int u=0;u<5;u++)
	{
	time_temp[u]=Recieve_String[u+i+198];
	
	}
}
		
	
	
		
	Gui_DrawFont_GBK16(1, 96,BLACK,WHITE, "                  ");
	Gui_DrawFont_GBK16(1, 96,BLACK,WHITE, "TIME:");
	Gui_DrawFont_GBK16(1, 112,BLACK,WHITE, time_temp);


TIME_HOUR=(time_temp[0]-'0')*10+(time_temp[1]-'0');
	TIME_MINUTE=(time_temp[3]-'0')*10+(time_temp[4]-'0');
Update_hour=TIME_HOUR+8;
Sleep_hour=TIME_HOUR+3;
TIME_GET=1;

}
else
{
Delay_s(1);
goto Time_back;

}


//USART_SendString(Recieve_String);





}
			
void GET_IP()
{
	Lcd_Clear(WHITE);
					Gui_DrawFont_GBK16(1, 1,BLACK,WHITE, "GETTING IP...");
	state=0;
	int b;
	int c=0;
	int IP_temp=0;
	char temp[37];
	char location_temp[13]={"000000:000000"};
	
	USART_SendString("AT+CIPCLOSE\r\n");
	Delay_ms(200);
	IP_loop:
	pRxstate=0;
	
USART_SendString("AT+CIPSTART=\42TCP\42,\42ip.42.pl\42,80\r\n");
Delay_ms(1000);

if(check_internet<=15)
{
if((Recieve_String[31]=='C'&&Recieve_String[32]=='O')||Recieve_String[31]=='A')//判断是否成功连接服务器
{
		
	pRxstate=0;
	USART_SendString("AT+CIPSTART=\42TCP\42,\42ip.42.pl\42,80\r\n");
	Delay_ms(1000);
 
		if(Recieve_String[31]=='A')
			{Delay_ms(100);
			USART_SendString("AT+CIPSEND=25\r\n");
				Delay_ms(200);
				USART_SendString("GET http://ip.42.pl/raw\r\n");
				pRxstate=0;
				Delay_ms(600);
				//USART_SendString(Recieve_String);
				
				pRxstate=0;
				//while(USART_GetITStatus(USART1,USART_IT_RXNE)!=SET);
				Delay_ms(3000);
			//	USART_SendString(Recieve_String);
				
				if(Recieve_String[0]=='+'||Recieve_String[7]=='+')
				{		Lcd_Clear(WHITE);
				
					Gui_DrawFont_GBK16(1, 1,BLACK,WHITE, "IP:");
					
					for(i=0;i<100;i++)
					{
						if(Recieve_String[i]==':')
							b=i;
					
					}
					if(Recieve_String[b+1]=='<')
						goto IP_loop;
					for(i=0;i<14;i++)
					{
						IP[i]=Recieve_String[i+b+1];
					
					}
					for(int i=0;i<14;i++)
				{
				if(IP[i]=='C')
					IP[i]=0;
				
				
				}
				//USART_SendString(IP);
				/*for(i=0;i<14;i++)
					{
					if(0<=IP[i]<=9)
						IP[i]=0;
					
					
					}*/
					Gui_DrawFont_GBK16(1, 16,BLACK,WHITE, IP);
					Gui_DrawFont_GBK16(1, 48,BLACK,WHITE, "GETTING ADDRESS");
				//USART_SendString(Get_Location);
					Delay_ms(200);
					
					for(i=0;i<13;i++)
					{
						Get_Location[i+44]=IP[i];
					
					}
					
					
					//Delay_ms(200);
					//USART_SendString(Get_Location);//此时已经将公网ip地址换到了请求地区的字符串中
					Delay_ms(100);
				
					//USART_SendString("AT+CIPCLOSE\r\n");
	//Delay_ms(200);
					LOCATION_loop:
					pRxstate=0;
					
            USART_SendString("AT+CIPSTART=\42TCP\42,\42api.ipdatacloud.com\42,80\r\n");
              Delay_ms(500);
					
					
					 //USART_SendString(Recieve_String);
					//USART_SendByte(Recieve_String[42]);
					if((Recieve_String[42]=='C'&&Recieve_String[43]=='O')||(Recieve_String[42]=='A'&&Recieve_String[43]=='L'))
					{LOCATION_SEND_loop:
						Delay_ms(200);
          pRxstate=0;
						
					 USART_SendString("AT+CIPSEND=100\r\n");
					Delay_ms(200);
					
						
						if(Recieve_String[14]=='E'&&Recieve_String[15]=='R')
						{
						
						goto LOCATION_SEND_loop;
						
						}
				
						Delay_ms(200);
						
						USART_SendString(Get_Location);
							
						USART_SendString(Get_Location);
					pRxstate=0;
				
					Delay_ms(2000);
					//	USART_SendString(Recieve_String);
						//while(1);
					//	char *location="000000:000000";
						//USART_SendByte(location[1]);
					//	location[1]='9';
						//USART_SendByte(location[1]);
						//USART_SendString("111111111111111");
						Delay_ms(500);
						for(int e=0;e<36;e++)
						{
							temp[e]=Recieve_String[e+344];
						}
							for(int e=0;e<6;e++)
						{
							location_temp[e]=temp[e+1];
							location_temp[e+7]=temp[e+25];
						}
					
						
						
						//Gui_DrawFont_GBK16(1, 64,BLACK,WHITE,location_temp);
												//USART_SendString(location_temp);

					
						
						
						
					
					//USART_SendString(location_temp);
					Gui_DrawFont_GBK16(1, 48,BLACK,WHITE, "                  ");
						
						Gui_DrawFont_GBK16(1, 48,BLACK,WHITE, "ADDRESS:");
						Gui_DrawFont_GBK16(1, 64,BLACK,WHITE, location_temp);

						//USART_SendString(Weather_location);
						
						
						for(i=0;i<13;i++)
						{
						Weather_location[i+84]=location_temp[i];
						
						}
						
						GET_TIME();
						Delay_ms(200);
					//	USART_SendString(Weather_location);
						Gui_DrawFont_GBK16(1, 128,BLACK,WHITE, "PRESS ANY BUTTON");
						Gui_DrawFont_GBK16(1, 144,BLACK,WHITE, "TO CONTINUE");
								//USART_SendString(Weather_location);
				
					}
else 
{
	USART_SendString("AT+CIPCLOSE\r\n");
	Delay_s(2);
	goto LOCATION_loop	;				
}
				
				}
			
				else{
					goto IP_loop;
				
				}
			}
else 			
{	
goto IP_loop;
}
}
else
{
check_internet++;
goto IP_loop;
}

}
else 
{
Gui_DrawFont_GBK16(1,1,BLACK,WHITE,"PLEASE CHECK");
Gui_DrawFont_GBK16(1,16,BLACK,WHITE,"INTERNET");
	Gui_DrawFont_GBK16(1,32,BLACK,WHITE,"PLEASE REBOOT");


}


		// USART_SendString(temp);
//Gui_DrawFont_GBK16(1,1,BLACK,WHITE,temp);


}	
			
void Get_Weather(void)
		
	{
	
	WEATHER_loop:
		 
		WEATHER_GET=0;
		
	char temp[8];
	char apstate[4];
	char time[15];
	char AT[5];
	char ATOK[5];
	char CONNECT[8];	
	char ERROR[8];
		int r=0;
		char temperature[2];
		char weather[2];
		
		for(i=0;i<500;i++)
		{
		
		Recieve_String[i]=0;
		}
		
		
		 pRxstate=0;
		  Delay_ms(2);
		  USART_SendString("AT\r\n");
		
		  Delay_ms(50);
		  OLED_Clear();
		
		 
		
		for(i=0;i<5;i++)
		 {ATOK[i]=Recieve_String[i];}
		USART_SendString("ATOK");
		 if(strcmp(ATOK,"ATOK\0")==0||strcmp(ATOK,"OK\0")==0||strcmp(ATOK,"AT+CW\0")==0)
		 {
		
			    //get ip
			 Delay_ms(50);
			for(i=0;i<8;i++)
			 {
			 temp[i]=Recieve_String[i+4];
			 
			 }
		
			
			 pRxstate=0;
				USART_SendString("AT+CWJAP?\r\n");
				Delay_ms(50);
				for(i=0;i<14;i++)
				{
				apstate[0]=Recieve_String[9];
				}
				
			
			 
				if(apstate[0]=='N')
				{
					Show_Internet_Failed();
				}
				
				else
				{
					Show_connect_successful();
				Delay_s(1);
					pRxstate=0;
	 USART_SendString("AT+CIPSTART=\42TCP\42,\42api.seniverse.com\42,80\r\n");
		 Delay_ms(3000);
					
				CONNECT[0]=Recieve_String[38];
							
				if(CONNECT[0]=='A')
				{
					WEATHER_ERROR_loop:
					pRxstate=0;
					 USART_SendString("AT+CIPCLOSE\r\n");
				Delay_ms(50);
					for(i=0;i<14;i++)
				{
				ERROR[i]=Recieve_String[i+11];
				}
				if(strcmp(ERROR,"ERROR\0")==0)
				{
					
					
					Delay_ms(100);
				goto WEATHER_ERROR_loop;
				}
				else
				{
				goto WEATHER_loop;
				}
				
				}
				
		
			 Delay_ms(1500);
		 USART_SendString("AT+CIPSEND=150\r\n");
		  Delay_ms(500);
		 state=1;
				pRxstate=0;
		 USART_SendString(Weather_location);
		 USART_SendString(Weather_location);
					
					pRxstate=0;
	Delay_ms(500);
					state=0;
					Delay_ms(500);

				DATA_loop:
				
				for(i=0;i<sizeof(Recieve_String);i++)
				{
					if(Recieve_String[i]==':')
					{
					DATA_ANAYLISE_TEMP++;
						
						switch(DATA_ANAYLISE_TEMP)
						{
						
						case 16:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[0]=atoi(temperature);break;
						case 26:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[1]=atoi(temperature);break;
						case 36:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[2]=atoi(temperature);break;
						case 46:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[3]=atoi(temperature);break;
						case 56:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[4]=atoi(temperature);break;
						case 66:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[5]=atoi(temperature);break;
						case 76:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[6]=atoi(temperature);break;
						case 86:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[7]=atoi(temperature);break;			
						case 97:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[8]=atoi(temperature);break;	
						case 107:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[9]=atoi(temperature);break;	
						case 117:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2+r];};Temperature[10]=atoi(temperature);break;	
						case 127:for(e=0;e<2;e++){temperature[e]=Recieve_String[i+e+2];};Temperature[11]=atoi(temperature);break;//以上为温度获取
					
						case 15:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[0]=atoi(weather);break;
						case 25:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[1]=atoi(weather);break;
						case 35:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[2]=atoi(weather);break;
						case 45:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[3]=atoi(weather);break;
						case 55:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[4]=atoi(weather);break;
						case 65:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[5]=atoi(weather);break;
						case 75:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[6]=atoi(weather);break;
						case 85:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[7]=atoi(weather);break;
						case 96:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[8]=atoi(weather);break;
						case 106:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[9]=atoi(weather);break;
						case 116:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[10]=atoi(weather);break;
						case 126:for(e=0;e<2;e++){weather[e]=Recieve_String[i+e+2];};Weather[11]=atoi(weather);break;//以上为天气代码获取
						//获取到的温度储存在Temperature[]中，天气代码储存在Weather[]中；
						
						}
					

					}	
					Tem_Now=Temperature[0];
					Temperature[7]=Temperature[6];
					Temperature[8]=Temperature[9];
					Weather[7]=Weather[6];
					Weather[8]=Weather[9];
					
					for(int i=0;i<11;i++)
					{
					if(Weather[i]==13|Weather[i]==14|Weather[i]==15|Weather[i]==16|Weather[i]==17|Weather[i]==18)
					{rain_or_not=1;}
					
					if(Weather[i]==0)
					{sun_or_not=1;}
					
					
					
					}
				
				}
				
				
			/*for(i=0;i<12;i++)
				{
				if(Temperature[i]>=45)
					Temperature[i]=(Temperature[i-1]+Temperature[i+1])/2;
				if(Temperature[i+1]-Temperature[i]>=3)
					Temperature[i-1]=(Temperature[i-2]+Temperature[i])/2;

				}*/
				
				
				for(i=0;i<11;i++)
				{
				if(Temperature[i]>=Tem_High)
				{
				Tem_High=Temperature[i];
				
				}
				if(Temperature[i]<Tem_Low)
				{
				Tem_Low=Temperature[i];
				
				}
				
				
				}
				Lcd_Clear(WHITE);

				 WEATHER_GET=1; 
				for(int temp;temp<12;temp++)
				{
				Tem_of_day[TIME_HOUR+temp]=weather[i];
				}
				
				
				if(Temperature[0]==0)
				{
					r=18;
					goto DATA_loop;
				//t=2;
				
				}
		 }
				
	 }
		 else
		 {
			 Show_Wrong(0,0);
			Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "002");
		 }

	
	}
	
void System_sleep()
{
Lcd_Clear(BLACK);
}

int main(void)

{
	OLED_Init();
	MYUSART_Init();
	W25Q64_Init();
	Key_Init();
	Timer_Init();
	SystemInit();	
	Lcd_Init();
	Voice_Init();
	Lcd_Clear(WHITE);
	Show_Waiting();
	Delay_s(1);
		
	
	GET_IP();
	while(Key_GetNum()==0);
	
 Show_press_to_continue();
	
	
	
	

	
	while(1){
		DATA_GET_loop:
		if(INTERRUPT_CHECK==1)
		{
			key=Key_GetNum();
			switch(key)
			{
				case 1:time=0;Get_Weather();get_weather_succeed=1; INTERRUPT_CHECK=0; Count=0;rain_or_not=0;break;
				case 2:if(get_weather_succeed==1){time++;Weather_Show();INTERRUPT_CHECK=0;Count=0;break;}else {goto DATA_GET_loop;}
				case 3:if(get_weather_succeed==1){time--;Weather_Show();INTERRUPT_CHECK=0;Count=0;break;}else {goto DATA_GET_loop;}
			}
	}
		
		if(WEATHER_GET==1)
		{
			Show_Temperature_Image(0,0);//38*60
				Gui_DrawFont_GBK16(100, 15,BLACK,WHITE, "C");
				Gui_Circle(95,15,3,BLACK);
				Gui_Circle(95,15,4,BLACK);
			OLED_ShowNum(4,1,Tem_High,2);
			OLED_ShowNum(4,4,Tem_Low,2);
			Weather_Show();
			
			
			if(8<=TIME_HOUR<=17)
			{
			
	Voice_SendData(0x0A);
	Voice_SendData(0x09);
	Voice_SendData(0x09);
	Voice_SendData(0x0C);//set the valume//音量大小设置
	Voice_SendData(0x0A);
	Voice_SendData(0x01);
	Voice_SendData(0x0b);//select track//曲目选择"未来12小时内最高温度为"
	Delay_ms(2550);
	Voice_High();//voice chip play the highest temperature
	Delay_ms(1200);
	Voice_SendData(0x0A);
	Voice_SendData(0x02);
	Voice_SendData(0x0b);//select track//曲目选择“最低温度为”
	Delay_ms(1400);
  Voice_Low();//voice chip play the lowest temperature




			Delay_ms(1200);
		
			
			if(rain_or_not==0)
				{
				
				if(sun_or_not==1)
				{
				
				Voice_sun();//voice chip play if it is going to be sunny
				
				}
				else 
				break;
				
			}
				else 
				{Voice_rain();}//voice chip play if it is going to be rainning
			
			}
			
			WEATHER_GET=0; 			
			
		}
		if(WEATHER_GET==2)
		{
		
		Show_Wrong(0,0);
			Gui_DrawFont_GBK16(80, 62,BLACK,WHITE, "001");
		WEATHER_GET=0;
		
		}
	
		
	
	 
}
}







void TIM2_IRQHandler(void)
	{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET )
	{	
		Count++;
		time_count++;
		if(Count==2) 
		{
		Count=0;
			INTERRUPT_CHECK=1;
		
		}
		
		if(TIME_GET==1)
		{
		if(time_count==6000)
		{
		time_count=0;
			TIME_MINUTE++;
			time_temp[0]=TIME_HOUR/10+'0';
			time_temp[1]=TIME_HOUR-(TIME_HOUR/10)*10+'0';
				time_temp[3]=TIME_MINUTE/10+'0';
			time_temp[4]=TIME_MINUTE-(TIME_MINUTE/10)*10+'0';
			if(TIME_MINUTE==60)
			{
			TIME_MINUTE=0;
				TIME_HOUR++;
			
			}
			if(TIME_HOUR==Update_hour)
			{
				Get_Weather();
				Update_hour=Update_hour+8;
			}
			if(Sleep_hour==TIME_HOUR)
			{
			System_sleep();
			Sleep_hour=Sleep_hour+3;
				while(Key_GetNum()==0);
				Get_Weather();
			}
			
			
		
		
		}
		
		
		}
		
		 TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
		}
		

	}

	
	/*W25Q64_SectorErase(0x000000);
	W25Q64_SectorErase(0x001000);
	W25Q64_SectorErase(0x002000);
	for(p=0;p<60;p++)
	{
		for(i=0;i<256;i++)
		{
		temp[i]=gImage_rain_night[i+256*p];
		}
		USART_SendArray(temp,256);
	
	W25Q64_PageProgram(0x000000+0x000100*p,temp,256);
	
	}

	Delay_s(1);*/
	
	//此为向W25Q64写入数据
	//0x000000   0x001000   0x002000   ......
