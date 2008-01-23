// DECLARATION
#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#define RAD2DEG(x) ((x) * 57.29578)
#define DEG2RAD(x) ((x) / 57.29578)
template <typename _type>
class Vector2D {
private:
	_type m_x, m_y, m_length, m_direction;
public:
	Vector2D(_type x = 1, _type y = 1){ SetPoints(x,y); }
	void x(_type x)
	{
		m_x = x;
		m_direction = atan2(m_y,m_x);
		m_length = sqrt((m_x * m_x) + (m_y + m_y));
	}
	void y(_type y)
	{
		m_y = y;
		m_direction = atan2(m_y,m_x);
		m_length = sqrt((m_x * m_x) + (m_y + m_y));
	}
	void Direction(_type a)
	{
		m_direction = a;
		m_x = cos(m_direction) * m_length;
		m_y = sin(m_direction) * m_length;
	}
	void Length(_type m)
	{
		m_length = m;
		m_x = cos(m_direction) * m_length;
		m_y = sin(m_direction) * m_length;
	}
	void SetPoints(_type x, _type y)
	{
		m_x = x;
		m_y = y;
		m_length = (_type)sqrt((m_x * m_x) + (m_y + m_y));
		m_direction = (_type)atan2(m_y,m_x);
	}

	void ReflectAngle(int NormalAngle)
	{
	   int NormDiffAngle; //difference between the inverted angle & the BoundaryNormal angle
	   int angle = (int)RAD2DEG(m_direction);	// new angle
	   int OppAngle = (angle + 180) % 360; // Inverted angle
	   if( NormalAngle >= OppAngle ){
		  NormDiffAngle = NormalAngle - OppAngle;
		  angle = (NormalAngle + NormDiffAngle) % 360;
	   } else {
		  NormDiffAngle = OppAngle - NormalAngle;
		  angle = NormalAngle - NormDiffAngle;
		  if( angle < 0 ) angle += 360;
	   }

	   this->Direction(DEG2RAD(angle));
	}
	_type x(){ return m_x; }

	_type y(){ return m_y; }
	_type Direction(){ return m_direction; }
	_type Length(){ return m_length; }

	// Vector arithmetic operators
	Vector2D& operator+= (Vector2D& v)
	{
		SetPoints(m_x + v.x(),m_y + v.y());
		return *this;
	}
	Vector2D& operator-= (Vector2D& v)
	{
		SetPoints(m_x-v.x(),m_y-v.y());
		return *this;
	}
	Vector2D& operator*= (Vector2D& v)
	{
		SetPoints(m_x*v.x(),m_y*v.y());
		return *this;
	}
	Vector2D& operator/= (Vector2D& v)
	{
		SetPoints(m_x/v.x(),m_y/v.y());
		return *this;
	}

	// scalar operators for speed and resolving ambiguity problems
	// with implicit constructor calls
	Vector2D& operator+= (_type f)
	{
		SetPoints(m_x+f,m_y+f);
		return *this;
	}
	Vector2D& operator-= (_type f)
	{
		SetPoints(m_x-f,m_y-f);
		return *this;
	}
	Vector2D& operator*= (_type f)
	{
		SetPoints(m_x*f,m_y*f);
		return *this;
	}
	Vector2D& operator/= (_type f)
	{
		SetPoints(m_x/f,m_y/f);
		return *this;
	}
};
#endif
