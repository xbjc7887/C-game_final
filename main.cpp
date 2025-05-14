#include <iostream>
#include <tchar.h>
#include <easyx.h>
#include <time.h>
#include <string>
#include "characters.h"
#include "UI.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ShellScalingAPI.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Shcore.lib")
using namespace std;

//ԭʼ����
IMAGE wholebk0;
//��ǰ����
IMAGE wholebk;

IMAGE common1_image;
IMAGE medic1_image;
IMAGE sniper1_image;
IMAGE common2_image;
IMAGE medic2_image;
IMAGE sniper2_image;

//�Ƿ���ʾ��ɫ���
bool showtable = 0;

enum whichButton {empty, Double, Single, help};

//�ҷ���λ
Character allycommon1(33, 33, 512, 160 + 64 * 0, "�Ҳ�1", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon2(33, 33, 512, 160 + 64 * 1, "�Ҳ�2", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon3(33, 33, 512, 160 + 64 * 2, "�Ҳ�3", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon4(33, 33, 512, 160 + 64 * 3, "�Ҳ�4", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon5(33, 33, 512, 160 + 64 * 4, "�Ҳ�5", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon6(33, 33, 512, 160 + 64 * 5, "�Ҳ�6", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allymedic1(33, 33, 512 - 64 * 1, 160 + 64 * 1, "��ҽ1", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allymedic2(33, 33, 512 - 64 * 1, 160 + 64 * 2.5, "��ҽ2", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allymedic3(33, 33, 512 - 64 * 1, 160 + 64 * 4, "��ҽ3", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allysniper1(33, 33, 512 - 64 * 2, 160 + 64 * 0, "�Ҿ�1", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::ally);
Character allysniper2(33, 33, 512 - 64 * 2, 160 + 64 * 5, "�Ҿ�2", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::ally);

//�з���λ
Character enemycommon1(33, 33, 736, 160 + 64 * 0, "�в�1", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon2(33, 33, 736, 160 + 64 * 1, "�в�2", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon3(33, 33, 736, 160 + 64 * 2, "�в�3", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon4(33, 33, 736, 160 + 64 * 3, "�в�4", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon5(33, 33, 736, 160 + 64 * 4, "�в�5", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon6(33, 33, 736, 160 + 64 * 5, "�в�6", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemymedic1(33, 33, 736 + 64 * 1, 160 + 64 * 1, "��ҽ1", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemymedic2(33, 33, 736 + 64 * 1, 160 + 64 * 2.5, "��ҽ2", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemymedic3(33, 33, 736 + 64 * 1, 160 + 64 * 4, "��ҽ3", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemysniper1(33, 33, 736 + 64 * 2, 160 + 64 * 0, "�о�1", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::enemy);
Character enemysniper2(33, 33, 736 + 64 * 2, 160 + 64 * 5, "�о�2", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::enemy);

CharacButton* commandbutton = nullptr;  //ʹ��ָ�����ť��������


//��ɫ�������λ�õı���
IMAGE tableBK;
std::vector<Character*> allcharacters = Character::getAllCharacters();
std::vector<Character*> allycharacters = Character::getAllyCharacters();
std::vector<Character*> enemycharacters = Character::getEnemyCharacters();

//��ɫ�ж��׶�
GameState currentState = GameState::Idle;
//�ĸ���Ӫ�����ж�
bool whichturn = 0;
// ��ǰ��ͣ��ɫ
Character* hovered = nullptr;
//��ǰ������ɫ
Character* nowcharac = nullptr;
//��ǰ�ж���Ӫ
Faction thisfaction = Faction::ally;
//��Ӫת����־
bool exchangefaction = false;

//��ɫ�ƶ��߽�
int boundaryLX = 11 * 32 - 1;
int boundaryRX = 28 * 32 + 1;
int boundaryUY = 5 * 32 - 1;
int boundaryDY = 19 * 32 + 1;

void playBackgroundMusic() 
{
	waveOutSetVolume(NULL, 0x0FFF);
	PlaySound("C:\\Users\\DELL\\Desktop\\NOKIA - Swimming.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
}

void drawGameInstructions() 
{
	// ����������ʽ
	settextstyle(20, 0, "΢���ź�");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	// Ӳ����������
	int startY = 120;  // ��ʼY����
	int lineHeight = 40; // �м��

	outtextxy(270, startY, _T("ʹ�������Ƽ��������ƶ����������ƶ���������������������4������"));
	startY += lineHeight;

	outtextxy(270, startY, _T("�ƶ����ж������������������ƶ���ɹ���/����/���⶯����֮���ж�����"));
	startY += lineHeight;

	outtextxy(270, startY, _T("�������룺����=2  ҽ�Ʊ�=1  �ѻ���=3 | ����ֱ�ӽ����ж�"));
	startY += lineHeight;

	outtextxy(270, startY, _T("���⶯����"));
	startY += lineHeight;

	outtextxy(290, startY, _T("- �����������⶯��"));
	startY += lineHeight;

	outtextxy(290, startY, _T("- ҽ�Ʊ�������1��Χ1���ѷ�5������"));
	startY += lineHeight;

	outtextxy(290, startY, _T("- �ѻ��֣�����5����1���з�5���˺�������3������"));
	startY += lineHeight;

	outtextxy(270, startY, _T("�������򣺴��������ģ��ѻ������⶯����3���������1"));
	startY += lineHeight;

	outtextxy(270, startY, _T("����=�����ʣ�50=50%���ܣ����ѻ������⹥������"));
	startY += lineHeight;

	outtextxy(270, startY, _T("�غ��л���"));
	startY += lineHeight;

	outtextxy(270, startY, _T("1. ȫ����ɫ�ж�����Զ��л�"));
	startY += lineHeight;

	outtextxy(290, startY, _T("2. ���[һ������]�����л�"));
	startY += lineHeight;

	outtextxy(290, startY, _T("3. �»غϿ�ʼȫ��+1����"));
}

int main() 
{
	playBackgroundMusic(); 

	//����һ������
	initgraph(1280, 736, EX_DBLCLKS | WS_POPUP);

	//FPS 100f
	const clock_t FPS = 1000 / 100;
	int startTime = 0;
	int frameTime = 0;
	
	//������ť����
	std::vector<Button> buttons;

	Button btnStandby(120, 40, 20, 20, "һ������");  //һ��������ť
	Button btnReturn(120, 40, 160, 20, "����");     //���ذ�ť
	Button btnHelp(620, 540, 260, 120, "");     //���ذ�ť

	//���㰴ť����
	const int BUTTON_WIDTH = 200;
	const int BUTTON_HEIGHT = 50;
	const int SPACING = 20;
	const int TOTAL_HEIGHT = 4 * BUTTON_HEIGHT + 3 * SPACING;
	const int START_Y = (736 - TOTAL_HEIGHT) / 2;
	const int CENTER_X = (1280 - BUTTON_WIDTH) / 2;

	//�����ĸ���ť
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y, "˫����Ϸ");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + BUTTON_HEIGHT + SPACING, "������Ϸ");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + 2 * (BUTTON_HEIGHT + SPACING), "��Ϸ˵��");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + 3 * (BUTTON_HEIGHT + SPACING), "�˳���Ϸ");

	//��ҵ�����ĸ���ť
	whichButton whichbutton = whichButton::empty;

	ExMessage msg = { 0 };
	//������Ϣ�ṹ�����
	ExMessage msg1 = { 0 };

	while (1)
	{
		//�������а�ť
		BeginBatchDraw();
		//�������˵�ͼƬ
		loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\mainmenu.png"), getwidth(), getheight());
		putimage(0, 0, &wholebk0);
		for (auto& btn : buttons)
		{
			btn.printButton();
		}
		// ����������ʽ
		settextstyle(72, 0, _T("΢���ź�"));  // 72������
		settextcolor(RGB(0, 160, 255));      // ����ɫ��R,G,B��
		setbkmode(TRANSPARENT);             // ͸������

		// �����Ͻ�������֣������΢����
		outtextxy(20, 20, _T("ɳ�̸�ս��"));
		EndBatchDraw();

	    peekmessage(&msg, EX_MOUSE);

		if (msg.message == WM_LBUTTONDOWN)
		{
			for (auto& btn : buttons)
			{
				if (btn.isMouseInButton(msg.x, msg.y))
				{
					if (btn.getbuttontext() == "˫����Ϸ")
					{
						msg = { 0 };
						whichbutton = whichButton::Double;
					}
					else if (btn.getbuttontext() == "������Ϸ")
					{
						msg = { 0 };
						whichbutton = whichButton::Single;
					}
					else if (btn.getbuttontext() == "��Ϸ˵��")
					{
						msg = { 0 };
						whichbutton = whichButton::help;
					}
					else if (btn.getbuttontext() == "�˳���Ϸ")
					{
						msg = { 0 };
						return 0;
					}
				}
			}
		}

		switch (whichbutton)
		{
		case Double:
			BeginBatchDraw();
			loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\beijingtu.png"), getwidth(), getheight());
			putimage(0, 0, &wholebk0);
			
			//�������н�ɫ
			for (Character* c : allcharacters)
			{
				c->paintCharacter();
			}
			
			//�������Ͻǰ�ť
			btnStandby.printButton();
			btnReturn.printButton();

			getimage(&wholebk, 0, 0, getwidth(), getheight());
			EndBatchDraw();

			//��ʼ����ǰ״̬
			currentState = GameState::Idle;
			//��Ϣ�ṹ�����
			msg1 = { 0 };

			//��ʼ�����н�ɫ��屳��
			for (Character* c : allcharacters)
			{
				if (c)
				{
					getimage(&tableBK, c->getright() + 20, c->gettop() - 20, 131, 171);
					c->tablebk = tableBK;
				}
			}

			// ��ǰ��ͣ��ɫ
			hovered = nullptr;
			//��ǰ������ɫ
			nowcharac = nullptr;
			//��ʼ�����1�ж��ִ�
			Character::setroundval(thisfaction, false);
			//��Ӫת����־
			exchangefaction = false;

			while (true)
			{
				// ������ʽ�ȴ���Ϣ
				peekmessage(&msg1, EX_MOUSE);
				//�������һ�������������ֻغ�
				if (msg1.message == WM_LBUTTONDOWN && btnStandby.isMouseInButton(msg1.x, msg1.y))
				{					
					Character::setroundval(thisfaction, true);
				}
				else if (msg1.message == WM_LBUTTONDOWN && btnReturn.isMouseInButton(msg1.x, msg1.y))
				{
					msg1 = { 0 };
					whichbutton = whichButton::empty;
					break;
				}
				else 
				{
					if (exchangefaction)
					{
						Character::setroundval(thisfaction, true);
						thisfaction = (thisfaction == Faction::ally) ? Faction::enemy : Faction::ally;
						Character::setroundval(thisfaction, false);
						exchangefaction = false;	
						IMAGE temp;
						getimage(&temp, 0, 0, getwidth(), getheight());
						//�������Ѱ�ť
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //����
						drawText("������Ӫת��", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
					}

					switch (currentState)
					{
						// ��ʼ״̬���ȴ������ɫ
					case GameState::Idle:
						if (msg1.message == WM_MOUSEMOVE)//����ƶ�����ɫ��ʾ�������
						{
							// ��ȡ��ǰ��ͣ��ɫΪ������ɫ
							nowcharac = Character::getHoveredCharacter(msg1.x, msg1.y);
							//�����ǰ������ɫ��Ϊ��
							if (nowcharac)
							{
								//���ƽ�ɫ�������
								BeginBatchDraw();
								setfillcolor(WHITE);
								solidrectangle(nowcharac->getright() + 20, nowcharac->gettop() - 20, nowcharac->getright() + 150, nowcharac->gettop() + 150);//����
								//drawText("������" + nowcharac->getname(), nowcharac->getright() + 20, nowcharac->gettop() - 20)
								drawText("��Ӫ��" + nowcharac->getfactionname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
								drawText("ְҵ��" + nowcharac->getkindname(), nowcharac->getright() + 20, nowcharac->gettop() - 0);
								drawText("����ֵ��" + std::to_string(nowcharac->getlife()), nowcharac->getright() + 20, nowcharac->gettop() + 20);
								drawText("��������" + std::to_string(nowcharac->getATK()), nowcharac->getright() + 20, nowcharac->gettop() + 40);
								drawText("�������룺" + std::to_string(nowcharac->getATKran()), nowcharac->getright() + 20, nowcharac->gettop() + 60);
								drawText("������" + std::to_string(nowcharac->getenergy()), nowcharac->getright() + 20, nowcharac->gettop() + 80);
								drawText("���ݣ�" + std::to_string(nowcharac->getagility()), nowcharac->getright() + 20, nowcharac->gettop() + 100);
								drawText("�ж�����" + std::to_string(nowcharac->getmovement()), nowcharac->getright() + 20, nowcharac->gettop() + 120);
								EndBatchDraw();
							}
							else
							{
								for (Character* c : allcharacters)
								{
									//�ر����н�ɫ���
									putimage(c->getright() + 20, c->gettop() - 20, &c->tablebk);
								}
							}
						}
						//������治���κδ���
						if (msg1.message == WM_LBUTTONDOWN && nowcharac == nullptr)
						{

						}
						//�����ǰ��ɫ�����ж�û�н���
						else if (msg1.message == WM_LBUTTONDOWN && nowcharac->rounddone == false)
						{
							// ��ȡ��ǰ�����Ľ�ɫ
							//nowcharac = Character::getHoveredCharacter(msg.x, msg.y);
							if (nowcharac)
							{   // ��ʾ��ɫָ�ť
								commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
								//�رս�ɫ���
								putimage(nowcharac->getright() + 20, nowcharac->gettop() - 20, &nowcharac->tablebk);
								commandbutton->printButton();
								currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
								FlushBatchDraw();
							}
						}
						break;

					case GameState::ShowCommand:// ��ʾ��ť״̬���ȴ������ť���Ҽ�ȡ��
						// ����ʽ�ȴ���Ϣ
						getmessage(&msg1, EX_MOUSE);

						// ����ƶ���ť������ȴ�Ŀ�ĵ�״̬
						if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInMov(msg1.x, msg1.y) && nowcharac->roundmov == false)
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//�������н�ɫ��Ϣ�����ռ����
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForMovTarget;
							FlushBatchDraw();
						}

						// ���������ť������ѡ�񹥻�Ŀ��״̬
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAttack(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//�������н�ɫ�����ռ����
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForAtkTarget;
							FlushBatchDraw();
						}

						// ���������ť������ѡ����Ŀ��״̬
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAct(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//�������н�ɫ�����ռ����
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForActTarget;
							FlushBatchDraw();
						}

						// ���������ť����ɫ���������ж�
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInStandby(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//�������н�ɫ�����ռ����
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							nowcharac->rounddone = true;
							currentState = GameState::Idle;
							FlushBatchDraw();
							Sleep(100);
						}

						//�Ҽ������˳�ȡ��ָ���
						else if (msg1.message == WM_RBUTTONDOWN || (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInQuit(msg1.x, msg1.y)))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//�������н�ɫ�����ռ����
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							currentState = GameState::Idle;
							FlushBatchDraw();
							Sleep(100);//����������
						}
						break;

						//�ȴ�ѡ��Ŀ��λ���ƶ�
					case GameState::WaitingForMovTarget:
						//����ʽ�ȴ���Ϣ
						getmessage(&msg1, EX_MOUSE);
						//ѡ��Ŀ�ĵ�
						if (msg1.message == WM_LBUTTONDOWN)
						{
							int TargetX = (msg1.x / 32) * 32 + 16;
							int TargetY = (msg1.y / 32) * 32 + 16;
							// ������������������
							int deltaX = (TargetX - nowcharac->getmx()) / 32;
							int deltaY = (TargetY - nowcharac->getmy()) / 32;
							// ����ŷ����þ��루����λ��
							double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
							//Ŀ�ĵ��Ƿ���������ɫ
							Character* targetempty = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							// �������һ���ƶ�����
							if (nowcharac->getenergy() > 0 && gridDistance <= double(nowcharac->getmovement()) && targetempty == nullptr
								&& TargetX >= boundaryLX && TargetX <= boundaryRX && TargetY >= boundaryUY && TargetY <= boundaryDY)
							{
								// ��ȡĿ��λ�ò��ƶ�
								nowcharac->characmov(TargetX, TargetY);
								commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
								commandbutton->printButton();
								//�������н�ɫ�����ռ����
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								nowcharac->roundmov = true;//��ɫ���ƶ�
								currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
								FlushBatchDraw();
							}
							//�����߽�
							else if (!(TargetX >= boundaryLX && TargetX <= boundaryRX && TargetY >= boundaryUY && TargetY <= boundaryDY))
							{
								IMAGE temp;
								getimage(&temp, 0, 0, getwidth(), getheight());
								//�������Ѱ�ť
								setfillcolor(WHITE);
								solidrectangle(560, 288, 715, 350); //����
								drawText("�����ж��߽�", 580, 308);
								Sleep(700);
								putimage(0, 0, &temp);
							}
							//Ŀ��ص㳬���ж���Χ����������ɫ
							else
							{
								if (nowcharac->getenergy() == 0)
								{
									IMAGE temp;
									getimage(&temp, 0, 0, getwidth(), getheight());
									//�������Ѱ�ť
									setfillcolor(WHITE);
									solidrectangle(560, 288, 715, 350); //����
									drawText("��ɫ��������", 580, 308);
									Sleep(700);
									putimage(0, 0, &temp);
								}
								else
								{
									//������Χ�Ļ�
									if (gridDistance > double(nowcharac->getmovement()))
									{
										IMAGE temp;
										getimage(&temp, 0, 0, getwidth(), getheight());
										//�������Ѱ�ť
										setfillcolor(WHITE);
										solidrectangle(560, 288, 715, 350); //����
										drawText("�����ƶ���Χ", 580, 308);
										Sleep(700);
										putimage(0, 0, &temp);
									}
									//��������ɫ�Ļ�
									else if (gridDistance <= double(nowcharac->getmovement()) && targetempty != nullptr)
									{
										IMAGE temp;
										getimage(&temp, 0, 0, getwidth(), getheight());
										//�������Ѱ�ť
										setfillcolor(WHITE);
										solidrectangle(560, 288, 730, 350); //����
										drawText("�����ƶ����˴�", 580, 308);
										Sleep(700);
										putimage(0, 0, &temp);
									}
								}

							}
						}
						//�Ҽ��˳�ѡ��Ŀ�ĵ�
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// ��ʾ��ɫָ�ť
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
							FlushBatchDraw();
						}
						break;

						// �ȴ�ѡ�񹥻�Ŀ��
					case GameState::WaitingForAtkTarget:
						// ����ʽ�ȴ���Ϣ
						getmessage(&msg1, EX_MOUSE);
						//ѡ�й���Ŀ��
						if (msg1.message == WM_LBUTTONDOWN)
						{
							//ѡ������Ŀ��
							Character* atktarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							if (atktarget != nullptr)
							{
								if (nowcharac->attack(atktarget))//��������Ѿ�ʵʩ
								{
									if (!nowcharac->isdeath)
									{
										currentState = GameState::Idle;//һ�ֹ��������������ý�ɫ�����ж����
										FlushBatchDraw();
									}
								}
								//�������н�ɫ��Ϣ�����ռ����
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								time_t now = time(nullptr);
								while (time(nullptr) - now <= 0.5)
								{
									msg1.message = { 0 };
									// ������ʽ�ȴ���Ϣ
									peekmessage(&msg1, EX_MOUSE);
								}
							}
						}
						//�Ҽ��˳�ѡ�񹥻�Ŀ��
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// ��ʾ��ɫָ�ť
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
							FlushBatchDraw();
						}
						break;

						// �ȴ�ѡ����Ŀ��
					case GameState::WaitingForActTarget:
						// ����ʽ�ȴ���Ϣ
						getmessage(&msg1, EX_MOUSE);
						//ѡ�ж���Ŀ��
						if (msg1.message == WM_LBUTTONDOWN)
						{
							//ѡ������Ŀ��
							Character* acttarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							if (acttarget != nullptr)
							{
								if (nowcharac->action(acttarget))
								{
									currentState = GameState::Idle;//һ�ֶ����������ý�ɫ�����ж����
									FlushBatchDraw();
								}
								//�������н�ɫ��Ϣ�����ռ����
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								time_t now = time(nullptr);
								while (time(nullptr) - now <= 0.5)
								{
									msg1.message = { 0 };
									// ������ʽ�ȴ���Ϣ
									peekmessage(&msg1, EX_MOUSE);
								}
							}

						}
						//�Ҽ��˳�ѡ����Ŀ��
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// ��ʾ��ɫָ�ť
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
							FlushBatchDraw();
						}
						break;
					}


					//��ǰ�غ��ҷ��Ƿ�ȫ���ж����,���ȫ����������з��׶Σ��ҷ�ˢ��roundmov��rounddone�����н�ɫ������1
					if (Character::allrounddone(thisfaction))
					{
						exchangefaction = true;
					}

					frameTime = clock() - startTime;
					if (frameTime < FPS)
					{
						Sleep(FPS - frameTime);
					}
				}
				


			}


			break;
		case Single:
			BeginBatchDraw();
			loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\beijingtu.png"), getwidth(), getheight());
			putimage(0, 0, &wholebk0);

			//�������н�ɫ
			for (Character* c : allcharacters)
			{
				if (c->getkind() == Kind::medic || c->getkind() == Kind::sniper)
				{
					c->death();
				}
				else
				{
					c->paintCharacter();
				}
			}

			//�������Ͻǰ�ť
			btnStandby.printButton();
			btnReturn.printButton();

			getimage(&wholebk, 0, 0, getwidth(), getheight());
			EndBatchDraw();

			//��ʼ����ǰ״̬
			currentState = GameState::Idle;
			//��Ϣ�ṹ�����
			msg1 = { 0 };

			//��ʼ�����н�ɫ��屳��
			for (Character* c : allcharacters)
			{
				if (c)
				{
					getimage(&tableBK, c->getright() + 20, c->gettop() - 20, 131, 171);
					c->tablebk = tableBK;
				}
			}

			whichturn = 0;//�ĸ���Ӫ�����ж�
			// ��ǰ��ͣ��ɫ
			hovered = nullptr;
			//��ǰ������ɫ
			nowcharac = nullptr;

			while (true)
			{
				if (msg1.message == WM_LBUTTONDOWN && btnReturn.isMouseInButton(msg1.x, msg1.y))
				{
					msg1 = { 0 };
					whichbutton = whichButton::empty;
					break;
				}
				else
				{
					Character::setroundval(Faction::ally, false);
					while (whichturn == 0)
					{
						// ������ʽ�ȴ���Ϣ
						peekmessage(&msg1, EX_MOUSE);
						if (btnReturn.isMouseInButton(msg1.x, msg1.y))
						{
							break;
						}
						else
						{
							switch (currentState)
							{
								// ��ʼ״̬���ȴ������ɫ
							case GameState::Idle:
								if (msg1.message == WM_MOUSEMOVE)//����ƶ�����ɫ��ʾ�������
								{
									// ��ȡ��ǰ��ͣ��ɫΪ������ɫ
									nowcharac = Character::getHoveredCharacter(msg1.x, msg1.y);
									//�����ǰ������ɫ��Ϊ��
									if (nowcharac)
									{
										//���ƽ�ɫ�������
										BeginBatchDraw();
										setfillcolor(WHITE);
										solidrectangle(nowcharac->getright() + 20, nowcharac->gettop() - 20, nowcharac->getright() + 150, nowcharac->gettop() + 150);//����
										//drawText("������" + nowcharac->getname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
										drawText("��Ӫ��" + nowcharac->getfactionname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
										drawText("ְҵ��" + nowcharac->getkindname(), nowcharac->getright() + 20, nowcharac->gettop() - 0);
										drawText("����ֵ��" + std::to_string(nowcharac->getlife()), nowcharac->getright() + 20, nowcharac->gettop() + 20);
										drawText("��������" + std::to_string(nowcharac->getATK()), nowcharac->getright() + 20, nowcharac->gettop() + 40);
										drawText("�������룺" + std::to_string(nowcharac->getATKran()), nowcharac->getright() + 20, nowcharac->gettop() + 60);
										drawText("������" + std::to_string(nowcharac->getenergy()), nowcharac->getright() + 20, nowcharac->gettop() + 80);
										drawText("���ݣ�" + std::to_string(nowcharac->getagility()), nowcharac->getright() + 20, nowcharac->gettop() + 100);
										drawText("�ж�����" + std::to_string(nowcharac->getmovement()), nowcharac->getright() + 20, nowcharac->gettop() + 120);
										EndBatchDraw();
									}
									else
									{
										for (Character* c : allcharacters)
										{
											//�ر����н�ɫ���
											putimage(c->getright() + 20, c->gettop() - 20, &c->tablebk);
										}
									}
								}
								//������治���κδ���
								if (msg1.message == WM_LBUTTONDOWN && nowcharac == nullptr)
								{

								}
								//�����ǰ��ɫ�����ж�û�н���
								else if (msg1.message == WM_LBUTTONDOWN && nowcharac->rounddone == false && nowcharac->getfaction() == Faction::ally)
								{
									// ��ȡ��ǰ�����Ľ�ɫ
									//nowcharac = Character::getHoveredCharacter(msg.x, msg.y);
									if (nowcharac)
									{   // ��ʾ��ɫָ�ť
										commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
										//�رս�ɫ���
										putimage(nowcharac->getright() + 20, nowcharac->gettop() - 20, &nowcharac->tablebk);
										commandbutton->printButton();
										currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
										FlushBatchDraw();
									}
								}
								break;

							case GameState::ShowCommand:// ��ʾ��ť״̬���ȴ������ť���Ҽ�ȡ��
								// ����ʽ�ȴ���Ϣ
								getmessage(&msg1, EX_MOUSE);

								// ����ƶ���ť������ȴ�Ŀ�ĵ�״̬
								if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInMov(msg1.x, msg1.y) && nowcharac->roundmov == false)
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//�������н�ɫ��Ϣ�����ռ����
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForMovTarget;
									FlushBatchDraw();
								}

								// ���������ť������ѡ�񹥻�Ŀ��״̬
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAttack(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//�������н�ɫ�����ռ����
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForAtkTarget;
									FlushBatchDraw();
								}

								// ���������ť������ѡ����Ŀ��״̬
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAct(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//�������н�ɫ�����ռ����
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForActTarget;
									FlushBatchDraw();
								}

								// ���������ť����ɫ���������ж�
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInStandby(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//�������н�ɫ�����ռ����
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									nowcharac->rounddone = true;
									currentState = GameState::Idle;
									FlushBatchDraw();
									Sleep(100);
								}

								//�Ҽ������˳�ȡ��ָ���
								else if (msg1.message == WM_RBUTTONDOWN || (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInQuit(msg1.x, msg1.y)))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//�������н�ɫ�����ռ����
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									currentState = GameState::Idle;
									FlushBatchDraw();
									Sleep(100);//����������
								}
								break;

								//�ȴ�ѡ��Ŀ��λ���ƶ�
							case GameState::WaitingForMovTarget:
								//����ʽ�ȴ���Ϣ
								getmessage(&msg1, EX_MOUSE);
								//ѡ��Ŀ�ĵ�
								if (msg1.message == WM_LBUTTONDOWN)
								{
									int TargetX = (msg1.x / 32) * 32 + 16;
									int TargetY = (msg1.y / 32) * 32 + 16;
									// ������������������
									int deltaX = (TargetX - nowcharac->getmx()) / 32;
									int deltaY = (TargetY - nowcharac->getmy()) / 32;
									// ����ŷ����þ��루����λ��
									double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
									//Ŀ�ĵ��Ƿ���������ɫ
									Character* targetempty = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									// �����ɫ����������Ŀ��������ƶ���Χ����Ŀ�������������ɫ
									if (nowcharac->getenergy() > 0 && gridDistance <= double(nowcharac->getmovement()) && targetempty == nullptr)
									{
										// ��ȡĿ��λ�ò��ƶ�
										nowcharac->characmov(TargetX, TargetY);
										commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
										commandbutton->printButton();
										//�������н�ɫ�����ռ����
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										nowcharac->roundmov = true;//��ɫ���ƶ�
										currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
										FlushBatchDraw();
									}
									//���Ŀ��ص㳬���ж���Χ����������ɫ
									else
									{
										IMAGE temp;
										if (nowcharac->getenergy() == 0)
										{
											getimage(&temp, 0, 0, getwidth(), getheight());
											//�������Ѱ�ť
											setfillcolor(WHITE);
											solidrectangle(560, 288, 715, 350); //����
											drawText("��ɫ��������", 580, 308);
											Sleep(700);
											putimage(0, 0, &temp);
										}
										else
										{
											//������Χ�Ļ�
											if (gridDistance > double(nowcharac->getmovement()))
											{
												getimage(&temp, 0, 0, getwidth(), getheight());
												//�������Ѱ�ť
												setfillcolor(WHITE);
												solidrectangle(560, 288, 715, 350); //����
												drawText("�����ƶ���Χ", 580, 308);
												Sleep(700);
												putimage(0, 0, &temp);
											}
											//��������ɫ�Ļ�
											else if (gridDistance <= double(nowcharac->getmovement()) && targetempty != nullptr)
											{
												getimage(&temp, 0, 0, getwidth(), getheight());
												//�������Ѱ�ť
												setfillcolor(WHITE);
												solidrectangle(560, 288, 730, 350); //����
												drawText("�����ƶ����˴�", 580, 308);
												Sleep(700);
												putimage(0, 0, &temp);
											}
										}

									}
								}
								//�Ҽ��˳�ѡ��Ŀ�ĵ�
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// ��ʾ��ɫָ�ť
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
									FlushBatchDraw();
								}
								break;

								// �ȴ�ѡ�񹥻�Ŀ��
							case GameState::WaitingForAtkTarget:
								// ����ʽ�ȴ���Ϣ
								getmessage(&msg1, EX_MOUSE);
								//ѡ�й���Ŀ��
								if (msg1.message == WM_LBUTTONDOWN)
								{
									//ѡ������Ŀ��
									Character* atktarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									if (atktarget != nullptr)
									{
										if (nowcharac->attack(atktarget))//��������Ѿ�ʵʩ
										{
											if (!nowcharac->isdeath)
											{
												currentState = GameState::Idle;//һ�ֹ��������������ý�ɫ�����ж����
												FlushBatchDraw();
											}
										}
										//�������н�ɫ��Ϣ�����ռ����
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										time_t now = time(nullptr);
										while (time(nullptr) - now <= 0.5)
										{
											msg1.message = { 0 };
											// ������ʽ�ȴ���Ϣ
											peekmessage(&msg1, EX_MOUSE);
										}
									}
								}
								//�Ҽ��˳�ѡ�񹥻�Ŀ��
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// ��ʾ��ɫָ�ť
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
									FlushBatchDraw();
								}
								break;

								// �ȴ�ѡ����Ŀ��
							case GameState::WaitingForActTarget:
								// ����ʽ�ȴ���Ϣ
								getmessage(&msg1, EX_MOUSE);
								//ѡ�ж���Ŀ��
								if (msg1.message == WM_LBUTTONDOWN)
								{
									//ѡ������Ŀ��
									Character* acttarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									if (acttarget != nullptr)
									{
										if (nowcharac->action(acttarget))
										{
											currentState = GameState::Idle;//һ�ֶ����������ý�ɫ�����ж����
											FlushBatchDraw();
										}
										//�������н�ɫ��Ϣ�����ռ����
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										time_t now = time(nullptr);
										while (time(nullptr) - now <= 0.5)
										{
											msg1.message = { 0 };
											// ������ʽ�ȴ���Ϣ
											peekmessage(&msg1, EX_MOUSE);
										}
									}

								}
								//�Ҽ��˳�ѡ����Ŀ��
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// ��ʾ��ɫָ�ť
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // ������ʾ��ť״̬
									FlushBatchDraw();
								}
								break;
							}


							//��ǰ�غ��ҷ��Ƿ�ȫ���ж����,���ȫ����������з��׶Σ��ҷ�ˢ��roundmov��rounddone�����н�ɫ������1
							if (Character::allrounddone(Faction::ally))
							{
								whichturn = 1;
							}
						}

					}

					if (whichturn == 1)//��ǰ�ǵз��ж��غ�
					{
						Character::setroundval(Faction::enemy, false);
						//�������ез���ɫ
						for (Character* enemy : enemycharacters)
						{
							//Ѱ������Ұ�ڵ��ҷ�Ŀ��
							Character* nearTarget = nullptr;
							double minDistance;
							double gridDistance1;
							double gridDistance2;
							double gridDistance3;
							double gridDistance4;
							int TargetX;
							int TargetY;
							int deltaX;
							int deltaY;
							int deltaX1;
							int deltaY1;
							int deltaX2;
							int deltaY2;
							for (Character* ally : allycharacters)
							{
								TargetX = ally->getmx();
								TargetY = ally->getmy();
								// ������������������
								deltaX = (TargetX - enemy->getmx()) / 32;
								deltaY = (TargetY - enemy->getmy()) / 32;
								deltaX1 = deltaX + 2;
								deltaX2 = deltaX - 2;
								deltaY1 = deltaY + 2;
								deltaY2 = deltaY - 2;
								// ����ŷ����þ��루����λ��
								gridDistance1 = std::sqrt(deltaX * deltaX + deltaY1 * deltaY1);
								gridDistance2 = std::sqrt(deltaX1 * deltaX1 + deltaY * deltaY);
								gridDistance3 = std::sqrt(deltaX * deltaX + deltaY2 * deltaY2);
								gridDistance4 = std::sqrt(deltaX2 * deltaX2 + deltaY * deltaY);
								minDistance = min(gridDistance1, gridDistance2);
								minDistance = min(minDistance, gridDistance3);
								minDistance = min(minDistance, gridDistance4);
								if (minDistance <= enemy->getmovement())
								{
									nearTarget = ally;
									break;
								}
							}
							if (enemy->getenergy() >= 2 && nearTarget != nullptr)//����ý�ɫ������2����
							{
								if (minDistance <= enemy->getmovement() && minDistance != 2.0)
								{
									if (minDistance == gridDistance1)
									{
										enemy->characmov(TargetX, TargetY + 64);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance2)
									{
										enemy->characmov(TargetX + 64, TargetY);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance3)
									{
										enemy->characmov(TargetX, TargetY - 64);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance4)
									{
										enemy->characmov(TargetX - 64, TargetY);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
											nearTarget->attack(enemy);
									}
								}
								else if (minDistance == 2.0)
								{
									enemy->attack(nearTarget);
									if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
										nearTarget->attack(enemy);
								}
							}
							else if (enemy->getenergy() == 1 && nearTarget != nullptr)
							{
								if (minDistance == 2.0)
								{
									enemy->attack(nearTarget);
									if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//�ҷ����з���
										nearTarget->attack(enemy);
								}
							}
							else if (nearTarget == nullptr)//û�й���Ŀ��ʹ���
							{

							}
							enemy->rounddone = true;
						}
						//�������н�ɫ��Ϣ�����ռ����
						for (Character* c : allcharacters)
						{
							getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
						}
						Character::setroundval(Faction::enemy, false);
						whichturn = 0;
					}
				}

				frameTime = clock() - startTime;
				if (frameTime < FPS)
				{
					Sleep(FPS - frameTime);
				}


			}
			break;
		case help:
			//�������˵�ͼƬ
			loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\mainmenu.png"), getwidth(), getheight());
			putimage(0, 0, &wholebk0);
			btnReturn.printButton();
			btnHelp.printButton();
			drawGameInstructions();
			while (true)
			{
				// ������ʽ�ȴ���Ϣ
				peekmessage(&msg1, EX_MOUSE);
				if (msg1.message == WM_LBUTTONDOWN && btnReturn.isMouseInButton(msg1.x, msg1.y))
				{
					msg1 = { 0 };
					whichbutton = whichButton::empty;
					break;
				}
			}
			break;
		default:
			break;
		}






	}

	


		
	

	
	
	

	





}
