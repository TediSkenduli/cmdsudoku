#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
#include <dos.h>
#include <dir.h>
#include <time.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//colour function

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}
//shortening
void red(){
  SetColor(4);
}
void green(){
  SetColor(2);
}
void white(){
  SetColor(15);
}
void black(){
  SetColor(0);
} 
void lightgreen(){
  SetColor(10);
}
//check validity of completed sudoku
int check(int s[9][9])
{
	int b, c, i, j, k, g, a=0;
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			for(k=0; k<9; k++)
			{
				if((i!=k) && (j!=k))
				{
					if((s[i][j]==s[i][k]) || (s[i][j]==s[k][j])) 
					{
						a=1;
						break;
					}
				}
				if(s[i][j]==0 || s[i][k]==0 || s[k][j]==0)
				{
					a=1;
					break;
				}
			}
			b=floor(i/3);
			c=floor(j/3);
			for(k=(b*3); k<((b*3)+3); k++)
			{
				for(g=(c*3); g<((c*3)+3); g++)
				{
					if((i!=k) || (j!=g))
					{
						if(s[i][j]==s[k][g] && a==0) 
						{
							a=1;
							break;
						}
					}
				}
				if(a==1)
					break;
			}
			if(a==1)
				break;
		}
		if(a==1)
			break;
	}
	return a;
}
//shows the sudoku the way I structured it
void printmatrix(int n[9][9])
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{	
			if(n[i][j]<10 && n[i][j]>0)
			{
				green();
				printf("%d ",n[i][j]);
				white();
			}
			else
				if(n[i][j]>10)
				{printf("%d ",n[i][j]-10);}
				else
				{	red();
					printf("? ");
					white();
				}
			if(j==2 || j==5)
			{
				printf(" ");
			}
		}
		printf("\n");
		if(i==2 || i==5)
		{
			printf("\n");
		}
	} 
}


int main(int argc, char *argv[]) {
	srand(time(NULL));
	//this 2D array is only for the help option, not to check validity
	int m[9][9]={
	{5,3,4,6,7,8,9,1,2},//0 1 4
	{6,7,2,1,9,5,3,4,8},//0 3 4 5
	{1,9,8,3,4,2,5,6,7},//1 2 7
	{8,5,9,7,6,1,4,2,3},//0 4 8
	{4,2,6,8,5,3,7,9,1},//0 3 5 8
	{7,1,3,9,2,4,8,5,6},//0 4 8
	{9,6,1,5,3,7,2,8,4},//1 6 7
	{2,8,7,4,1,9,6,3,5},//3 4 5 8
	{3,4,5,2,8,6,1,7,9} //4 8
				}; 
	//this is the main 2D array the user will be able to modify
	int n[9][9]={
	{5,3,0,0,7,0,0,0,0},//0 1 4     0
	{6,0,0,1,9,5,0,0,0},//0 3 4 5   1
	{0,9,8,0,0,0,0,6,0},//1 2 7     2
	{8,0,0,0,6,0,0,0,3},//0 4 8     3
	{4,0,0,8,0,3,0,0,1},//0 3 5 8   4
	{7,0,0,0,2,0,0,0,6},//0 4 8     5
	{0,6,0,0,0,0,2,8,0},//1 6 7     6
	{0,0,0,4,1,9,0,0,5},//3 4 5 8   7
	{0,0,0,0,8,0,0,7,9} //4 7 8     8
				};
	//a, b -> row, column | v -> value
	int i,j,a,b,v;
	//command serves to specify if input, remove input or get hint | count0 is to break command==3 while
	int command,count0;
	//test will be used as the return value of the 2D array validity function
	int test=check(n);
while(test>0)
{	//show 2D array + menu options
	system("cls");
	printmatrix(n);
	printf("Continue - 1\nRemove - 2\nHint - 3\n");
	scanf("%d",&command);
	//check numerical value
	while(command<1 || command>3)
	{
		printf("Give a number between 1 and 3\n");
		scanf("%d",&command);
	}
	//remove value
	if(command==2)
	{
		printf("Give Row: ");
		scanf("%d",&a);
		printf("\nGive Column: ");
		scanf("%d",&b);
		if(n[a][b]>9)
		{
			n[a][b]=0;
		}
		//user should only be able to remove values they input
		else
		{
			printf("This is a fixed value.");
			Sleep(3000);
		}
	}
	//hint fills a random blank
	if(command==3)
	{
		int xa=(rand() % 9);
		int xb=(rand() % 9);
		count0=0;
		while(n[xa][xb]!=0 && count0!=100)
		{
			xa=(rand() % 9);
			xb=(rand() % 9);
			count0=count0+1;
		}
		n[xa][xb]=m[xa][xb]+10;
	}
	//user input to fill a square of the sudoku
	if(command==1)
	{
		system("cls");
		printmatrix(n);
		printf("Row (0-8): ");
		scanf("%d",&a);
		printf("\nColumn (0-8): ");
		scanf("%d",&b);
		printf("\nValue (1-9): ");
		scanf("%d",&v);
		//check numerical value
		while(v<1 || v>9)
		{
			printf("\nGive a value between 1 and 9: ");
			scanf("%d",&v);
		}
		//check if square is empty
		if(n[a][b]==0)
		{
			n[a][b]=v+10;
		}
		//note: user inputs are saved with +10 to differentiate from fixed values then displayed with -10
		//this so the user doesn't remove fixed values and also for colour coding the output
		else
		{
			printf("There is a fixed value in this square.");
			Sleep(4000);
		}
	}
	//resetting command and updating test variable
	command=0;
	test=check(n);
}
system("cls");
printmatrix(n);
lightgreen();
printf("You Won!");
white();
return 0;
}
