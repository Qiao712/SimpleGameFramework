#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
#include <memory>
using std::shared_ptr;

/**
* @brief ��ҿ��ƵĽ�ɫ
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

    /**���ռ���������*/
    void control();

    /**��������ʱ�Ķ���*/
    void walkingAction();
};

