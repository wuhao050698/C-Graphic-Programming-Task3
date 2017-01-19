
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
int position_x,position_y; 
int bullet_x,bullet_y; 
int enemy_x,enemy_y; 
int high,width;
int score,die; 

void HideCursor()
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup()
{
	high=20;
	width=30;
	position_x=high/2;
	position_y=width/2;
	bullet_x=-2;
	bullet_y=position_y;
	enemy_x=0;
	enemy_y=position_y;
	score=0;
	die=0;
}

void show() 
{
	gotoxy(0,0);  
	int i,j;
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==position_x) && (j==position_y))
				printf("*");  //   输出飞机*
			else if ((i==enemy_x) && (j==enemy_y))
				printf("@");  //   输出敌机@
			else if ((i==bullet_x) && (j==bullet_y))
				printf("|");  //   输出子弹|
			else
				printf(" ");  //   输出空格
		}
		printf("|");
		printf("\n");
	}
	for(i=0;i<width;i++)
	printf("-");
	printf("-\n得分：%d\n死亡次数：%d\n",score,die); 
}	

void updateWithoutInput(int sp) 
{	
	if (bullet_x>-1)
		bullet_x--; 

	if ((bullet_x==enemy_x) && (bullet_y==enemy_y)) 
	{
		score++;               
		enemy_x = -1;          
		enemy_y = rand()%width;
		bullet_x = -2;         
	}
	if (enemy_x>high)  
	{
		enemy_x = -1;          
		enemy_y = rand()%width;
		die++;
	}
	if((enemy_x==position_x)&&(enemy_y==position_y))
	{
		position_x = high/2;
	    position_y = width/2;
	    enemy_x = -1;          
		enemy_y = rand()%width;
	    die++;
	}
	static int speed = 0;  
	if (speed<20/sp)
		speed++;
	if (speed==20/sp)
	{
		enemy_x++;			
		speed=0;
	}
}

void updateWithInput()  
{
	char input;
	if(kbhit())  
	{
		input = getch(); 
		if (input == 'a')   
		{
			if(position_y>=1)
			position_y--;  
		}
		if (input == 'd')
		{
			if(position_y<29)
			position_y++;
		  }  
		if (input == 'w')
		{
			if(position_x>=1)
			position_x--;
		  }  
		if (input == 's')
		{
			if(position_x<19)
			position_x++;
		  }  
		if (input == ' ')  
		{
			bullet_x = position_x-1;  
			bullet_y = position_y;
		}
		
	}
}

int main()
{
	int sp;
	printf("wu出品\n\n\nw上s下a左d右 空格发射子弹\n撞上敌机或者让敌机到达下方算死亡\n死亡3次游戏结束\n");
	printf("\n\n选择游戏难度\n\n输入难度(1~3):"); 
    while(1)
	{
		scanf("%d",&sp);
		if(sp<1||sp>3)
		printf("输入有误\n");
		else 
			break; 
	}	
	HideCursor();
	startup();  	
	while (1) 
	{
		show();  
		updateWithoutInput(sp);  
		updateWithInput();
		if(die==3)
		{
			system("cls");
			printf("游戏结束\n");
			scanf("%s");
			break;
	    }
		
	}
	return 0;
}
