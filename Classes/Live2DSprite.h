/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#ifndef __sampleCocos2dx__Live2DSprite__
#define __sampleCocos2dx__Live2DSprite__

#include "cocos2d.h"
#include "2d/CCSprite.h"
#include <vector>
#include "Live2DModelOpenGL.h"
#include "motion/Live2DMotion.h"
#include "motion/MotionQueueManager.h"
#include "HelloWorldScene.h"
#include "result.h"

class Live2DSprite :public cocos2d::DrawNode {


	live2d::Live2DModelOpenGL* live2DModel;
	live2d::MotionQueueManager* motionManager;
	std::vector<cocos2d::Texture2D*> textures;
	cocos2d::Texture2D* texture1;
	//可変配列を作成
	std::vector<live2d::AMotion *> m0;
	std::vector<live2d::AMotion *> m1;
	std::vector<live2d::AMotion *> m2;
	std::vector<std::vector<live2d::AMotion *>> motion;

public:
	Live2DSprite();
	virtual ~Live2DSprite();
	
	virtual bool init();
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	static Live2DSprite* createDrawNode();
	//タッチ
	/*
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	
	bool tapCheck(char *area, float ox, float oy);
	*/
	void setAnimation_Prize(int num);
	void setAnimation_Blank(int num);
	

	

protected:
	cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__sampleCocos2dx__Lisve2DSprite__) */