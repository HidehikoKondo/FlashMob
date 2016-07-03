//
//  MobLayer.cpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#include "MobLayer.hpp"

#include "RoundedBoxSprite.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
MobLayer::MobLayer()
{
}


MobLayer::~MobLayer()
{
}


#pragma mark -
PhotonScene * MobLayer::createScene()
{
    auto scene = PhotonScene::create();

    if (scene)
    {
        if (auto layer = MobLayer::create())
        {
            scene->addChild(layer);
        }
    }

    return scene;
}


#pragma mark -
MobLayer * MobLayer::create()
{
    auto pRep = new MobLayer();

    if (pRep && pRep->init())
    {
        pRep->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRep);
    }

    return pRep;
}


bool MobLayer::init()
{
    auto result = false;

    do
    {
        if (! ModalLayer::init() )
        {
            break;
        }


        //TEST: 角丸ボタン
        {
            auto sprite1 = RoundedBoxSprite::create(cocos2d::Size(300.0f, 50.0f),
                                                   Color3B(111, 201, 88),
                                                   10,
                                                   30,
                                                   "TEST 1",
                                                   Color3B::WHITE,
                                                   32.0f);

            auto sprite2 = RoundedBoxSprite::create(cocos2d::Size(300.0f, 50.0f),
                                                    Color3B(111 - 25, 201 - 25, 88 - 25),
                                                    10,
                                                    30,
                                                    "TEST 2",
                                                    Color3B(255 - 25, 255 - 25, 255 - 25),
                                                    32.0f);


            auto func = [this](Ref * pSender) {
                //Photon
                if (auto scene = dynamic_cast<PhotonScene *>(this->getParent()))
                {
                    if (auto logic = scene->getNetworkLogic())
                    {
                        //相手に通知
                        {
                            auto eventContent = new ExitGames::Common::Hashtable();
                            {
                                eventContent->put<int, int>(1, 999);

                                logic->sendEvent(2, eventContent);
                            }
                            delete eventContent;
                        }
                    }
                }
            };

            if (auto item = MenuItemSprite::create(sprite1, sprite2, func))
            {
                if (auto menu = Menu::createWithItem(item))
                {
                    auto pos = cocos2d::Point::ZERO;
                    {
                        auto visibleRect = cocos2d::Rect::ZERO;
                        {
                            visibleRect.origin = Director::getInstance()->getVisibleOrigin();
                            visibleRect.size   = Director::getInstance()->getVisibleSize();
                        }

                        pos = cocos2d::Point(visibleRect.getMidX(), visibleRect.getMaxY() - 50.0f);
                    }
                    menu->setPosition(pos);

                    this->addChild(menu, 100);
                }
            }
        }


        result = true;
    } while (0);

    return result;
}


#pragma mark -
void MobLayer::onEnter()
{
    ModalLayer::onEnter();
}


void MobLayer::onExit()
{
    ModalLayer::onExit();
}
