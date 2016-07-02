//
//  ReplyLayer.hpp
//  SpaJam2016
//
//  Created by UdonkoApps on 2016/07/03.
//
//

#ifndef ReplyLayer_hpp
#define ReplyLayer_hpp

#include "cocos2d.h"
#include "ModalLayer.hpp"

#include "PhotonScene.hpp"


class ReplyLayer : ModalLayer
{
protected:
    ReplyLayer();
    virtual ~ReplyLayer();

public:
    static PhotonScene * createScene();
    CREATE_FUNC(ReplyLayer);

protected:
    virtual bool init() override;


protected:
    virtual void onEnter() override;
    virtual void onExit() override;


protected:
    virtual void update(float delta) override;
};

#endif
