#include "Scene.h"
#include "Utilities.h"

Scene::Scene(std::string name)
{
	m_physicsWorld = new b2World(m_gravity);
	m_name = name;
}

void Scene::Unload()
{
	if (m_sceneReg != nullptr)
	{
		delete m_sceneReg;
		m_sceneReg = nullptr;
	}

	if (m_physicsWorld != nullptr)
	{
		delete m_physicsWorld;
		m_physicsWorld = nullptr;
	}
}

void Scene::InitScene(float windowWidth, float windowHeight)
{
	//Default scene class init just includes a camera so stuff doesn't immediately crash
	printf("You shouldn't be running this, while initializing this Scene Type.\n");

	//Dynamically allocates the register
	if (m_sceneReg == nullptr)
	{
		m_sceneReg = new entt::registry;
	}

	//Attach the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup Main Camera entity
	{
		//Creates Camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		//ECS::AttachComponent<HorizontalScroll>(entity);
		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);
	}

	//Setup new Entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity();
		m_helloWorldSign = entity;

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets up components
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));
	}
}

void Scene::Update()
{
	auto& tempSpr = m_sceneReg->get<Sprite>(m_helloWorldSign);

	tempSpr.SetTransparency((0.5 * sin(Timer::time * 3.f)) + 0.5f);
}

void Scene::GUI()
{
	//Does nothin

}

void Scene::AdjustScrollOffset()
{
	float maxSizeX = ECS::GetComponent<Camera>(MainEntities::MainCamera()).GetOrthoSize().y;
	float maxSizeY = ECS::GetComponent<Camera>(MainEntities::MainCamera()).GetOrthoSize().w;

	float playerHalfSize = ECS::GetComponent<Sprite>(MainEntities::MainPlayer()).GetWidth() / 2.f;

	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetOffset((maxSizeX * BackEnd::GetAspectRatio()) - playerHalfSize);
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetOffset(maxSizeY - playerHalfSize);
}

void Scene::CreateMainCameraEntity(float windowWidth, float windowHeight, vec4 temp, float zNear, float zFar, float aspectRatio)
{
	//Creates Camera entity
	auto entity = ECS::CreateEntity();
	ECS::SetIsMainCamera(entity, true);

	//Creates new orthographic camera
	ECS::AttachComponent<Camera>(entity);
	ECS::AttachComponent<HorizontalScroll>(entity);
	ECS::AttachComponent<VerticalScroll>(entity);

	ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
	ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
	ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, zNear, zFar);

	//Attaches the camera to vert and horiz scrolls
	ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
	ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
}

void Scene::CreateMapEntity(std::string name, int width, int height, float transparency, vec3 position)
{
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);

	//Set up the components
	std::string fileName = name;
	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, width, height);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(position);

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetSleepingAllowed(false);
}

void Scene::CreateStarGUIEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	auto entity = ECS::CreateEntity();
	target = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up the components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), false, OBJECTS, PLAYER, 0.3f);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateMainPlayerEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor, float gravityScale)
{
	auto entity = ECS::CreateEntity();
	ECS::SetIsMainPlayer(entity, true);

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<CanJump>(entity);

	//Sets up the components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetSleepingAllowed(false);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
		vec2(0.f, 0.f), false, PLAYER, ENEMY | OBJECTS | PICKUP | TRIGGER, 5.5f, 3.f);

	tempPhsBody.SetStar(0);
	tempPhsBody.SetHealth(100);
	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
	tempPhsBody.SetGravityScale(gravityScale);
}

