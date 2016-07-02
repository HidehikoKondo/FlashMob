//
//  ModalLayer.cpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#include "ModalLayer.hpp"


USING_NS_CC;


#pragma mark -
ModalLayer::ModalLayer()
{
}


ModalLayer::~ModalLayer()
{
}


#pragma mark -
bool ModalLayer::init()
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
void ModalLayer::onEnter()
{
    Layer::onEnter();

    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [this](Touch *touch, Event *unused_event) -> bool {
            return false;
        };

        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    }
}


void ModalLayer::onExit()
{
    Layer::onExit();

    this->getEventDispatcher()->removeEventListenersForTarget(this);
}
