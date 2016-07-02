//
//  PhotonScene.cpp
//  SpaJam2016
//
//  Created by OhsakaTakashi on 2016/07/03.
//
//

#include "PhotonScene.hpp"

#include "MobLayer.hpp"
#include "ReplyLayer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
PhotonScene::PhotonScene()
{
    this->_networkLogic = new NetworkLogic();
}


PhotonScene::~PhotonScene()
{
    CC_SAFE_DELETE(this->_networkLogic);
}


#pragma mark -
bool PhotonScene::init()
{
    auto result = false;

    do
    {
        if (! Scene::init())
        {
            break;
        }


        // add a label shows "Hello World"
        // create and initialize a label
        if (auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24))
        {
            label->setName("label");

            auto pos = cocos2d::Point::ZERO;
            {
                auto labelSize = label->getContentSize();

                const auto visibleSize   = Director::getInstance()->getVisibleSize();
                const auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

                pos  = visibleOrigin;
                pos += cocos2d::Point(visibleSize.width * 0.5f, visibleSize.height);
                pos += cocos2d::Point(0.0f, -labelSize.height);
            }
            label->setPosition(pos);


            // add the label as a child to this layer
            this->addChild(label, 1);
        }


        result = true;
    } while (0);

    return result;
}


#pragma mark -
void PhotonScene::update(float delta)
{
    //デバッグ処理
    auto func_log = [this](const std::string & message) {
        CCLOG("%s log:%s", __PRETTY_FUNCTION__, message.c_str());
        if (auto label = dynamic_cast<Label *>(this->getChildByName("label")))
        {
            label->setString(message);
        }
    };


    if (auto logic = this->getNetworkLogic())
    {
        logic->run();

        switch (logic->getState())
        {
            case (STATE_CONNECTED):
            case (STATE_LEFT):
            {
                // ルームが存在すればジョイン、なければ作成
                if (logic->isRoomExists())
                {
                    func_log("Join");
                    logic->setLastInput(INPUT_2);
                }
                else
                {
                    func_log("Create");
                    logic->setLastInput(INPUT_1);
                }
                break;
            }
            case (STATE_DISCONNECTED):
            {
                func_log("Disconnected ... reConnect");
                logic->connect();
                break;
            }

            case (STATE_CONNECTING):
            {
//                CCLOG("Connecting ...");
                break;
            }

            case (STATE_JOINING):
            {
                func_log("Joining ...");
                break;
            }
            case (STATE_JOINED):
            {
                func_log("Joined");
                break;
            }

            case (STATE_LEAVING):
            {
                func_log("Leaving ...");
                break;
            }
            case (STATE_DISCONNECTING):
            {
                func_log("Disconnecting ...");
                break;
            }

            default:
                break;
        }


        while (! logic->eventQueue.empty())
        {
            //std::array<float, 3>
            auto arr = logic->eventQueue.front();
            logic->eventQueue.pop();

            {
                ValueMap map;
                {
                    map["playerNr"] = arr[0];
                    map["event"]    = arr[1];
                    map["value"]    = arr[2];
                }

                auto event = EventCustom(EVENT_NAME__PHOTON_RECIEVE);
                event.setUserData(&map);
                this->getEventDispatcher()->dispatchEvent(&event);
            }
//            auto playerNr = static_cast<int>(arr[0]);
//            auto pos = cocos2d::Point(arr[1], arr[2]);
//            this->addParticle(playerNr, pos);
        }
    }
}


void PhotonScene::onEnter()
{
    Scene::onEnter();

    this->scheduleUpdate();
}


void PhotonScene::onExit()
{
    Scene::onExit();

    this->unscheduleUpdate();
}
