#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


#pragma mark -
HelloWorld::HelloWorld()
{
    this->_networkLogic = new NetworkLogic();
}


HelloWorld::~HelloWorld()
{
    CC_SAFE_DELETE(this->_networkLogic);
}


#pragma mark -
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
    auto result = false;

    do {
        if (! Layer::init())
        {
            break;
        }

        if (! this->initHelloWorld())
        {
            break;
        }

        result = true;
    } while (false);

    return result;
}


bool HelloWorld::initHelloWorld()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // add a "close" icon to exit the progress. it's an autorelease object
    {
        auto callback = [this](Ref* pSender) {
            Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        };

        auto closeItem = MenuItemImage::create(
                                               "CloseNormal.png",
                                               "CloseSelected.png",
                                               callback);

        auto pos = Vec2::ZERO;
        {
            auto itemSize = closeItem->getBoundingBox().size;

            pos = origin;
            pos += Vec2(visibleSize.width, visibleSize.height);
            pos += Vec2(-itemSize.width * 0.5f, +itemSize.height * 0.5f);
        }
        closeItem->setPosition(pos);

        // create menu, it's an autorelease object
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }


    // add a label shows "Hello World"
    // create and initialize a label
    if (auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24))
    {
        label->setVisible(false);

        label->setName("label");

        auto pos = Vec2::ZERO;
        {
            auto labelSize = label->getContentSize();

            pos  = origin;
            pos += Vec2(visibleSize.width * 0.5f, visibleSize.height);
            pos += Vec2(0.0f, -labelSize.height);
        }
        label->setPosition(pos);


        // add the label as a child to this layer
        this->addChild(label, 1);
    }


    // add "HelloWorld" splash screen"
    {
        auto sprite = Sprite::create("HelloWorld.png");

        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    return true;
}


#pragma mark -
void HelloWorld::onEnter()
{
    Layer::onEnter();

    this->scheduleUpdate();

    if (auto listener = EventListenerTouchOneByOne::create())
    {
        listener->onTouchBegan      = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
        listener->onTouchMoved      = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
        listener->onTouchEnded      = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
        listener->onTouchCancelled  = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    }
}

void HelloWorld::onExit()
{
    Layer::onExit();

    this->unscheduleUpdate();

    this->getEventDispatcher()->removeEventListenersForTarget(this);
}


#pragma mark -
void HelloWorld::update(float delta)
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


            auto playerNr = static_cast<int>(arr[0]);
            auto pos = cocos2d::Point(arr[1], arr[2]);
            this->addParticle(playerNr, pos);
        }
    }
}


#pragma mark -
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if (auto logic = this->getNetworkLogic())
    {
        //if (logic->playerNr)
        {
            auto location = touch->getLocation();

            //自分 ( ... 0？)
            this->addParticle(logic->playerNr, location);

            //相手に通知
            {
                auto eventContent = new ExitGames::Common::Hashtable();
                {
                    eventContent->put<int, float>(1, location.x);
                    eventContent->put<int, float>(2, location.y);

                    //TEST
                    eventContent->put<int, int>(3, 12345);
                    eventContent->put<int, bool>(4, true);
                    eventContent->put<int, bool>(5, false);

                    //NG: 文字列の送信
                    //eventContent->put<int, const char *>(10, "test");

                    logic->sendEvent(1, eventContent);
                }
                delete eventContent;
            }
        }
    }
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    this->onTouchEnded(touch, unused_event);
}


#pragma mark -
void HelloWorld::addParticle(const int &playerNr, const cocos2d::Point &position)
{
    ParticleSystemQuad * particle = nullptr;
    switch (playerNr)
    {
        case (0):
        {
            particle = ParticleFire::create();
            break;
        }

        case (1):
        {
            particle = ParticleSun::create();
            break;
        }

        case (2):
        {
            particle = ParticleSmoke::create();
            break;
        }

        case (3):
        {
            particle = ParticleFlower::create();
            break;
        }

        default:
        {
            particle = ParticleSpiral::create();
            break;
        }
    }

    if (particle)
    {
        particle->setDuration(0.1f);
        particle->setSpeed(500);
        particle->setPosition(position);
        particle->setAutoRemoveOnFinish(true);

        this->addChild(particle);
    }


    //番号確認用
    if (auto label = Label::createWithSystemFont(StringUtils::format("playerNr:%d", playerNr), "", 24.0f))
    {
        label->setPosition(position);

        this->addChild(label);

        {
            auto action = Sequence::create(DelayTime::create(0.2f),
                                           FadeOut::create(0.1f),
                                           nullptr);
            if (action)
            {
                label->runAction(action);
            }
        }
    }
}
