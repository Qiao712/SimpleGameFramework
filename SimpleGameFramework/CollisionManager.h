#pragma once
class Sprite;
class Vector;
/**
* @brief �������Ϸ��������ײ���
* ����������ѯ���Ƿ���ײ��
*/
class CollisionManager
{
public:
	static CollisionManager* instance();

	/**
	* @brief ������������ײ���
	* @param ���������������
	*/
	bool isCollised(const Sprite& a, const Sprite& b);
	/**
	* @brief ���������Tile֮�����ײ���
	* @param a �����������
	* @param offset ƫ������ָ������ƶ����ܷ��뾫�����ͼ����ײ,�䷽��ȡ������ײʱa�ļ������ĵ�λ��
	*/
	bool isCollisedWithTile(Sprite& a, Vector& offset);
private:
	static CollisionManager* _instance;
	
	CollisionManager();
};

