#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H 1

#include <stdio.h>

#define CAMERA_MOVESPEED 0.8f

struct Camera {
public:
	Camera();
	inline float GetX() { return m_x; }
	inline float GetY() { return m_y; }
    void set( float pos_x, float pos_y) {
        m_x = pos_x;
        m_y = pos_y;
	}
	void add( float pos_x, float pos_y) {
        m_x += pos_x;
        m_y += pos_y;
	}
	void move( float d_x, float d_y) {
        m_x += d_x*m_movespeed;
        m_y += d_y*m_movespeed;
	}
protected:
private:
    float m_x, m_y;
    float m_movespeed;
};

#endif
