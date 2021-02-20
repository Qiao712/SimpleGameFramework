#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
#include <memory>
using std::shared_ptr;

/**
* @brief 玩家控制的角色
*/
class Player :
    public Sprite
{
public:
    Player();
    void update() override;
protected:
    shared_ptr<Sprite> _head;
    shared_ptr<Sprite> _body;
    shared_ptr<Sprite> _hand_left;
    shared_ptr<Sprite> _hand_right;

    /**接收键盘鼠标控制*/
    void control();

    /**控制行走时的动作*/
    void walkingAction();
};

