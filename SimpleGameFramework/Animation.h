#pragma once
#include "Texture.h"
/**
* @brief ������
* Texture�����࣬����ʱ��ı������
*/
class Animation :
    public Texture
{
public:
    Animation(int width_frame = 0, int interval = 0, SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

    virtual void draw(Point position, int w, int h, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, int w, int h, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, CROOD crood = WORLD_CROOD);

    /**
    * @brief ���ſ���
    * @{
    */
    virtual void pause() { _play = false; }
    virtual void play() { _play = true; }
    virtual int getCurrentFrame() { return _current_frame;}
    virtual void setCurrentFrame(int frame) { _current_frame = frame % _num_frame; }
    virtual int getIntervalTime() { return _interval; }
    virtual void setIntervalTime(int interval) { _interval = interval; }
    /**
    * @}
    */

    int getWidth() { return _width_frame; }
private:
    /**��ȡ��ǰ֡������ͼƬ�еľ�������*/
    SDL_Rect _getSrcRect();
    /**��drawʱ���ã�ˢ�¶����ĵ�ǰ֡*/
    void _refresh();

    int _width_frame;    //! �����Ŀ��
    int _interval;       //! ֮֡����ʱ�䣬ms
    int _num_frame;      //! ��֡��
    int _current_frame = 0;  //! ��ǰ֡
    bool _play = true;       //����״̬
    unsigned int _time_last; //�ϴλ���ʱ��ʱ�䣬ms
};

