#include "main_character.h"
#include "monster.h"
//for kbhit in linux
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
//for delay function
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <curses.h>
#define	times_can_die	3
#define	linewidth		30      //do not change it
#define	columnwidth 	100		//do not change it
#define	MonVelocity		150		//move velocity of every monster
#define checkdie_V		6000
#define	GenVelocity 	300		//generate velocity of small ball
#define	Gen2Velocity 	1320    //generate velocity of middle ball
#define	Gen3Velocity 	3010   	//generate velocity of large ball
#define	SCORE1			100		//hit small ball can get SCORE1 point
#define	SCORE2			300		//hit middle ball can get SCORE2 point
#define	SCORE3			600     //hit large ball can get SCORE3 point
#define	USLEEP			300		//do not change it
void	initial();
int		kbhit();
void	ifMOhit(bullet &,MonsterOne &);
bool	ifMOhit(bullet &,MonsterTwo &);
bool	ifMOhit(bullet &,MonsterThree &);
bool	ifMAINhit(me &,MonsterOne &);
bool	ifMAINhit(me &,MonsterTwo &);
bool	ifMAINhit(me &,MonsterThree &);
int		ch = EOF;
int		bullet::count=0;
int		bullet::velocity=0;
int		MonsterOne::monCount=0;
int		monVelocity=0;
int		genVelocity=0;
int		gen2Velocity=0;
int		gen3Velocity=0;
int		score=0,test,endgame=0;
void	dead();
void	deadwin();
void	startwin();
void    winwin();
int level=0,diecount=0,checkdie_v=0;
WINDOW *boxwin;
using namespace std;
int	main()
{
	printf("\033[?25l");
	int i=0,countbul=0;
	me A; 
	vector <MonsterOne*> mon;
	vector	<MonsterOne*>::iterator itomon;
	vector	<MonsterOne*>::iterator i2tomon;
	vector <MonsterTwo*> mon2;
	vector	<MonsterTwo*>::iterator itomon2;
	vector	<MonsterTwo*>::iterator i2tomon2;
	vector <MonsterThree*> mon3;
	vector	<MonsterThree*>::iterator itomon3;
	vector	<MonsterThree*>::iterator i2tomon3;	
while(1)
{		
	char t;
	cout<<"\033[31mPlease select :\033[0m"<<endl
		<<"1.Start Normal Mode"	<<endl
		<<"2.Start Crazy Mode"	<<endl
		<<"3.Game Instructions"	<<endl
		<<"4.Leave"		<<endl; 
	cin>>t;

	switch(t)
	{
		case '1':	
			initial();
			boxwin=newwin(linewidth+2,columnwidth+2,0,0);
			A.New();
			startwin();
			wrefresh(boxwin);
			usleep(1000000);
			std::cin>>test;
			wclear(boxwin);
			box(boxwin,'|','-');
			wrefresh(boxwin);
			do                                              
			{
				mvwprintw(boxwin,linewidth+1,(columnwidth+2)/2-8,"Score = %d",score);
				mvwprintw(boxwin,0,(columnwidth+2)/2-8,"LEVEL = %d ",level);
				mvwprintw(boxwin,0,3,"lives remain = %d",times_can_die-diecount);
				wrefresh(boxwin);
				if(kbhit())                                 
				{		                                    //
					switch(ch) 								//判斷輸入字元為何 	
					{                                       //
						case 'a':							//判斷是否"A"鍵被按下
									A.gunleft();	        //
									break;		            //
						case 'd':			               	//判斷是否"D"鍵被按下
									A.gunright(); 			//		
									break;                  //		
						case 'w':				            // 判斷是否"W"鍵被按
									A.gunup();              //
									break;					//	
						case KEY_RIGHT:	A.bodygoright();	//判斷是否"→"鍵被按下
										break;              //
						case KEY_LEFT:	A.bodygoleft();		//判斷是否"←"鍵被按下
										break;              //
						case 27: 	endwin();           	//判斷是否[ESC]鍵被按
									exit(1);             	//結束 curses 模式 					
					}
				}
				//LEVEL SET
				if(level>9&&MonsterOne::monCount<=4)
					mon.push_back(new MonsterOne);
				
				if(level==0&&score==0)	{mon.push_back(new MonsterOne(70,5,7));level++;}
				if(level==1&&score==100)
					{mon.push_back(new MonsterOne(70,5,1));mon.push_back(new MonsterOne(30,5,4));level++;}
								if(level==2&&score==300)
				{
					for(int k=0;k<4;k++)
					    mon.push_back(new MonsterOne);
					level++;
				}
				if(level==3&&score==700)
				{
					for(int k=0;k<8;k++)
					    mon.push_back(new MonsterOne);
					level++;
				}
				if(level==4&&score==1500)
				{
					for(int k=0;k<5;k++)
					    mon.push_back(new MonsterOne);
					mon2.push_back(new MonsterTwo(70,5,1));
					level++;
				}
				if(level==5&&score>2300)
				{
					for(int k=0;k<5;k++)
					    mon.push_back(new MonsterOne);
					mon2.push_back(new MonsterTwo(70,5,1));
					mon2.push_back(new MonsterTwo(30,5,4));
					level++;
				}
				if(level==6&&score>3800)
				{
					for(int k=0;k<5;k++)
					    mon.push_back(new MonsterOne);
					mon2.push_back(new MonsterTwo(70,5,1));
					mon2.push_back(new MonsterTwo(30,5,4));
					mon2.push_back(new MonsterTwo(15,5,2));
					level++;
				}
				if(level==7&&score>5700)
				{
					for(int k=0;k<5;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==8&&score>8000)
				{
					for(int k=0;k<8;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==9&&score>12000)
				{
					mon3.push_back(new MonsterThree(50,5,1));
					for(int k=0;k<5;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==10&&score>15500)
				{
					//B
                    for(int j=3;j<12;j=j+4)
	                    for(int i=4;i<14;i++)
		                    mon.push_back(new MonsterOne(i,j,100));
                    for(int j=3;j<=11;j++)
	                    mon.push_back(new MonsterOne(3,j,100));
                    for(int j=4;j<=10;j=j+2)
	                    for(int i=13;i<=14;i++)
		                    mon.push_back(new MonsterOne(i,j,100));
                    mon.push_back(new MonsterOne(14,5,100));	
                    mon.push_back(new MonsterOne(14,9,100));
                    //O							
                    for(int i=23;i<=33;i++)
	                    {mon.push_back(new MonsterOne(i,3,100));mon.push_back(new MonsterOne(i,11,100));}
                    for(int j=4;j<=10;j++)
	                    {mon.push_back(new MonsterOne(22,j,100));mon.push_back(new MonsterOne(34,j,100));}
                    //N
                    for(int j=3;j<=11;j++)
                    {
	                    mon.push_back(new MonsterOne(42,j,100));mon.push_back(new MonsterOne(53,j,100));
	                    mon.push_back(new MonsterOne(j+40,j,100));
                    }
                    mon.push_back(new MonsterOne(52,11,100));
                
                     //U
	
                    for(int j=3;j<=10;j++)
	                    {mon.push_back(new MonsterOne(63,j,100));mon.push_back(new MonsterOne(75,j,100));}
                    for(int i=64;i<=74;i++)
	                    mon.push_back(new MonsterOne(i,11,100));
                    //S
                    for(int i=83;i<=95;i++)
	                    {mon.push_back(new MonsterOne(i,3,100));mon.push_back(new MonsterOne(i,11,100));}
                    mon.push_back(new MonsterOne(82,4,100));
                    mon.push_back(new MonsterOne(96,10,100));
                    mon.push_back(new MonsterOne(96,4,100));
                    mon.push_back(new MonsterOne(82,10,100));
                    mon.push_back(new MonsterOne(83,5,100));
                    mon.push_back(new MonsterOne(84,5,100));
                    mon.push_back(new MonsterOne(95,9,100));
                    mon.push_back(new MonsterOne(96,9,100));
                    mon.push_back(new MonsterOne(84,6,100));
                    mon.push_back(new MonsterOne(85,6,100));
                    mon.push_back(new MonsterOne(86,6,100));
                    mon.push_back(new MonsterOne(93,8,100));
                    mon.push_back(new MonsterOne(94,8,100));
                    mon.push_back(new MonsterOne(95,8,100));
                    for(int i=86;i<=93;i++)
	                    mon.push_back(new MonsterOne(i,7,100));
					level++;
		   		}
			   	if(level==11&&score>15500+18800)
				{
					for(int k=0;k<3;k++)
					    mon3.push_back(new MonsterThree);
					for(int k=0;k<5;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==12&&score>21000+18800)
				{
					for(int k=0;k<3;k++)
					    mon3.push_back(new MonsterThree);
					for(int k=0;k<8;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==13&&score>28000+18800)
				{
					for(int k=0;k<5;k++)
					    mon3.push_back(new MonsterThree);
					for(int k=0;k<5;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==14&&score>35500+18800)
				{
					for(int k=0;k<5;k++)
					    mon3.push_back(new MonsterThree);
					for(int k=0;k<8;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==15&&score>44500+18800)
				{
					for(int k=0;k<10;k++)
					    mon.push_back(new MonsterOne);
					for(int k=0;k<5;k++)
					    mon3.push_back(new MonsterThree);
					for(int k=0;k<8;k++)
					    mon2.push_back(new MonsterTwo);
					level++;
				}
				if(level==16&&score>54500+18800)
				{   
			        clear();
	                refresh();
					winwin();
					wrefresh(boxwin);
					usleep(3000000);
	                clear();
	                refresh();
	                mvwprintw(boxwin,(linewidth+1)/2,(columnwidth+2)/2-9,"Your Final Score : %d",score);
	                wrefresh(boxwin);
	                usleep(3000000);
	                endwin();
				}
				
				//END LEVEL SET
				//move monster
				if(monVelocity==MonVelocity)
				{
					monVelocity=0;
					//ckeck rebound
					//1to1
					if(!mon.empty())
						for(itomon = mon.begin(); itomon != mon.end()-1;itomon++)
							for(i2tomon = mon.begin()+1; i2tomon != mon.end();i2tomon++)
									(*itomon)->rebound(**i2tomon);
					//2to1 and 3to1	
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
					{	
						for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
							(*itomon2)->rebound(**itomon);
						for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
							(*itomon3)->rebound(**itomon);
					}	
					//2to2
					if(!mon2.empty())
						for(itomon2 = mon2.begin(); itomon2 != mon2.end()-1;itomon2++)
							for(i2tomon2 = mon2.begin()+1; i2tomon2 != mon2.end();i2tomon2++)
								(*itomon2)->rebound(**i2tomon2);
					//3to2
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
							(*itomon3)->rebound(**itomon2);
					//3to3
					if(!mon3.empty())	
						for(itomon3 = mon3.begin(); itomon3 != mon3.end()-1;itomon3++)
							for(i2tomon3 = mon3.begin()+1; i2tomon3 != mon3.end();i2tomon3++)
									(*itomon3)->rebound(**i2tomon3);
					//end check rebound
					//purely move
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
						(*itomon)->moveMO();
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						(*itomon2)->moveMO();
					for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
						(*itomon3)->moveMO();
				}
				monVelocity++;
				//end move monster
				
				//check if kill the monster
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					for(int j=0;j<bullet::count;j++)
						ifMOhit(*A.b[j],**itomon);
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)	
					for(int j=0;j<bullet::count;j++)	
						if(ifMOhit(*A.b[j],**itomon2))
						{
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety(),3));
							mon.push_back(new MonsterOne(A.b[j]->getx(),A.b[j]->gety(),4));
						}
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					for(int j=0;j<bullet::count;j++)
						if(ifMOhit(*A.b[j],**itomon3))
						{
							mon.push_back(new MonsterOne(A.b[j]->getx()  ,A.b[j]->gety()+1,1));
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety()+1,2));
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety()  ,3));
							mon.push_back(new MonsterOne(A.b[j]->getx()  ,A.b[j]->gety()  ,4));
						}	
				//end check
				//ckeck if end the game				
				if(!A.bekilled)
				{	
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
						if(ifMAINhit(A,**itomon))
						{
							dead();
							endgame=1;
							break;
						}		
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						if(ifMAINhit(A,**itomon2))
						{
							dead();
							endgame=1;
							break;
						}		
					for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
						if(ifMAINhit(A,**itomon3))
						{
							dead();
							endgame=1;
							break;
						}
				}
				if(A.bekilled && checkdie_v==checkdie_V)
				{checkdie_v=0; A.bekilled=0;}
				if(checkdie_v==checkdie_V)
					checkdie_v=0;
				checkdie_v++;
				if(endgame==1)
					break;
				//end check
				//FREE the space if monster die
				for(itomon = mon.begin(); itomon != mon.end();)
				{
					if ((*itomon)->bekilled)
					{
						--MonsterOne::monCount;
						(*itomon)->free();
						mon.erase(itomon);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon++;
				}				
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();)
				{
					if ((*itomon2)->bekilled)
					{
						--MonsterOne::monCount;
						(*itomon2)->free();
						mon2.erase(itomon2);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon2++;
				}
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();)
				{
					if ((*itomon3)->bekilled)
					{
						--MonsterOne::monCount;
						(*itomon3)->free();
						mon3.erase(itomon3);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon3++;
				}
				//end FREE
				
				//show every monster
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					(*itomon)->print();
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
					(*itomon2)->print();
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					(*itomon3)->print();
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					(*itomon)->refresh();
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
					(*itomon2)->refresh();
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					(*itomon3)->refresh();
				//end show every monster
				A.showbody();
				A.showgun();
				A.allmove();//show every bullet
				A.refresh();
				A.free();
				usleep(USLEEP);
	
			} while(1);
			endwin();
			exit(0);
		case '2':
			initial();
			boxwin=newwin(linewidth+2,columnwidth+2,0,0);
			A.New();
			startwin();
			wrefresh(boxwin);
			usleep(1000000);
			std::cin>>test;
			wclear(boxwin);
			box(boxwin,'|','-');
			wrefresh(boxwin);
			do                                              
			{
				mvwprintw(boxwin,linewidth+1,(columnwidth+2)/2-8,"Score = %d",score);
				mvwprintw(boxwin,0,(columnwidth+2)/2-8,"lives remain = %d",times_can_die-diecount);
				wrefresh(boxwin);
				if(kbhit())                                 
				{		                                    //
					switch(ch) 								//判斷輸入字元為何 	
					{                                       //
						case 'a':							//判斷是否"A"鍵被按下
									A.gunleft();	        //
									break;		            //
						case 'd':			               	//判斷是否"D"鍵被按下
									A.gunright(); 			//		
									break;                  //		
						case 'w':				            // 判斷是否"W"鍵被按
									A.gunup();              //
									break;					//	
						case KEY_RIGHT:	A.bodygoright();	//判斷是否"→"鍵被按下
										break;              //
						case KEY_LEFT:	A.bodygoleft();		//判斷是否"←"鍵被按下
										break;              //
						case 27: 	endwin();           	//判斷是否[ESC]鍵被按
									exit(1);             	//結束 curses 模式 					
					}
				}
				//automatically generate monster
				if(MonsterOne::monCount<50){
				if(genVelocity==GenVelocity)
				{
					mon.push_back(new MonsterOne);//build monsterone	
					genVelocity=0;
				}
				genVelocity++;\
				if(gen2Velocity==Gen2Velocity)
				{	
					mon2.push_back(new MonsterTwo);//build monsteron2
					gen2Velocity=0;
				}
				gen2Velocity++;
				if(gen3Velocity==Gen3Velocity)
				{
					mon3.push_back(new MonsterThree);//build monsterone3
					gen3Velocity=0;
				}
				gen3Velocity++;}
				
				//move monster
				if(monVelocity==MonVelocity/2)
				{
					monVelocity=0;
					//ckeck rebound
					//1to1
					if(!mon.empty())
						for(itomon = mon.begin(); itomon != mon.end()-1;itomon++)
							for(i2tomon = mon.begin()+1; i2tomon != mon.end();i2tomon++)
									(*itomon)->rebound(**i2tomon);
					//2to1 and 3to1	
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
					{	
						for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
							(*itomon2)->rebound(**itomon);
						for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
							(*itomon3)->rebound(**itomon);
					}	
					//2to2
					if(!mon2.empty())
						for(itomon2 = mon2.begin(); itomon2 != mon2.end()-1;itomon2++)
							for(i2tomon2 = mon2.begin()+1; i2tomon2 != mon2.end();i2tomon2++)
								(*itomon2)->rebound(**i2tomon2);
					//3to2
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
							(*itomon3)->rebound(**itomon2);
					//3to3
					if(!mon3.empty())	
						for(itomon3 = mon3.begin(); itomon3 != mon3.end()-1;itomon3++)
							for(i2tomon3 = mon3.begin()+1; i2tomon3 != mon3.end();i2tomon3++)
									(*itomon3)->rebound(**i2tomon3);
					//end check rebound
					//purely move
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
						(*itomon)->moveMO();
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						(*itomon2)->moveMO();
					for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
						(*itomon3)->moveMO();
				}
				monVelocity++;
				//end move monster
				
				//check if kill the monster
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					for(int j=0;j<bullet::count;j++)
						ifMOhit(*A.b[j],**itomon);
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)	
					for(int j=0;j<bullet::count;j++)	
						if(ifMOhit(*A.b[j],**itomon2))
						{
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety(),3));
							mon.push_back(new MonsterOne(A.b[j]->getx(),A.b[j]->gety(),4));
						}
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					for(int j=0;j<bullet::count;j++)
						if(ifMOhit(*A.b[j],**itomon3))
						{
							mon.push_back(new MonsterOne(A.b[j]->getx(),A.b[j]->gety()+1,1));
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety()+1,2));
							mon.push_back(new MonsterOne(A.b[j]->getx()+1,A.b[j]->gety(),3));
							mon.push_back(new MonsterOne(A.b[j]->getx(),A.b[j]->gety(),4));
						}	
				//end check
				//ckeck if end the game
				if(!A.bekilled)
				{	
					for(itomon = mon.begin(); itomon != mon.end();itomon++)
						if(ifMAINhit(A,**itomon))
						{
							dead();
							endgame=1;
							break;
						}		
					for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
						if(ifMAINhit(A,**itomon2))
						{
							dead();
							endgame=1;
							break;
						}		
					for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
						if(ifMAINhit(A,**itomon3))
						{
							dead();
							endgame=1;
							break;
						}
				}
				if(A.bekilled && checkdie_v==checkdie_V)
				{checkdie_v=0; A.bekilled=0;}
				if(checkdie_v==checkdie_V)
					checkdie_v=0;
				checkdie_v++;
				if(endgame==1)
					break;
				//end check
				//FREE the space if monster die
				for(itomon = mon.begin(); itomon != mon.end();)
				{
					if ((*itomon)->bekilled)
					{
						--MonsterOne::monCount;
						(*itomon)->free();
						mon.erase(itomon);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon++;
				}
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();)
				{
					if ((*itomon2)->bekilled)
					{
						(*itomon2)->free();
						mon2.erase(itomon2);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon2++;
				}
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();)
				{
					if ((*itomon3)->bekilled)
					{
						(*itomon3)->free();
						mon3.erase(itomon3);		// 使用 erase ，並將回傳值給 iterator itomon
					}
					else
						itomon3++;
				}
				//end FREE
				
				//show every monster
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					(*itomon)->print();
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
					(*itomon2)->print();
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					(*itomon3)->print();
				for(itomon = mon.begin(); itomon != mon.end();itomon++)
					(*itomon)->refresh();
				for(itomon2 = mon2.begin(); itomon2 != mon2.end();itomon2++)
					(*itomon2)->refresh();
				for(itomon3 = mon3.begin(); itomon3 != mon3.end();itomon3++)
					(*itomon3)->refresh();
				//end show every monster
				A.showbody();
				A.showgun();
				A.allmove();//show every bullet
				A.refresh();
				A.free();
				usleep(USLEEP);
	
			} while(1);
			endwin();
			exit(0);
		case '3':
			cout<<"You can:\n"
				<<"press \"→\" to move right\n"
				<<"press \"←\" to move left \n"
				<<"press \"A\" to shoot left \n"
				<<"press \"D\" to shoot right \n"
				<<"press \"W\" to shoot up \n"
				<<"If you don't want to play anymore in the game, you can press \"ESC\" to leave.\n"
				<<"If you shoot a ball, the ball will die, and you can get some points.\n"
				<<"If you are hit by a ball, you lose!!!!\n"
				<<"You just finished the instructions!\n"
				<<"Now choose a mode to play!\n\n\n";
			break;
		case '4':
			exit(0);
		default:
			break;
			//exit(0);
	}
}
	return 0;
}

