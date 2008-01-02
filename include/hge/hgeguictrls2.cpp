// hgeguictrls2.cpp: implementation of the hgeGUILabel class.
//
// Version 1.2
//
//////////////////////////////////////////////////////////////////////

#include "hgeguictrls2.h"

//////////////////////////////////////////////////////////////////////
// hgeGUILabel
//////////////////////////////////////////////////////////////////////

hgeGUILabel::hgeGUILabel(int _id, float x, float y, hgeFont *fnt, char* text, DWORD color, int align)
{
	bStatic=true;
	bVisible=true;
	bEnabled=true;
	id = _id;

	m_Font = fnt;
	m_Pos.x = x;
	m_Pos.y = y;
	m_Color = color;

	m_Align = align;

	SetText(text);
}



void hgeGUILabel::SetVisible(bool yesno)
{
	bVisible = yesno;
}



void hgeGUILabel::SetText(int v)
{
	char str[16];
	itoa(v, str, 10);
	SetText(str);
}



void hgeGUILabel::SetText(char* text)
{
	strncpy(m_Text, text, 256);
	m_Text[255] = 0;

	char* p = strchr(m_Text, '\n');
	int lines = 1;

	float w = m_Font->GetStringWidth(m_Text);

	while (p++)					// skip '\n' character
	{
		float tw = m_Font->GetStringWidth(p);
		if (tw > w)	w = tw;

		p = strchr(p, '\n');
		lines++;
	}

	float h = m_Font->GetHeight() * m_Font->GetScale() * lines;

	switch (m_Align)
	{
	case HGETEXT_LEFT:
		rect.Set(m_Pos.x, m_Pos.y, m_Pos.x + w, m_Pos.y + h);
		break;

	case HGETEXT_CENTER:
		rect.Set(m_Pos.x - w/2, m_Pos.y, m_Pos.x + w/2, m_Pos.y + h);
		break;

	case HGETEXT_RIGHT:
		rect.Set(m_Pos.x - w, m_Pos.y, m_Pos.x, m_Pos.y + h);
		break;
	}
}



void hgeGUILabel::SetAlign(int align)
{
	m_Align = align;

	float w = rect.x2 - rect.x1;
	float h = rect.y2 - rect.y1;

	switch (m_Align)
	{
	case HGETEXT_LEFT:
		rect.Set(m_Pos.x, m_Pos.y, m_Pos.x + w, m_Pos.y + h);
		break;

	case HGETEXT_CENTER:
		rect.Set(m_Pos.x - w/2, m_Pos.y, m_Pos.x + w/2, m_Pos.y + h);
		break;

	case HGETEXT_RIGHT:
		rect.Set(m_Pos.x - w, m_Pos.y, m_Pos.x, m_Pos.y + h);
		break;
	}
}



void hgeGUILabel::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;

	SetAlign(m_Align);
}



void hgeGUILabel::SetColor(DWORD col)
{
	m_Color = col;
}



void hgeGUILabel::Render()
{
	m_Font->SetColor(m_Color);
	m_Font->Render(m_Pos.x, m_Pos.y, m_Align, m_Text);
}



/////////////////////////////////////////////////////////////////////
// hgeGUIMemo
//////////////////////////////////////////////////////////////////////

hgeGUIMemo::hgeGUIMemo(int _id, float x, float y, float w, float h, hgeFont *fnt, char* text, DWORD color)
{
	bStatic=true;
	bVisible=true;
	bEnabled=true;
	id = _id;

	m_Font = fnt;
	m_Pos.x = x;
	m_Pos.y = y;
	m_Color = color;

	m_Width = w;
	m_Height = h;

	rect.Set(x, y, x + w, y + h);

	SetText(text);
}



void hgeGUIMemo::SetVisible(bool yesno)
{
	bVisible = yesno;
}



void hgeGUIMemo::SetText(char* text)
{
	int lines = 1;
	char *d = m_Text;
	char *t = m_Text;
	ZeroMemory(m_Text, sizeof(m_Text));

	for (char *p=text; p<text+512; p++, d++)
	{
		if (!*p)
			break;

		*d = *p;

		if (*d == '\n')
		{
			t = d + 1;
			p = text + int(d - m_Text);
		}

		float tw = m_Font->GetStringWidth(t);

		if (tw > m_Width)
		{
			d = strrchr(t, ' ') + 1;
			p = text + int(d - m_Text) - 1;

			*d = '\n';
			t = d;

			lines++;

			float h = m_Font->GetHeight() * m_Font->GetScale() * lines;
			if (h > m_Height)
				break;
		}
	}
}



void hgeGUIMemo::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}



void hgeGUIMemo::SetColor(DWORD col)
{
	m_Color = col;
}



