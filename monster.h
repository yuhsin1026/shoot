#ifndef MONSTER_H
#define MONSTER_H
#include <curses.h>
//MonsterOne
class MonsterOne
{
protected:	
	int		x,y,type;
	WINDOW *monsteronewin;
public:
    bool	kill;
	bool	bekilled;
	static int monCount;//how many monsterone builded
	MonsterOne();//random initial point
	MonsterOne(int,int,int);//set initial point
	virtual	void print();//showbody
	virtual	void monclear();
	void setX(int mv);//move x & determine type
	void setY(int mv);//move y & determine type
	void setType(int t){type=t;}
	void moveMO();//main
	
	virtual	void moveLeftDown();//move & clear & print
	virtual	void moveRightDown();
	virtual	void moveLeftUp();
	virtual	void moveRightUp();
	
	void	moveLeft();//move & clear & print
	virtual	void moveRight();
	virtual	void moveUp();
	void	moveDown();
	void	rebound(MonsterOne &);
	void	refresh(){wrefresh(monsteronewin);}
	int		getx()		{return x;}
	int		gety()		{return y;}
	int		gettype()	{return type;}
	void	free();
	WINDOW*	getwin()	{return monsteronewin;}
};
//MonsterTwo
class MonsterTwo :public MonsterOne
{
	public:
		MonsterTwo();
		MonsterTwo(int ,int ,int );
		void	print();
		void	monclear();
		void	moveLeftDown();
		void	moveRightDown();
		void	moveLeftUp();
		void	moveRightUp();
		void	moveUp();
		void	moveRight();	
		void	rebound(MonsterOne &);
		void	rebound(MonsterTwo &);
};
//MonsterThree
class MonsterThree : public MonsterOne
{
	public:
		MonsterThree();
		MonsterThree(int ,int ,int );
		void	print();
		void	monclear();
		void	moveLeftDown();
		void	moveRightDown();
		void	moveLeftUp();
		void	moveRightUp();
		void	moveUp();
		void	moveRight();	
		void	rebound(MonsterOne &);
		void	rebound(MonsterTwo &);
		void	rebound(MonsterThree &);
};

#endif
