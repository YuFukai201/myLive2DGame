#ifndef __result_SCENE_H__
#define __result_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class result : public cocos2d::Layer
{
private:
	


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	//std::vector<cocos2d::ui::Button *>b_spr;

	int m_Score;

	void touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);




    // implement the "static create()" method manually
    CREATE_FUNC(result);
};

#endif // __result_SCENE_H__
