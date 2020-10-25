#include "monster.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#define	linewidth	30
#define	columnwidth 100

using namespace std;
//MonsterOne
MonsterOne::MonsterOne()
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	bekilled=0;
	kill=0;
	//srand(time(NULL));
	//srand(0);
	x=rand()%90+10;
	y=rand()%15+3;
	type=rand()%8+1;
	//type=6;
	monCount++;
	refresh();
}
MonsterOne::MonsterOne(int X,int Y,int TYPE)
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	bekilled=0;
	kill=0;
	//srand(time(NULL));
	x=X;
	y=Y;
	type=TYPE;
	monCount++;
	refresh();
}
void	MonsterOne::free()
{
	monsteronewin=NULL;
}
void MonsterOne::print()
{
	if(!bekilled)
		mvwprintw(monsteronewin,y,x,"O");
	else
		monclear();
}
void MonsterOne::monclear()
{
	mvwprintw(monsteronewin,y,x," ");
}
void MonsterOne::setX(int mv)
{
	if(x>=1&&x<=columnwidth)
		x+=mv;
}
void MonsterOne::setY(int mv)
{
	if(y>=0&&y<=linewidth)
		y+=mv;
}
void MonsterOne::moveMO()
{
	if(type==1)
		moveLeftDown();
	if(type==2)
		moveRightDown();
	if(type==3)
		moveRightUp();
	if(type==4)
		moveLeftUp();
	if(type==5)
		moveLeft();
	if(type==6)
		moveRight();
	if(type==7)
		moveUp();
	if(type==8)
		moveDown();
}
void MonsterOne::moveLeftDown()
{
	monclear();
	setX(-1);
	setY(1);
	if(y==linewidth)
		type=4;
	if(x==1)
		type=2;
	if(y==linewidth&&x==1)
		type=3;	
	print();
	refresh();
}
void MonsterOne::moveRightDown()
{
	monclear();
	setX(1);
	setY(1);
	if(y==linewidth)
		type=3;
	if(x==columnwidth-1)
		type=1;
	if(y==linewidth&&x==columnwidth-1)
		type=4;	
	print();
	refresh();
}
void MonsterOne::moveLeftUp()
{
	monclear();
	setX(-1);
	setY(-1);
	if(y==0)
		type=1;
	if(x==1)
		type=3;
	if(y==0&&x==1)
		type=2;
	print();
	refresh();
}
void MonsterOne::moveRightUp()
{
	monclear();
	setX(1);
	setY(-1);
	if(y==0)
		type=2;
	if(x==columnwidth-1)
		type=4;
	if(x==columnwidth-1&&y==0)
		type=1;
	print();
	refresh();
}
void MonsterOne::moveLeft()
{
	monclear();
	setX(-1);
	setY(0);
	if(x==1)
		type=6;
	print();
	refresh();
}
void MonsterOne::moveRight()
{
	monclear();
	setX(1);
	setY(0);
	if(x==columnwidth-1)
		type=5;
	print();
	refresh();
}
void MonsterOne::moveUp()
{
	monclear();
	setX(0);
	setY(-1);
	if(y==0)
		type=8;
	print();
	refresh();
}
void MonsterOne::moveDown()
{
	monclear();
	setX(0);
	setY(1);
	if(y==linewidth-1)
		type=7;
	print();
	refresh();
}

