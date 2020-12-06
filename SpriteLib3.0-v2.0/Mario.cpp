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
	Scene::CreateMainCameraEntity(windowWidth, windowHeight, vec4(-125.f, 125.f, -125.f, 125.f), -100.f, 100.f, aspectRatio);

	// Worlds
	Scene::CreateMapEntity("World1.png", 3392, 448, 1.f, vec3(0.f, 0.f, 0.f));
	Scene::CreateMapEntity("World2.png", 3392, 448, 1.f, vec3(5000.f, 0.f, 0.f));
	Scene::CreateMapEntity("World3.png", 2992, 1048, 1.f, vec3(10000.f, 0.f, 0.f));
	Scene::CreateMapEntity("Castle.png", 640, 480, 1.f, vec3(0.f, 7000.f, 0.f));

	// Mario
	Scene::CreateMainPlayerEntity("Mario.png", 15, 20, 1.f, vec3(0.f, 30.f, 2.f), b2_dynamicBody, -1600.f, 30.f, 0.f, true, vec4(1.f, 0.f, 1.f, 0.3f), 1.f);

	// World1 Start Point: (-1600.f, 30.f)
	// World2 Start Point: (3452.f, -150.f)
	// World3 Start Point: (8650.f, -400.f)

	// GUI
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI1, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI2, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI3, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI4, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI5, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI6, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI7, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI8, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI9, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI10, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI11, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarGUIEntity("Star.png", 10, 10, 0.f, vec3(45.f, -8.f, 3.f), starGUI12, b2_staticBody, -1550.f, 30.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));

	/////////////////////////////////////////////////////////////////////////// WORLD 1 //////////////////////////////////////////////////////////////////

	// World1 Star1
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world1_star1, b2_staticBody, -1232.f, -80.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_starCounter1, world1_star1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_star1, world1_starCounter1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World1 Star2
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world1_star2, b2_staticBody, -284.f, -148.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_starCounter2, world1_star2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_star2, world1_starCounter2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World1 Star3
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world1_star3, b2_staticBody, 442.f, -140.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_starCounter3, world1_star3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_star3, world1_starCounter3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World1 Star4
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world1_star4, b2_staticBody, 762.f, 134.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_starCounter4, world1_star4, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_star4, world1_starCounter4, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World1 Star5
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world1_star5, b2_staticBody, 961.f, -175.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_starCounter5, world1_star5, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world1_star5, world1_starCounter5, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World1 Platforms
	Scene::CreateGroundEntity("box.png", 176, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1608.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 226, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1538.f, -110.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 278, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1286.f, 8.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 226, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1408.f, -110.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 176, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -988.f, 38.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 166, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -970.f, -142.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 186, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -970.f, -70.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 188, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -1232.f, -110.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 186, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -756.f, -16.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 270, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -490.f, 38.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 96, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -233.f, 8.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 274, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -371.f, -88.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 138, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -202.f, -156.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -330.f, 28.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -275.f, -16.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -330.f, -62.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -330.f, -130.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -284.f, -168.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -244.f, -106.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 226, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, -78.f, -124.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 138, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 168.f, -64.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 158, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 218.f, -144.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 374.f, -10.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 218, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 324.f, -114.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 586.f, 30.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 762.f, 104.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 604.f, -96.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 442.f, -166.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 68, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 442.f, -190.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 745.f, -166.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 48, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 691.f, -200.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 68, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 795.f, -190.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 68, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 961.f, -205.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 781.f, -35.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1039.f, -37.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 174, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1050.f, -137.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1252.f, -42.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 174, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1259.f, -137.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 134, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1447.f, -37.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 174, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1450.f, -137.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 174, 33, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 1608.f, 7.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Death Trigger
	Scene::CreatePositionTriggerEntity(3592, 1000, vec3(0, 0, 0), MainEntities::MainPlayer(), b2Vec2(-1600.f, 30.f), b2_staticBody, 50, -700, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Next World Trigger
	Scene::CreatePositionTriggerEntity(20, 15, vec3(30.f, -20.f, 2.f), MainEntities::MainPlayer(), b2Vec2(8650.f, -400.f), b2_staticBody, 1580.f, 20.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	/////////////////////////////////////////////////////////////////////////// WORLD 1 //////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////// WORLD 2 //////////////////////////////////////////////////////////////////

	// World2 Star1
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world2_star1, b2_staticBody, 3402.f, 50.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_starCounter1, world2_star1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_star1, world2_starCounter1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World2 Star2
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world2_star2, b2_staticBody, 4412.f, -190.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_starCounter2, world2_star2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_star2, world2_starCounter2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World2 Star3
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world2_star3, b2_staticBody, 5026.f, 10.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_starCounter3, world2_star3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_star3, world2_starCounter3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World2 Star4
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world2_star4, b2_staticBody, 5756.f, -130.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_starCounter4, world2_star4, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world2_star4, world2_starCounter4, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Bowser
	Scene::CreateEnemyEntity("Bowser.png", 50, 60, 1.f, vec3(45.f, -8.f, 3.f), Bowser, b2_dynamicBody, 6609.f, -5.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));

	// World2 Platforms
	Scene::CreateGroundEntity("box.png", 3392, 35, 0.f, vec3(5000.f, 0.f, 0.f), b2_staticBody, 5000.f, 150.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Roof
	Scene::CreateGroundEntity("box.png", 192, 50, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3402.f, 10.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 192, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3322.f, 40.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 192, 5, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3322.f, -100.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 208, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3602.f, -6.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 35, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3802.f, -30.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 200, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3662.f, -89.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 196, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3570.f, -112.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 95, 95, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3354.f, -56.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 196, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3504.f, -185.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 490, 20, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3548.f, -215.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 78, 20, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3908.f, -215.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 70, 20, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4054.f, -215.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 100, 20, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4224.f, -215.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 200, 23, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4452.f, -214.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 200, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 3954.f, -49.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 196, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4196.f, -69.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 196, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4452.f, -121.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 110, 95, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4494.f, -154.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 776, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5028.f, -208.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 196, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4982.f, -128.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 196, 70, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4946.f, -76.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 230, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4962.f, -24.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 156, 160, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 4926.f, 66.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 206, 180, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5314.f, -100.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 156, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5198.f, -176.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 156, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5196.f, -78.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 126, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5552.f, -52.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 166, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5748.f, -52.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 140, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 5756.f, -162.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 336, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6174.f, -52.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 336, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6138.f, -88.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 336, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6098.f, -124.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 336, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6058.f, -160.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 340, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6506.f, -54.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 340, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6526.f, -86.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 340, 130, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6526.f, -162.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 240, 35, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 6679.f, 22.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateBlockEntity("Block.png", 30, 166, 1.f, vec3(30.f, -20.f, 2.f), starWall, b2_staticBody, 6315.f, 50.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateBlockEntity("Block.png", 30, 166, 1.f, vec3(30.f, -20.f, 2.f), finalBossWall, b2_staticBody, 6315.f, -10000.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Death Trigger
	Scene::CreatePositionTriggerEntity(3592, 1000, vec3(5000, 0, 0), MainEntities::MainPlayer(), b2Vec2(3452.f, -150.f), b2_staticBody, 5050, -710, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Previous World Trigger
	Scene::CreatePositionTriggerEntity(40, 15, vec3(30.f, -20.f, 2.f), MainEntities::MainPlayer(), b2Vec2(8650.f, -400.f), b2_staticBody, 3322.f, -210.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Final Boss Trigger
	Scene::CreatePositionTriggerEntity(10, 200, vec3(30.f, -20.f, 2.f), finalBossWall, b2Vec2(6315.f, 50.f), b2_staticBody, 6335.f, 40.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Bowser Triggers
	Scene::CreateBowserTriggerEntity(10, 50, vec3(30.f, -20.f, 2.f), Bowser, 0.5, b2_staticBody, 6358.f, -20.f, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateBowserTriggerEntity(10, 50, vec3(30.f, -20.f, 2.f), Bowser, -0.5, b2_staticBody, 6658.f, -20.f, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreatePushMarioTriggerEntity(10, 70, vec3(30.f, -20.f, 2.f), bowserAttack1, MainEntities::MainPlayer(), -25, b2Vec2(-40000000000.f, 0.f), b2_dynamicBody, 6580.f, -10.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreatePushMarioTriggerEntity(10, 70, vec3(30.f, -20.f, 2.f), bowserAttack2, MainEntities::MainPlayer(), -25, b2Vec2(40000000000.f, 0.f), b2_dynamicBody, 6635.f, -10.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateBowserHealthTriggerEntity(10, 30, vec3(30.f, -20.f, 2.f), marioAttack, Bowser, -100, b2_dynamicBody, 6607.f, 30.f, 90.f, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreatePushMarioTriggerEntity(10, 30, vec3(30.f, -20.f, 2.f), marioAttackJump, MainEntities::MainPlayer(), 0, b2Vec2(0.f, 60000000000.f), b2_dynamicBody, 6607.f, 30.f, 90.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	/////////////////////////////////////////////////////////////////////////// WORLD 2 //////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////// WORLD 3 //////////////////////////////////////////////////////////////////

	// World3 Star1
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world3_star1, b2_staticBody, 8614.f, 185.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_starCounter1, world3_star1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_star1, world3_starCounter1, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World3 Star2
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world3_star2, b2_staticBody, 9813.f, -100.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_starCounter2, world3_star2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_star2, world3_starCounter2, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World3 Star3
	Scene::CreateStarEntity("Star.png", 20, 20, 1.f, vec3(45.f, -8.f, 3.f), world3_star3, b2_staticBody, 11165.f, -450.f, 0.f, false, vec4(1.f, 0.f, 1.f, 0.3f));
	Scene::CreateStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_starCounter3, world3_star3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));
	Scene::CreateDestroyStarTriggerEntity(vec3(30.f, -20.f, 80.f), world3_star3, world3_starCounter3, b2_staticBody, 0, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// World3 Platforms
	Scene::CreateGroundEntity("box.png", 2992, 64, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10000.f, -500.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f)); //Floor
	Scene::CreateGroundEntity("box.png", 70, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9250.f, -390.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 70, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9410.f, -342.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9549.f, -290.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9613.f, -472.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9679.f, -440.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 85, 95, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9724.f, -424.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 128, 95, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9813.f, -411.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 265, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9812.f, -244.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9710.f, -232.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 100, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9708.f, -110.f, 90.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9550.f, -30.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9258.f, 0.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9018.f, 35.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 8878.f, 80.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 8744.f, 125.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 115, 15, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 8614.f, 165.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 85, 95, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9904.f, -426.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 9946.f, -440.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10010.f, -472.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10468.f, -486.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 65, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10518.f, -472.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 95, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10584.f, -456.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 125, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10680.f, -442.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 155, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10810.f, -426.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 175, 65, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 10870.f, -416.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));
	Scene::CreateGroundEntity("box.png", 190, 125, 0.f, vec3(30.f, -20.f, 2.f), b2_staticBody, 11025.f, -406.f, 0.f, true, vec4(0.f, 1.f, 0.f, 0.3f));

	// Death Trigger
	Scene::CreatePositionTriggerEntity(4592, 1000, vec3(10000.f, 0, 0), MainEntities::MainPlayer(), b2Vec2(8650.f, -400.f), b2_staticBody, 10050.f, -1010, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Previous World
	Scene::CreatePositionTriggerEntity(20, 15, vec3(30.f, -20.f, 2.f), MainEntities::MainPlayer(), b2Vec2(-1600.f, 30.f), b2_staticBody, 8550.f, -470.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	// Next World
	Scene::CreatePositionTriggerEntity(20, 15, vec3(30.f, -20.f, 2.f), MainEntities::MainPlayer(), b2Vec2(3452.f, -150.f), b2_staticBody, 11405.f, -470.f, 0.f, true, vec4(1.f, 0.f, 0.f, 0.3f));

	/////////////////////////////////////////////////////////////////////////// WORLD 3 //////////////////////////////////////////////////////////////////

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

	int increase = 1;

	if (ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() <= 800 || ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() >= 600)
	{
		increase = 2;
	}
	if (ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() <= 500 || ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() >= 300)
	{
		increase = 3.5;
	}
	if (ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() <= 200)
	{
		increase = 5;
	}

	/////////////////////////////////////////////////////////////////////////// GUI //////////////////////////////////////////////////////////////////

	ECS::GetComponent<PhysicsBody>(starGUI1).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 200, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI2).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 185, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI3).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 170, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI4).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 155, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI5).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 140, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI6).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 125, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 100));
	ECS::GetComponent<PhysicsBody>(starGUI7).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 200, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));
	ECS::GetComponent<PhysicsBody>(starGUI8).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 185, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));
	ECS::GetComponent<PhysicsBody>(starGUI9).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 170, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));
	ECS::GetComponent<PhysicsBody>(starGUI10).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 155, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));
	ECS::GetComponent<PhysicsBody>(starGUI11).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 140, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));
	ECS::GetComponent<PhysicsBody>(starGUI12).SetPosition(b2Vec2(ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().x + 125, ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition().y + 85));

	if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 1)
	{
		ECS::GetComponent<Sprite>(starGUI1).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 2)
	{
		ECS::GetComponent<Sprite>(starGUI2).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 3)
	{
		ECS::GetComponent<Sprite>(starGUI3).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 4)
	{
		ECS::GetComponent<Sprite>(starGUI4).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 5)
	{
		ECS::GetComponent<Sprite>(starGUI5).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 6)
	{
		ECS::GetComponent<Sprite>(starGUI6).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 7)
	{
		ECS::GetComponent<Sprite>(starGUI7).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 8)
	{
		ECS::GetComponent<Sprite>(starGUI8).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 9)
	{
		ECS::GetComponent<Sprite>(starGUI9).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 10)
	{
		ECS::GetComponent<Sprite>(starGUI10).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 11)
	{
		ECS::GetComponent<Sprite>(starGUI11).SetTransparency(1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() == 12)
	{
		ECS::GetComponent<Sprite>(starGUI12).SetTransparency(1.f);
		ECS::GetComponent<PhysicsBody>(starWall).SetPosition(b2Vec2(6315.f, -10000.f));
	}

	/////////////////////////////////////////////////////////////////////////// GUI //////////////////////////////////////////////////////////////////

	ECS::GetComponent<PhysicsBody>(bowserAttack1).SetPosition(ECS::GetComponent<PhysicsBody>(bowserAttack1).GetPosition() + b2Vec2(ECS::GetComponent<PhysicsBody>(Bowser).speed * increase, 0), true);
	ECS::GetComponent<PhysicsBody>(bowserAttack2).SetPosition(ECS::GetComponent<PhysicsBody>(bowserAttack2).GetPosition() + b2Vec2(ECS::GetComponent<PhysicsBody>(Bowser).speed * increase, 0), true);
	ECS::GetComponent<PhysicsBody>(marioAttack).SetPosition(ECS::GetComponent<PhysicsBody>(marioAttack).GetPosition() + b2Vec2(ECS::GetComponent<PhysicsBody>(Bowser).speed * increase, 0), true);
	ECS::GetComponent<PhysicsBody>(marioAttackJump).SetPosition(ECS::GetComponent<PhysicsBody>(marioAttackJump).GetPosition() + b2Vec2(ECS::GetComponent<PhysicsBody>(Bowser).speed * increase, 0), true);
	ECS::GetComponent<PhysicsBody>(Bowser).SetPosition(ECS::GetComponent<PhysicsBody>(Bowser).GetPosition() + b2Vec2(ECS::GetComponent<PhysicsBody>(Bowser).speed * increase, 0), true);

	if (ECS::GetComponent<PhysicsBody>(Bowser).GetHealth() == 0)
	{
		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).SetPosition(b2Vec2(0, 6810));
		m_clearColor = vec4(0.408f, 0.533f, 1.f, 1.f);
	}
	if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition() == b2Vec2(3452.f, -150.f))
	{
		m_clearColor = vec4(0.f, 0.f, 0.f, 0.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition() == b2Vec2(-1600.f, 30.f))
	{
		m_clearColor = vec4(0.408f, 0.533f, 1.f, 1.f);
	}
	else if (ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetPosition() == b2Vec2(8650.f, -400.f))
	{
		m_clearColor = vec4(0.549f, 0.639f, 0.796f, 1.f);
	}

	//std::cout << "Stars Captured: " << ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetStar() << std::endl;

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

		if (ImGui::ImageButton((void*)(intptr_t)TextureManager::FindTexture(imageLoad1)->GetID(), ImVec2(100.f, 100.f), ImVec2(0, 1), ImVec2(1, 0)))
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
		speed *= 1.5f;
	}

	if (Input::GetKey(Key::A))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(-400000.f * speed, 0.f), true);
	}
	if (Input::GetKey(Key::D))
	{
		player.GetBody()->ApplyForceToCenter(b2Vec2(400000.f * speed, 0.f), true);
	}

	////Change physics body size for circle
	//if (Input::GetKey(Key::O))
	//{
	//	player.ScaleBody(1.3 * Timer::deltaTime, 0);
	//}
	//else if (Input::GetKey(Key::I))
	//{
	//	player.ScaleBody(-1.3 * Timer::deltaTime, 0);
	//}
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
