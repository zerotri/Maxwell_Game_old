// DECLARATION
#include <math.h>
#define RAD2DEG(x) ((x) * 57.29578)
#define DEG2RAD(x) ((x) / 57.29578)
class Vector2D {
private:
	float m_x, m_y, m_length, m_direction;
public:
	Vector2D(float x = 1, float y = 1){ SetPoints(x,y); }
	void x(float x);
	void y(float y);
	void Direction(float a);
	void Length(float m);
	void SetPoints(float x, float y);

	void ReflectAngle(int NormalAngle);
	float x(){ return m_x; }
	float y(){ return m_y; }
	float Direction(){ return m_direction; }
	float Length(){ return m_length; }

	// Vector arithmetic operators
	Vector2D& operator+= (Vector2D& v);
	Vector2D& operator-= (Vector2D& v);
	Vector2D& operator*= (Vector2D& v);
	Vector2D& operator/= (Vector2D& v);

	// scalar operators for speed and resolving ambiguity problems
	// with implicit constructor calls
	Vector2D& operator+= (float f);
	Vector2D& operator-= (float f);
	Vector2D& operator*= (float f);
	Vector2D& operator/= (float f);
};
