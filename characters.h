#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

extern IMAGE wholebk0;
extern IMAGE wholebk;
extern IMAGE common1_image;
extern IMAGE medic1_image;
extern IMAGE sniper1_image;
extern IMAGE common2_image;
extern IMAGE medic2_image;
extern IMAGE sniper2_image;

extern void drawText(std::string a, int x, int y);
extern void movline(bool c, IMAGE d);


//��ɫ��Ӫ
enum class Faction { ally, enemy };
//��ɫְҵ�����֣�
enum class Kind { common, medic, scout, sniper };



//������
class Character
{
private:
    int chang;  // ��
    int kuan;   // ��
    int mx;     // ���ĺ�����
    int my;     // ����������
    int gobackX;//�ƶ�ǰ��ɫ������
    int gobackY;//�ƶ�ǰ��ɫ������
    string name;//��ɫ����
    int life;   //��ɫ����ֵ
    int energy; //��ɫ����
    int ATK;    //��ɫ������
    int movement; //��ɫ�ƶ���
    int agility;  //��ɫ����
    double atkran; //��ɫ��������
    Kind kind;    //��ɫְҵ�����֣�
    Faction faction; //��ɫ��Ӫ��0Ϊ�ҷ���1Ϊ�з���
    static std::vector<Character*> allCharacters; // ��̬��Ա���洢���н�ɫ
    static std::vector<Character*> allyCharacters; // ��̬��Ա���洢�����ҷ���ɫ
    static std::vector<Character*> enemyCharacters; // ��̬��Ա���洢���ез���ɫ
  
public:
    IMAGE character_img;    //��ɫͼƬ
    bool isdeath;//��ɫ�Ƿ�����
    bool roundmov = true; //��ɫ�����Ƿ��ƶ����
    bool rounddone = true; //��ɫ�����Ƿ�����ж�
    IMAGE tablebk; //��ɫ��������帲�ǵı���
    //���캯��
    Character(int a, int b, int c, int d, string e, int atk, int f, int g, int h, int i, double atkRan, Kind kin, Faction j);
    //��������
    void death();

    //��ȡ���н�ɫ
    static const std::vector<Character*>& getAllCharacters() 
    {
        return allCharacters;
    }

    //��ȡ���н�ɫ
    static const std::vector<Character*>& getAllyCharacters()
    {
        return allyCharacters;
    }

    //��ȡ���н�ɫ
    static const std::vector<Character*>& getEnemyCharacters()
    {
        return enemyCharacters;
    }

    //��ȡ�����ͣ�Ľ�ɫ�����ص�һ��ƥ��ģ�
    static Character* getHoveredCharacter(int mouseX, int mouseY) 
    {
        for (Character* c : allCharacters) 
        {
            if (c->isMouseInCharacter(mouseX, mouseY)) 
            {
                return c; 
            }
        }
        return nullptr; // δ�ҵ�
    }
    //�ж��ң��У����Ƿ����ȫ���ж����
    static bool allrounddone(Faction f);
    int getmx();
    int getmy();
    int getgobackX();
    int getgobackY();
    int getchang();
    int getkuan();
    int getright();
    int gettop();
    Kind getkind();
    string getkindname();
    int getATK();
    int getATKran();
    Faction getfaction();
    string getfactionname();
    string getname();
    int getlife();
    int getenergy();
    int getmovement();
    int getagility();
    void setmx(int a);
    void setmy(int a);
    //�µĻغ����������ң��У�����roundmov��rounddoneΪfalse
    static void setroundval(Faction f, bool TorF);
    //void setbk(IMAGE a);
    //��������
    void paintCharacter();
    void characmov(int x, int y);
    bool isMouseInCharacter(int x, int y);
    //��������
    bool attack(Character* a);
    //��������
    bool action(Character* a);

};
