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

    //this->scheduleUpdate();

    {
        auto callback = [this](EventCustom * event) {

            if (auto data = static_cast<ValueMap *>(event->getUserData()))
            {
//                CCLOG("playerNr : %d", (*data)["playerNr"].asInt());
//                CCLOG("   event : %d", (*data)["event"].asInt());
//                CCLOG("   value : %d", (*data)["value"].asInt());

                const auto eventId = (*data)["event"].asInt();
                const auto value   = (*data)["value"].asInt();
                if ((eventId == 2) && (value == 999))
                {
                    cocos2dExt::NativeInterface::putTextToWatch("REPLY");
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__PHOTON_RECIEVE, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }

    {
        auto callback = [this](EventCustom * event) {

            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                const auto text = data->asString();

                if (text.compare("REPLYOK") == 0)
                {
                    CCLOG("OK");
                }
                else if (text.compare("REPLYNG") == 0)
                {
                    CCLOG("NG");
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


#pragma mark -
void ReplyLayer::update(float delta)
{
//    //デバッグ処理
//    auto func_log = [this](const std::string & message) {
//        CCLOG("%s log:%s", __PRETTY_FUNCTION__, message.c_str());
//        if (auto label = dynamic_cast<Label *>(this->getChildByName("label")))
//        {
//            label->setString(message);
//        }
//    };
//
//
//    if (auto scene = dynamic_cast<PhotonScene *>(this->getParent()))
//    {
//        if (auto logic = scene->getNetworkLogic())
//        {
//            logic->run();
//
//            while (! logic->eventQueue.empty())
//            {
//                //std::array<float, 3>
//                auto arr = logic->eventQueue.front();
//                logic->eventQueue.pop();
//
//
//                auto playerNr = static_cast<int>(arr[0]);
//                if (arr[1] == 999)
//                {
//                    cocos2dExt::NativeInterface::putTextToWatch("REPLY");
//                }
//            }
//        }
//    }
}