void initial()
{
	initscr();                 
	cbreak();                  
	nonl();                    
	noecho();                  
	intrflush(stdscr,FALSE);
	keypad(stdscr,TRUE);
	refresh();
}
//check if a keyboard is pressed
int kbhit()
{
	struct termios oldt, newt;
	int oldf;
	ch = EOF;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	
	ch = getch();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	
	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	
	return 0;
}
void ifMOhit(bullet & b,MonsterOne & m)
{
	if(!b.done&&!m.bekilled)
		if(b.getx()==m.getx()&&b.gety()==m.gety())
		{
			b.done=1;
			m.bekilled=1;
			score+=SCORE1;
		}
}
bool ifMOhit(bullet & b,MonsterTwo & m)
{
	if(!b.done&&!m.bekilled)
		if(b.getx()>=m.getx()&&b.getx()<=m.getx()+4&&b.gety()==m.gety())
		{
			b.done=1;
			m.bekilled=1;
			score+=SCORE2;
			return 1;
		}
	return 0;
}
bool	ifMOhit(bullet & b,MonsterThree & m)
{
	if(!b.done&&!m.bekilled)
		if(b.getx()>=m.getx()&&b.getx()<=m.getx()+6&&b.gety()==m.gety())
		{
			b.done=1;
			m.bekilled=1;
			score+=SCORE3;
			return 1;
		}
	return 0;
}
bool ifMAINhit(me & MC,MonsterOne & MO)
{
	if(!MO.bekilled)
		if(!MC.bekilled&&!MO.kill)
			if(MO.getx()>=MC.getx()&&MO.getx()<=MC.getx()+4&&MO.gety()>=MC.gety()-2)
			{
				if(diecount<times_can_die)
				{MC.bekilled=1;diecount++;return 0;}
				MO.kill=1;
				//MC.bekilled=1;
				return 1;
			}	
	return 0;			
}
bool ifMAINhit(me & MC,MonsterTwo & MO)
{
	if(!MO.bekilled)
		if(!MC.bekilled&&!MO.kill)
			if(MO.getx()+4>=MC.getx() && MO.getx()<=MC.getx()+4&&MO.gety()>=MC.gety()-2)
			{
				if(diecount<times_can_die)
				{MC.bekilled=1;diecount++;return 0;}
				MO.kill=1;
				//MC.bekilled=1;
				return 1;
			}		
	return 0;
}
bool ifMAINhit(me & MC,MonsterThree & MO)
{
	if(!MO.bekilled)
		if(!MC.bekilled&&!MO.kill)
			if(MO.getx()+6>=MC.getx()&&MO.getx()<=MC.getx()+4&&MO.gety()>=MC.gety()-2)
			{
				if(diecount<times_can_die)
				{MC.bekilled=1;diecount++;return 0;}
				MO.kill=1;
				//MC.bekilled=1;
				return 1;
			}	
	return 0;
}
void	dead()
{
	clear();
	refresh();
	deadwin();
	wrefresh(boxwin);
	usleep(3000000);
	clear();
	refresh();
	mvwprintw(boxwin,(linewidth+1)/2,(columnwidth+2)/2-9,"Your Final Score : %d",score);
	wrefresh(boxwin);
	usleep(3000000);
	endwin();
	//exit(1);
}
void	deadwin()
{
	mvwprintw(boxwin,0 ,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,1 ,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,2 ,0,"||||              |||||||||               ||||||||    |||||||||||||    |||||||                  ||||");
	mvwprintw(boxwin,3 ,0,"|||   ||||||||||   |||||||   |||||||||||   |||||||  |  |||||||||||  |  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,4 ,0,"|||  ||||||||||||  |||||||  |||||||||||||  |||||||  ||  |||||||||  ||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,5 ,0,"|||  |||||||||||||||||||||  |||||||||||||  |||||||  |||  |||||||  |||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,6 ,0,"|||  |||||||||||||||||||||  |||||||||||||  |||||||  ||||  |||||  ||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,7 ,0,"|||  |||||||||||||||||||||  |||||||||||||  |||||||  |||||  |||  |||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,8 ,0,"|||  ||||||       ||||||||                 |||||||  ||||||     ||||||  |||||||            ||||||||||");
	mvwprintw(boxwin,9 ,0,"|||  |||||||||||   |||||||  |||||||||||||  |||||||  |||||||||||||||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,10,0,"|||  ||||||||||||  |||||||  |||||||||||||  |||||||  |||||||||||||||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,11,0,"|||  ||||||||||||  |||||||  |||||||||||||  |||||||  |||||||||||||||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,12,0,"|||   ||||||||||   |||||||  |||||||||||||  |||||||  |||||||||||||||||  |||||||  ||||||||||||||||||||");
	mvwprintw(boxwin,13,0,"||||              ||||||||  |||||||||||||  |||||||  |||||||||||||||||  |||||||                  ||||");
	mvwprintw(boxwin,14,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,15,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,16,0,"||||              ||||||||  |||||||||||||  |||||||                     |||||||                 |||||");
	mvwprintw(boxwin,17,0,"|||   ||||||||||   |||||||  |||||||||||||  |||||||  ||||||||||||||||||||||||||  |||||||||||||   ||||");
	mvwprintw(boxwin,18,0,"|||  ||||||||||||  |||||||  |||||||||||||  |||||||  ||||||||||||||||||||||||||  ||||||||||||||  ||||");
	mvwprintw(boxwin,19,0,"|||  ||||||||||||  |||||||  |||||||||||||  |||||||  ||||||||||||||||||||||||||  ||||||||||||||  ||||");
	mvwprintw(boxwin,20,0,"|||  ||||||||||||  |||||||   |||||||||||   |||||||  ||||||||||||||||||||||||||  ||||||||||||||  ||||");
	mvwprintw(boxwin,21,0,"|||  ||||||||||||  ||||||||   |||||||||   ||||||||  ||||||||||||||||||||||||||  |||||||||||||   ||||");
	mvwprintw(boxwin,22,0,"|||  ||||||||||||  |||||||||   |||||||   |||||||||             |||||||||||||||                 |||||");
	mvwprintw(boxwin,23,0,"|||  ||||||||||||  ||||||||||  |||||||  ||||||||||  ||||||||||||||||||||||||||  ||||||  ||||||||||||");
	mvwprintw(boxwin,24,0,"|||  ||||||||||||  |||||||||||  |||||  |||||||||||  ||||||||||||||||||||||||||  |||||||   ||||||||||");
	mvwprintw(boxwin,25,0,"|||  ||||||||||||  ||||||||||||  |||  ||||||||||||  ||||||||||||||||||||||||||  ||||||||   |||||||||");
	mvwprintw(boxwin,26,0,"|||   ||||||||||   |||||||||||||  |  |||||||||||||  ||||||||||||||||||||||||||  ||||||||||   |||||||");
	mvwprintw(boxwin,27,0,"||||              |||||||||||||||   ||||||||||||||                     |||||||  ||||||||||||      ||");
	mvwprintw(boxwin,28,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,29,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}   
void	startwin()
{
	mvwprintw(boxwin,0 ,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,1 ,0,"|||             ||||||              ||||||               ||||||             |||||||             ||||");
	mvwprintw(boxwin,2 ,0,"|||  |||||||||   |||||  ||||||||||   |||||  ||||||||||||||||||   |||||||||   |||||   |||||||||   |||");
	mvwprintw(boxwin,3 ,0,"|||  ||||||||||  |||||  |||||||||||  |||||  |||||||||||||||||||  ||||||||||||||||||  |||||||||||||||");
	mvwprintw(boxwin,4 ,0,"|||  |||||||||   |||||  ||||||||||   |||||  ||||||||||||||||||||   |||||||||||||||||   |||||||||||||");
	mvwprintw(boxwin,5 ,0,"|||             ||||||              ||||||          |||||||||||||     |||||||||||||||     ||||||||||");
	mvwprintw(boxwin,6 ,0,"|||  |||||||||||||||||  |||||  |||||||||||  ||||||||||||||||||||||||      ||||||||||||||      ||||||");
	mvwprintw(boxwin,7 ,0,"|||  |||||||||||||||||  ||||||  ||||||||||  |||||||||||||||||||||||||||    ||||||||||||||||    |||||");
	mvwprintw(boxwin,8 ,0,"|||  |||||||||||||||||  |||||||  |||||||||  ||||||||||||||||||||||||||||||  ||||||||||||||||||  ||||");
	mvwprintw(boxwin,9 ,0,"|||  |||||||||||||||||  ||||||||  ||||||||  ||||||||||||||||||   |||||||||   |||||   |||||||||   |||");
	mvwprintw(boxwin,10,0,"|||  |||||||||||||||||  |||||||||     ||||               ||||||             |||||||             ||||");
	mvwprintw(boxwin,11,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,12,0,"||||||||||||||||||||||||||||||||||          ||||||||||         |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,13,0,"||||||||||||||||||||||||||||||||||||||  ||||||||||||||  |||||  |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,14,0,"||||||||||||||||||||||||||||||||||||||  ||||||||||||||  |||||  |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,15,0,"||||||||||||||||||||||||||||||||||||||  ||||||||||||||  |||||  |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,16,0,"||||||||||||||||||||||||||||||||||||||  ||||||||||||||  |||||  |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,17,0,"||||||||||||||||||||||||||||||||||||||  ||||||||||||||         |||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,18,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,19,0,"||||             |||||               ||||||             ||||||              ||||||               |||");
	mvwprintw(boxwin,20,0,"|||   |||||||||   ||||||||||   |||||||||||   |||||||||   |||||  ||||||||||   |||||||||||   |||||||||");
	mvwprintw(boxwin,21,0,"||||  ||||||||||||||||||||||   |||||||||||  |||||||||||  |||||  |||||||||||  |||||||||||   |||||||||");
	mvwprintw(boxwin,22,0,"|||||   ||||||||||||||||||||   |||||||||||  |||||||||||  |||||  ||||||||||   |||||||||||   |||||||||");
	mvwprintw(boxwin,23,0,"||||||     |||||||||||||||||   |||||||||||  |||||||||||  |||||              ||||||||||||   |||||||||");
	mvwprintw(boxwin,24,0,"|||||||||      |||||||||||||   |||||||||||               |||||  |||||  |||||||||||||||||   |||||||||");
	mvwprintw(boxwin,25,0,"||||||||||||    ||||||||||||   |||||||||||  |||||||||||  |||||  ||||||  ||||||||||||||||   |||||||||");
	mvwprintw(boxwin,26,0,"|||||||||||||||  |||||||||||   |||||||||||  |||||||||||  |||||  |||||||  |||||||||||||||   |||||||||");
	mvwprintw(boxwin,27,0,"|||   |||||||||   ||||||||||   |||||||||||  |||||||||||  |||||  ||||||||  ||||||||||||||   |||||||||");
	mvwprintw(boxwin,28,0,"||||             |||||||||||   |||||||||||  |||||||||||  |||||  |||||||||     ||||||||||   |||||||||");
	mvwprintw(boxwin,29,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}    
void winwin()
{
	mvwprintw(boxwin,0 ,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,1 ,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,2 ,0,"|||||||||||||    ||||||||||    ||||||||||||||              |||||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,3 ,0,"||||||||||||||    ||||||||    ||||||||||||||   ||||||||||   ||||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,4 ,0,"|||||||||||||||    ||||||    ||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,5 ,0,"||||||||||||||||    ||||    |||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,6 ,0,"|||||||||||||||||    ||    ||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,7 ,0,"||||||||||||||||||        |||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,8 ,0,"|||||||||||||||||||      ||||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,9 ,0,"||||||||||||||||||||    |||||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,10,0,"||||||||||||||||||||    |||||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,11,0,"||||||||||||||||||||    |||||||||||||||||||   ||||||||||||   |||||||||||||   ||||||||||   ||||||||||");
	mvwprintw(boxwin,12,0,"||||||||||||||||||||    ||||||||||||||||||||   ||||||||||   |||||||||||||||   ||||||||   |||||||||||");
	mvwprintw(boxwin,13,0,"||||||||||||||||||||    |||||||||||||||||||||              |||||||||||||||||            ||||||||||||");
	mvwprintw(boxwin,14,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,15,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,16,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,17,0,"||||||||||   ||||||||||     |||||||||||   ||||              ||||||||||      ||||||||   |||||||||||||");
	mvwprintw(boxwin,18,0,"|||||||||||   ||||||||        ||||||||   |||||              ||||||||||       |||||||   |||||||||||||");
	mvwprintw(boxwin,19,0,"|||||||||||   ||||||||   ||   ||||||||   ||||||||||    |||||||||||||||   |    ||||||   |||||||||||||");
	mvwprintw(boxwin,20,0,"||||||||||||   ||||||   ||||   ||||||   |||||||||||    |||||||||||||||   ||    |||||   |||||||||||||");
	mvwprintw(boxwin,21,0,"||||||||||||   ||||||   ||||   ||||||   |||||||||||    |||||||||||||||   |||    ||||   |||||||||||||");
	mvwprintw(boxwin,22,0,"|||||||||||||   ||||   ||||||   ||||   ||||||||||||    |||||||||||||||   ||||    |||   |||||||||||||");
	mvwprintw(boxwin,23,0,"|||||||||||||   ||||   ||||||   ||||   ||||||||||||    |||||||||||||||   |||||    ||   |||||||||||||");
	mvwprintw(boxwin,24,0,"||||||||||||||   ||   ||||||||   ||   |||||||||||||    |||||||||||||||   ||||||    |   |||||||||||||");
	mvwprintw(boxwin,25,0,"|||||||||||||||      ||||||||||      |||||||||              ||||||||||   |||||||       |||||||||||||");
	mvwprintw(boxwin,26,0,"||||||||||||||||    ||||||||||||    ||||||||||              ||||||||||   ||||||||      |||||||||||||");
	mvwprintw(boxwin,27,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,28,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
	mvwprintw(boxwin,29,0,"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}                                     