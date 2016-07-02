//
//  MobLayer.hpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#ifndef MobLayer_hpp
#define MobLayer_hpp

#include "cocos2d.h"

#include "PhotonScene.hpp"
#include "ModalLayer.hpp"


class MobLayer : public ModalLayer
{
protected:
    MobLayer();
    virtual ~MobLayer();


public:
    static PhotonScene * createScene();
    static MobLayer * create();

protected:
    bool init();


protected:
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    //virtual void update(float delta) override;
};

#endif
