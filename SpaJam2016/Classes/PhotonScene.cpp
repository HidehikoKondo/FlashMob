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
