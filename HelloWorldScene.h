#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

private:
    // ===== 创建 =====
    void createCharacter();
    void createCamera();
    void setupInput();

    // ===== 动画 =====
    void playWalk();
    void playIdle();

    // ===== 更新 =====
    virtual void update(float dt) override;

private:
    cocos2d::Sprite3D* _character = nullptr;
    cocos2d::Camera* _camera = nullptr;

    // 输入
    bool _w = false;
    bool _a = false;
    bool _s = false;
    bool _d = false;

    enum class AnimState
    {
        IDLE,
        WALK
    };

    AnimState _animState = AnimState::IDLE;
};

#endif // __HELLOWORLD_SCENE_H__
