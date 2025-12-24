#include "PlayerWalkScene.h"

Scene* PlayerWalkScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayerWalkScene::create();
    if (layer)
    {
        scene->addChild(layer);
    }
    return scene;
}

bool PlayerWalkScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载3D模型
    std::string c3bFilePath = "models/walkfinal.c3b";
    auto sprite3D = Sprite3D::create(c3bFilePath);

    if (sprite3D == nullptr)
    {
        log("错误：加载 %s 失败！", c3bFilePath.c_str());
        auto tipLabel = Label::createWithSystemFont("walkfinal.c3b 加载失败", "Arial", 30);
        tipLabel->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(tipLabel);
        return true;
    }

    sprite3D->setScale(1.0f);
    sprite3D->setPosition3D(Vec3(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2,
        0));
    sprite3D->setRotation3D(Vec3(0, 180, 0));
    this->addChild(sprite3D);

    // 3D相机
    auto camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 1000);
    camera->setPosition3D(Vec3(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2,
        100));
    camera->lookAt(Vec3(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2,
        0));
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);

    // 方向光
    auto dirLight = DirectionLight::create(Vec3(-1, -1, -1), Color3B::WHITE);
    this->addChild(dirLight);

    return true;
}