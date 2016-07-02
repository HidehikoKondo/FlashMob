#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "audio/include/SimpleAudioEngine.h"


USING_NS_CC;


static cocos2d::Size designResolutionSize = cocos2d::Size( 480,  320);
static cocos2d::Size smallResolutionSize  = cocos2d::Size( 480,  320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024,  768);
static cocos2d::Size largeResolutionSize  = cocos2d::Size(2048, 1536);


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}


//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}


// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}


bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("SpaJam2016", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("SpaJam2016");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);


    {
        // Set the design resolution
        glview->setDesignResolutionSize(designResolutionSize.width,
                                        designResolutionSize.height,
                                        ResolutionPolicy::FIXED_HEIGHT);

        auto frameSize = glview->getFrameSize();

        auto scaleRate = 1.0f;

        scaleRate = 2.0f;

//        // if the frame's height is larger than the height of medium size.
//        if (frameSize.height > mediumResolutionSize.height)
//        {
//            scaleRate = MIN(largeResolutionSize.height / designResolutionSize.height,
//                            largeResolutionSize.width /  designResolutionSize.width);
//        }
//        // if the frame's height is larger than the height of small size.
//        else if (frameSize.height > smallResolutionSize.height)
//        {
//            scaleRate = MIN(mediumResolutionSize.height / designResolutionSize.height,
//                            mediumResolutionSize.width  / designResolutionSize.width);
//        }
//        // if the frame's height is smaller than the height of medium size.
//        else
//        {
//            scaleRate = MIN(smallResolutionSize.height / designResolutionSize.height,
//                            smallResolutionSize.width  / designResolutionSize.width);
//        }

        director->setContentScaleFactor(scaleRate);
    }

    if (auto fileUtils = FileUtils::getInstance())
    {
        std::vector<std::string> searchPaths;
        {
            searchPaths.push_back("fonts");
            searchPaths.push_back("sounds");
            searchPaths.push_back("res");
        }
        fileUtils->setSearchPaths(searchPaths);
    }

    register_all_packages();


    if (auto simpleAudio = CocosDenshion::SimpleAudioEngine::getInstance())
    {
        //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");
        simpleAudio->playBackgroundMusic("bgm.mp3", true);

        simpleAudio->preloadEffect("drinking_a_hot_one2.mp3");
        simpleAudio->preloadEffect("drum-japanese2.mp3");
        simpleAudio->preloadEffect("shakashaka.mp3");
    }

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
