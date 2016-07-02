//
//  RoundedBoxSprite.cpp
//
//
//  Created by lp6m on 2015/04/02.
//
//  URL
//  http://lp6m.hatenablog.com/entry/2015/04/02/053252
//
//

#include "RoundedBoxSprite.hpp"


USING_NS_CC;


#pragma mark -
RoundedBoxSprite::RoundedBoxSprite()
{
}


RoundedBoxSprite::~RoundedBoxSprite()
{
}


#pragma mark -
RoundedBoxSprite * RoundedBoxSprite::create(const Size &size,
                                            const Color3B &BGColor,
                                            const float CornerRadius,
                                            const int CornerSegment,
                                            const std::string &String,
                                            const Color3B &FontColor,
                                            const int FontSize)
{
    auto pRep = new RoundedBoxSprite();
    if (pRep && pRep->init(size, BGColor, CornerRadius, CornerSegment, String, FontColor, FontSize))
    {
        pRep->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRep);
    }

    return pRep;
}


bool RoundedBoxSprite::init(const Size &size,
                            const Color3B &BGColor,
                            const float CornerRadius,
                            const int CornerSegment,
                            const std::string &String,
                            const Color3B &FontColor,
                            const int FontSize)
{
    auto result = false;
    do
    {
        if (! Sprite::init())
        {
            break;
        }

        this->setContentSize(size);

        //構成
        {
            //マスクを作成
            if (auto clipNode = this->createRoundedRectMaskNode(size, CornerRadius, CornerSegment))
            {
                //マスクされる元となるスプライトを用意
                if (auto sita = Sprite::create())
                {
                    sita->setTextureRect(Rect(0, 0,size.width,size.height));
                    sita->setColor(BGColor);

                    //元スプライトをクリップノードの子として登録
                    clipNode->addChild(sita);
                }

                //Sprite の真ん中に配置
                const auto pos = Point(size * 0.5f);
                clipNode->setPosition(pos);

                //クリップノードとラベルを結果用のスプライトの子として登録
                this->addChild(clipNode);

                //ラベル
                if (auto label = Label::createWithSystemFont(String, "Arial",FontSize))
                {
                    label->setColor(FontColor);

                    clipNode->addChild(label);
                }
            }
        }

        result = true;
    } while (0);

    return result;
}


#pragma mark -

//quote from http://discuss.cocos2d-x.org/t/how-can-i-create-sprite-with-rounded-corner/15403/4
//stevetranby,Thanks!!!
//void RoundedBoxSprite::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
void RoundedBoxSprite::appendCubicBezier(const int startPoint,
                                         std::vector<Vec2>& verts,
                                         const Vec2& from,
                                         const Vec2& control1,
                                         const Vec2& control2,
                                         const Vec2& to,
                                         const uint32_t segments)
{
    float t = 0;
    for(int i = 0; i < segments; i++)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;

        verts[startPoint + i] = Vec2(x,y);

        t += 1.0f / segments;
    }
}

ClippingNode * RoundedBoxSprite::createRoundedRectMaskNode(const Size &size,
                                                           const float radius,
                                                           const int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);

    // define corner control points
    std::vector<Vec2> verts(16);

    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);

    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);

    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);

    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);

    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);

    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];

    for(int i = 0; i<polyVerts.size(); i++){//追加
        polyVerts[i].x -= size.width/2; polyVerts[i].y -= size.height/2;
    }
    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0],(int)polyVerts.size(), Color4F::WHITE, 0.0f, Color4F::WHITE);

    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}
