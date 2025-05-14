#include "characters.h"
#include <locale>

// ��ʼ����̬��Ա
std::vector<Character*> Character::allCharacters;
std::vector<Character*> Character::allyCharacters;
std::vector<Character*> Character::enemyCharacters;



//�����๹�캯��
Character::Character(int a, int b, int c, int d, string e, int f, int g, int atk, int h, int i, double atkRan, Kind kin, Faction j)
{
	isdeath = false; 
	chang = a;
	kuan = b;
	mx = (c / 32) * 32 + 16;
	my = (d / 32) * 32 + 16;
	gobackX = mx;
	gobackY = my;
	name = e;  //��ɫ����
	life = f;   //��ɫ����ֵ
	energy = g; //��ɫ����
	ATK = atk;  //��ɫ������
	movement = h; //��ɫ�ƶ���
	agility = i;  //��ɫ����
	atkran = atkRan;//��ɫ������Χ
	kind = kin;  //��ɫְҵ
	faction = j;  //��ɫ��Ӫ
	if (this->kind == Kind::common)
	{
		if (this->faction == Faction::ally)
		{
			//���벽����ͼ
			loadimage(&common1_image, _T("C:\\Users\\DELL\\Desktop\\common1.png"), 33, 33);
			this->character_img = common1_image;
		}
		else
		{
			//���벽����ͼ
			loadimage(&common2_image, _T("C:\\Users\\DELL\\Desktop\\common2.png"), 33, 33);
			this->character_img = common2_image;
		}
	}
	else if(this->kind == Kind::medic)
	{
		if (this->faction == Faction::ally)
		{
			//����ҽ�Ʊ���ͼ
			loadimage(&medic1_image, _T("C:\\Users\\DELL\\Desktop\\medic1.png"), 33, 33);
			this->character_img = medic1_image;
		}
		else
		{
			//����ҽ�Ʊ���ͼ
			loadimage(&medic2_image, _T("C:\\Users\\DELL\\Desktop\\medic2.png"), 33, 33);
			this->character_img = medic2_image;
		}
	}
	else if(this->kind == Kind::sniper)
	{
		if (this->faction == Faction::ally)
		{
			//����ѻ�����ͼ
			loadimage(&sniper1_image, _T("C:\\Users\\DELL\\Desktop\\sniper1.png"), 33, 33);
			this->character_img = sniper1_image;
		}
		else
		{
			//����ѻ�����ͼ
			loadimage(&sniper2_image, _T("C:\\Users\\DELL\\Desktop\\sniper2.png"), 33, 33);
			this->character_img = sniper2_image;
		}
	}
	else
	{

	}
	allCharacters.push_back(this); // ���ý�ɫ��ӵ�ȫ������
	if (j == Faction::ally)
	{
		allyCharacters.push_back(this);
	}
	else
	{
		enemyCharacters.push_back(this);
	}
}

//��������
void Character::death()
{
	//��ԭ��ɫ���ڱ���
	IMAGE a = wholebk0;
	BeginBatchDraw();
	putimage(0, 0, &wholebk0);
	getimage(&a, mx - chang / 2, my - kuan / 2, chang, kuan);
	putimage(0, 0, &wholebk);
	putimage(mx - chang / 2, my - kuan / 2, &a);
	getimage(&wholebk, 0, 0, getwidth(), getheight());
	EndBatchDraw();

	//��ȫ���������Ƴ�����
	auto it = std::find(allCharacters.begin(), allCharacters.end(), this);
	if (it != allCharacters.end()) 
	{
		allCharacters.erase(it);
	}
	//���ҷ��������Ƴ�����������ҷ���
	it = std::find(allyCharacters.begin(), allyCharacters.end(), this);
	if (it != allyCharacters.end())
	{
		allyCharacters.erase(it);
	}
	//�ӵз��������Ƴ���������ǵз���
	it = std::find(enemyCharacters.begin(), enemyCharacters.end(), this);
	if (it != enemyCharacters.end())
	{
		enemyCharacters.erase(it);
	}
	isdeath = true;
}

