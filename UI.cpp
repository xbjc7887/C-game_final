#include "UI.h"

//���ֻ���
void drawText(std::string a, int x, int y)
{
	settextstyle(20, 10, "΢���ź�");
	setbkcolor(WHITE);
	settextcolor(BLACK);
	outtextxy(x, y, a.c_str());
}

// ��ť��
Button::Button(int a, int b, int c, int d, std::string e)
{
	chang = a;
	kuan = b;
	left = c;
	top = d;
	text = e;
}
//����Ƿ��ڰ�ť����
bool Button::isMouseInButton(int x, int y)
{
	if ((x > left && (x < left + chang)) && (y > top && y < (top + kuan)))
		return true;
	return false;
}
//���ư�ť
void  Button::printButton()
{
	setfillcolor(WHITE);
	solidrectangle(left, top, left + chang, top + kuan);//�ޱ߿����
	drawText(text, left, top);
}

//���ذ�ť����
string Button::getbuttontext()
{
	return text;
}

//���ﰴť��
CharacButton::CharacButton(int a, int b, int c, int d, std::string e) : Button(a, b, c, d, e)
{

}
void CharacButton::printButton() 
{
	getimage(&bk, 0, 0, getwidth(), getheight());
	setfillcolor(WHITE);
	solidrectangle(left, top, left + chang, top + kuan);
	drawText("�ƶ�", left, top);
	drawText("����", left , top + 20);
	drawText("����", left , top + 40);
	drawText("����", left , top + 60);
	drawText("�˳�", left , top + 80);
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK);
	line(left, top + 20, left + chang, top + 20);
	line(left, top + 40, left + chang, top + 40);
	line(left, top + 60, left + chang, top + 60);
	line(left, top + 80, left + chang, top + 80);
}
//������ƶ�����
bool CharacButton::isMouseInMov(int x, int y)
{
	if (x > left && x<left + chang && y>top && y < top + 20)
		return true;
	return false;
}
//����ڹ�������
bool CharacButton::isMouseInAttack(int x, int y)
{
	if (x > left && x<left + chang && y>top + 20 && y < top + 40)
		return true;
	return false;
}
//����ڶ�������
bool CharacButton::isMouseInAct(int x, int y)
{
	if (x > left && x<left + chang && y>top + 40 && y < top + 60)
		return true;
	return false;
}
//����ڴ�������
bool CharacButton::isMouseInStandby(int x, int y)
{
	if (x > left && x<left + chang && y>top + 60 && y < top + 80)
		return true;
	return false;
}
//������˳�����
bool CharacButton::isMouseInQuit(int x, int y)
{
	if (x > left && x<left + chang && y>top + 80 && y < top + kuan)
		return true;
	return false;
}
//ɾ����ť
void CharacButton::deleteButton()
{
	putimage(0, 0, &bk);	
}

//�ж�������
void movline(bool c, IMAGE d)
{
	if (c == 0)
	{
		int a = 0;
		int b = 0;
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		while (a != 22)
		{
			a++;
			line(0, 32 * a, getwidth(), 32 * a);
		}
		while (b != 39)
		{
			b++;
			line(32 * b, 0, 32 * b, getheight());
		}
	}
	else
	{
		putimage(0, 0, &d);
	}
}



