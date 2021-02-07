#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Texture.h"
class Player :
    public Sprite
{
public:
    Player();
    void update() override;
    //void draw() override;
protected:
    Texture _texture_head;
    Texture _texture_body;
    Texture _texture_hand;
    Texture _texture_leg;
};