void MonsterOne::rebound(MonsterOne & M1)
{
	if(bekilled==0&&M1.bekilled==0)
		if(x==M1.getx()&&y==M1.gety())
		{	
			if((type==5||type==6||type==7||type==8)&&(M1.gettype()==1||M1.gettype()==2||M1.gettype()==3||M1.gettype()==4))
				{M1.rebound(*this);return;}
			if(type==1&&M1.gettype()==5)
				{type=4; M1.setType(5);}
			if(type==1&&M1.gettype()==6)
				{type=2; M1.setType(5);}
			if(type==1&&M1.gettype()==7)
				{type=4; M1.setType(8);}
			if(type==1&&M1.gettype()==8)
				{type=2; M1.setType(8);}
			if(type==2&&M1.gettype()==5)
				{type=1; M1.setType(6);}
			if(type==2&&M1.gettype()==6)
				{type=3; M1.setType(6);}
			if(type==2&&M1.gettype()==7)
				{type=3; M1.setType(8);}
			if(type==2&&M1.gettype()==8)
				{type=1; M1.setType(8);}
			if(type==3&&M1.gettype()==5)
				{type=4; M1.setType(6);}
			if(type==3&&M1.gettype()==6)
				{type=2; M1.setType(6);}
			if(type==3&&M1.gettype()==7)
				{type=4; M1.setType(7);}
			if(type==3&&M1.gettype()==8)
				{type=2; M1.setType(7);}
			if(type==4&&M1.gettype()==5)
				{type=1; M1.setType(5);}
			if(type==4&&M1.gettype()==6)
				{type=3; M1.setType(5);}
			if(type==4&&M1.gettype()==7)
				{type=3; M1.setType(7);}
			if(type==4&&M1.gettype()==8)
				{type=1; M1.setType(7);}
		}
}

//MonsterTwo
MonsterTwo::MonsterTwo()
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	//MonsterOne::monCount--;
	bekilled=0;
	kill=0;
	x=rand()%80+10;
	y=rand()%15+5;
	type=rand()%2+3;
	refresh();
}
MonsterTwo::MonsterTwo(int X,int Y,int TYPE)
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	//MonsterOne::monCount--;
	bekilled=0;
	kill=0;
	//srand(time(NULL));
	x=X;
	y=Y;
	type=TYPE;
	refresh();
}
void MonsterTwo::print()
{
	if(!bekilled)
	{
	    mvwprintw(monsteronewin,y-2,x," ___ ");
		mvwprintw(monsteronewin,y-1,x,"|   |");
	    mvwprintw(monsteronewin,y-0,x,"|___|");
	}
	else
		monclear();
}
void MonsterTwo::monclear()
{
	mvwprintw(monsteronewin,y-2,x,"     ");
	mvwprintw(monsteronewin,y-1,x,"     ");
	mvwprintw(monsteronewin,y-0,x,"     ");
}
void MonsterTwo::moveRightDown()
{
	monclear();
	setX(1);
	setY(1);
	if(y==linewidth||y==linewidth-1)
		type=3;
	if(x==columnwidth-5||x==columnwidth-4)
		type=1;
	if((y==linewidth||y==linewidth-1)&&(x==columnwidth-5||x==columnwidth-4))
		type=4;
	print();
	refresh();
}
void MonsterTwo::moveLeftUp()
{
	monclear();
	setX(-1);
	setY(-1);
	if(y==2||y==1)
		type=1;
	if(x==1||x==0)
		type=3;
	if((x==1||x==0)&&(y==2||y==1))
		type=2;
	print();
	refresh();
}
void MonsterTwo::moveLeftDown()
{
	monclear();
	setX(-1);
	setY(1);
	if(y==30||y==29)
		type=4;
	if(x==1||x==0)
		type=2;
	if((y==30||y==29)&&(x==1||x==0))
		type=3;	
	print();
	refresh();
}
void MonsterTwo::moveRightUp()
{
	monclear();
	setX(1);
	setY(-1);
	if(y==2||y==1)
		type=2;
	if(x==columnwidth-4||x==columnwidth-5)
		type=4;
	if((x==columnwidth-4||x==columnwidth-5)&&(y==2||y==1))
		type=1;
	print();
	refresh();
}
void MonsterTwo::moveUp()
{
	monclear();
	setY(-1);
	if(y==1)
		type=8;
	print();
	refresh();
}
void MonsterTwo::moveRight()
{
	monclear();
	setX(1);
	if(x==columnwidth-5)
		type=5;
	print();
	refresh();
}

