#include "characters.h"
#include <locale>

// 初始化静态成员
std::vector<Character*> Character::allCharacters;
std::vector<Character*> Character::allyCharacters;
std::vector<Character*> Character::enemyCharacters;



//人物类构造函数
Character::Character(int a, int b, int c, int d, string e, int f, int g, int atk, int h, int i, double atkRan, Kind kin, Faction j)
{
	isdeath = false; 
	chang = a;
	kuan = b;
	mx = (c / 32) * 32 + 16;
	my = (d / 32) * 32 + 16;
	gobackX = mx;
	gobackY = my;
	name = e;  //角色名字
	life = f;   //角色生命值
	energy = g; //角色体力
	ATK = atk;  //角色攻击力
	movement = h; //角色移动力
	agility = i;  //角色敏捷
	atkran = atkRan;//角色攻击范围
	kind = kin;  //角色职业
	faction = j;  //角色阵营
	if (this->kind == Kind::common)
	{
		if (this->faction == Faction::ally)
		{
			//载入步兵贴图
			loadimage(&common1_image, _T("C:\\Users\\DELL\\Desktop\\common1.png"), 33, 33);
			this->character_img = common1_image;
		}
		else
		{
			//载入步兵贴图
			loadimage(&common2_image, _T("C:\\Users\\DELL\\Desktop\\common2.png"), 33, 33);
			this->character_img = common2_image;
		}
	}
	else if(this->kind == Kind::medic)
	{
		if (this->faction == Faction::ally)
		{
			//载入医疗兵贴图
			loadimage(&medic1_image, _T("C:\\Users\\DELL\\Desktop\\medic1.png"), 33, 33);
			this->character_img = medic1_image;
		}
		else
		{
			//载入医疗兵贴图
			loadimage(&medic2_image, _T("C:\\Users\\DELL\\Desktop\\medic2.png"), 33, 33);
			this->character_img = medic2_image;
		}
	}
	else if(this->kind == Kind::sniper)
	{
		if (this->faction == Faction::ally)
		{
			//载入狙击手贴图
			loadimage(&sniper1_image, _T("C:\\Users\\DELL\\Desktop\\sniper1.png"), 33, 33);
			this->character_img = sniper1_image;
		}
		else
		{
			//载入狙击手贴图
			loadimage(&sniper2_image, _T("C:\\Users\\DELL\\Desktop\\sniper2.png"), 33, 33);
			this->character_img = sniper2_image;
		}
	}
	else
	{

	}
	allCharacters.push_back(this); // 将该角色添加到全局数组
	if (j == Faction::ally)
	{
		allyCharacters.push_back(this);
	}
	else
	{
		enemyCharacters.push_back(this);
	}
}

//死亡函数
void Character::death()
{
	//还原角色所在背景
	IMAGE a = wholebk0;
	BeginBatchDraw();
	putimage(0, 0, &wholebk0);
	getimage(&a, mx - chang / 2, my - kuan / 2, chang, kuan);
	putimage(0, 0, &wholebk);
	putimage(mx - chang / 2, my - kuan / 2, &a);
	getimage(&wholebk, 0, 0, getwidth(), getheight());
	EndBatchDraw();

	//从全体数组中移除自身
	auto it = std::find(allCharacters.begin(), allCharacters.end(), this);
	if (it != allCharacters.end()) 
	{
		allCharacters.erase(it);
	}
	//从我方数组中移除自身（如果是我方）
	it = std::find(allyCharacters.begin(), allyCharacters.end(), this);
	if (it != allyCharacters.end())
	{
		allyCharacters.erase(it);
	}
	//从敌方数组中移除自身（如果是敌方）
	it = std::find(enemyCharacters.begin(), enemyCharacters.end(), this);
	if (it != enemyCharacters.end())
	{
		enemyCharacters.erase(it);
	}
	isdeath = true;
}

//给出mx
 int Character::getmx()
{
	 return mx;
}
	
//给出my	
 int Character::getmy()
 {
	 return my;
 }

 //给出gobackX
 int Character::getgobackX()
 {
	 return gobackX;
 }

 //给出gobackY
 int Character::getgobackY()
 {
	 return gobackY;
 }

//给出chang
int Character:: getchang()
{
		return chang;
}
//给出kuan
int Character::getkuan()
	{
		return kuan;
	}

//给出右边界
int Character::getright()
{
	return mx + chang / 2;
}
//给出上边界
int Character::gettop()
{
	return my - kuan / 2;
}

Kind Character::getkind()
{
	if (kind == Kind::common)
	{
		return Kind::common;
	}
	else if (kind == Kind::medic)
	{
		return Kind::medic;
	}
	else if (kind == Kind::sniper)
	{
		return Kind::sniper;
	}
}

