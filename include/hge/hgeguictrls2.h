// hgeguictrls2.h: interface for the hgeLabel class.
//
// Version 1.2
//
//////////////////////////////////////////////////////////////////////

#ifndef _HGELABEL_H_
#define _HGELABEL_H_

#if _MSC_VER > 1000
#pragma once
#endif



#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <hgecolor.h>
#include <hgevector.h>


class hgeGUILabel : public hgeGUIObject
{
public:
	hgeGUILabel(int id, float x, float y, hgeFont *fnt, char* text, DWORD color = 0xFFFFFFFF, int align = HGETEXT_LEFT);

	void SetAlign(int align);
	void SetVisible(bool yesno);
	void SetText(char *text);
	void SetText(int value);
	void SetColor(DWORD col);
	void SetPos(float x, float y);

	virtual void	Render();

private:
	hgeFont*		m_Font;
	hgeVector		m_Pos;
	int					m_Align;
	char				m_Text[256];
	DWORD				m_Color;
};



class hgeGUIMemo : public hgeGUIObject
{
public:
	hgeGUIMemo(int id, float x, float y, float w, float h, hgeFont *fnt, char* text, DWORD color = 0xFFFFFFFF);

	void SetVisible(bool yesno);
	void SetText(char *text);
	void SetColor(DWORD col);
	void SetPos(float x, float y);

	virtual void	Render();

private:
	hgeFont*		m_Font;
	float				m_Width;
	float				m_Height;
	hgeVector		m_Pos;
	char				m_Text[512];
	DWORD				m_Color;
};



class hgeGUIImage : public hgeGUIObject
{
public:
	hgeGUIImage(int id, float x, float y, char* file);
	virtual ~hgeGUIImage();

	void			Scale(float factor);
	void			SetPos(float x, float y);

	void			Render();

private:
	hgeQuad			m_Quad;
	float				m_Width;
	float				m_Height;
};



class hgeGUIEditBox : public hgeGUIObject
{
public:
	hgeGUIEditBox(int id, float x, float y, float w, hgeFont *fnt, char* str = "");

	char*					GetText();
	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);
	virtual void	Focus(bool bFocused);
	virtual void	Update(float dt);

	void					Render();

private:
	hgeFont*		m_Font;
	bool				m_Focus;
	int					m_Pos;
	char				m_Text[64];
	float				m_Time;
	bool				m_Blink;
};



class hgeGUIMenuItem : public hgeGUIObject
{
public:
	hgeGUIMenuItem(int id, float x, float y, hgeFont *fnt, char *title, HEFFECT snd);

	void SetText(char* text);

	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);

private:
	hgeFont*			m_Font;
	hgeVector			m_Pos;
	HEFFECT				m_Sound;
	char					m_Text[64];
	hgeColor			m_NColor;
	hgeColor			m_HColor;
	hgeColor			m_Color;
	bool					m_Focus;
	float					m_IPol;
	float					m_APol;
	bool					m_Up;

	hgeColor	scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
	hgeColor	color, shadow;
	float		soffset, doffset, offset;
	float		timer, timer2;
};



#endif
