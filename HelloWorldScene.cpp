#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
        return false;

    createCharacter();
    createCamera();
    setupInput();

    scheduleUpdate();
    return true;
}

// ================= 角色 =================

void HelloWorld::createCharacter()
{
    _character = Sprite3D::create("models/walkfinal.c3b");
    CCASSERT(_character, "❌ walkfinal.c3b 加载失败");

    _character->setScale(1.0f);

    // ⚠ 重要：角色站在地面上（Z 向上体系）
    _character->setPosition3D(Vec3(0, 0, 0));
    _character->setRotation3D(Vec3(0, 0, 0));

    addChild(_character);

    playIdle();
}

// ================= 相机 =================

void HelloWorld::createCamera()
{
    auto size = Director::getInstance()->getVisibleSize();
    _camera = Camera::createPerspective(
        60.0f,
        size.width / size.height,
        0.1f,
        1000.0f
    );
    addChild(_camera);
}

// ================= 输入 =================

void HelloWorld::setupInput()
{
    auto kb = EventListenerKeyboard::create();

    kb->onKeyPressed = [&](EventKeyboard::KeyCode key, Event*)
        {
            if (key == EventKeyboard::KeyCode::KEY_W) _w = true;
            if (key == EventKeyboard::KeyCode::KEY_S) _s = true;
            if (key == EventKeyboard::KeyCode::KEY_A) _a = true;
            if (key == EventKeyboard::KeyCode::KEY_D) _d = true;
        };

    kb->onKeyReleased = [&](EventKeyboard::KeyCode key, Event*)
        {
            if (key == EventKeyboard::KeyCode::KEY_W) _w = false;
            if (key == EventKeyboard::KeyCode::KEY_S) _s = false;
            if (key == EventKeyboard::KeyCode::KEY_A) _a = false;
            if (key == EventKeyboard::KeyCode::KEY_D) _d = false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(kb, this);
}

// ================= 动画 =================

void HelloWorld::playIdle()
{
    if (_animState == AnimState::IDLE)
        return;

    _character->stopAllActions();

    auto anim3d = Animation3D::create("models/walkfinal.c3b");

    // idle：用 1 帧假静止
    auto animate = Animate3D::createWithFrames(
        anim3d,
        1,
        2,
        30.0f
    );

    auto repeat = RepeatForever::create(animate);
    _character->runAction(repeat);

    _animState = AnimState::IDLE;
}

void HelloWorld::playWalk()
{
    if (_animState == AnimState::WALK)
        return;

    _character->stopAllActions();

    auto anim3d = Animation3D::create("models/walkfinal.c3b");

    // ✅ walk：1 – 36（你刚刚 Bake 的区间）
    auto animate = Animate3D::createWithFrames(
        anim3d,
        1,
        37,     // 注意：结束帧不包含
        30.0f
    );

    auto repeat = RepeatForever::create(animate);
    _character->runAction(repeat);

    _animState = AnimState::WALK;
}

// ================= Update =================

void HelloWorld::update(float dt)
{
    if (!_character || !_camera)
        return;

    float moveSpeed = 3.0f * dt;
    float rotSpeed = 90.0f * dt;

    // ===== 旋转 =====
    Vec3 rot = _character->getRotation3D();
    if (_a) rot.y += rotSpeed;
    if (_d) rot.y -= rotSpeed;
    _character->setRotation3D(rot);

    // ===== 前进方向（基于朝向）=====
    Vec3 forward;
    Mat4 mat = _character->getNodeToWorldTransform();
    mat.getForwardVector(&forward);
    forward = -forward;   // cocos 前向修正
    forward.normalize();

    Vec3 pos = _character->getPosition3D();
    bool moving = false;

    if (_w)
    {
        pos += forward * moveSpeed;
        moving = true;
    }
    if (_s)
    {
        pos -= forward * moveSpeed;
        moving = true;
    }

    _character->setPosition3D(pos);

    // ===== 动画切换 =====
    if (moving)
        playWalk();
    else
        playIdle();

    // ===== 第三人称相机（脑后 45°）=====
    Vec3 camPos = pos
        - forward * 6.0f   // 后方
        + Vec3(0, 2.0f, 0); // 高度

    _camera->setPosition3D(camPos);
    _camera->lookAt(pos + Vec3(0, 1.2f, 0));
}
