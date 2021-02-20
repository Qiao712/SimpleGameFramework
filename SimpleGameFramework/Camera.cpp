#include "Camera.h"
#include "GameObject.h"
#include "Window.h"
#include <cmath>

Camera* Camera::_instance = nullptr;

Camera* Camera::instance()
{
    if (_instance == nullptr) {
        _instance = new Camera;
    }
    return _instance;
}

void Camera::setPosition(Point position)
{
    //整数化，防止绘制地图时因小数的误差而产生缝隙。
    _position.x = round(position.x);
    _position.y = round(position.y);
}

Point Camera::transform2win(const Point& pos_abs)
{
    return pos_abs - _position;
}

Point Camera::transform2abs(const Point& pos_win)
{
    return pos_win + _position;
}

void Camera::update()
{
    if(_target != nullptr)
        setCenterPosition(_target->getAbsolutePosition());
}

Camera::Camera(){
    _w = Window::instance()->getWidth();
    _h = Window::instance()->getHeight();
    _position = Point(0, 0);
}