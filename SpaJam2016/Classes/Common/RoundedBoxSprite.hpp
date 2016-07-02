//
//  RoundedBoxSprite.hpp
//
//
//  Created by lp6m on 2015/04/02.
//
//  URL
//  http://lp6m.hatenablog.com/entry/2015/04/02/053252
//

#ifndef RoundedBoxSprite_hpp
#define RoundedBoxSprite_hpp

#include "cocos2d.h"


class RoundedBoxSprite : public cocos2d::Sprite
{
protected:
    RoundedBoxSprite();
    virtual ~RoundedBoxSprite();

public:
    static RoundedBoxSprite * create(const cocos2d::Size &size,
                                     const cocos2d::Color3B &BGColor,
                                     const float CornerRadius,
                                     const int CornerSegment,
                                     const std::string &String,
                                     const cocos2d::Color3B &FontColor,
                                     const int FontSize);

protected:
    bool init(const cocos2d::Size &size,
              const cocos2d::Color3B &BGColor,
              const float CornerRadius,
              const int CornerSegment,
              const std::string &String,
              const cocos2d::Color3B &FontColor,
              const int FontSize);


protected:
    void appendCubicBezier(const int startPoint,
                           std::vector<cocos2d::Vec2>& verts,
                           const cocos2d::Vec2& from,
                           const cocos2d::Vec2& control1,
                           const cocos2d::Vec2& control2,
                           const cocos2d::Vec2& to,
                           const uint32_t segments);

    cocos2d::ClippingNode * createRoundedRectMaskNode(const cocos2d::Size &size,
                                                      const float radius,
                                                      const int cornerSegments);
};

#endif
