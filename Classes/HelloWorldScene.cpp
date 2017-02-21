#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Live2DSprite.h"
#include "result.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
   
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("room.jpg");
	//sprite->addTouchEventListener(CC_CALLBACK_2(HelloWorld::TouchEvent, this));
	// position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto pLive2DSprite = Live2DSprite::createDrawNode();
	this->addChild(pLive2DSprite);
	pLive2DSprite->setTag(100);

	

	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	

	this->scheduleUpdate();
	

	//�s�����{�^��
	
	HZR_Point = Sprite::create("wall.png");
	HZR_Point->setPosition(Vec2(visibleSize.width / 2.08 + origin.x, visibleSize.height / 2 + origin.y));
	HZR_Point->setScale(0.45f, 0.8f);
	HZR_Point->setTag(2);
	this->addChild(HZR_Point,-1);
	
	//�s�����{�^���͈̔�
	Blank_Rect = Rect(HZR_Point->getPosition().x - HZR_Point->getContentSize().width / 2,
	HZR_Point->getPosition().y - HZR_Point->getContentSize().width / 2,
	HZR_Point->getContentSize().width,
	HZR_Point->getContentSize().height);
	
	

	//�^�C�}�[
	timeLabel = Label::createWithSystemFont(" ", "Arial", 30);
	timeLabel->setPosition(ccp(100, 600));
	timeLabel->setColor(Color3B::BLACK);
	this->addChild(timeLabel);
	CCString* timer = CCString::createWithFormat("time:%i", Main_Time);
	timeLabel->setString(timer->getCString());

	//�X�R�A
	Score_Label = Label::createWithSystemFont(" ", "Arial", 30);
	Score_Label->setPosition(ccp(900, 600));
	Score_Label->setColor(Color3B::RED);
	this->addChild(Score_Label);
	CCString* Score = CCString::createWithFormat("Score:%iP", Touch_Score);
	Score_Label->setString(Score->getCString());


	
	
	srand((unsigned int)time(NULL));
	
	//�X�^�[�g���o
	Text_Production();


	
    return true;
}

void HelloWorld::update(float delta)
{
	if (p_flag)
	{
		if (!Game_Over)
		{

			//�^�C�}�[
			m_counter++;
			int c = Main_Time - m_counter / 60;

			CCString* timer = CCString::createWithFormat("time:%i", c);
			timeLabel->setString(timer->getCString());

			//�X�R�A
			CCString* Score = CCString::createWithFormat("Score:%iP", Touch_Score);
			Score_Label->setString(Score->getCString());

			//�Q�[���I�[�o�[
			if (c <= 0)
			{
				Game_Over = true;
				//timeUP���o
				Text_Production();
			}
		}
	}
}

//���o
void HelloWorld::Text_Production()
{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//�Q�[���J�n
		if (!p_flag)
		{

			
			auto Start_Sprite = Sprite::create("ui/Start.png");
			Start_Sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
			this->addChild(Start_Sprite);

			auto Fade_out = FadeOut::create(0.8f);
			auto Rotate = RotateTo::create(1,1440);
			auto Scale = ScaleTo::create(1,1.5);
			
			//�\�����o
			Start_Sprite->runAction(Sequence::create(DelayTime::create(0.01), Rotate, Scale, NULL));
			//�����鏈��
			Start_Sprite->runAction(Sequence::create(DelayTime::create(2.3), Fade_out,NULL));

			//4�b��Ƀ����_�������s
			this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([this]() {
				
				//�����{�^������
				_TouchButton = Sprite::create("ui/point_48.png");
				_TouchButton->setTag(1);

				this->addChild(_TouchButton);

				//�{�^���\��
				Move_button();
				//���o�I��
				p_flag = true;
			}), NULL));


		}
		//�I��
		else
		{
			auto TimeUp_Sprite = Sprite::create("ui/Time_Up.png");
			TimeUp_Sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
			this->addChild(TimeUp_Sprite);


			auto move_action = MoveTo::create(1.0f, Point(visibleSize.width / 2, visibleSize.height / 2));
			TimeUp_Sprite->runAction(EaseElasticOut::create(move_action, 0.2f));

			//�X�R�A��ۑ�
			auto def = UserDefault::getInstance();
			def->setIntegerForKey("Score",Touch_Score);



			//4�b��Ƀ����_�������s
			this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([this]() {
				//�V�[���ړ�
				Director::getInstance()->replaceScene(result::createScene());
				
				CCLOG("MOVE_SCENE");
			}), NULL));


		}
		
		
	
}



//�{�^��
void HelloWorld::Move_button()
{

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		
		ram = rand() % 2;
		
		//��pos
		auto rand_face_pos_x = GetRandom_Range(650,450);
		auto rand_face_pos_y = GetRandom_Range(620, 330);
		//��pos
		auto rand_body_pos_x = GetRandom_Range(700, 380);
		auto rand_body_pos_y = GetRandom_Range(270, 10);

		Vec2 ram_pos[2]
		{
			//��̂ǂ���
			Vec2(rand_face_pos_x,rand_face_pos_y),
			//�̂̂ǂ���
			Vec2(rand_body_pos_x,rand_body_pos_y),
			
		};
		//�����{�^���ړ�
		_TouchButton->setPosition(ram_pos[ram]);
		
		
}


//�^�b�`�J�n
bool HelloWorld::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
	if (!Game_Over && p_flag)
	{
		Vec2 location = pTouch->getLocation();
		Live2DSprite* l2dsp = (Live2DSprite*)this->getChildByTag(100);

		Rect spriteRect = Rect(_TouchButton->getPosition().x - _TouchButton->getContentSize().width / 2,
			_TouchButton->getPosition().y - _TouchButton->getContentSize().height / 2,
			_TouchButton->getContentSize().width,
			_TouchButton->getContentSize().height);
		//�����̏ꍇ
		if (spriteRect.containsPoint(location)) {
			//�X�R�A�v���X
			Touch_Score++;
			//���[�V����			
			l2dsp->setAnimation_Prize(0);
			
			
		}
		//�s�����̏ꍇ
		else if (Blank_Rect.containsPoint(location))
		{

			//�X�R�A�}�C�i�X
			Touch_Score--;
			//���[�V����
			l2dsp->setAnimation_Blank(0);
		}

	}
	return true;
}
//�����͈͎̔w��
int HelloWorld::GetRandom_Range(int max, int min)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
};

//�^�b�`��
void HelloWorld::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
	Vec2 location = pTouch->getLocation();
	
}
//�^�b�`�I��
void HelloWorld::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
	Vec2 location = pTouch->getLocation();
	
}

/*
void HelloWorld::TouchEvent(Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	//auto def = UserDefault::getInstance();
	auto spr = (CCSprite *)pSender;
	auto tag = spr->getTag();
	
	//bool touch_flag = false;
	//�^�b�`�C�x���g
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		switch (tag)
		{
		case 1:
			//�������[�V����
			l2dsp->setAnimation_Prize(0);
			//�{�^���폜
			this->removeChild(spr);
			break;
		case 2:
			//�s�������[�V����
			l2dsp->setAnimation_Blank(1);
			break;
		default:
			break;
		}
	default:
		break;
	}
	
		//button_anim(false);
		
		

}
*/



