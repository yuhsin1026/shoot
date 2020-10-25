//main_character.h
#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H
#include <curses.h>
#include <ctime>
#include <vector>
#define	linewidth	30
#define	columnwidth 100
class bullet
{
	public:
		bullet();
		~bullet();
		void	free();
		void	set(int b_x,int b_y,int pos)	{x=b_x;y=b_y;type=pos;}
		int		getx()	{return x;}
		int		gety()	{return y;}
		void	refresh(){wrefresh(bulletwin);}
		void	move();
		void	show();
		static 	int count;
		static	int	velocity;
		bool	done;
	private:
		int x;
		int y;
		int type; // 1 or 2 or 3 according to gunpos
		WINDOW	*bulletwin;		//bullet's window
};
class me
{
	public:
		me();
		void	free();
		void	New(){mewin=newwin(linewidth,columnwidth,1,1);}
		void	showbody();		//show main_character's body on screen
		void	showgun();		//show main_character's gun on screen
		void	clear();
		void	bodygoright();	//
		void	bodygoleft();	//
		void	gunright();		//
		void	gunleft();		//
		void	gunup();		//
		void	shoot();		//
		void	refresh(){wrefresh(mewin);}
		void	allmove();
		int		getx()	{return x;}
		int		gety()	{return y;}
		std::vector 	<bullet*> b;
		std::vector		<bullet*>::iterator i;
		bool	bekilled;
	private:
		WINDOW	*mewin;  		//main character's window1
		int	gunpos;
		int	x;
		int	y;
		
};
#endif