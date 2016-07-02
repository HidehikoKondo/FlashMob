//
//  InputLayer.cpp
//  ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#include "InputLayer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
InputLayer::InputLayer()
{
}
InputLayer::~InputLayer()
{
}


#pragma mark -
bool InputLayer::init()
{
    auto result = false;

    do
    {
        if (! Layer::init())
        {
            break;
        }

        result = true;
    } while (0);

    return result;
}


#pragma mark -
void InputLayer::onEnter()
{
    Layer::onEnter();

    if (auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(InputLayer::onAcceleration, this)))
    {
        //MARK: 傾きセンサー使用
        Device::setAccelerometerEnabled(true);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    }
}

void InputLayer::onExit()
{
    Layer::onExit();

    this->getEventDispatcher()->removeEventListenersForTarget(this);
}


#pragma mark -
void InputLayer::onAcceleration(Acceleration * acc, Event * unused_event)
{
    //イベント通知
    {
        auto event = EventCustom(EVENT_NAME__ACCELERATION);

        event.setUserData(acc);

        this->getEventDispatcher()->dispatchEvent(&event);
    }
}
