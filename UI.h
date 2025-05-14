#pragma once
#include <easyx.h>
#include <string>
#include "characters.h"
using namespace std;

//��ɫ�׶�
enum class GameState { Idle, ShowCommand, DoneMov, WaitingForMovTarget, WaitingForAtkTarget, WaitingForActTarget};

//���ֻ���
void drawText(std::string a, int x, int y);

// ��ť��
class Button 
{
protected:
	int chang, kuan;
	int left, top;
	std::string text;
public:
	Button(int a, int b, int c, int d, std::string e);
	//����Ƿ��ڰ�ť����
	bool isMouseInButton(int x, int y);
	//���ư�ť
	virtual void  printButton();
	//���ذ�ť����
	string getbuttontext();
};

//���ﰴť��
class CharacButton : public Button
{
public:
	IMAGE bk;
	CharacButton(int a, int b, int c, int d, std::string e);
	void printButton() override;
	bool isMouseInMov(int x, int y);
	bool isMouseInAttack(int x, int y);
	bool isMouseInAct(int x, int y);
	bool isMouseInStandby(int x, int y);
	bool isMouseInQuit(int x, int y);
	//ɾ����ť
	void deleteButton();
};

//�ƶ������ߣ�bool c�����ǻ��ƻ�������
void movline(bool c, IMAGE d);