void hgeGUIMemo::Render()
{
	m_Font->SetColor(m_Color);
	m_Font->Render(m_Pos.x, m_Pos.y, HGETEXT_LEFT, m_Text);
}


//////////////////////////////////////////////////////////////////////
// hgeGUIImage
//////////////////////////////////////////////////////////////////////


hgeGUIImage::hgeGUIImage(int _id, float x, float y, char* file)
{
	bStatic = true;
	bVisible = true;
	bEnabled = true;
	id=_id;

	HTEXTURE tex = hge->Texture_Load(file);

	m_Width  = (float)hge->Texture_GetWidth(tex);
	m_Height = (float)hge->Texture_GetHeight(tex);

	rect.Set(x, y, x + m_Width, y + m_Height);

	for(int i=0;i<4;i++)
	{
		m_Quad.v[i].z=0.5f;
		m_Quad.v[i].col=0xFFFFFFFF;
	}

	m_Quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_ZWRITE;
	m_Quad.tex = tex;

	m_Quad.v[0].x = x;					m_Quad.v[0].y = y;
	m_Quad.v[1].x = x+m_Width;	m_Quad.v[1].y = y;
	m_Quad.v[2].x = x+m_Width;	m_Quad.v[2].y = y+m_Height;
	m_Quad.v[3].x = x;					m_Quad.v[3].y = y+m_Height;

	m_Quad.v[0].tx = 0;					m_Quad.v[0].ty = 0;
	m_Quad.v[1].tx = 1;					m_Quad.v[1].ty = 0;
	m_Quad.v[2].tx = 1;					m_Quad.v[2].ty = 1;
	m_Quad.v[3].tx = 0;					m_Quad.v[3].ty = 1;
}



hgeGUIImage::~hgeGUIImage()
{
	hge->Texture_Free(m_Quad.tex);
}



void hgeGUIImage::SetPos(float x, float y)
{
	m_Quad.v[0].x = x;					m_Quad.v[0].y = y;
	m_Quad.v[1].x = x+m_Width;	m_Quad.v[1].y = y;
	m_Quad.v[2].x = x+m_Width;	m_Quad.v[2].y = y+m_Height;
	m_Quad.v[3].x = x;					m_Quad.v[3].y = y+m_Height;
}


void hgeGUIImage::Render()
{
	hge->Gfx_RenderQuad(&m_Quad);
}


//////////////////////////////////////////////////////////////////////
// hgeGUIEditBox
//////////////////////////////////////////////////////////////////////


hgeGUIEditBox::hgeGUIEditBox(int _id, float x, float y, float w, hgeFont* fnt, char* str)
{
	bStatic = false;
	bVisible = true;
	bEnabled = true;
	id=_id;

	m_Font = fnt;
	m_Focus = false;

	m_Time = 0;
	m_Blink = 0;

	strncpy(m_Text, str, 64);
	m_Pos = strlen(m_Text);

	rect.Set(x-2, y-2, x+w+4, y+fnt->GetHeight()*fnt->GetScale()+4);
}



bool hgeGUIEditBox::KeyClick(int key, int chr)
{
	int i, len = strlen(m_Text);

	switch (key)
	{
	case HGEK_ENTER:
		gui->SetFocus(0);
		break;

	case HGEK_LEFT:
		if (m_Pos > 0) m_Pos--;
		break;

	case HGEK_RIGHT:
		if (m_Pos < (int)strlen(m_Text)) m_Pos++;
		break;

	case HGEK_DELETE:
		for (i=m_Pos; i<len; i++)	m_Text[i] = m_Text[i+1];
		break;

	case HGEK_BACKSPACE:
		if (m_Pos == 0)
			break;

		for (i=m_Pos; i<len+1; i++) m_Text[i-1] = m_Text[i];
		m_Pos--;
		break;

	default:
		{
			if (chr == 0)
				break;

			char tmp[64];
			strcpy(tmp, m_Text);

			for (i=len; i>m_Pos && i>0; i--) m_Text[i] = m_Text[i-1];
			m_Text[m_Pos] = chr;
			m_Text[len+1] = 0;
			m_Pos++;

			if (m_Font->GetStringWidth(m_Text) > rect.x2 - rect.x1)
			{
				strcpy(m_Text, tmp);
				m_Pos--;
			}
		}
		break;
	};

	// keep caret from vanishing
	m_Blink = true;
	m_Time = 0;

	return false;
}



bool hgeGUIEditBox::MouseLButton(bool bDown)
{
	if(bDown) gui->SetFocus(id);

	return false;
}



void hgeGUIEditBox::Focus(bool bFocused)
{
	m_Focus = bFocused;
}