void MonsterTwo::rebound(MonsterOne & M1)
{
	if(bekilled==0&&M1.bekilled==0)
	{	
		if(M1.gety()<=y&&M1.gety()>=y-2&&(M1.getx()==x-1||M1.getx()==x||M1.getx()==x+1))//left side
		{	
			if(M1.gettype()==6)
				M1.setType(5);
			if(M1.gettype()==2)
				M1.setType(1);
			if(M1.gettype()==3)
				M1.setType(4);
			if((type==2||type==3)&&(M1.gettype()==7||M1.gettype()==8))
				M1.setType(6);
		}
		if(M1.gety()<=y+1&&M1.gety()>=y-2&& (M1.getx()==x+5||M1.getx()==x+4||M1.getx()==x+3))//right side
		{	
			if(M1.gettype()==1)
				M1.setType(2);
			if(M1.gettype()==5)
				M1.setType(6);
			if(M1.gettype()==4)
				M1.setType(3);
			if((type==1||type==4)&&(M1.gettype()==7||M1.gettype()==8))
				M1.setType(5);
		}
		if(M1.getx()>=x-1&&M1.getx()<=x+5&&(M1.gety()==y-3||M1.gety()==y-2||M1.gety()==y-1))//up side
		{	
			if(M1.gettype()==2)
				M1.setType(3);
			if(M1.gettype()==8)
				M1.setType(7);
			if(M1.gettype()==1)
				M1.setType(4);
			if((type==3||type==4)&&(M1.gettype()==6||M1.gettype()==5))
				M1.setType(7);
		}
		if(M1.getx()>=x-1&&M1.getx()<=x+5&&(M1.gety()==y+1||M1.gety()==y+2||M1.gety()==y))//down side
		{	
			if(M1.gettype()==3)
				M1.setType(2);
			if(M1.gettype()==7)
				M1.setType(8);
			if(M1.gettype()==4)
				M1.setType(1);
			if((type==1||type==2)&&(M1.gettype()==6||M1.gettype()==5))
				M1.setType(8);
		}
	}
}

void MonsterTwo::rebound(MonsterTwo & M1)
{
	if(bekilled==0&&M1.bekilled==0)
	{
		if(type==1&&M1.gettype()==2)
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-2<=y&&M1.gety()>y-2)//left
				{type=2; M1.setType(1);}
		if(type==1&&M1.gettype()==3)
		{
			if((M1.gety()-2==y+1||M1.gety()-2==y+2||M1.gety()-2==y)&&M1.getx()+4>=x&&M1.getx()<=x+4)//down
			{type=4; M1.setType(2);}
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-2<=y&&M1.gety()>y-2)//left
			{type=2; M1.setType(4);}
		}
		if(type==1&&M1.gettype()==4)
			if((M1.gety()-2==y+1||M1.gety()-2==y+2||M1.gety()-2==y)&&M1.getx()+4>=x&&M1.getx()<=x+4)//down
				{type=4; M1.setType(1);}
		
		if(type==2&&M1.gettype()==1)
			if((M1.getx()==x+5||M1.getx()==x+4||M1.getx()==x+3)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
				{type=1; M1.setType(2);}
		if(type==2&&M1.gettype()==3)
			if((M1.gety()-2==y+1||M1.gety()-2==y+2||M1.gety()-2==y)&&M1.getx()+4>=x&&M1.getx()<=x+4)//down
				{type=3; M1.setType(2);}
		if(type==2&&M1.gettype()==4)
		{
			if((M1.gety()-2==y+1||M1.gety()-2==y+2||M1.gety()-2==y)&&M1.getx()+4>=x&&M1.getx()<=x+4)//down
			{type=3; M1.setType(1);}
			if((M1.getx()==x+5||M1.getx()==x+4||M1.getx()==x+3)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
			{type=1; M1.setType(3);}
		}
		
		if(type==3&&M1.gettype()==1)
		{	
			if((M1.gety()==y-3||M1.gety()==y-2||M1.gety()==y-1)&&M1.getx()+4>=x&&M1.getx()<=x+4)//up
			{type=2; M1.setType(4);}
			if((M1.getx()==x+5||M1.getx()==x+4||M1.getx()==x+3)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
			{type=4; M1.setType(2);}
		}
		if(type==3&&M1.gettype()==2)
			if((M1.gety()==y-3||M1.gety()==y-2||M1.gety()==y-1)&&M1.getx()+4>=x&&M1.getx()<=x+4)//up
				{type=2; M1.setType(3);}
		if(type==3&&M1.gettype()==4)
			if((M1.getx()==x+5||M1.getx()==x+4||M1.getx()==x+3)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
				{type=4; M1.setType(3);}
		
		
		if(type==4&&M1.gettype()==1)
			if((M1.gety()==y-3||M1.gety()==y-2||M1.gety()==y-1)&&M1.getx()+4>=x&&M1.getx()<=x+4)//up
				{type=1; M1.setType(4);}
		if(type==4&&M1.gettype()==2)
		{
			if((M1.gety()==y-3||M1.gety()==y-2||M1.gety()==y-1)&&M1.getx()+4>=x&&M1.getx()<=x+4)//up
			{type=1; M1.setType(3);}
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-2<=y&&M1.gety()>y-2)//left
			{type=3; M1.setType(1);}
		}
		if(type==4&&M1.gettype()==3)
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-2<=y&&M1.gety()>y-2)//left
				{type=3; M1.setType(4);}
	}
}