string Character::getkindname()
{
	if (kind == Kind::common)
	{
		return "步兵";
	}
	else if (kind == Kind::medic)
	{
		return "医疗兵";
	}
	else if (kind == Kind::sniper)
	{
		return "狙击手";
	}
}

int Character::getATK()
{
	return ATK;
}

int Character::getATKran()
{
	return int(atkran);
}

Faction Character::getfaction()
{
	return faction;
}
string Character::getfactionname()
{
	if (this->faction == Faction::ally)
	{
		return "玩家1";
	}
	else
	{
		return "玩家2";
	}	
}
string Character::getname()
{
	return name;
}
int Character::getlife()
{
	return life;
}
int Character::getenergy()
{
	return energy;
}
int Character::getmovement()
{
	return movement;
}
int Character::getagility()
{
	return agility;
}

//设置mx
void Character::setmx(int a)
{
	mx = a;
}
//设置my
void Character::setmy(int a)
{
	my = a;
}
//新的回合设置所有我（敌）方的roundmov与rounddone为false，角色体力加1
void Character::setroundval(Faction f, bool TorF) 
{
	//筛选器
	std::vector<Character*> filteredCharacters; 

	if (f == Faction::ally) 
	{
		std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
			[](Character* c) { return c->faction == Faction::ally; });
		for (Character* c : filteredCharacters) 
		{
			if (TorF)
			{
				c->roundmov = true;
				c->rounddone = true;
			}
			else
			{
				c->roundmov = false;
				c->rounddone = false;
				if (c->energy < 10)
					c->energy++;
			}
		}
	}
	else if (f == Faction::enemy) 
	{
		std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
			[](Character* c) { return c->faction == Faction::enemy; });
		for (Character* c : filteredCharacters) 
		{
			if (TorF)
			{
				c->roundmov = true;
				c->rounddone = true;
			}
			else
			{
				c->roundmov = false;
				c->rounddone = false;
				if (c->energy < 10)
					c->energy++;
			}
		}
	}
}

//绘制人物
void Character::paintCharacter()
{
	putimage(mx - 16, my - 16, &character_img);
	getimage(&wholebk, 0, 0, getwidth(), getheight());
}

