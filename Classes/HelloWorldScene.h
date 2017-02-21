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
	//演出用関数
	void  Text_Production();
	//タッチ
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	//update
	void update(float delta);
	//ランダムレンジ
	int GetRandom_Range(int max, int min);


	//タイマー
	int m_counter = 0;
	int Main_Time = 30;
	cocos2d::Label* timeLabel;
	//乱数
	int ram;
	cocos2d::Rect Blank_Rect;

	//Score
	int Touch_Score = 0;

	cocos2d::Label* Score_Label;
	
	//正解ボタン
	cocos2d::Sprite* _TouchButton;
	//不正解ボタン
	cocos2d::Sprite* HZR_Point;
    
	//ゲームオーバー
	bool Game_Over = false;

	//演出終了フラグ
	bool p_flag = false;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
