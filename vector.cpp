#include "vector.h"
#include <math.h>
//DEFINITION
void Vector2D::x(float x)
{
	m_x = x;
	m_direction = atan2(m_y,m_x);
	m_length = sqrt((m_x * m_x) + (m_y + m_y));
}
void Vector2D::y(float y)
{
	m_y = y;
	m_direction = atan2(m_y,m_x);
	m_length = sqrt((m_x * m_x) + (m_y + m_y));
}
void Vector2D::Direction(float a){
	m_direction = a;
	m_x = cos(m_direction) * m_length;
	m_y = sin(m_direction) * m_length;
}
void Vector2D::Length(float m){
	m_length = m;
	m_x = cos(m_direction) * m_length;
	m_y = sin(m_direction) * m_length;
}
void Vector2D::SetPoints(float x, float y){
	m_x = x;
	m_y = y;
	m_length = sqrt((m_x * m_x) + (m_y + m_y));
	m_direction = atan2(m_y,m_x);
}


void Vector2D::ReflectAngle(int NormalAngle)
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


// scalar operators for speed and resolving ambiguity problems
// with implicit constructor calls

/// Componentwise addition
Vector2D& Vector2D::operator+= (float f) {
	SetPoints(m_x+f,m_y+f);
	return *this;
}

/// Componentwise subtraction
Vector2D& Vector2D::operator-= (float f) {
	SetPoints(m_x-f,m_y-f);
	return *this;
}

/// Componentwise multiplication
Vector2D& Vector2D::operator*= (float f) {
	SetPoints(m_x*f,m_y*f);
	return *this;
}

/// Componentwise division
Vector2D& Vector2D::operator/= (float f) {
	SetPoints(m_x/f,m_y/f);
	return *this;
}


// Vector arithmetic operators

Vector2D& Vector2D::operator+= (Vector2D& v) {
	SetPoints(m_x + v.x(),m_y + v.y());
	return *this;
}

Vector2D& Vector2D::operator-= (Vector2D& v) {
	SetPoints(m_x-v.x(),m_y-v.y());
	return *this;
}

Vector2D& Vector2D::operator*= (Vector2D& v) {
	SetPoints(m_x*v.x(),m_y*v.y());
	return *this;
}

Vector2D& Vector2D::operator/= (Vector2D& v) {
	SetPoints(m_x/v.x(),m_y/v.y());
	return *this;
}
