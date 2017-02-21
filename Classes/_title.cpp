#include "_title.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "result.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* _title::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = _title::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool _title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//background
	auto sprite = Sprite::create("wallpaper.jpg");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	
	//スタートボタン
	auto start_button = ui::Button::create("ui/start_button.png", "ui/start_button_Select.png");
	start_button->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2.5f + origin.y));
	start_button->setOpacity(0);
	start_button->setTag(1);
	auto button_action = CCSequence::create(DelayTime::create(0.5f), FadeIn::create(1.0f), NULL);
	this->addChild(start_button,1);
	start_button->runAction(button_action);
	//タッチを有効に
	start_button->addTouchEventListener(CC_CALLBACK_2(_title::touchEvent, this));



	//girl
	auto _girl = Sprite::create("title2.png");
	_girl->setPosition(Vec2(visibleSize.width / 1.2f + origin.x, visibleSize.height / 2 + origin.y));
	_girl->setOpacity(0);
	_girl-> setScale(0.8f);
	this->addChild(_girl);
	_girl ->runAction(FadeIn::create(1));
	
	
	
    return true;
}


void _title::touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
	auto spr = (CCSprite *)pSender;
	auto tag = spr->getTag();
	//typeでタッチイベント指定
	switch (type)
	{
		//タッチ開始
	case ui::Widget::TouchEventType::BEGAN:
		//タグをゲットし、割り振る
		switch (tag)
		{
			
		case 1:
			this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this]() {
				//シーン移動
				Director::getInstance()->replaceScene(HelloWorld::createScene());
			}), NULL));
			break;
		default:
			break;
		}

	}

}




