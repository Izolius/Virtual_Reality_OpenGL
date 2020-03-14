#pragma once
class CEngine;
class CGLObject;

class CColorPicker
{
	bool m_Enabled = false;
	std::vector<GLuint> Programs;
	GLuint m_PickerProgram;
private:
	void BeforeDraw(CEngine* Engine);
	void AfterDraw(CEngine* Engine);
public:
	CColorPicker(GLuint PickerProgram);
	CGLObject* Pick(CEngine* Engine);
	void Draw(CEngine* Engine);
	void Enable();
	void Disable();
	bool Enabled() const;
};

