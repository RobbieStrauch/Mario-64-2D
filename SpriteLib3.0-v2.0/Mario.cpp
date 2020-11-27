#include "Mario.h"
#include "Utilities.h"

#include <random>

Mario::Mario(std::string name)
	: Scene(name)
{
	//No gravity this is a top down scene
	m_gravity = b2Vec2(0.f, -98.f);
	m_physicsWorld->SetGravity(m_gravity);

	m_physicsWorld->SetContactListener(&listener);
}

void Mario::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocates the register
	m_sceneReg = new entt::registry;

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//EffectManager::CreateEffect(EffectType::Vignette, windowWidth, windowHeight);
	//EffectManager::CreateEffect(EffectType::Sepia, windowWidth, windowHeight);

	// Main Camera
	Scene::CreateCameraEntity(true, windowWidth, windowHeight, vec4(-155.f, 155.f, -155.f, 155.f), -100.f, 100.f, aspectRatio);

	// Map
	Scene::CreateMapEntity("Background.png", 3392, 448, 1.f, vec3(0.f, 0.f, 0.f));
	
	// Mario
	Scene::CreateMainPlayerEntity("Mario.png", 15, 20, 1.f, vec3(0.f, 30.f, 2.f), b2_dynamicBody, -1600.f, 30.f, 0.f, true, vec4(1.f, 0.f, 1.f, 0.3f), 1.f);

	// Platforms
	Scene::CreateGroundEntity("boxSprite.jpg", 1106, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1144.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 240, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -440.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 1026, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 240.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 910, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1240.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Ramp1
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 48, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 496.f, 48.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 480.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 504.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 456.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Ramp2
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 48, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 560.f, 48.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 576.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 552.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 600.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Ramp3
	Scene::CreateGroundEntity("boxSprite.jpg", 48, 48, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 728.f, 48.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 704.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 736.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 680.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Ramp4
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 48, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 800.f, 48.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 816.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 792.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 840.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Ramp5
	Scene::CreateGroundEntity("boxSprite.jpg", 48, 112, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1320.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 48, 64, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1272.f, 56.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1232.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1208.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1240.f, 64.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1288.f, 112.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1280.f, 96.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1328.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Tubes
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1232.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 48, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1072.f, 48.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 64, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -944.f, 56.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 64, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -768.f, 56.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 928.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 32, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1184.f, 40.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Bricks
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1432.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 80, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1336.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1336.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -664.f, 96.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 48, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -440.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 128, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -352.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -184.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 64, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -208.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -80.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 8.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 56.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 56.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 104.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 200.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 48, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 264.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 64, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 384.f, 144.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 32, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 384.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 64, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1024.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("boxSprite.jpg", 16, 16, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1480.f, 32.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Translate Trigger
	Scene::CreatePositionTriggerEntity(3392.f, 448.f, vec3(30.f, -20.f, 80.f), MainEntities::MainPlayer(), b2Vec2(-1600.f, 100.f), b2_staticBody, 0.f, -275.f, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));	

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
}

void Mario::Update()
{
	//if (m_lerpEnabled)
	//{
	//	m_tVal += Timer::deltaTime;
	//	m_lerpVal = Util::Lerp<float>(m_val1, m_val2, m_tVal);
	//}

	if (m_lerpEnabled)
	{

		VignetteEffect* vig = (VignetteEffect*)EffectManager::GetEffect(EffectManager::GetVignetteHandle());
		vig->SetOuterRadius(Util::Lerp<float>(m_val1, m_val2, m_lerpVal));

		if (m_lerpVal >= 1.f)
		{
			float temp = m_val2;
			m_val2 = m_val1;
			m_val1 = temp;

			m_lerpVal = 0.f;
		}

		m_lerpVal += Timer::deltaTime * m_lerpSpeed;
	}
}

void Mario::GUI()
{
	GUIWindowUI();

	if (m_firstWindow)
	{
		GUIWindowOne();
	}

	if (m_secondWindow)
	{
		GUIWindowTwo();
	}
}

void Mario::GUIWindowUI()
{
	ImGui::Begin("Test");

	ImGui::Checkbox("Enable First Window", &m_firstWindow);
	ImGui::SameLine();
	if (ImGui::Button("Toggle Second Window", ImVec2(180.f, 15.f)))
	{
		m_secondWindow = !m_secondWindow;
	}
	
	ImGui::End();
}

void Mario::GUIWindowOne()
{
	//Window begin
	ImGui::Begin("Side Docked Window");
	//is the buffer initialized
	static bool init = false;

	//Buffers
	const unsigned int BUF_LEN = 512;
	static char buf[BUF_LEN];
	//Image load
	static std::string imageLoad = "LinkStandby.png";
	//World gravity slider
	float gravity[2] = { m_physicsWorld->GetGravity().x, m_physicsWorld->GetGravity().y };

	if (!init)
	{
		memset(buf, 0, BUF_LEN);
		init = true;
	}
	m_physicsWorld->SetAllowSleeping(true);

	//ImGui content
	if (ImGui::TreeNode("Vignette Effect"))
	{
		if (EffectManager::GetVignetteHandle() != -1)
		{
			VignetteEffect* vig = (VignetteEffect*)EffectManager::GetEffect(EffectManager::GetVignetteHandle());

			if (ImGui::TreeNode("Special Effect"))
			{
				if (ImGui::Button(m_lerpEnabled ? "Disable Pusle" : "Enable Pulse", ImVec2(150.f, 30.f)))
				{
					m_lerpEnabled = !m_lerpEnabled;
					m_tVal = 0.f;
				}

				ImGui::SliderFloat("Value 1", &m_val1, 0.f, 1.f);
				ImGui::SliderFloat("Value 2", &m_val2, m_val1, 1.f);
				ImGui::SliderFloat("Pulse Speed", &m_lerpSpeed, 0.01f, 10.f);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Properties"))
			{

				//if (m_lerpEnabled)
				//{
				//	if (m_tVal >= 1.f)
				//	{
				//		m_lerpEnabled = false;
				//		m_tVal = 0.f;
				//		m_lerpVal = m_val2;
				//	}

				//	vig->SetOuterRadius(m_lerpVal);
				//}

				float innerRad = vig->GetInnerRadius();
				float outerRad = vig->GetOuterRadius();
				float opacity = vig->GetOpacity();


				if (ImGui::SliderFloat("Inner Radius", &innerRad, 0.f, outerRad))
				{
					vig->SetInnerRadius(innerRad);
				}
				if (ImGui::SliderFloat("Outer Radius", &outerRad, innerRad, 1.f))
				{
					vig->SetOuterRadius(outerRad);
				}
				if (ImGui::SliderFloat("Opacity", &opacity, 0.f, 1.f))
				{
					vig->SetOpacity(opacity);
				}

				//if (ImGui::Button("Transition Out", ImVec2(150.f, 30.f)))
				//{
				//	vig->SetInnerRadius(0.f);
				//	m_lerpEnabled = true;
				//	m_val1 = 1.f;
				//	m_val2 = 0.f;
				//}

				//if (ImGui::Button("Transition In", ImVec2(150.f, 30.f)))
				//{
				//	vig->SetInnerRadius(0.f);
				//	m_lerpEnabled = true;
				//	m_val1 = 0.f;
				//	m_val2 = 1.f;
				//}

				ImGui::TreePop();
			}

			if (ImGui::Button("Remove Effect", ImVec2(100.f, 30.f)))
			{
				EffectManager::RemoveEffect(EffectManager::GetVignetteHandle());
				m_lerpEnabled = false;
			}
		}
		else
		{
			if (ImGui::Button("Apply Effect", ImVec2(100.f, 30.f)))
			{
				EffectManager::CreateEffect(Vignette, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());
			}
		}


		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Sepia Effect"))
	{
		if (EffectManager::GetSepiaHandle() != -1)
		{
			if (ImGui::TreeNode("Properties"))
			{
				SepiaEffect* sep = (SepiaEffect*)EffectManager::GetEffect(EffectManager::GetSepiaHandle());
				float intensity = sep->GetIntensity();

				if (ImGui::SliderFloat("Inner Radius", &intensity, 0.f, 1.f))
				{
					sep->SetIntensity(intensity);
				}

				ImGui::TreePop();
			}

			if (ImGui::Button("Remove Effect", ImVec2(100.f, 30.f)))
			{
				EffectManager::RemoveEffect(EffectManager::GetSepiaHandle());
			}
		}
		else
		{
			if (ImGui::Button("Apply Effect", ImVec2(100.f, 30.f)))
			{
				EffectManager::CreateEffect(Sepia, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());
			}
		}


		ImGui::TreePop();
	}

	ImGui::Separator();
	
	ImGui::Text("Editing World Variables!");
	if (ImGui::SliderFloat2("World Gravity", gravity, -1000.f, 1000.f, "%.2f"))
	{
		m_physicsWorld->SetGravity(b2Vec2(gravity[0], gravity[1]));
		m_physicsWorld->SetAllowSleeping(false);
	}

	ImGui::Separator();

	ImGui::Text("Displaying image dynamically");
	ImGui::InputText("Input filename for image", buf, BUF_LEN, ImGuiInputTextFlags_CharsNoBlank);

	if (ImGui::Button("Confirm File", ImVec2(100.f, 30.f)))
	{
		imageLoad = buf;
	}

	ImGui::Image((void*)(intptr_t)TextureManager::FindTexture(imageLoad)->GetID(), ImVec2(150.f, 150.f), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::Separator();
	
	ImGui::Text("Editing Colors");
	ImGui::ColorPicker4("Scene Background Color", &m_clearColor.x);

	ImGui::End();
}

void Mario::GUIWindowTwo()
{
	//Second docked window
	ImGui::Begin("Second Window");
	//Image load
	static std::string imageLoad1 = "FunnyButton.png";
	static std::string imageLoad2 = "LikeButton.png";
	static std::string hahaPressed = "";
	static std::string likePressed = "";

	ImGui::BeginTabBar("Tab Bar Test");

	if (ImGui::BeginTabItem("Tab 1"))
	{
		ImGui::Text("You are within Tab 1");

		if (ImGui::ImageButton((void*)(intptr_t)TextureManager::FindTexture(imageLoad1)->GetID(), ImVec2(100.f, 100.f), ImVec2(0,1), ImVec2(1,0)))
		{
			hahaPressed = "You shouldn't have pressed that...";
		}

		ImGui::Text("%s", hahaPressed.c_str());

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Tab 2"))
	{
		ImGui::Text("You are within Tab 2");

		if (ImGui::ImageButton((void*)(intptr_t)TextureManager::FindTexture(imageLoad2)->GetID(), ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0)))
		{
			likePressed = "LIKED!!!";
		}

		ImGui::Text("%s", likePressed.c_str());

		ImGui::EndTabItem();
	}
	
	ImGui::EndTabBar();

	ImGui::End();
}




void Mario::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());

	float speed = 1.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::Shift))
	{
		speed *= 5.f;
	}

	if (Input::GetKey(Key::A))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(-400000.f * speed, 0.f), true);
	}
	if (Input::GetKey(Key::D))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(400000.f * speed, 0.f), true);
	}

	//Change physics body size for circle
	if (Input::GetKey(Key::O))
	{
		player.ScaleBody(1.3 * Timer::deltaTime, 0);
	}
	else if (Input::GetKey(Key::I))
	{
		player.ScaleBody(-1.3 * Timer::deltaTime, 0);
	}
}

void Mario::KeyboardDown()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	auto& canJump = ECS::GetComponent<CanJump>(MainEntities::MainPlayer());

	if (Input::GetKeyDown(Key::T))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}
	if (canJump.m_canJump)
	{
		if (Input::GetKeyDown(Key::Space))
		{
			player.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, 160000.f), true);
			canJump.m_canJump = false;
		}
	}
}

void Mario::KeyboardUp()
{
	

}
