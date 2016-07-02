#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//Photon Sample Class
#include "NetworkLogic.h"


class HelloWorld : public cocos2d::Layer
{
public:
    CC_SYNTHESIZE_READONLY(NetworkLogic *, _networkLogic, NetworkLogic);


protected:
    HelloWorld();
    virtual ~HelloWorld();

public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(HelloWorld);

protected:
    virtual bool init() override;

private:
    bool initHelloWorld();


protected:
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    virtual void update(float delta) override;


protected:
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;


private:
    void addParticle(const int &playerNr, const cocos2d::Point &position);

public:
    void addParticle(const int &playerNr, const float &x, const float &y) {
        this->addParticle(playerNr, cocos2d::Point(x, y));
    };
};

#endif
