#include "stdafx.h"
#include "CColorPicker.h"
#include "CGLObject.h"
#include "CEngine.h"
using namespace std;

void CColorPicker::BeforeDraw(CEngine* Engine)
{
	auto& Objects = Engine->GetObjects();
	Programs.clear();
	Programs.reserve(Objects.size());
	for (CGLObject* Object : Objects)
	{
		Programs.push_back(Object->GetProgram());
		Object->SetProgram(m_PickerProgram);
	}
}

void CColorPicker::AfterDraw(CEngine* Engine)
{
	auto& Objects = Engine->GetObjects();
	for (size_t i = 0; i < Objects.size(); i++)
	{
		Objects[i]->SetProgram(Programs[i]);
	}
}

CColorPicker::CColorPicker(GLuint PickerProgram):
	m_PickerProgram(PickerProgram)
{
}

CGLObject* CColorPicker::Pick(CEngine* Engine)
{
	auto& Objects = Engine->GetObjects();
	BeforeDraw(Engine);

	Engine->DrawObjects();

	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glm::vec<4, unsigned char> data;
	GLint x, y;
	x = Engine->GetCursor().x;
	y = Engine->GetCursor().y;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);

	CGLObject* result = nullptr;

	for (size_t i=0;i<Objects.size();i++)
	{
		if (Objects[i]->GetUniqueColor() == data)
		{
			result = Objects[i];
		}
	}

	AfterDraw(Engine);

	return result;
}

void CColorPicker::Draw(CEngine* Engine)
{
	BeforeDraw(Engine);

	Engine->DrawObjects();

	AfterDraw(Engine);
}

void CColorPicker::Enable()
{
	m_Enabled = true;
}

void CColorPicker::Disable()
{
	m_Enabled = false;
}

bool CColorPicker::Enabled() const
{
	return m_Enabled;
}
