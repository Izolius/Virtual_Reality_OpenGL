#pragma once
class CEngine;
class CGLObject;

class CColorPicker
{
	bool m_Enabled = false;
	GLuint m_PickerProgram;
public:
	CColorPicker(GLuint PickerProgram);
	CGLObject* Pick(CEngine* Engine);
	void Enable();
	void Disable();
	bool Enabled() const;
};

