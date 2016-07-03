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

#include "audio/include/SimpleAudioEngine.h"


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


        {
            //TEST: 角丸ボタン
            {
                auto sprite1 = RoundedBoxSprite::create(cocos2d::Size(200.0f, 50.0f),
                                                        Color3B(0x2E, 0x64, 0xFE),
                                                        10,
                                                        30,
                                                        "応援する",
                                                        Color3B::WHITE,
                                                        32.0f);

                auto sprite2 = RoundedBoxSprite::create(cocos2d::Size(200.0f, 50.0f),
                                                        Color3B(0x2E - 25, 0x64 - 25, 0xFE - 25),
                                                        10,
                                                        30,
                                                        "応援する",
                                                        Color3B(255 - 25, 255 - 25, 255 - 25),
                                                        32.0f);


                auto func = [this](Ref * pSender) {

                    //みんなに通知
                    //Photon
                    if (auto scene = dynamic_cast<PhotonScene *>(this->getParent()))
                    {
                        if (auto logic = scene->getNetworkLogic())
                        {
                            auto eventContent = new ExitGames::Common::Hashtable();
                            {
                                auto visibleRect = cocos2d::Rect::ZERO;
                                {
                                    visibleRect.origin = Director::getInstance()->getVisibleOrigin();
                                    visibleRect.size   = Director::getInstance()->getVisibleSize();
                                }

                                std::random_device rnd;                                 // 非決定的な乱数生成器を生成
                                std::mt19937 mt(rnd());                                 //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
                                std::uniform_int_distribution<> rand_range(0, 20);      // [0, 10] 範囲の一様乱数

                                eventContent->put<int, int>(1, 1);
                                eventContent->put<int, int>(2, static_cast<int>(visibleRect.size.height * rand_range(mt)));

                                logic->sendEvent(4, eventContent);
                            }
                            delete eventContent;
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
                            
                            pos = cocos2d::Point(visibleRect.getMidX(), visibleRect.getMinY() + 50.0f);
                        }
                        menu->setPosition(pos);
                        
                        this->addChild(menu, 100);
                    }
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
        auto callback = [this, label](EventCustom * event) {

            if (auto data = static_cast<ValueMap *>(event->getUserData()))
            {
                CCLOG("playerNr : %d", (*data)["playerNr"].asInt());
                CCLOG("   event : %d", (*data)["event"].asInt());
                CCLOG("   value : %d", (*data)["value"].asInt());

                const auto eventId = (*data)["event"].asInt();
                const auto value   = (*data)["value"].asInt();

                if (eventId == 3)
                {
                    if (label)
                    {
                        const std::string list[] = {
                            "CONGRATULATIONS !!",
                            "GOOD",
                            "BAD",
                            "OH MY GOD...",
                        };

                        const auto count = sizeof(list) / sizeof(*list);

                        const auto index = count - 1 - value;

                        const auto text = list[index];
                        label->setString(text);


                        const auto name = "particle";
                        if (auto particle = dynamic_cast<ParticleSystemQuad *>(this->getChildByName(name)))
                        {
                            particle->removeFromParentAndCleanup(true);
                        }


                        //BGM
                        {
                            const std::string bgmFile[] = {
                                "success.mp3",
                                "success.mp3",
                                "fail.mp3",
                                "fail.mp3",
                            };

                            const auto name = bgmFile[index];
                            if (name.length() > 0)
                            {
                                CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(name.c_str());
                            }
                        }


                        //パーティクル
                        {
                            const auto name = "particle";
                            if (auto particle = dynamic_cast<ParticleSystemQuad *>(this->getChildByName(name)))
                            {
                                particle->removeFromParentAndCleanup(true);
                            }

                            //if (index < 2)
                            {
                                const std::string paticleList[] = {
                                    "Particle_5.plist",
                                    "",
                                    "",
                                    "Particle_4.plist",
                                };


                                const auto partileName = paticleList[index];
                                if (partileName.length() > 0)
                                {
                                    if (auto particle = ParticleSystemQuad::create(partileName))
                                    {
                                        particle->setName(name);
                                        particle->setAutoRemoveOnFinish(true);

                                        auto pos = Vec2::ZERO;
                                        {
                                            auto visibleRect = cocos2d::Rect::ZERO;
                                            {
                                                visibleRect.origin = Director::getInstance()->getVisibleOrigin();
                                                visibleRect.size   = Director::getInstance()->getVisibleSize();
                                            }

                                            if (index == 0)
                                            {
                                                pos = Vec2(visibleRect.getMidX(), visibleRect.getMaxY());
                                                pos += Vec2(0.0f, 100.0f);
                                            }
                                            else if (index == (sizeof(paticleList)/sizeof(*paticleList) - 1))
                                            {
                                                pos = Vec2(visibleRect.getMidX(), visibleRect.getMidY());
                                                //pos += Vec2(0.0f, 100.0f);
                                            }
                                        }
                                        particle->setPosition(pos);

                                        this->addChild(particle, 200);
                                    }
                                }
                            }
                        }

                        //TODO: 協力者用処理
                    }
                }

                if (eventId == 4)
                {
                    const std::string textList[] = {
                        "wwwwww",
                        "見てるよww",
                        "ちょww はやくwwwwww",
                    };

                    const float fontSizeList[] = {
                        32.0f,
                        24.0f,
                    };

                    const auto count = sizeof(textList)/sizeof(*textList);


                    std::random_device rnd;                                     // 非決定的な乱数生成器を生成
                    std::mt19937 mt(rnd());                                     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
                    std::uniform_int_distribution<> rand_range1(0, sizeof(textList)/sizeof(*textList) - 1);             // テキスト
                    std::uniform_int_distribution<> rand_range2(0, sizeof(fontSizeList)/sizeof(*fontSizeList) - 1);     // フォントサイズ

                    if (auto label = Label::createWithSystemFont(textList[rand_range1(mt)],
                                                                 "",
                                                                 fontSizeList[rand_range2(mt)]))
                    {

                    }
                }
            }
        };

        if (auto listener = EventListenerCustom::create(EVENT_NAME__PHOTON_RECIEVE, callback))
        {
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        }
    }
}


void MobLayer::onExit()
{
    ModalLayer::onExit();
}
