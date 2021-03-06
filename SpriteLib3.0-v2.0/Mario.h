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

	int starGUI1;
	int starGUI2;
	int starGUI3;
	int starGUI4;
	int starGUI5;
	int starGUI6;
	int starGUI7;
	int starGUI8;
	int starGUI9;
	int starGUI10;
	int starGUI11;
	int starGUI12;

	PhysicsPlaygroundListener listener;

	int finalBossWall;
	int starWall;

	int Bowser;
	int bowserAttack1;
	int bowserAttack2;
	int marioAttack;
	int marioAttackJump;

	int world1_star1;
	int world1_star2;
	int world1_star3;
	int world1_star4;
	int world1_star5;
	int world1_starCounter1;
	int world1_starCounter2;
	int world1_starCounter3;
	int world1_starCounter4;
	int world1_starCounter5;

	int world2_star1;
	int world2_star2;
	int world2_star3;
	int world2_star4;
	int world2_starCounter1;
	int world2_starCounter2;
	int world2_starCounter3;
	int world2_starCounter4;

	int world3_star1;
	int world3_star2;
	int world3_star3;
	int world3_starCounter1;
	int world3_starCounter2;
	int world3_starCounter3;

};
