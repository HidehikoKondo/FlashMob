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
        if (auto label = Label::createWithSystemFont("", "", 24))
        {
            //label->setVisible(false);

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
                    func_log("接続中");
                    logic->setLastInput(INPUT_2);
                }
                else
                {
                    func_log("接続開始");
                    logic->setLastInput(INPUT_1);
                }
                break;
            }
            case (STATE_DISCONNECTED):
            {
                func_log("再接続");
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
                func_log("接続処理中 ...");
                break;
            }
            case (STATE_JOINED):
            {
                func_log("接続");
                break;
            }

            case (STATE_LEAVING):
            {
                func_log("切断 ...");
                break;
            }
            case (STATE_DISCONNECTING):
            {
                func_log("切断 ...");
                break;
            }

            default:
                break;
        }


        while (! logic->eventQueue.empty())
        {
            //std::array<float, 4>
            auto arr = logic->eventQueue.front();
            logic->eventQueue.pop();

            {
                ValueMap map;
                {
                    map["playerNr"] = arr[0];
                    map["event"]    = arr[1];
                    map["value"]    = arr[2];
                    map["value2"]   = arr[3];
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