//人物移动
void Character::characmov(int x, int y)
{
	x = (x / 32) * 32 + 16;
	y = (y / 32) * 32 + 16;
		IMAGE bk = wholebk;
		IMAGE partimage = wholebk0;
		////////////////////////
		//人物移动前把背景设置为不含人物的背景
		putimage(0, 0, &wholebk0);
		getimage(&partimage, mx - chang / 2, my - kuan / 2, chang + 1, kuan + 1);
		putimage(0, 0, &wholebk);
		putimage(mx - chang / 2, my - kuan / 2, &partimage);
		//setfillcolor(LIGHTBLUE);
		//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
		getimage(&bk, 0, 0, getwidth(), getheight());   //当前bk为不含人物的背景
		////////////////////////
		if (mx == x && my == y)
		{
			BeginBatchDraw();
			//保持除移动人物外的一切不变
			putimage(0, 0, &bk);
			putimage(mx - 16, my - 16, &character_img);
			//setfillcolor(YELLOW);
			//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
			EndBatchDraw();
		}
		while (mx != x || my != y)
		{
			if (mx != x && my != y)
			{
				if (x > mx && y > my)
				{
					mx += 1;
					my += 1;
				}
				else if (x < mx && y > my)
				{
					mx -= 1;
					my += 1;
				}
				else if (x > mx && y < my)
				{
					mx += 1;
					my -= 1;
				}
				else if (x < mx && y < my)
				{
					mx -= 1;
					my -= 1;
				}
			}
			else if (mx != x && my == y)
			{
				if (x < mx)
				{
					mx -= 1;
				}
				else if (x > mx)
				{
					mx += 1;
				}
			}
			else if (mx == x && my != y)
			{
				if (y < my)
				{
					my -= 1;
				}
				else if (y > my)
				{
					my += 1;
				}
			}
			BeginBatchDraw();
			//保持除移动人物外的一切不变
			putimage(0, 0, &bk);
			putimage(mx - 16, my - 16, &character_img);
			//setfillcolor(YELLOW);
			//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //无填充矩形
			EndBatchDraw();
		}
		if (energy > 0)
			energy--;//体力减1
		getimage(&bk, 0, 0, getwidth(), getheight());
		wholebk = bk;
	
	
}
	//选中人物
	bool Character::isMouseInCharacter(int x, int y)
	{
		if ((x > mx - chang / 2 + 5 && x < mx + chang / 2 - 5) && (y > my - kuan / 2 + 5 && y < my + kuan / 2 - 5))
			return true;
		return false;
	}

	bool Character::allrounddone(Faction f)
	{
		std::vector<Character*> filteredCharacters;

		if (f == Faction::ally)
		{
			// 使用 std::copy_if 筛选出满足条件的对象
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::ally; });
			//如果该轮还有没行动的角色返回false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //全部我方角色已行动完毕
		}
		else if (f == Faction::enemy)
		{
			// 使用 std::copy_if 筛选出满足条件的对象
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::enemy; });
			//如果该轮还有没行动的角色返回false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //全部我方角色已行动完毕
		}

	}


	//攻击函数
    bool Character::attack(Character* a)
	{
		//srand(time(0)); // 设置随机数种子
		IMAGE temp;

		int TargetX = a->mx;
		int TargetY = a->my;
		// 计算横向和纵向的网格差
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// 计算欧几里得距离（网格单位）
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		int atk = ATK;//攻击力
		double missrate = double(a->getagility() - 1);//定义闪避几率 
		srand(time(0)); // 设置随机数种子

			if (energy == 0)//如果体力不足无法攻击
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//绘制提醒按钮
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //矩形
				drawText("角色体力不足", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;//角色此轮动作未结束
			}
			else//体力充足可以攻击
			{
				if (a->faction == this->faction && this != a)//不可以攻击友军
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //矩形
					drawText("不可以攻击友军", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else if (this == a)//不可以攻击自己
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //矩形
					drawText("不可以攻击自己", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else
				{
					if (gridDistance <= atkran)//进行攻击
					{
						if (rand() % 100 <= missrate)//远程攻击但是发生闪避
						{
							movline(1, wholebk);
								getimage(&temp, 0, 0, getwidth(), getheight());
								//绘制提醒按钮
								setfillcolor(WHITE);
								solidrectangle(560, 288, 715, 350); //矩形
								drawText("哎呀！没打中！", 580, 308);
								Sleep(700);
								putimage(0, 0, &temp);							
							rounddone = true;
							energy--;
							return true;
						}
						else//没有闪避，正常远程攻击
						{
							movline(1, wholebk);
							getimage(&temp, 0, 0, getwidth(), getheight());
							//绘制提醒按钮
							setfillcolor(WHITE);
							solidrectangle(560, 288, 715, 350); //矩形
							drawText("成功击中目标", 580, 308);
							Sleep(700);
							putimage(0, 0, &temp);
							if (atk >= a->life)
							{
								a->death();
								//delete a;
								rounddone = true;
								energy--;
								return true;
							}
							a->life -= atk;
							rounddone = true;
							energy--;
							return true;
						}
					}
					else//超出攻击范围
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("超出攻击范围", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}
				}
			}
	}

	bool Character::action(Character* a)
	{
		IMAGE temp;

		int TargetX = a->mx;
		int TargetY = a->my;
		// 计算横向和纵向的网格差
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// 计算欧几里得距离（网格单位）
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

		//4个角色对应4个动作
		if (kind == Kind::medic)//医疗兵
		{
			if (this->energy >= 1)
			{
				if (gridDistance <= 1.5)//必须紧贴才能生效
				{
					if (a->faction == this->faction && a != this)
					{
						movline(1, wholebk);
						a->life += 5;
						this->energy--;
						rounddone = true;
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("成功治疗友军！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return true;
					}
					else if (a->faction == this->faction && a == this)
					{
						movline(1, wholebk);
						a->life += 5;
						this->energy--;
						rounddone = true;
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("成功治疗自己！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return true;
					}
					else
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 790, 350); //矩形
						drawText("不能以敌军作为目标！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}

				}
				else//超出距离则提示
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //矩形
					drawText("目标超出距离！", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
			}
			else
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//绘制提醒按钮
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //矩形
				drawText("体力不足！", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;
			}
		}
		else if (kind == Kind::common)//步兵
		{
			getimage(&temp, 0, 0, getwidth(), getheight());
			//绘制提醒按钮
			setfillcolor(WHITE);
			solidrectangle(560, 288, 790, 350); //矩形
			drawText("不存在特殊动作！", 580, 308);
			Sleep(700);
			putimage(0, 0, &temp);
			return false;
		}
		else if (kind == Kind::sniper)//狙击手
		{
			if (this->energy >= 3)
			{
				if (gridDistance <= 5)//狙击距离
				{
					if (a->faction != this->faction && a != this)
					{
						movline(1, wholebk);
						if (a->life >= 6)
						{
							a->life -= 5;
						}
						else
						{
							a->death();
						}
						this->energy -= 3;
						rounddone = true;
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("成功伤害敌军！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return true;
					}
					else if (a->faction == this->faction && a == this)
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("不要伤害自己！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}
					else
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 790, 350); //矩形
						drawText("不能以敌军作为目标！", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}

				}
				else//超出距离则提示
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//绘制提醒按钮
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //矩形
					drawText("目标超出距离！", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
			}
			else
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//绘制提醒按钮
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //矩形
				drawText("体力不足！", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;
			}
			
		}
	}

