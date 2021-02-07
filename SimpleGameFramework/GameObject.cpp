#include "GameObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <algorithm>
using std::find;

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	//�����ӽڵ��parent��¼
	for (auto i : _sub) {
		i->_parent = nullptr;
	}
}


void GameObject::update()
{
	//do nothing now
}

void GameObject::draw()
{
	//draw nothing now
}

void GameObject::insert(GameObject* sub)
{
	//�Ѵ������˳�
	if (find(_sub.begin(), _sub.end(), sub) != _sub.end()) return;
	
	//��ֹ��������
	if (sub == this) return;

	//���и��ڵ㣬���Ƚ����ԭ���ĸ��ڵ����Ƴ�
	if (sub->_parent != nullptr) {
		sub->_parent->remove(sub);
	}

	sub->_parent = this;
	_sub.push_back(sub);
}

void GameObject::remove(GameObject* sub)
{
	auto i = find(_sub.begin(), _sub.end(), sub);
	if (i == _sub.end()) return;
	sub->_parent = nullptr;
	_sub.erase(i);
}

void GameObject::_update()
{
	update();
	
	for (auto i : _sub) {
		i->_update();
	}
}

void GameObject::_draw()
{
	draw();
	for (auto i : _sub) {
		i->_draw();
	}
}
