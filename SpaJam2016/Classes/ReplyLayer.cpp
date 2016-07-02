//
//  ReplyLayer.cpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#include "ReplyLayer.hpp"

#include "PrivateConfig.h"


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

        result = true;
    } while (0);

    return result;
}


#pragma mark -
void ReplyLayer::onEnter()
{
    ModalLayer::onEnter();

    {
        auto callback = [this](EventCustom * event) {

            if (auto data = static_cast<Value *>(event->getUserData()))
            {
                const auto text = data->asString();

                if (text.compare("REPLYOK") == 0)
                {
                }
                else if (text.compare("REPLYNG") == 0)
                {
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
}
