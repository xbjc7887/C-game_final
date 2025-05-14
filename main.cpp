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

//原始背景
IMAGE wholebk0;
//当前背景
IMAGE wholebk;

IMAGE common1_image;
IMAGE medic1_image;
IMAGE sniper1_image;
IMAGE common2_image;
IMAGE medic2_image;
IMAGE sniper2_image;

//是否显示角色面板
bool showtable = 0;

enum whichButton {empty, Double, Single, help};

//我方单位
Character allycommon1(33, 33, 512, 160 + 64 * 0, "我步1", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon2(33, 33, 512, 160 + 64 * 1, "我步2", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon3(33, 33, 512, 160 + 64 * 2, "我步3", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon4(33, 33, 512, 160 + 64 * 3, "我步4", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon5(33, 33, 512, 160 + 64 * 4, "我步5", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allycommon6(33, 33, 512, 160 + 64 * 5, "我步6", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::ally);
Character allymedic1(33, 33, 512 - 64 * 1, 160 + 64 * 1, "我医1", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allymedic2(33, 33, 512 - 64 * 1, 160 + 64 * 2.5, "我医2", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allymedic3(33, 33, 512 - 64 * 1, 160 + 64 * 4, "我医3", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::ally);
Character allysniper1(33, 33, 512 - 64 * 2, 160 + 64 * 0, "我狙1", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::ally);
Character allysniper2(33, 33, 512 - 64 * 2, 160 + 64 * 5, "我狙2", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::ally);

//敌方单位
Character enemycommon1(33, 33, 736, 160 + 64 * 0, "敌步1", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon2(33, 33, 736, 160 + 64 * 1, "敌步2", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon3(33, 33, 736, 160 + 64 * 2, "敌步3", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon4(33, 33, 736, 160 + 64 * 3, "敌步4", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon5(33, 33, 736, 160 + 64 * 4, "敌步5", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemycommon6(33, 33, 736, 160 + 64 * 5, "敌步6", 10, 5, 4, 3, 20, 2.0, Kind::common, Faction::enemy);
Character enemymedic1(33, 33, 736 + 64 * 1, 160 + 64 * 1, "敌医1", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemymedic2(33, 33, 736 + 64 * 1, 160 + 64 * 2.5, "敌医2", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemymedic3(33, 33, 736 + 64 * 1, 160 + 64 * 4, "敌医3", 6, 4, 4, 2, 50, 1.0, Kind::medic, Faction::enemy);
Character enemysniper1(33, 33, 736 + 64 * 2, 160 + 64 * 0, "敌狙1", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::enemy);
Character enemysniper2(33, 33, 736 + 64 * 2, 160 + 64 * 5, "敌狙2", 15, 10, 4, 4, 30, 3.0, Kind::sniper, Faction::enemy);

CharacButton* commandbutton = nullptr;  //使用指针管理按钮生命周期


//角色面板所在位置的背景
IMAGE tableBK;
std::vector<Character*> allcharacters = Character::getAllCharacters();
std::vector<Character*> allycharacters = Character::getAllyCharacters();
std::vector<Character*> enemycharacters = Character::getEnemyCharacters();

//角色行动阶段
GameState currentState = GameState::Idle;
//哪个阵营正在行动
bool whichturn = 0;
// 当前悬停角色
Character* hovered = nullptr;
//当前操作角色
Character* nowcharac = nullptr;
//当前行动阵营
Faction thisfaction = Faction::ally;
//阵营转换标志
bool exchangefaction = false;

//角色移动边界
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
	// 设置文字样式
	settextstyle(20, 0, "微软雅黑");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);

	// 硬编码分行输出
	int startY = 120;  // 起始Y坐标
	int lineHeight = 40; // 行间距

	outtextxy(270, startY, _T("使用鼠标控制己方人物移动，人物有移动、攻击、动作、待命等4个动作"));
	startY += lineHeight;

	outtextxy(270, startY, _T("移动按行动力限制最大格子数，移动后可攻击/待命/特殊动作，之后行动结束"));
	startY += lineHeight;

	outtextxy(270, startY, _T("攻击距离：步兵=2  医疗兵=1  狙击手=3 | 待命直接结束行动"));
	startY += lineHeight;

	outtextxy(270, startY, _T("特殊动作："));
	startY += lineHeight;

	outtextxy(290, startY, _T("- 步兵：无特殊动作"));
	startY += lineHeight;

	outtextxy(290, startY, _T("- 医疗兵：治疗1周围1名友方5点生命"));
	startY += lineHeight;

	outtextxy(290, startY, _T("- 狙击手：攻击5格内1名敌方5点伤害（消耗3体力）"));
	startY += lineHeight;

	outtextxy(270, startY, _T("体力规则：待命不消耗，狙击手特殊动作耗3，其余均耗1"));
	startY += lineHeight;

	outtextxy(270, startY, _T("敏捷=闪避率（50=50%闪避），狙击手特殊攻击必中"));
	startY += lineHeight;

	outtextxy(270, startY, _T("回合切换："));
	startY += lineHeight;

	outtextxy(270, startY, _T("1. 全部角色行动完毕自动切换"));
	startY += lineHeight;

	outtextxy(290, startY, _T("2. 点击[一键待命]立即切换"));
	startY += lineHeight;

	outtextxy(290, startY, _T("3. 新回合开始全体+1体力"));
}

int main() 
{
	playBackgroundMusic(); 

	//创建一个窗口
	initgraph(1280, 736, EX_DBLCLKS | WS_POPUP);

	//FPS 100f
	const clock_t FPS = 1000 / 100;
	int startTime = 0;
	int frameTime = 0;
	
	//创建按钮容器
	std::vector<Button> buttons;

	Button btnStandby(120, 40, 20, 20, "一键待命");  //一键待命按钮
	Button btnReturn(120, 40, 160, 20, "返回");     //返回按钮
	Button btnHelp(620, 540, 260, 120, "");     //返回按钮

	//计算按钮参数
	const int BUTTON_WIDTH = 200;
	const int BUTTON_HEIGHT = 50;
	const int SPACING = 20;
	const int TOTAL_HEIGHT = 4 * BUTTON_HEIGHT + 3 * SPACING;
	const int START_Y = (736 - TOTAL_HEIGHT) / 2;
	const int CENTER_X = (1280 - BUTTON_WIDTH) / 2;

	//创建四个按钮
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y, "双人游戏");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + BUTTON_HEIGHT + SPACING, "单人游戏");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + 2 * (BUTTON_HEIGHT + SPACING), "游戏说明");
	buttons.emplace_back(BUTTON_WIDTH, BUTTON_HEIGHT, CENTER_X, START_Y + 3 * (BUTTON_HEIGHT + SPACING), "退出游戏");

	//玩家点击了哪个按钮
	whichButton whichbutton = whichButton::empty;

	ExMessage msg = { 0 };
	//定义消息结构体变量
	ExMessage msg1 = { 0 };

	while (1)
	{
		//绘制所有按钮
		BeginBatchDraw();
		//载入主菜单图片
		loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\mainmenu.png"), getwidth(), getheight());
		putimage(0, 0, &wholebk0);
		for (auto& btn : buttons)
		{
			btn.printButton();
		}
		// 设置文字样式
		settextstyle(72, 0, _T("微软雅黑"));  // 72号字体
		settextcolor(RGB(0, 160, 255));      // 亮蓝色（R,G,B）
		setbkmode(TRANSPARENT);             // 透明背景

		// 在左上角输出文字（坐标可微调）
		outtextxy(20, 20, _T("沙盘格战争"));
		EndBatchDraw();

	    peekmessage(&msg, EX_MOUSE);

		if (msg.message == WM_LBUTTONDOWN)
		{
			for (auto& btn : buttons)
			{
				if (btn.isMouseInButton(msg.x, msg.y))
				{
					if (btn.getbuttontext() == "双人游戏")
					{
						msg = { 0 };
						whichbutton = whichButton::Double;
					}
					else if (btn.getbuttontext() == "单人游戏")
					{
						msg = { 0 };
						whichbutton = whichButton::Single;
					}
					else if (btn.getbuttontext() == "游戏说明")
					{
						msg = { 0 };
						whichbutton = whichButton::help;
					}
					else if (btn.getbuttontext() == "退出游戏")
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
			
			//绘制所有角色
			for (Character* c : allcharacters)
			{
				c->paintCharacter();
			}
			
			//绘制左上角按钮
			btnStandby.printButton();
			btnReturn.printButton();

			getimage(&wholebk, 0, 0, getwidth(), getheight());
			EndBatchDraw();

			//初始化当前状态
			currentState = GameState::Idle;
			//消息结构体变量
			msg1 = { 0 };

			//初始化所有角色面板背景
			for (Character* c : allcharacters)
			{
				if (c)
				{
					getimage(&tableBK, c->getright() + 20, c->gettop() - 20, 131, 171);
					c->tablebk = tableBK;
				}
			}

			// 当前悬停角色
			hovered = nullptr;
			//当前操作角色
			nowcharac = nullptr;
			//初始化玩家1行动轮次
			Character::setroundval(thisfaction, false);
			//阵营转换标志
			exchangefaction = false;

			while (true)
			{
				// 非阻塞式等待消息
				peekmessage(&msg1, EX_MOUSE);
				//如果按下一键待命则进入对手回合
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
						//绘制提醒按钮
						setfillcolor(WHITE);
						solidrectangle(560, 288, 715, 350); //矩形
						drawText("操作阵营转换", 580, 308);
						Sleep(700);
						putimage(0, 0, &temp);
					}

					switch (currentState)
					{
						// 初始状态：等待点击角色
					case GameState::Idle:
						if (msg1.message == WM_MOUSEMOVE)//鼠标移动到角色显示属性面板
						{
							// 获取当前悬停角色为操作角色
							nowcharac = Character::getHoveredCharacter(msg1.x, msg1.y);
							//如果当前操作角色不为空
							if (nowcharac)
							{
								//绘制角色属性面板
								BeginBatchDraw();
								setfillcolor(WHITE);
								solidrectangle(nowcharac->getright() + 20, nowcharac->gettop() - 20, nowcharac->getright() + 150, nowcharac->gettop() + 150);//矩形
								//drawText("姓名：" + nowcharac->getname(), nowcharac->getright() + 20, nowcharac->gettop() - 20)
								drawText("阵营：" + nowcharac->getfactionname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
								drawText("职业：" + nowcharac->getkindname(), nowcharac->getright() + 20, nowcharac->gettop() - 0);
								drawText("生命值：" + std::to_string(nowcharac->getlife()), nowcharac->getright() + 20, nowcharac->gettop() + 20);
								drawText("攻击力：" + std::to_string(nowcharac->getATK()), nowcharac->getright() + 20, nowcharac->gettop() + 40);
								drawText("攻击距离：" + std::to_string(nowcharac->getATKran()), nowcharac->getright() + 20, nowcharac->gettop() + 60);
								drawText("体力：" + std::to_string(nowcharac->getenergy()), nowcharac->getright() + 20, nowcharac->gettop() + 80);
								drawText("敏捷：" + std::to_string(nowcharac->getagility()), nowcharac->getright() + 20, nowcharac->gettop() + 100);
								drawText("行动力：" + std::to_string(nowcharac->getmovement()), nowcharac->getright() + 20, nowcharac->gettop() + 120);
								EndBatchDraw();
							}
							else
							{
								for (Character* c : allcharacters)
								{
									//关闭所有角色面板
									putimage(c->getright() + 20, c->gettop() - 20, &c->tablebk);
								}
							}
						}
						//点击地面不做任何处理
						if (msg1.message == WM_LBUTTONDOWN && nowcharac == nullptr)
						{

						}
						//如果当前角色本轮行动没有结束
						else if (msg1.message == WM_LBUTTONDOWN && nowcharac->rounddone == false)
						{
							// 获取当前操作的角色
							//nowcharac = Character::getHoveredCharacter(msg.x, msg.y);
							if (nowcharac)
							{   // 显示角色指令按钮
								commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
								//关闭角色面板
								putimage(nowcharac->getright() + 20, nowcharac->gettop() - 20, &nowcharac->tablebk);
								commandbutton->printButton();
								currentState = GameState::ShowCommand;  // 进入显示按钮状态
								FlushBatchDraw();
							}
						}
						break;

					case GameState::ShowCommand:// 显示按钮状态：等待点击按钮或右键取消
						// 阻塞式等待消息
						getmessage(&msg1, EX_MOUSE);

						// 点击移动按钮，进入等待目的地状态
						if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInMov(msg1.x, msg1.y) && nowcharac->roundmov == false)
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//更新所有角色信息面板所占背景
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForMovTarget;
							FlushBatchDraw();
						}

						// 点击攻击按钮，进入选择攻击目标状态
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAttack(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//更新所有角色面板所占背景
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForAtkTarget;
							FlushBatchDraw();
						}

						// 点击动作按钮，进入选择动作目标状态
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAct(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//更新所有角色面板所占背景
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							movline(0, wholebk);
							currentState = GameState::WaitingForActTarget;
							FlushBatchDraw();
						}

						// 点击待命按钮，角色结束本轮行动
						else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInStandby(msg1.x, msg1.y))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//更新所有角色面板所占背景
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							nowcharac->rounddone = true;
							currentState = GameState::Idle;
							FlushBatchDraw();
							Sleep(100);
						}

						//右键或点击退出取消指令框
						else if (msg1.message == WM_RBUTTONDOWN || (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInQuit(msg1.x, msg1.y)))
						{
							commandbutton->deleteButton();
							delete commandbutton;
							commandbutton = nullptr;
							//更新所有角色面板所占背景
							for (Character* c : allcharacters)
							{
								getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
							}
							currentState = GameState::Idle;
							FlushBatchDraw();
							Sleep(100);//防抖动处理
						}
						break;

						//等待选择目标位置移动
					case GameState::WaitingForMovTarget:
						//阻塞式等待消息
						getmessage(&msg1, EX_MOUSE);
						//选中目的地
						if (msg1.message == WM_LBUTTONDOWN)
						{
							int TargetX = (msg1.x / 32) * 32 + 16;
							int TargetY = (msg1.y / 32) * 32 + 16;
							// 计算横向和纵向的网格差
							int deltaX = (TargetX - nowcharac->getmx()) / 32;
							int deltaY = (TargetY - nowcharac->getmy()) / 32;
							// 计算欧几里得距离（网格单位）
							double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
							//目的地是否有其他角色
							Character* targetempty = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							// 如果满足一切移动条件
							if (nowcharac->getenergy() > 0 && gridDistance <= double(nowcharac->getmovement()) && targetempty == nullptr
								&& TargetX >= boundaryLX && TargetX <= boundaryRX && TargetY >= boundaryUY && TargetY <= boundaryDY)
							{
								// 获取目标位置并移动
								nowcharac->characmov(TargetX, TargetY);
								commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
								commandbutton->printButton();
								//更新所有角色面板所占背景
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								nowcharac->roundmov = true;//角色已移动
								currentState = GameState::ShowCommand;  // 进入显示按钮状态
								FlushBatchDraw();
							}
							//超出边界
							else if (!(TargetX >= boundaryLX && TargetX <= boundaryRX && TargetY >= boundaryUY && TargetY <= boundaryDY))
							{
								IMAGE temp;
								getimage(&temp, 0, 0, getwidth(), getheight());
								//绘制提醒按钮
								setfillcolor(WHITE);
								solidrectangle(560, 288, 715, 350); //矩形
								drawText("超出行动边界", 580, 308);
								Sleep(700);
								putimage(0, 0, &temp);
							}
							//目标地点超出行动范围或有其他角色
							else
							{
								if (nowcharac->getenergy() == 0)
								{
									IMAGE temp;
									getimage(&temp, 0, 0, getwidth(), getheight());
									//绘制提醒按钮
									setfillcolor(WHITE);
									solidrectangle(560, 288, 715, 350); //矩形
									drawText("角色体力不足", 580, 308);
									Sleep(700);
									putimage(0, 0, &temp);
								}
								else
								{
									//超出范围的话
									if (gridDistance > double(nowcharac->getmovement()))
									{
										IMAGE temp;
										getimage(&temp, 0, 0, getwidth(), getheight());
										//绘制提醒按钮
										setfillcolor(WHITE);
										solidrectangle(560, 288, 715, 350); //矩形
										drawText("超出移动范围", 580, 308);
										Sleep(700);
										putimage(0, 0, &temp);
									}
									//有其他角色的话
									else if (gridDistance <= double(nowcharac->getmovement()) && targetempty != nullptr)
									{
										IMAGE temp;
										getimage(&temp, 0, 0, getwidth(), getheight());
										//绘制提醒按钮
										setfillcolor(WHITE);
										solidrectangle(560, 288, 730, 350); //矩形
										drawText("不能移动到此处", 580, 308);
										Sleep(700);
										putimage(0, 0, &temp);
									}
								}

							}
						}
						//右键退出选择目的地
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// 显示角色指令按钮
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // 进入显示按钮状态
							FlushBatchDraw();
						}
						break;

						// 等待选择攻击目标
					case GameState::WaitingForAtkTarget:
						// 阻塞式等待消息
						getmessage(&msg1, EX_MOUSE);
						//选中攻击目标
						if (msg1.message == WM_LBUTTONDOWN)
						{
							//选定攻击目标
							Character* atktarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							if (atktarget != nullptr)
							{
								if (nowcharac->attack(atktarget))//如果攻击已经实施
								{
									if (!nowcharac->isdeath)
									{
										currentState = GameState::Idle;//一轮攻击互动结束，该角色该轮行动完毕
										FlushBatchDraw();
									}
								}
								//更新所有角色信息面板所占背景
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								time_t now = time(nullptr);
								while (time(nullptr) - now <= 0.5)
								{
									msg1.message = { 0 };
									// 非阻塞式等待消息
									peekmessage(&msg1, EX_MOUSE);
								}
							}
						}
						//右键退出选择攻击目标
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// 显示角色指令按钮
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // 进入显示按钮状态
							FlushBatchDraw();
						}
						break;

						// 等待选择动作目标
					case GameState::WaitingForActTarget:
						// 阻塞式等待消息
						getmessage(&msg1, EX_MOUSE);
						//选中动作目标
						if (msg1.message == WM_LBUTTONDOWN)
						{
							//选定动作目标
							Character* acttarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
							if (acttarget != nullptr)
							{
								if (nowcharac->action(acttarget))
								{
									currentState = GameState::Idle;//一轮动作结束，该角色该轮行动完毕
									FlushBatchDraw();
								}
								//更新所有角色信息面板所占背景
								for (Character* c : allcharacters)
								{
									getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
								}
								time_t now = time(nullptr);
								while (time(nullptr) - now <= 0.5)
								{
									msg1.message = { 0 };
									// 非阻塞式等待消息
									peekmessage(&msg1, EX_MOUSE);
								}
							}

						}
						//右键退出选动作目标
						else if (msg1.message == WM_RBUTTONDOWN)
						{
							movline(1, wholebk);
							// 显示角色指令按钮
							commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
							commandbutton->printButton();
							currentState = GameState::ShowCommand;  // 进入显示按钮状态
							FlushBatchDraw();
						}
						break;
					}


					//当前回合我方是否全部行动完毕,如果全部完毕则进入敌方阶段，我方刷新roundmov和rounddone且所有角色体力加1
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

			//绘制所有角色
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

			//绘制左上角按钮
			btnStandby.printButton();
			btnReturn.printButton();

			getimage(&wholebk, 0, 0, getwidth(), getheight());
			EndBatchDraw();

			//初始化当前状态
			currentState = GameState::Idle;
			//消息结构体变量
			msg1 = { 0 };

			//初始化所有角色面板背景
			for (Character* c : allcharacters)
			{
				if (c)
				{
					getimage(&tableBK, c->getright() + 20, c->gettop() - 20, 131, 171);
					c->tablebk = tableBK;
				}
			}

			whichturn = 0;//哪个阵营正在行动
			// 当前悬停角色
			hovered = nullptr;
			//当前操作角色
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
						// 非阻塞式等待消息
						peekmessage(&msg1, EX_MOUSE);
						if (btnReturn.isMouseInButton(msg1.x, msg1.y))
						{
							break;
						}
						else
						{
							switch (currentState)
							{
								// 初始状态：等待点击角色
							case GameState::Idle:
								if (msg1.message == WM_MOUSEMOVE)//鼠标移动到角色显示属性面板
								{
									// 获取当前悬停角色为操作角色
									nowcharac = Character::getHoveredCharacter(msg1.x, msg1.y);
									//如果当前操作角色不为空
									if (nowcharac)
									{
										//绘制角色属性面板
										BeginBatchDraw();
										setfillcolor(WHITE);
										solidrectangle(nowcharac->getright() + 20, nowcharac->gettop() - 20, nowcharac->getright() + 150, nowcharac->gettop() + 150);//矩形
										//drawText("姓名：" + nowcharac->getname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
										drawText("阵营：" + nowcharac->getfactionname(), nowcharac->getright() + 20, nowcharac->gettop() - 20);
										drawText("职业：" + nowcharac->getkindname(), nowcharac->getright() + 20, nowcharac->gettop() - 0);
										drawText("生命值：" + std::to_string(nowcharac->getlife()), nowcharac->getright() + 20, nowcharac->gettop() + 20);
										drawText("攻击力：" + std::to_string(nowcharac->getATK()), nowcharac->getright() + 20, nowcharac->gettop() + 40);
										drawText("攻击距离：" + std::to_string(nowcharac->getATKran()), nowcharac->getright() + 20, nowcharac->gettop() + 60);
										drawText("体力：" + std::to_string(nowcharac->getenergy()), nowcharac->getright() + 20, nowcharac->gettop() + 80);
										drawText("敏捷：" + std::to_string(nowcharac->getagility()), nowcharac->getright() + 20, nowcharac->gettop() + 100);
										drawText("行动力：" + std::to_string(nowcharac->getmovement()), nowcharac->getright() + 20, nowcharac->gettop() + 120);
										EndBatchDraw();
									}
									else
									{
										for (Character* c : allcharacters)
										{
											//关闭所有角色面板
											putimage(c->getright() + 20, c->gettop() - 20, &c->tablebk);
										}
									}
								}
								//点击地面不做任何处理
								if (msg1.message == WM_LBUTTONDOWN && nowcharac == nullptr)
								{

								}
								//如果当前角色本轮行动没有结束
								else if (msg1.message == WM_LBUTTONDOWN && nowcharac->rounddone == false && nowcharac->getfaction() == Faction::ally)
								{
									// 获取当前操作的角色
									//nowcharac = Character::getHoveredCharacter(msg.x, msg.y);
									if (nowcharac)
									{   // 显示角色指令按钮
										commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
										//关闭角色面板
										putimage(nowcharac->getright() + 20, nowcharac->gettop() - 20, &nowcharac->tablebk);
										commandbutton->printButton();
										currentState = GameState::ShowCommand;  // 进入显示按钮状态
										FlushBatchDraw();
									}
								}
								break;

							case GameState::ShowCommand:// 显示按钮状态：等待点击按钮或右键取消
								// 阻塞式等待消息
								getmessage(&msg1, EX_MOUSE);

								// 点击移动按钮，进入等待目的地状态
								if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInMov(msg1.x, msg1.y) && nowcharac->roundmov == false)
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//更新所有角色信息面板所占背景
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForMovTarget;
									FlushBatchDraw();
								}

								// 点击攻击按钮，进入选择攻击目标状态
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAttack(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//更新所有角色面板所占背景
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForAtkTarget;
									FlushBatchDraw();
								}

								// 点击动作按钮，进入选择动作目标状态
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInAct(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//更新所有角色面板所占背景
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									movline(0, wholebk);
									currentState = GameState::WaitingForActTarget;
									FlushBatchDraw();
								}

								// 点击待命按钮，角色结束本轮行动
								else if (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInStandby(msg1.x, msg1.y))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//更新所有角色面板所占背景
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									nowcharac->rounddone = true;
									currentState = GameState::Idle;
									FlushBatchDraw();
									Sleep(100);
								}

								//右键或点击退出取消指令框
								else if (msg1.message == WM_RBUTTONDOWN || (msg1.message == WM_LBUTTONDOWN && commandbutton->isMouseInQuit(msg1.x, msg1.y)))
								{
									commandbutton->deleteButton();
									delete commandbutton;
									commandbutton = nullptr;
									//更新所有角色面板所占背景
									for (Character* c : allcharacters)
									{
										getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
									}
									currentState = GameState::Idle;
									FlushBatchDraw();
									Sleep(100);//防抖动处理
								}
								break;

								//等待选择目标位置移动
							case GameState::WaitingForMovTarget:
								//阻塞式等待消息
								getmessage(&msg1, EX_MOUSE);
								//选中目的地
								if (msg1.message == WM_LBUTTONDOWN)
								{
									int TargetX = (msg1.x / 32) * 32 + 16;
									int TargetY = (msg1.y / 32) * 32 + 16;
									// 计算横向和纵向的网格差
									int deltaX = (TargetX - nowcharac->getmx()) / 32;
									int deltaY = (TargetY - nowcharac->getmy()) / 32;
									// 计算欧几里得距离（网格单位）
									double gridDistance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
									//目的地是否有其他角色
									Character* targetempty = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									// 如果角色体力充足且目标点在其移动范围内且目标点内无其他角色
									if (nowcharac->getenergy() > 0 && gridDistance <= double(nowcharac->getmovement()) && targetempty == nullptr)
									{
										// 获取目标位置并移动
										nowcharac->characmov(TargetX, TargetY);
										commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
										commandbutton->printButton();
										//更新所有角色面板所占背景
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										nowcharac->roundmov = true;//角色已移动
										currentState = GameState::ShowCommand;  // 进入显示按钮状态
										FlushBatchDraw();
									}
									//如果目标地点超出行动范围或有其他角色
									else
									{
										IMAGE temp;
										if (nowcharac->getenergy() == 0)
										{
											getimage(&temp, 0, 0, getwidth(), getheight());
											//绘制提醒按钮
											setfillcolor(WHITE);
											solidrectangle(560, 288, 715, 350); //矩形
											drawText("角色体力不足", 580, 308);
											Sleep(700);
											putimage(0, 0, &temp);
										}
										else
										{
											//超出范围的话
											if (gridDistance > double(nowcharac->getmovement()))
											{
												getimage(&temp, 0, 0, getwidth(), getheight());
												//绘制提醒按钮
												setfillcolor(WHITE);
												solidrectangle(560, 288, 715, 350); //矩形
												drawText("超出移动范围", 580, 308);
												Sleep(700);
												putimage(0, 0, &temp);
											}
											//有其他角色的话
											else if (gridDistance <= double(nowcharac->getmovement()) && targetempty != nullptr)
											{
												getimage(&temp, 0, 0, getwidth(), getheight());
												//绘制提醒按钮
												setfillcolor(WHITE);
												solidrectangle(560, 288, 730, 350); //矩形
												drawText("不能移动到此处", 580, 308);
												Sleep(700);
												putimage(0, 0, &temp);
											}
										}

									}
								}
								//右键退出选择目的地
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// 显示角色指令按钮
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // 进入显示按钮状态
									FlushBatchDraw();
								}
								break;

								// 等待选择攻击目标
							case GameState::WaitingForAtkTarget:
								// 阻塞式等待消息
								getmessage(&msg1, EX_MOUSE);
								//选中攻击目标
								if (msg1.message == WM_LBUTTONDOWN)
								{
									//选定攻击目标
									Character* atktarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									if (atktarget != nullptr)
									{
										if (nowcharac->attack(atktarget))//如果攻击已经实施
										{
											if (!nowcharac->isdeath)
											{
												currentState = GameState::Idle;//一轮攻击互动结束，该角色该轮行动完毕
												FlushBatchDraw();
											}
										}
										//更新所有角色信息面板所占背景
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										time_t now = time(nullptr);
										while (time(nullptr) - now <= 0.5)
										{
											msg1.message = { 0 };
											// 非阻塞式等待消息
											peekmessage(&msg1, EX_MOUSE);
										}
									}
								}
								//右键退出选择攻击目标
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// 显示角色指令按钮
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // 进入显示按钮状态
									FlushBatchDraw();
								}
								break;

								// 等待选择动作目标
							case GameState::WaitingForActTarget:
								// 阻塞式等待消息
								getmessage(&msg1, EX_MOUSE);
								//选中动作目标
								if (msg1.message == WM_LBUTTONDOWN)
								{
									//选定动作目标
									Character* acttarget = Character::getHoveredCharacter((msg1.x / 32) * 32 + 16, (msg1.y / 32) * 32 + 16);
									if (acttarget != nullptr)
									{
										if (nowcharac->action(acttarget))
										{
											currentState = GameState::Idle;//一轮动作结束，该角色该轮行动完毕
											FlushBatchDraw();
										}
										//更新所有角色信息面板所占背景
										for (Character* c : allcharacters)
										{
											getimage(&(c->tablebk), c->getright() + 20, c->gettop() - 20, 131, 171);
										}
										time_t now = time(nullptr);
										while (time(nullptr) - now <= 0.5)
										{
											msg1.message = { 0 };
											// 非阻塞式等待消息
											peekmessage(&msg1, EX_MOUSE);
										}
									}

								}
								//右键退出选动作目标
								else if (msg1.message == WM_RBUTTONDOWN)
								{
									movline(1, wholebk);
									// 显示角色指令按钮
									commandbutton = new CharacButton(50, 100, nowcharac->getright() + 20, nowcharac->gettop(), "");
									commandbutton->printButton();
									currentState = GameState::ShowCommand;  // 进入显示按钮状态
									FlushBatchDraw();
								}
								break;
							}


							//当前回合我方是否全部行动完毕,如果全部完毕则进入敌方阶段，我方刷新roundmov和rounddone且所有角色体力加1
							if (Character::allrounddone(Faction::ally))
							{
								whichturn = 1;
							}
						}

					}

					if (whichturn == 1)//当前是敌方行动回合
					{
						Character::setroundval(Faction::enemy, false);
						//遍历所有敌方角色
						for (Character* enemy : enemycharacters)
						{
							//寻找在视野内的我方目标
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
								// 计算横向和纵向的网格差
								deltaX = (TargetX - enemy->getmx()) / 32;
								deltaY = (TargetY - enemy->getmy()) / 32;
								deltaX1 = deltaX + 2;
								deltaX2 = deltaX - 2;
								deltaY1 = deltaY + 2;
								deltaY2 = deltaY - 2;
								// 计算欧几里得距离（网格单位）
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
							if (enemy->getenergy() >= 2 && nearTarget != nullptr)//如果该角色有至少2体力
							{
								if (minDistance <= enemy->getmovement() && minDistance != 2.0)
								{
									if (minDistance == gridDistance1)
									{
										enemy->characmov(TargetX, TargetY + 64);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance2)
									{
										enemy->characmov(TargetX + 64, TargetY);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance3)
									{
										enemy->characmov(TargetX, TargetY - 64);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
											nearTarget->attack(enemy);
									}
									else if (minDistance == gridDistance4)
									{
										enemy->characmov(TargetX - 64, TargetY);
										enemy->attack(nearTarget);
										if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
											nearTarget->attack(enemy);
									}
								}
								else if (minDistance == 2.0)
								{
									enemy->attack(nearTarget);
									if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
										nearTarget->attack(enemy);
								}
							}
							else if (enemy->getenergy() == 1 && nearTarget != nullptr)
							{
								if (minDistance == 2.0)
								{
									enemy->attack(nearTarget);
									if (!nearTarget->isdeath && nearTarget->getenergy() > 0)//我方进行反击
										nearTarget->attack(enemy);
								}
							}
							else if (nearTarget == nullptr)//没有攻击目标就待命
							{

							}
							enemy->rounddone = true;
						}
						//更新所有角色信息面板所占背景
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
			//载入主菜单图片
			loadimage(&wholebk0, _T("C:\\Users\\DELL\\Desktop\\mainmenu.png"), getwidth(), getheight());
			putimage(0, 0, &wholebk0);
			btnReturn.printButton();
			btnHelp.printButton();
			drawGameInstructions();
			while (true)
			{
				// 非阻塞式等待消息
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
