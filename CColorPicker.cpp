#include "stdafx.h"
#include "CColorPicker.h"
#include "CGLObject.h"
#include "CEngine.h"
using namespace std;

CColorPicker::CColorPicker(GLuint PickerProgram):
	m_PickerProgram(PickerProgram)
{
}

CGLObject* CColorPicker::Pick(CEngine* Engine)
{
	auto& Objects = Engine->GetObjects();
	vector<GLuint> Programs;
	Programs.reserve(Objects.size());
	for (CGLObject* Object : Objects)
	{
		Programs.push_back(Object->GetProgram());
		Object->SetProgram(m_PickerProgram);
	}

	Engine->DrawObjects();

	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glm::vec<4, unsigned char> data;
	GLint x, y;
	x = Engine->GetCursor().x;
	y = Engine->GetCursor().y;
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
	// TODO: возвращает не ту дату

	CGLObject* result = nullptr;

	for (size_t i=0;i<Objects.size();i++)
	{
		if (Objects[i]->GetUniqueColor() == glm::vec<3, unsigned char>(data))
		{
			result = Objects[i];
		}
		Objects[i]->SetProgram(Programs[i]);
	}

	return nullptr;
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
