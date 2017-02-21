#include "result.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "_title.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* result::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = result::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool result::init()
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
	auto sprite = Sprite::create("BB.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setOpacity(0);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	sprite->runAction(FadeIn::create(1));
	
	//スコアを取得
	auto def = UserDefault::getInstance();
	m_Score = def->getIntegerForKey("Score");
	
	//アニメーション
	auto rank_action = CCSequence::create(DelayTime::create(1.3f), FadeIn::create(0.8f), NULL);
	auto girl_action = CCSequence::create(DelayTime::create(1.0f), FadeIn::create(0.8f), NULL);
	if (m_Score >= 30)
	{
		//ランクA
		CCLOG("a");

		//ランクsprite
		auto resultSprite = Sprite::create("ui/result/rank_a.png");
		resultSprite->setPosition(Vec2(visibleSize.width / 1.4 + origin.x, visibleSize.height / 1.5 - origin.y));
		resultSprite->setOpacity(0);
		resultSprite->runAction(rank_action);
		this->addChild(resultSprite);
		
		//girl_Face
		auto girl_face = Sprite::create("ui/result/Face/_a.PNG");
		girl_face->setPosition(Vec2(visibleSize.width / 5.7 + origin.x, visibleSize.height / 2 - origin.y));
		girl_face->setOpacity(0);
		girl_face->runAction(girl_action);
		this->addChild(girl_face);


	}
	else if (m_Score >= 15)
	{
		//ランクB
		CCLOG("b");

		//ランクsprite
		auto resultSprite = Sprite::create("ui/result/rank_b.png");
		resultSprite->setPosition(Vec2(visibleSize.width / 1.4 + origin.x, visibleSize.height / 1.5 - origin.y));
		resultSprite->setOpacity(0);
		resultSprite->runAction(rank_action);
		this->addChild(resultSprite);
		
		//girl_Face
		auto girl_face = Sprite::create("ui/result/Face/_b.PNG");
		girl_face->setPosition(Vec2(visibleSize.width / 5.7 + origin.x, visibleSize.height / 2 - origin.y));
		girl_face->setOpacity(0);
		girl_face->runAction(girl_action);
		this->addChild(girl_face);



	}
	else if (m_Score >= 0)
	{
		//ランクC
		CCLOG("c");

		//ランクsprite
		auto resultSprite = Sprite::create("ui/result/rank_c.png");
		resultSprite->setPosition(Vec2(visibleSize.width / 1.4 + origin.x, visibleSize.height / 1.5 - origin.y));
		resultSprite->setOpacity(0);
		resultSprite->runAction(rank_action);
		this->addChild(resultSprite);
		
		//girl_Face
		auto girl_face = Sprite::create("ui/result/Face/_c.PNG");
		girl_face->setPosition(Vec2(visibleSize.width / 5.7 + origin.x, visibleSize.height / 2 - origin.y));
		girl_face->setOpacity(0);
		girl_face->runAction(girl_action);
		this->addChild(girl_face);



	}
	//アニメーション
	auto text_action = CCSequence::create(DelayTime::create(2.0f), FadeIn::create(1.0f), NULL);
	//スコア表示
	//スコア
	auto Score_Label = Label::createWithSystemFont(" ", "Arial", 72);
	Score_Label->setPosition(Vec2(visibleSize.width / 1.3 + origin.x, visibleSize.height / 3.0 - origin.y));
	Score_Label->setColor(Color3B::BLACK);
	this->addChild(Score_Label);
	CCString* Score = CCString::createWithFormat("Score:%i P", m_Score);
	Score_Label->setString(Score->getCString());
	Score_Label->setOpacity(0);
	Score_Label->runAction(text_action);
	
	//move title
	auto Title_Button = ui::Button::create("ui/result/title_button.png");
	Title_Button->setPosition(Vec2(visibleSize.width / 1.2 + origin.x, visibleSize.height / 12 - origin.y));
	Title_Button->setOpacity(0);
	auto button_action = CCSequence::create(DelayTime::create(2.5f), FadeIn::create(1.0f), NULL);
	Title_Button->runAction(button_action);
	Title_Button->setTag(1);
	this->addChild(Title_Button);
	//タッチを有効に
	Title_Button->addTouchEventListener(CC_CALLBACK_2(result::touchEvent, this));
	
	
    return true;
}


void result::touchEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
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
			CCLOG("MOVE!");
			//シーン移動
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, _title::createScene(), Color3B::WHITE));
			break;

		default:
			break;
		}

	}

}




