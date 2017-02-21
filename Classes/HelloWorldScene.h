#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
private:
	


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	//std::vector<cocos2d::ui::Button *>b_spr;

	void Move_button();
	//���o�p�֐�
	void  Text_Production();
	//�^�b�`
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	//update
	void update(float delta);
	//�����_�������W
	int GetRandom_Range(int max, int min);


	//�^�C�}�[
	int m_counter = 0;
	int Main_Time = 30;
	cocos2d::Label* timeLabel;
	//����
	int ram;
	cocos2d::Rect Blank_Rect;

	//Score
	int Touch_Score = 0;

	cocos2d::Label* Score_Label;
	
	//�����{�^��
	cocos2d::Sprite* _TouchButton;
	//�s�����{�^��
	cocos2d::Sprite* HZR_Point;
    
	//�Q�[���I�[�o�[
	bool Game_Over = false;

	//���o�I���t���O
	bool p_flag = false;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
