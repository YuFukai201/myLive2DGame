#ifndef ___title_SCENE_H__
#define ___title_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class _title : public cocos2d::Layer
{
private:
	


public:
    static cocos2d::Scene* createScene();

    virtual bool init();


	void touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);


    // implement the "static create()" method manually
    CREATE_FUNC(_title);
};

#endif // ___title_SCENE_H__