void Scene::CreateGroundEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetSleepingAllowed(false);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateBlockEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();
	target = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetSleepingAllowed(false);

	tempPhsBody = PhysicsBody(entity, tempBody, float(tempSpr.GetWidth() - shrinkX),
		float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false, GROUND, PLAYER | ENEMY | OBJECTS);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateEnemyEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	auto entity = ECS::CreateEntity();
	target = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up the components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempBody->SetSleepingAllowed(false);

	tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY)), float((tempSpr.GetHeight() - shrinkY)), vec2(0.f, 0.f), false, ENEMY, GROUND | ENVIRONMENT | PLAYER | OBJECTS | TRIGGER, 0.3f);

	tempPhsBody.SetHealth(1000);
	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateBowserTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target, float amount,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new BowserTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target);

	BowserTrigger* temp = (BowserTrigger*)ECS::GetComponent<Trigger*>(entity);
	temp->newSpeed = amount;

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(imageWidth - shrinkX), float(imageHeight - shrinkY), vec2(0.f, 0.f), true, TRIGGER, ENEMY);

	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreatePushMarioTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target1, int target2,
	int amount, b2Vec2 movement, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();
	target1 = entity;

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new PushTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target2);

	PushTrigger* temp = (PushTrigger*)ECS::GetComponent<Trigger*>(entity);
	temp->movement = movement;
	temp->amount = amount;

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(imageWidth - shrinkX), float(imageHeight - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateBowserHealthTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int& target1, int target2,
	int amount, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();
	target1 = entity;

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new HealthTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target2);

	HealthTrigger* temp = (HealthTrigger*)ECS::GetComponent<Trigger*>(entity);
	temp->amount = amount;

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(imageWidth - shrinkX), float(imageHeight - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreatePositionTriggerEntity(int imageWidth, int imageHeight, vec3 spritePosition, int target,
	b2Vec2 movement, b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new TranslateTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target);

	TranslateTrigger* temp = (TranslateTrigger*)ECS::GetComponent<Trigger*>(entity);
	temp->movement = movement;

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(imageWidth - shrinkX), float(imageHeight - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER | OBJECTS);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateStarEntity(std::string name, int imageWidth, int imageHeight, float transparency, vec3 spritePosition, int& target,
	b2BodyType bodyType, float physicsPositionX, float physicsPositionY, float angle, bool fixed, vec4 physicsColor)
{
	auto entity = ECS::CreateEntity();
	target = entity;

	//Add components
	ECS::AttachComponent<Sprite>(entity);
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);

	//Sets up the components
	ECS::GetComponent<Sprite>(entity).LoadSprite(name, imageWidth, imageHeight);
	ECS::GetComponent<Sprite>(entity).SetTransparency(transparency);
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);

	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	float shrinkX = 0.f;
	float shrinkY = 0.f;

	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(physicsPositionX), float32(physicsPositionY));

	tempBody = m_physicsWorld->CreateBody(&tempDef);
	tempPhsBody = PhysicsBody(entity, tempBody, float((tempSpr.GetWidth() - shrinkY) / 2.f), vec2(0.f, 0.f), false, OBJECTS, GROUND | ENVIRONMENT | PLAYER | TRIGGER, 0.3f);

	tempPhsBody.SetRotationAngleDeg(angle);
	tempPhsBody.SetFixedRotation(fixed);
	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateDestroyStarTriggerEntity(vec3 spritePosition, int& target1, int& target2,
	b2BodyType bodyType, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new DestroyTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target1);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(target2);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(entity);

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	auto& targetBody = ECS::GetComponent<PhysicsBody>(target1);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(targetBody.GetPosition().x), float32(targetBody.GetPosition().y));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(targetBody.GetWidth() - shrinkX), float(targetBody.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);

	tempPhsBody.SetColor(physicsColor);
}

void Scene::CreateStarTriggerEntity(vec3 spritePosition, int& target1, int target2, b2BodyType bodyType, float angle, bool fixed, vec4 physicsColor)
{
	//Creates entity
	auto entity = ECS::CreateEntity();
	target1 = entity;

	//Add components
	ECS::AttachComponent<Transform>(entity);
	ECS::AttachComponent<PhysicsBody>(entity);
	ECS::AttachComponent<Trigger*>(entity);

	//Sets up components
	ECS::GetComponent<Transform>(entity).SetPosition(spritePosition);
	ECS::GetComponent<Trigger*>(entity) = new StarTrigger();
	ECS::GetComponent<Trigger*>(entity)->SetTriggerEntity(entity);
	ECS::GetComponent<Trigger*>(entity)->AddTargetEntity(MainEntities::MainPlayer());

	StarTrigger* temp = (StarTrigger*)ECS::GetComponent<Trigger*>(entity);
	temp->amount = 1;

	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);
	auto& targetBody = ECS::GetComponent<PhysicsBody>(target2);

	float shrinkX = 0.f;
	float shrinkY = 0.f;
	b2Body* tempBody;
	b2BodyDef tempDef;
	tempDef.type = bodyType;
	tempDef.position.Set(float32(targetBody.GetPosition().x), float32(targetBody.GetPosition().y));

	tempBody = m_physicsWorld->CreateBody(&tempDef);

	tempPhsBody = PhysicsBody(entity, tempBody, float(targetBody.GetWidth() - shrinkX), float(targetBody.GetHeight() - shrinkY), vec2(0.f, 0.f), true, TRIGGER, PLAYER);

	tempPhsBody.SetColor(physicsColor);
}

entt::registry* Scene::GetScene() const
{
	return m_sceneReg;
}

void Scene::SetScene(entt::registry& scene)
{
	m_sceneReg = &scene;
}

vec4 Scene::GetClearColor() const
{
	return m_clearColor;
}

void Scene::SetClearColor(vec4 clearColor)
{
	m_clearColor = clearColor;
}

std::string Scene::GetName() const
{
	return m_name;
}

void Scene::SetName(std::string name)
{
	m_name = name;
}

b2Vec2 Scene::GetGravity() const
{
	return m_gravity;
}

void Scene::SetGravity(b2Vec2 grav)
{
	m_gravity = grav;
}

b2World& Scene::GetPhysicsWorld()
{
	return *m_physicsWorld;
}

void Scene::SetWindowSize(float windowWidth, float windowHeight)
{
	//TODO: Find new way to get the main camera
	auto& tempCam = m_sceneReg->get<Camera>(MainEntities::MainCamera());

	tempCam.SetWindowSize(vec2(windowWidth, windowHeight));
	tempCam.Orthographic(float(windowWidth / windowHeight), tempCam.GetOrthoSize().x, tempCam.GetOrthoSize().y,
		tempCam.GetOrthoSize().z, tempCam.GetOrthoSize().w,
		tempCam.GetNear(), tempCam.GetFar());
}
