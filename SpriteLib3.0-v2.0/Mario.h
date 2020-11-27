#pragma once

#include "Scene.h"
#include "PhysicsPlaygroundListener.h"
#include <string>

class Mario : public Scene
{
public:
	Mario(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void Update() override;

	void GUI() override;

	void GUIWindowUI();
	void GUIWindowOne();
	void GUIWindowTwo();


	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	bool m_firstWindow = false;
	bool m_secondWindow = false;

	bool m_lerpEnabled = false;
	float m_lerpVal = 0.f;
	float m_lerpSpeed = 2.f;

	float m_tVal = 0.f;
	float m_val1 = 0.f;
	float m_val2 = 1.f;

	std::string m_fileInput;

	PhysicsPlaygroundListener listener;

	int puzzleWall1;
	int puzzleWall2;
};