//MonsterThree
MonsterThree::MonsterThree()
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	bekilled=0;
	x=rand()%80+10;
	y=rand()%15+5;
	type=rand()%2+3;
	//MonsterOne::monCount--;
	refresh();
}
MonsterThree::MonsterThree(int X,int Y,int TYPE)
{
	monsteronewin=newwin(linewidth,columnwidth,1,1);
	//MonsterOne::monCount--;
	bekilled=0;
	kill=0;
	//srand(time(NULL));
	x=X;
	y=Y;
	type=TYPE;
	refresh();
}
void MonsterThree::print()
{
	if(!bekilled)
	{
	    mvwprintw(monsteronewin,y-3,x," _____ ");
		mvwprintw(monsteronewin,y-2,x,"|     |");
		mvwprintw(monsteronewin,y-1,x,"|     |");
	    mvwprintw(monsteronewin,y-0,x,"|_____|");
	}
	else
		monclear();
}
void MonsterThree::monclear()
{
	mvwprintw(monsteronewin,y-3,x,"       ");
	mvwprintw(monsteronewin,y-2,x,"       ");
	mvwprintw(monsteronewin,y-1,x,"       ");
	mvwprintw(monsteronewin,y-0,x,"       ");
}
void MonsterThree::moveRightDown()
{
	monclear();
	setX(1);
	setY(1);
	if(y==30||y==29)
		type=3;
	if(x==94||x==93)
		type=1;
	if((y==30||y==29)&&(x==94||x==93))
		type=4;
	print();
	refresh();
}
void MonsterThree::moveLeftUp()
{
	monclear();
	setX(-1);
	setY(-1);
	if(y==3||y==2)
		type=1;
	if(x==1||x==0)
		type=3;
	if((y==3||y==2)&&(x==1||x==0))
		type=2;
	print();
	refresh();
}
void MonsterThree::moveLeftDown()
{
	monclear();
	setX(-1);
	setY(1);
	if(y==30||y==29)
		type=4;
	if(x==1||x==0)
		type=2;
	if((y==30||y==29)&&(x==1||x==0))
		type=3;	
	print();
	refresh();
}
void MonsterThree::moveRightUp()
{
	monclear();
	setX(1);
	setY(-1);
	if(y==3||y==2)
		type=2;
	if(x==94||x==93)
		type=4;
	if((x==94||x==93)&&(y==3||y==2))
		type=1;
	print();
	refresh();
}
void MonsterThree::moveUp()
{
	monclear();
	setY(-1);
	if(y==3)
		type=6;
	print();
	refresh();
}
void MonsterThree::moveRight()
{
	monclear();
	setX(1);
	if(x==94||x==93)
		type=7;
		print();
	refresh();
}
void MonsterThree::rebound(MonsterOne & M1)
{
	if(bekilled==0&&M1.bekilled==0)
	{	
        if(M1.gety()<=y&&M1.gety()>=y-3&&(M1.getx()==x-1))//left side
		{	
			if(M1.gettype()==6)
				M1.setType(5);
			if(M1.gettype()==2)
				M1.setType(1);
			if(M1.gettype()==3)
				M1.setType(4);
			if((type==1||type==4)&&(M1.gettype()==7||M1.gettype()==8))
				M1.setType(5);
		}
		if(M1.gety()<=y&&M1.gety()>=y-3&& (M1.getx()==x+8))//right side
		{	
			if(M1.gettype()==1)
				M1.setType(2);
			if(M1.gettype()==5)
				M1.setType(6);
			if(M1.gettype()==4)
				M1.setType(3);
			if((type==2||type==3)&&(M1.gettype()==7||M1.gettype()==8))
				M1.setType(6);
		}
		if(M1.getx()>=x&&M1.getx()<=x+7&&(M1.gety()==y-4||M1.gety()==y-3||M1.gety()==y-2))//up side
		{	
			if(M1.gettype()==2)
				M1.setType(3);
			if(M1.gettype()==8)
				M1.setType(7);
			if(M1.gettype()==1)
				M1.setType(4);
			if((type==3||type==4)&&(M1.gettype()==6||M1.gettype()==5))
				M1.setType(7);
		}
		if(M1.getx()>=x&&M1.getx()<=x+7&&(M1.gety()==y+1||M1.gety()==y+2||M1.gety()==y))//down side
		{	
			if(M1.gettype()==3)
				M1.setType(2);
			if(M1.gettype()==7)
				M1.setType(8);
			if(M1.gettype()==4)
				M1.setType(1);
			if((type==1||type==2)&&(M1.gettype()==6||M1.gettype()==5))
				M1.setType(8);
		}
	}
}
void MonsterThree::rebound(MonsterTwo & M1)
{
	if(bekilled==0&&M1.bekilled==0)
	{
		if(type==1&&M1.gettype()==2)
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=2; M1.setType(1);}
		if(type==1&&M1.gettype()==3)
		{
			if((M1.gety()-2==y||M1.gety()-2==y-1||M1.gety()-2==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=4; M1.setType(2);}
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=2; M1.setType(4);}
		}
		if(type==1&&M1.gettype()==4)
			if((M1.gety()-2==y||M1.gety()-2==y-1||M1.gety()-2==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=4; M1.setType(1);}
				
		if(type==2&&M1.gettype()==1)
			if((M1.getx()==x+5||M1.getx()==x+6||M1.getx()==x+7)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
				{type=1; M1.setType(2);}
		if(type==2&&M1.gettype()==3)
			if((M1.gety()-2==y||M1.gety()-2==y-1||M1.gety()-2==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=3; M1.setType(2);}
		if(type==2&&M1.gettype()==4)
		{
			if((M1.gety()-2==y||M1.gety()-2==y-1||M1.gety()-2==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
			{type=3; M1.setType(1);}
			if((M1.getx()==x+5||M1.getx()==x+6||M1.getx()==x+7)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
			{type=1; M1.setType(3);}
		}
		
		if(type==3&&M1.gettype()==1)
		{	
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
			{type=2; M1.setType(4);}
			if((M1.getx()==x+5||M1.getx()==x+7||M1.getx()==x+6)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
			{type=4; M1.setType(2);}
		}
		if(type==3&&M1.gettype()==2)
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
				{type=2; M1.setType(3);}
		if(type==3&&M1.gettype()==4)
			if((M1.getx()==x+5||M1.getx()==x+7||M1.getx()==x+6)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
				{type=4; M1.setType(3);}
				
		if(type==4&&M1.gettype()==1)
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
				{type=1; M1.setType(4);}
		if(type==4&&M1.gettype()==2)
		{
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
			{type=1; M1.setType(3);}
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
			{type=3; M1.setType(1);}
		}
		if(type==4&&M1.gettype()==3)
			if((M1.getx()+4==x-1||M1.getx()+4==x||M1.getx()+4==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=3; M1.setType(4);}
	}
}

void MonsterThree::rebound(MonsterThree & M1)
{
	if(bekilled==0&&M1.bekilled==0)
	{
		if(type==1&&M1.gettype()==2)
			if((M1.getx()+6==x-1||M1.getx()+6==x||M1.getx()+6==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=2; M1.setType(1);}
		if(type==1&&M1.gettype()==3)
		{
			if((M1.gety()-3==y||M1.gety()-3==y-1||M1.gety()-3==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=4; M1.setType(2);}
			if((M1.getx()+6==x-1||M1.getx()+6==x||M1.getx()+6==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=2; M1.setType(4);}
		}
		if(type==1&&M1.gettype()==4)
			if((M1.gety()-3==y||M1.gety()-3==y-1||M1.gety()-3==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=4; M1.setType(1);}
				
		if(type==2&&M1.gettype()==1)
			if((M1.getx()==x+5||M1.getx()==x+6||M1.getx()==x+7)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
				{type=1; M1.setType(2);}
		if(type==2&&M1.gettype()==3)
			if((M1.gety()-3==y||M1.gety()-3==y-1||M1.gety()-3==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
				{type=3; M1.setType(2);}
		if(type==2&&M1.gettype()==4)
		{
			if((M1.gety()-3==y||M1.gety()-3==y-1||M1.gety()-3==y+1)&&M1.getx()+6>=x&&M1.getx()<=x+6)//down
			{type=3; M1.setType(1);}
			if((M1.getx()==x+5||M1.getx()==x+6||M1.getx()==x+7)&&M1.gety()-2<=y&&M1.gety()>y-2)//right
			{type=1; M1.setType(3);}
		}
		
		if(type==3&&M1.gettype()==1)
		{	
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
			{type=2; M1.setType(4);}
			if((M1.getx()==x+5||M1.getx()==x+7||M1.getx()==x+6)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
			{type=4; M1.setType(2);}
		}
		if(type==3&&M1.gettype()==2)
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
				{type=2; M1.setType(3);}
		if(type==3&&M1.gettype()==4)
			if((M1.getx()==x+5||M1.getx()==x+7||M1.getx()==x+6)&&M1.gety()-3<=y&&M1.gety()>y-3)//right
				{type=4; M1.setType(3);}
				
		if(type==4&&M1.gettype()==1)
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
				{type=1; M1.setType(4);}
		if(type==4&&M1.gettype()==2)
		{
			if((M1.gety()==y-3||M1.gety()==y-4||M1.gety()==y-2)&&M1.getx()+6>=x&&M1.getx()<=x+6)//up
			{type=1; M1.setType(3);}
			if((M1.getx()+6==x-1||M1.getx()+6==x||M1.getx()+6==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
			{type=3; M1.setType(1);}
		}
		if(type==4&&M1.gettype()==3)
			if((M1.getx()+6==x-1||M1.getx()+6==x||M1.getx()+6==x+1)&&M1.gety()-3<=y&&M1.gety()>y-3)//left
				{type=3; M1.setType(4);}
	}
}