#pragma once
#include<SDL.h>
#include"Vector.h"
/**
* @brief InputHandler
* 为一个 Singleton\n
* 负责:\n
* 获取键盘鼠标输入\n
* 获取时间
* 
* 游戏使用的键盘按键标识符到SDL中定义的键盘扫描码的转换并没有完全覆盖。。。
* 根据需要再添加
*/
class InputHandler
{
public:
	static InputHandler* instance();
	
	/**更新，捕获最新的控制事件，用于此帧*/
	void update();

	/**获取当前时间（从开始运行到现在的时间）, 单位：毫秒*/
	unsigned int getTime();	
	/**获取上次update的时间，单位：毫秒*/
	unsigned int getLastUpdatingTime() { return _time_last_updating; }
	/**当前时间与上次的时间间隔毫秒*/
	unsigned int getIntervalTime() { return getTime() - _time_last_updating; }

	/**
	* @brief 获取键盘某按键的状态
	* @param key 按键标识，字母按键即其ASCII码，其他按键暂未定义。
	* @return 0：未按下；1：按下
	*/
	bool getKeyState(int key);
	/**
	* @brief 获取键盘某按键状态在该帧的改变，按下/弹起,用于捕获按键按下的瞬间
	* @param key 按键标识，字母按键即其ASCII码，其他按键暂未定义。
	* @return UNCHANGE/DOWN/UP
	*/
	int getKeyChange(int key);
	/**获取光标位置*/
	Point getCursorPos() { return Point(_x_cursor, _y_cursor); }
	/**
	* @brief 获取鼠标按键的状态
	* @param key LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON 分别对应三个鼠标按键
	* @return 0：未按下；1：按下
	*/
	bool getButtonState(int id_button) { return _button_state[id_button]; }
	/**
	* @brief 获取键盘某按键的连续点击次数（在不发生点击的帧总是为零）
	* @param key LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON 分别对应三个鼠标按键
	* @return 点击次数
	*/
	int getButtonClicks(int id_button) { return _button_clicks[id_button]; }

private:
	static InputHandler* _instance;

	/**内部的按键标识码转换为扫描码*/
	int ASCIIToScancode(char c);

	/**
	* 键盘各按键状态
	* 两个数组交替记录当前帧和上一帧的键盘状态
	*/
	Uint8 _keystate[2][SDL_NUM_SCANCODES];	
	bool _cur;
	
	/** 时间信息*/
	unsigned int _time_last_updating = 0;
	unsigned int _time_curr_updating = 0;

	/** 鼠标信息*/
	unsigned int _x_cursor;
	unsigned int _y_cursor;
	bool _button_state[3];			//!是否压下
	int _button_clicks[3];			//!点击次数
};

/** 标识按键状态的变化，UP：弹起，DOWN：按下，UNCHANGE：无改变*/
enum KEYSTATE{ UNCHANGE, UP , DOWN};
/** 标识鼠标按键，分别对应三个鼠标按键*/
enum MOUSE_BUTTON{LEFT_BUTTON,MID_BUTTON,RIGHT_BUTTON};