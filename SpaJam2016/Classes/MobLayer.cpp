//
//  MobLayer.cpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#include "MobLayer.hpp"


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
