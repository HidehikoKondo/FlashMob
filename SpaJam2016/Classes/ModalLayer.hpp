//
//  ModalLayer.hpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#ifndef ModalLayer_hpp
#define ModalLayer_hpp

#include "cocos2d.h"


class ModalLayer : public cocos2d::Layer
{
protected:
    ModalLayer();
    virtual ~ModalLayer();


public:
    CREATE_FUNC(ModalLayer);

protected:
    virtual bool init() override;


protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};

#endif
