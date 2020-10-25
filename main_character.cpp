//main_character.cpp
#include "main_character.h"
#include <unistd.h>

me::me()
{
	x=0;	y=linewidth-1;	gunpos=3; bekilled=0;
	//mewin=newwin(linewidth,columnwidth,1,1);
	//showbody();
	//showgun();
	//wrefresh(mewin);
}

void	me::showbody()
{
	mvwprintw(mewin,y-2,x+1,"_ _");
	mvwprintw(mewin,y-1,x,"/   \\");
	mvwprintw(mewin,y,x,"\\___/");
}

void	me::showgun()
{
	if(gunpos==1)
	{	
		mvwprintw(mewin,y-2,x+2,"_");
		mvwprintw(mewin,y-1,x-1,"_");
	}
	if(gunpos==2)
		mvwprintw(mewin,y-2,x+2,"|");
	if(gunpos==3)
	{	
		mvwprintw(mewin,y-2,x+2,"_");
		mvwprintw(mewin,y-1,x+5,"_");
	}
}

void	me::clear()
{
	mvwprintw(mewin,y-2,x+1,"   ");
	mvwprintw(mewin,y-1,x,"     ");
	mvwprintw(mewin,y,x,"     ");
	if(gunpos==1)
	{	
		mvwprintw(mewin,y-2,x+2," ");
		mvwprintw(mewin,y-1,x-1," ");
	}
	if(gunpos==2)
		mvwprintw(mewin,y-2,x+2," ");
	if(gunpos==3)
	{	
		mvwprintw(mewin,y-2,x+2," ");
		mvwprintw(mewin,y-1,x+5," ");
	}
}




void	me::bodygoright()
{
	clear();
	x=(x<columnwidth-5)?x+1:x;
	showbody();
	showgun();
	wrefresh(mewin);
}

void	me::bodygoleft()
{
	clear();
	x=(x>0)?x-1:x;
	showbody();
	showgun();
	wrefresh(mewin);
}

void	me::gunright()
{
	gunpos=3;
	clear();
	showbody();
	showgun();
	wrefresh(mewin);
	shoot();
	
}

void	me::gunleft()
{
	gunpos=1;
	clear();
	showbody();
	showgun();
	wrefresh(mewin);
	shoot();
}

void	me::gunup()
{
	gunpos=2;
	clear();
	showbody();
	showgun();
	wrefresh(mewin);
	shoot();
}

void	me::shoot()
{
	b.push_back(new bullet);	
	if(gunpos==1)
	{
		b[bullet::count++]->set(x-2,y-1,1);
		//mvwprintw(bulletwin,y-1,x-2,"_");
		//by =y-1; bx=x-2;
	}	
	if(gunpos==2)
	{
		b[bullet::count++]->set(x+2,y-3,2);
		//mvwprintw(bulletwin,y-3,x+2,"|");
		//by =y-3; bx=x+2;
	}
	if(gunpos==3)
	{
		b[bullet::count++]->set(x+6,y-1,3);
		//mvwprintw(bulletwin,y-1,x+6,"_");
		//by =y-1; bx=x+6;
	}
	
	showbody();
	showgun();
	wrefresh(mewin);
	for(int i=0;i<bullet::count;i++)
	{	
		b[i]->show();	
		b[i]->refresh();
	}		
}
void	bullet::show()
{
	if(!done)
	{	
		if(type==1||type==3)
			mvwprintw(bulletwin,y,x,"_");
		if(type==2)
			mvwprintw(bulletwin,y,x,"|");
	}
	else
		mvwprintw(bulletwin,y,x," ");
}
void	bullet::move()
{
	if(!done)
	{	
		if(type==1)
		{
			mvwprintw(bulletwin,y,x--," ");
			mvwprintw(bulletwin,y,x,"_");
		}	
		if(type==2)
		{
			mvwprintw(bulletwin,y--,x," ");
			mvwprintw(bulletwin,y,x,"|");
		}
		if(type==3)
		{
			mvwprintw(bulletwin,y,x++," ");
			mvwprintw(bulletwin,y,x,"_");
		}
	}	
	else
		mvwprintw(bulletwin,y,x++," ");
}
void	me::free()
{
	for (i = b.begin(); i != b.end();)
	{
		if ((*i)->getx()<0||(*i)->getx()>columnwidth+10||(*i)->gety()<-3||(*i)->gety()>linewidth+10)
		{	
			(*i)->free();
			b.erase(i);    // 使用 erase ，並將回傳值給 iterator i
		}
		else
			i++;
	}
}
void	me::allmove()
{
	if(bullet::velocity==40)
	{	
		for(int i=0;i<bullet::count;i++)	
			b[i]->move();
		for(int i=0;i<bullet::count;i++)
			b[i]->refresh();
		//wrefresh(mewin);
		bullet::velocity=0;
	}
	bullet::velocity++;
}
bullet::bullet()
{
	bulletwin=newwin(linewidth,columnwidth,1,1);
	wrefresh(bulletwin);
	done=0;
}
void	bullet::free()
{
	count--;
	//mvwprintw(bulletwin,0,(columnwidth+2)/2-8,"count = %d",count);
	//refresh();
	bulletwin=NULL;
}