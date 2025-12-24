#ifndef __PLAYER_WALK_SCENE_H__
#define __PLAYER_WALK_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

// 明确声明类为本地类，不使用dllimport
class PlayerWalkScene : public Layer
{
public:
    // 直接声明方法，不添加__declspec(dllimport)修饰
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PlayerWalkScene); // 该宏会自动生成create()方法，无需额外修饰
};

#endif // __PLAYER_WALK_SCENE_H__