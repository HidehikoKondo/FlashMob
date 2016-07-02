//
//  PhotonScene.hpp
//  SpaJam2016
//
//  Created by OhsakaTakashi on 2016/07/03.
//
//

#ifndef PhotonScene_hpp
#define PhotonScene_hpp

#include "cocos2d.h"

//Photon Sample Class
#include "NetworkLogic.h"


class PhotonScene : public cocos2d::Scene
{
public:
    CC_SYNTHESIZE_READONLY(NetworkLogic *, _networkLogic, NetworkLogic);

protected:
    PhotonScene();
    virtual ~PhotonScene();


public:
    CREATE_FUNC(PhotonScene);

protected:
    virtual bool init() override;


protected:
    virtual void update(float delta) override;


protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};

#endif
