#pragma once
#include<SDL.h>
#include"Vector.h"
/**
* @brief InputHandler
* Ϊһ�� Singleton\n
* ����:\n
* ��ȡ�����������\n
* ��ȡʱ��
* 
* ��Ϸʹ�õļ��̰�����ʶ����SDL�ж���ļ���ɨ�����ת����û����ȫ���ǡ�����
* ������Ҫ�����
*/
class InputHandler
{
public:
	static InputHandler* instance();
	
	/**���£��������µĿ����¼������ڴ�֡*/
	void update();

	/**��ȡ��ǰʱ�䣨�ӿ�ʼ���е����ڵ�ʱ�䣩, ��λ������*/
	unsigned int getTime();	
	/**��ȡ�ϴ�update��ʱ�䣬��λ������*/
	unsigned int getLastUpdatingTime() { return _time_last_updating; }
	/**��ǰʱ�����ϴε�ʱ��������*/
	unsigned int getIntervalTime() { return getTime() - _time_last_updating; }

	/**
	* @brief ��ȡ����ĳ������״̬
	* @param key ������ʶ����ĸ��������ASCII�룬����������δ���塣
	* @return 0��δ���£�1������
	*/
	bool getKeyState(int key);
	/**
	* @brief ��ȡ����ĳ����״̬�ڸ�֡�ĸı䣬����/����,���ڲ��񰴼����µ�˲��
	* @param key ������ʶ����ĸ��������ASCII�룬����������δ���塣
	* @return UNCHANGE/DOWN/UP
	*/
	int getKeyChange(int key);
	/**��ȡ���λ��*/
	Point getCursorPos() { return Point(_x_cursor, _y_cursor); }
	/**
	* @brief ��ȡ��갴����״̬
	* @param key LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON �ֱ��Ӧ������갴��
	* @return 0��δ���£�1������
	*/
	bool getButtonState(int id_button) { return _button_state[id_button]; }
	/**
	* @brief ��ȡ����ĳ��������������������ڲ����������֡����Ϊ�㣩
	* @param key LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON �ֱ��Ӧ������갴��
	* @return �������
	*/
	int getButtonClicks(int id_button) { return _button_clicks[id_button]; }

private:
	static InputHandler* _instance;

	/**�ڲ��İ�����ʶ��ת��Ϊɨ����*/
	int ASCIIToScancode(char c);

	/**
	* ���̸�����״̬
	* �������齻���¼��ǰ֡����һ֡�ļ���״̬
	*/
	Uint8 _keystate[2][SDL_NUM_SCANCODES];	
	bool _cur;
	
	/** ʱ����Ϣ*/
	unsigned int _time_last_updating = 0;
	unsigned int _time_curr_updating = 0;

	/** �����Ϣ*/
	unsigned int _x_cursor;
	unsigned int _y_cursor;
	bool _button_state[3];			//!�Ƿ�ѹ��
	int _button_clicks[3];			//!�������
};

/** ��ʶ����״̬�ı仯��UP������DOWN�����£�UNCHANGE���޸ı�*/
enum KEYSTATE{ UNCHANGE, UP , DOWN};
/** ��ʶ��갴�����ֱ��Ӧ������갴��*/
enum MOUSE_BUTTON{LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON};