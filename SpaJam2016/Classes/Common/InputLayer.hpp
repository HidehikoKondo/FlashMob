//
//  InputLayer.hpp
//  ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#ifndef InputLayer_hpp
#define InputLayer_hpp

#include "cocos2d.h"


class InputLayer : public cocos2d::Layer
{
protected:
    InputLayer();
    virtual ~InputLayer();

public:
    CREATE_FUNC(InputLayer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;


public:
    virtual void onAcceleration(cocos2d::Acceleration * acc, cocos2d::Event * unused_event) override;
};
#endif