void hgeGUIEditBox::Update(float dt)
{
	if (m_Focus)
	{
		m_Time += dt;

		if (m_Time > 0.3)
		{
			m_Time = 0;
			m_Blink = !m_Blink;
		}
	}
}



void hgeGUIEditBox::Render()
{
	hge->Gfx_RenderLine(rect.x1, rect.y1, rect.x2, rect.y1);
	hge->Gfx_RenderLine(rect.x2, rect.y1, rect.x2, rect.y2);
	hge->Gfx_RenderLine(rect.x2, rect.y2, rect.x1, rect.y2);
	hge->Gfx_RenderLine(rect.x1, rect.y2, rect.x1, rect.y1);

	m_Font->SetColor(0xFFC0C0C0);
	m_Font->Render(rect.x1 + 2, rect.y1 + 2,HGETEXT_CENTER, m_Text);

	if (m_Focus && m_Blink)
	{
		char tmp[64];
		strncpy(tmp, m_Text, m_Pos);
		tmp[m_Pos] = 0;

		float p = m_Font->GetStringWidth(tmp);
		hge->Gfx_RenderLine(rect.x1 + 2 + p, rect.y1 + 2, rect.x1 + 2 + p, rect.y2 - 2, 0xFFFFFFFF);
	}
}



//////////////////////////////////////////////////////////////////////
// hgeGUIMenuItem
//////////////////////////////////////////////////////////////////////



hgeGUIMenuItem::hgeGUIMenuItem(int _id, float x, float y, hgeFont *fnt, char *text, HEFFECT snd)
{
	bStatic  = false;
	bVisible = true;
	bEnabled = true;
	id       = _id;

	m_Font   = fnt;
	m_Sound  = snd;
	m_Up     = true;
	m_IPol   = 0;
	m_APol   = 0;
	m_Focus  = false;
	m_Pos.x  = x;
	m_Pos.y  = y;

	m_NColor.SetHWColor(0xFFC0C030);
	m_HColor.SetHWColor(0xFFFFFFFF);

	SetText(text);
}



void hgeGUIMenuItem::SetText(char* text)
{
	strncpy(m_Text, text, 64);
	m_Text[63] = 0;

	char* p = strchr(m_Text, '\n');
	int lines = 1;
	float w = m_Font->GetStringWidth(m_Text);

	while (p++)
	{
		float tw = m_Font->GetStringWidth(p);
		if (tw > w)	w = tw;

		p = strchr(p, '\n');					// skip '\n' character
		lines++;
	}

	float h = m_Font->GetHeight() * m_Font->GetScale() * lines;

	rect.Set(m_Pos.x - w/2, m_Pos.y, m_Pos.x + w/2, m_Pos.y + h);
}



void hgeGUIMenuItem::Render()
{
	m_Font->SetColor(m_Color.GetHWColor());
	m_Font->Render(rect.x1, rect.y1, HGETEXT_LEFT, m_Text);
}



void hgeGUIMenuItem::Update(float dt)
{
	if (m_APol < 1.0f)
	{
		m_APol += 5 * dt;
		if (m_APol > 1)
			m_APol = 1;

		m_Color.a = (m_Up) ? m_APol : 1 - m_APol;
	}

	if (m_Focus)
	{
		m_IPol += 3 * dt;
		if (m_IPol > 1)
			m_IPol = 1;
	} else
	{
		m_IPol -= 3 * dt;
		if (m_IPol < 0)
			m_IPol = 0;
	}

	m_Color.r = (1.0f - m_IPol) * m_NColor.r + m_IPol * m_HColor.r;
	m_Color.g = (1.0f - m_IPol) * m_NColor.g + m_IPol * m_HColor.g;
	m_Color.b = (1.0f - m_IPol) * m_NColor.b + m_IPol * m_HColor.b;
}


void hgeGUIMenuItem::Enter()
{
	m_Up = true;
	m_APol = 0;
	m_IPol = 0;
	m_Focus = false;
}



void hgeGUIMenuItem::Leave()
{
	m_Up = false;
	m_APol = 0;
}



bool hgeGUIMenuItem::IsDone()
{
	return m_APol >= 1.0f;
}



void hgeGUIMenuItem::Focus(bool bFocused)
{
	m_Focus = bFocused;

	if (m_Focus)
		hge->Effect_Play(m_Sound);
}



void hgeGUIMenuItem::MouseOver(bool bOver)
{
	if(bOver)
		gui->SetFocus(id);
}



bool hgeGUIMenuItem::MouseLButton(bool bDown)
{
	if(bDown)
	{
		hge->Effect_Play(m_Sound);
		return false;
	}

	return true;
}



bool hgeGUIMenuItem::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER || key==HGEK_SPACE)
	{
		hge->Effect_Play(m_Sound);
		return true;
	}

	return false;
}




