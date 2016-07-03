//
//  ReplyLayer.cpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#include "ReplyLayer.hpp"

#include "PrivateConfig.h"

#include "NativeInterface.h"

#include "RoundedBoxSprite.hpp"


USING_NS_CC;


#pragma mark -
ReplyLayer::ReplyLayer()
{
}


ReplyLayer::~ReplyLayer()
{
}


#pragma mark -
PhotonScene * ReplyLayer::createScene()
{
    auto scene = PhotonScene::create();

    if (scene)
    {
        if (auto layer = ReplyLayer::create())
        {
            scene->addChild(layer);
        }
    }

    return scene;
}


#pragma mark -
bool ReplyLayer::init()
{
    auto result = false;

    do
    {
        if (! ModalLayer::init() )
        {
            break;
        }

        const auto color = Color4B::GRAY;
        if (auto layer = LayerColor::create(color))
        {
            this->addChild(layer);
        }

        result = true;
    } while (0);

    return result;
}


#pragma mark -
void ReplyLayer::onEnter()
{
    ModalLayer::onEnter();


    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    if (label)
    {
        label->setName("result");

        auto pos = Vec2::ZERO;
        {
            auto visibleRect = cocos2d::Rect::ZERO;
            {
                visibleRect.origin = Director::getInstance()->getVisibleOrigin();
                visibleRect.size   = Director::getInstance()->getVisibleSize();
            }

            auto labelSize = label->getContentSize();

            pos  = visibleRect.origin + visibleRect.size * 0.5f;
            //pos += Vec2(0.0f, -labelSize.height);
        }
        label->setPosition(pos);


        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    {
        //TEST: 角丸ボタン
        {
            auto sprite1 = RoundedBoxSprite::create(cocos2d::Size(200.0f, 50.0f),
                                                    Color3B(111, 201, 88),
                                                    10,
                                                    30,
                                                    "MEARRY ?",
                                                    Color3B::WHITE,
                                                    32.0f);

            auto sprite2 = RoundedBoxSprite::create(cocos2d::Size(200.0f, 50.0f),
                                                    Color3B(111 - 25, 201 - 25, 88 - 25),
                                                    10,
                                                    30,
                                                    "MEARRY ?",
                                                    Color3B(255 - 25, 255 - 25, 255 - 25),
                                                    32.0f);


            auto func = [this, label](Ref * pSender) {

//                if (auto item = dynamic_cast<MenuItemSprite *>(pSender))
//                {
//                    item->setEnabled(false);
//                }

                {
                    cocos2dExt::NativeInterface::putTextToWatch("REPLY");

                    if (label)
                    {
                        label->setString("REPLY ... ?");
                    }


//TEST
#if (false)
                    {
                        auto func = [this]() {
                            const auto flag = false;
                            const auto text = (flag) ? ("REPLYOK") : ("REPLYNG");
                            cocos2dExt::NativeInterface::getTextFromWatch(text);
                        };

                        if (auto action = Sequence::create(DelayTime::create(1.0f), CallFunc::create(func), nullptr))
                        {
                            this->runAction(action);
                        }
                    }
#endif
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

                        pos = cocos2d::Point(visibleRect.getMidX(), visibleRect.getMaxY() - 100.0f);
                    }
                    menu->setPosition(pos);

                    this->addChild(menu, 100);
                }
            }
        }
    }

//    {
//        auto callback = [this, label](EventCustom * event) {
//
//            if (auto data = static_cast<ValueMap *>(event->getUserData()))
//            {
////                CCLOG("playerNr : %d", (*data)["playerNr"].asInt());
////                CCLOG("   event : %d", (*data)["event"].asInt());
////                CCLOG("   value : %d", (*data)["value"].asInt());
//
//                const auto eventId = (*data)["event"].asInt();
//                const auto value   = (*data)["value"].asInt();
//                if ((eventId == 2) && (value == 999))
//                {
//                    cocos2dExt::NativeInterface::putTextToWatch("REPLY");
//
//                    if (label)
//                    {
//                        label->setString("REPLY ... ?");
//                    }
//                }
//            }
//        };
//
//        if (auto listener = EventListenerCustom::create(EVENT_NAME__PHOTON_RECIEVE, callback))
//        {
//            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//        }
//    }

    {
        auto callback = [this, label](EventCustom * event) {

            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                const auto text = data->asString();

                auto rep = 0;
                if (text.compare("REPLYOK") == 0)
                {
                    CCLOG("OK");
                    rep = 1;

                    if (label)
                    {
                        label->setString("OK");
                    }
                }
                else if (text.compare("REPLYNG") == 0)
                {
                    CCLOG("NG");
                    rep = 0;

                    if (label)
                    {
                        label->setString("NG");
                    }
                }
                else
                {
                    if (label)
                    {
                        label->setString("ERROR ?");
                    }
                }

                //みんなに通知
                //Photon
                if (auto scene = dynamic_cast<PhotonScene *>(this->getParent()))
                {
                    if (auto logic = scene->getNetworkLogic())
                    {
                        auto eventContent = new ExitGames::Common::Hashtable();
                        {
                            eventContent->put<int, int>(1, rep);

                            logic->sendEvent(3, eventContent);
                        }
                        delete eventContent;
                    }
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__TEXTFROMWATCH, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }
}


void ReplyLayer::onExit()
{
    ModalLayer::onExit();

    this->unscheduleUpdate();
}
