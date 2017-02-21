

/*
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
//#include ""

#include "util/UtSystem.h"
#include "result_live2D.h"

#include "graphics/DrawProfileCocos2D.h"
#include "platform/CCFileUtils.h"
#include "Live2DSprite.h"
using namespace live2d;
USING_NS_CC;

const char* r_TEXTURES[] = {
	"izumi/model.1024/texture_00.png" ,
	"izumi/model.1024/texture_01.png" ,
	"izumi/model.1024/texture_02.png" ,
	"izumi/model.1024/texture_03.png" ,
	NULL
};
result_live2D::result_live2D()
	: live2DModel(nullptr)
{
}

result_live2D::~result_live2D()
{
	delete live2DModel;
	// テクスチャを解放
	Director::getInstance()->getTextureCache()->removeTextureForKey(std::string(r_TEXTURES[0]));
	
}



bool result_live2D::init()
{
	if (DrawNode::init())
	{
		if (live2DModel != nullptr)
		{
			delete live2DModel;
			live2DModel = nullptr;
		}

		const char* MODEL = "izumi/model.moc";

		unsigned char* buf;
		ssize_t bufSize;
		buf = FileUtils::getInstance()->getFileData(MODEL, "rb", &bufSize);

		live2DModel = Live2DModelOpenGL::loadModel(buf, bufSize);
		free(buf);

		auto chacheMgr = Director::getInstance()->getTextureCache();
		
		for (int i = 0; r_TEXTURES[i] != NULL; i++)
		{
			Texture2D* texture = chacheMgr->addImage(r_TEXTURES[i]);

			Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
			texture->setTexParameters(texParams);
			texture->generateMipmap();

			int glTexNo = texture->getName();

			live2DModel->setTexture(i, glTexNo);// テクスチャとモデルを結びつける
		}
		
		/////モーション追加
		unsigned char* motionbuf;
		ssize_t Motion_Size;
		
		//待機
		const char* idle_MOTION[] =
		{ 
			"izumi/animation/_idel.mtn",
			NULL
		};
		//正解
		const char* act_MOTION[] =
		{
			"izumi/animation/seikai.mtn",
			NULL
		};
		//不正解
		const char* blank_MOTION[] =
		{
			"izumi/animation/fuseikai.mtn",
			NULL
		};
		
		//ダミー。アクションの数だけいる
		//idle
		motion.push_back(m0);
		//act
		motion.push_back(m1);
		//blank
		motion.push_back(m2);

		for (int i = 0; idle_MOTION[i] != NULL; i++)
		{
			motionbuf = FileUtils::getInstance()->getFileData(idle_MOTION[i], "rb", &Motion_Size);
			//ベクトルに追加
			motion[0].push_back(Live2DMotion::loadMotion(motionbuf, (int)Motion_Size));
			motionbuf = NULL;
		}
		
		
		
		
		for (int i = 0; act_MOTION[i] != NULL; i++)
		{
			motionbuf = FileUtils::getInstance()->getFileData(act_MOTION[i], "rb", &Motion_Size);
			//ベクトルに追加
			motion[1].push_back(Live2DMotion::loadMotion(motionbuf, (int)Motion_Size));
			motionbuf = NULL;
		}
		
		for (int i = 0; blank_MOTION[i] != NULL; i++)
		{
			motionbuf = FileUtils::getInstance()->getFileData(blank_MOTION[i], "rb", &Motion_Size);
			//ベクトルに追加
			motion[2].push_back(Live2DMotion::loadMotion(motionbuf, (int)Motion_Size));
			motionbuf = NULL;
		}

		

		motionManager = new MotionQueueManager();
	
		

		// Live2Dモデルはローカル座標で左上を原点にして(CanvasWidth、CanvasWidth)
		// のサイズになるため、以下のようにして調整してください。
		float w = Director::getInstance()->getWinSize().width;
		float h = Director::getInstance()->getWinSize().height;
		float scx = 1.5 / live2DModel->getCanvasWidth();
		float scy = -1.5 / live2DModel->getCanvasWidth() * (w / h);
		float x = -0.75;
		float y = 1.25;
		float matrix[] = {
			scx , 0 , 0 , 0 ,
			0 , scy ,0 , 0 ,
			0 , 0 , 1 , 0 ,
			x , y , 0 , 1
		};

		live2DModel->setMatrix(matrix);// 位置を設定

		live2DModel->setPremultipliedAlpha(true);
	}

	
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(result_live2D::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(result_live2D::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(result_live2D::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	*/


	srand((unsigned int)time(NULL));

	return true;
}

void result_live2D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	//Sprite::draw(renderer, transform, transformUpdated);
	DrawNode::draw(renderer, transform, flags);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(result_live2D::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);


	}

void result_live2D::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	
	// Live2Dの描画前と描画後に以下の関数を呼んでください
	// live2d::DrawProfileCocos2D::preDraw() ;
	// live2d::DrawProfileCocos2D::postDraw() ;
	// これはOpenGLの状態をもとに戻すための処理です。
	// これを行わない場合、Cocos2DかLive2Dどちらかで状態の不整合が起こります。

	
	

	//アニメーションの再生
	//挙動がおかしいので調査

	int ram = 0;
	if (motionManager->isFinished())
	{		
		
		//ram = rand() % 2;
		//デフォルトモーション
		motionManager->startMotion(motion[0][ram], false);

	}
	motionManager->updateParam(live2DModel);

	live2d::DrawProfileCocos2D::preDraw();

	live2DModel->update();
	live2DModel->draw();

	live2d::DrawProfileCocos2D::postDraw();

	kmGLPopMatrix();
}

result_live2D* result_live2D::createDrawNode()
{
	result_live2D *ret = new result_live2D();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}


}


/*
bool result_live2D::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point p = touch->getLocationInView();
	float x = p.x;
	float y = p.y;

	//if (tapCheck("D_REF.BODY", x, y))CCLOG("BODY!", x, y);
	if (tapCheck("D_REF.HEAD", x, y))CCLOG("HEAD!", x, y);


	return true;
}
void result_live2D::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
}
void result_live2D::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
}

//あたり判定 create by nagga
bool result_live2D::tapCheck(char *area, float ox, float oy)
{
	int index = live2DModel->getDrawDataIndex(area);
	int pointCount = 0;
	float *points = live2DModel->getTransformedPoints(index, &pointCount);
	float left = live2DModel->getCanvasWidth();
	float right = 0;
	float top = live2DModel->getCanvasHeight();
	float bottom = 0;
	for (int i = 0; i < pointCount; i++)
	{
		float px = points[i * DEF::VERTEX_STEP + DEF::VERTEX_OFFSET];
		float py = points[i * DEF::VERTEX_STEP + DEF::VERTEX_OFFSET + 1];
		//キャラによって変える必要あり？
		if (px < left)left = (px/2)*1.25;
		if (px > right)right = (px/2)*1.15;
		if (py < top)top = (py/2);
		if (py > bottom)bottom = (py/2)*2.5;
	}
	float x = ox * 2;
	float y = oy * 2;
	//それぞれの頂点を取ってタッチされた場所がtrueかfalseで返す
	return (left <= x && x <= right && top <= y && y <= bottom);
}
*/

//正解モーション
void result_live2D::setAnimation_Prize(int num)
{
	
	motionManager->startMotion(motion[1][num], false);
	//helloからMove_buttonを引っ張ってくる
	((result*)this->getParent())->Move_button();

}
//不正解モーション
void result_live2D::setAnimation_Blank(int num)
{
	
	motionManager->startMotion(motion[2][num], false);
}



