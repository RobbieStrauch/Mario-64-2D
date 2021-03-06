#ifndef __SCENE_H__
#define __SCENE_H__

#include "JSON.h"
#include "ECS.h"
#include "Timer.h"
#include "Xinput.h"
#include "MainEntities.h"
#include <SDL2/SDL.h>


class Scene
{
public:
	Scene() { m_sceneReg = new entt::registry(); m_physicsWorld = new b2World(m_gravity); }
	Scene(std::string name);
	~Scene() { }

	void Unload();

	//Each scene will need to have a different
	//init, as each scene's contents will be different
	virtual void InitScene(float windowWidth, float windowHeight);

	virtual void Update();

	virtual void GUI();

	void AdjustScrollOffset();

	void CreateMainCameraEntity(float windowWidth, float windowHeight, vec4 temp, float zNear, float zFar, float aspectRatio);

	void CreateMapEntity(std::string name, int width, int height, float transparency, vec3 position);

	void CreateStarGUIEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateMainPlayerEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor, float gravityScale);

	void CreateGroundEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateBlockEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateEnemyEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateBowserTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target, float amount,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreatePushMarioTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target1, int target2,
		int amount, b2Vec2 movement, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateBowserHealthTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target1, int target2,
		int amount, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreatePositionTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int target,
		b2Vec2 movement, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateStarEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
		b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor);

	void CreateDestroyStarTriggerEntity(vec3 spritePosition, int& target1, int& target2, 
		b2BodyType bodyType, float angle, bool fixed, vec4 physicsColor);

	void CreateStarTriggerEntity(vec3 spritePosition, int& target1, int target2, b2BodyType bodyType, float angle, bool fixed, vec4 physicsColor);

	//Gamepad Input
	//Because these are virtual you can override them in your inherited classes.
	//The same way you do for Update().
	virtual void GamepadStroke(XInputController* con) { };
	virtual void GamepadUp(XInputController* con) { };
	virtual void GamepadDown(XInputController* con) { };
	virtual void GamepadStick(XInputController* con) { };
	virtual void GamepadTrigger(XInputController* con) { };
	virtual void KeyboardHold() { };
	virtual void KeyboardDown() { };
	virtual void KeyboardUp() { };

	//Mouse Input
	//Because these are virtual you can override them in your inherited classes.
	//The same way you do for Update().
	virtual void MouseMotion(SDL_MouseMotionEvent evnt) { };
	virtual void MouseClick(SDL_MouseButtonEvent evnt) { };
	virtual void MouseWheel(SDL_MouseWheelEvent evnt) { };

	//Get the scene registry
	entt::registry* GetScene() const;
	//Set the scene registry
	void SetScene(entt::registry& scene);

	//Gets the background color of the scene
	vec4 GetClearColor() const;
	//Sets the background color of the scene
	void SetClearColor(vec4 clearColor);

	//Gets the name of the scene
	std::string GetName() const;
	//Sets the name of the scene
	void SetName(std::string name);

	//Gravity
	b2Vec2 GetGravity() const;
	void SetGravity(b2Vec2 grav);
	//Physics world
	b2World& GetPhysicsWorld();

	//Set window size (makes sure the camera aspect is proper)
	void SetWindowSize(float windowWidth, float windowHeight);
protected:
	b2World* m_physicsWorld = nullptr;
	b2Vec2 m_gravity = b2Vec2(float32(0.f), float32(0.f));

	vec4 m_clearColor = vec4(0.408f, 0.533f, 1.f, 1.f);

	entt::registry* m_sceneReg = nullptr;
	std::string m_name = "Default Name";
private:
	//Hello world entity number
	int m_helloWorldSign = 0;
};

#endif // !__SCENE_H__