//����mx
 int Character::getmx()
{
	 return mx;
}
	
//����my	
 int Character::getmy()
 {
	 return my;
 }

 //����gobackX
 int Character::getgobackX()
 {
	 return gobackX;
 }

 //����gobackY
 int Character::getgobackY()
 {
	 return gobackY;
 }

//����chang
int Character:: getchang()
{
		return chang;
}
//����kuan
int Character::getkuan()
	{
		return kuan;
	}

//�����ұ߽�
int Character::getright()
{
	return mx + chang / 2;
}
//�����ϱ߽�
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
		return "����";
	}
	else if (kind == Kind::medic)
	{
		return "ҽ�Ʊ�";
	}
	else if (kind == Kind::sniper)
	{
		return "�ѻ���";
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
		return "���1";
	}
	else
	{
		return "���2";
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

//����mx
void Character::setmx(int a)
{
	mx = a;
}
//����my
void Character::setmy(int a)
{
	my = a;
}
//�µĻغ����������ң��У�����roundmov��rounddoneΪfalse����ɫ������1
void Character::setroundval(Faction f, bool TorF) 
{
	//ɸѡ��
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

//��������
void Character::paintCharacter()
{
	putimage(mx - 16, my - 16, &character_img);
	getimage(&wholebk, 0, 0, getwidth(), getheight());
}

//�����ƶ�
void Character::characmov(int x, int y)
{
	x = (x / 32) * 32 + 16;
	y = (y / 32) * 32 + 16;
		IMAGE bk = wholebk;
		IMAGE partimage = wholebk0;
		////////////////////////
		//�����ƶ�ǰ�ѱ�������Ϊ��������ı���
		putimage(0, 0, &wholebk0);
		getimage(&partimage, mx - chang / 2, my - kuan / 2, chang + 1, kuan + 1);
		putimage(0, 0, &wholebk);
		putimage(mx - chang / 2, my - kuan / 2, &partimage);
		//setfillcolor(LIGHTBLUE);
		//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //��������
		getimage(&bk, 0, 0, getwidth(), getheight());   //��ǰbkΪ��������ı���
		////////////////////////
		if (mx == x && my == y)
		{
			BeginBatchDraw();
			//���ֳ��ƶ��������һ�в���
			putimage(0, 0, &bk);
			putimage(mx - 16, my - 16, &character_img);
			//setfillcolor(YELLOW);
			//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //��������
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
			//���ֳ��ƶ��������һ�в���
			putimage(0, 0, &bk);
			putimage(mx - 16, my - 16, &character_img);
			//setfillcolor(YELLOW);
			//solidrectangle(mx - chang / 2, my - kuan / 2, mx + chang / 2, my + kuan / 2); //��������
			EndBatchDraw();
		}
		if (energy > 0)
			energy--;//������1
		getimage(&bk, 0, 0, getwidth(), getheight());
		wholebk = bk;
	
	
}
	//ѡ������
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
			// ʹ�� std::copy_if ɸѡ�����������Ķ���
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::ally; });
			//������ֻ���û�ж��Ľ�ɫ����false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //ȫ���ҷ���ɫ���ж����
		}
		else if (f == Faction::enemy)
		{
			// ʹ�� std::copy_if ɸѡ�����������Ķ���
			std::copy_if(allCharacters.begin(), allCharacters.end(), std::back_inserter(filteredCharacters),
				[](Character* c) { return c->faction == Faction::enemy; });
			//������ֻ���û�ж��Ľ�ɫ����false
			for (Character* c : filteredCharacters)
			{
				if (!(c->rounddone))
				{
					return false;
				}
			}
			return true; //ȫ���ҷ���ɫ���ж����
		}

	}


	//��������
    bool Character::attack(Character* a)
	{
		//srand(time(0)); // �������������
		IMAGE temp;

		int TargetX = a->mx;
		int TargetY = a->my;
		// ������������������
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// ����ŷ����þ��루����λ��
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		int atk = ATK;//������
		double missrate = double(a->getagility() - 1);//�������ܼ��� 
		srand(time(0)); // �������������

			if (energy == 0)//������������޷�����
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//�������Ѱ�ť
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //����
				drawText("��ɫ��������", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;//��ɫ���ֶ���δ����
			}
			else//����������Թ���
			{
				if (a->faction == this->faction && this != a)//�����Թ����Ѿ�
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//�������Ѱ�ť
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //����
					drawText("�����Թ����Ѿ�", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else if (this == a)//�����Թ����Լ�
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//�������Ѱ�ť
					setfillcolor(WHITE);
					solidrectangle(560, 288, 735, 350); //����
					drawText("�����Թ����Լ�", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
				else
				{
					if (gridDistance <= atkran)//���й���
					{
						if (rand() % 100 <= missrate)//Զ�̹������Ƿ�������
						{
							movline(1, wholebk);
								getimage(&temp, 0, 0, getwidth(), getheight());
								//�������Ѱ�ť
								setfillcolor(WHITE);
								solidrectangle(560, 288, 715, 350); //����
								drawText("��ѽ��û���У�", 580, 308);
								Sleep(700);
								putimage(0, 0, &temp);							
							rounddone = true;
							energy--;
							return true;
						}
						else//û�����ܣ�����Զ�̹���
						{
							movline(1, wholebk);
							getimage(&temp, 0, 0, getwidth(), getheight());
							//�������Ѱ�ť
							setfillcolor(WHITE);
							solidrectangle(560, 288, 715, 350); //����
							drawText("�ɹ�����Ŀ��", 580, 308);
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
					else//����������Χ
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("����������Χ", 580, 308);
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
		// ������������������
		int deltaX = (TargetX - mx) / 32;
		int deltaY = (TargetY - my) / 32;
		// ����ŷ����þ��루����λ��
		double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

		//4����ɫ��Ӧ4������
		if (kind == Kind::medic)//ҽ�Ʊ�
		{
			if (this->energy >= 1)
			{
				if (gridDistance <= 1.5)//�������������Ч
				{
					if (a->faction == this->faction && a != this)
					{
						movline(1, wholebk);
						a->life += 5;
						this->energy--;
						rounddone = true;
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("�ɹ������Ѿ���", 580, 308);
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
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("�ɹ������Լ���", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return true;
					}
					else
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 790, 350); //����
						drawText("�����Եо���ΪĿ�꣡", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}

				}
				else//������������ʾ
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//�������Ѱ�ť
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //����
					drawText("Ŀ�곬�����룡", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
			}
			else
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//�������Ѱ�ť
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //����
				drawText("�������㣡", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;
			}
		}
		else if (kind == Kind::common)//����
		{
			getimage(&temp, 0, 0, getwidth(), getheight());
			//�������Ѱ�ť
			setfillcolor(WHITE);
			solidrectangle(560, 288, 790, 350); //����
			drawText("���������⶯����", 580, 308);
			Sleep(700);
			putimage(0, 0, &temp);
			return false;
		}
		else if (kind == Kind::sniper)//�ѻ���
		{
			if (this->energy >= 3)
			{
				if (gridDistance <= 5)//�ѻ�����
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
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("�ɹ��˺��о���", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return true;
					}
					else if (a->faction == this->faction && a == this)
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("��Ҫ�˺��Լ���", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}
					else
					{
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 790, 350); //����
						drawText("�����Եо���ΪĿ�꣡", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
						return false;
					}

				}
				else//������������ʾ
				{
					getimage(&temp, 0, 0, getwidth(), getheight());
					//�������Ѱ�ť
					setfillcolor(WHITE);
					solidrectangle(560, 288, 715, 350); //����
					drawText("Ŀ�곬�����룡", 580, 308);
					Sleep(700);
					putimage(0, 0, &temp);
					return false;
				}
			}
			else
			{
				getimage(&temp, 0, 0, getwidth(), getheight());
				//�������Ѱ�ť
				setfillcolor(WHITE);
				solidrectangle(560, 288, 715, 350); //����
				drawText("�������㣡", 580, 308);
				Sleep(700);
				putimage(0, 0, &temp);
				return false;
			}
			
		}
	}

