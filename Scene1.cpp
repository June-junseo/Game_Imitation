#include "stdafx.h"
#include "Scene1.h"
#include "ArrowButton.h"

Scene1::Scene1()
	: Scene(SceneIds::Scene1)
{
}

void Scene1::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f size(25.f, 30.f);

	float yOffset = 20.f;
	leftArrow = new ArrowButton(ArrowDirection::Left, { 150, windowSize.y / 2 - 20 }, size);
	rightArrow = new ArrowButton(ArrowDirection::Right, { windowSize.x - 370, windowSize.y / 2 - 20 }, size);

	TEXTURE_MGR.Load(texIds);

	background1.setPosition(0.f, 0.f);

	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	leftArrow->SetCallBack([]() {
		std::cout << "¿ÞÂÊ È­»ìÇ¥ Å¬¸¯µÊ\n";
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
		});
	rightArrow->SetCallBack([]() {
		// Next scene
		});

	Scene::Init();
}

void Scene1::Enter()
{
	Scene::Enter();
	SetUpViews();
}

void Scene1::Exit()
{
	Scene::Exit();

	delete leftArrow;
	leftArrow = nullptr;

	delete rightArrow;
	rightArrow = nullptr;
}

void Scene1::Update(float dt)
{
	Scene::Update(dt);

	if (leftArrow) {
		leftArrow->UpdateHoverState(FRAMEWORK.GetWindow());
		leftArrow->Update();  
	}
	if (rightArrow) {
		rightArrow->UpdateHoverState(FRAMEWORK.GetWindow());
		rightArrow->Update();  
	}
}

void Scene1::ResourceLoad()
{
	texIds.push_back(texId);
}

void Scene1::SetUpViews()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);
    
	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

void Scene1::HandleEvent(const sf::Event& event)
{
	if (leftArrow)
		leftArrow->HandleEvent(event, FRAMEWORK.GetWindow());

	if (rightArrow)
		rightArrow->HandleEvent(event, FRAMEWORK.GetWindow());
}


void Scene1::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background1);
	if (leftArrow) window.draw(*leftArrow);
	if (rightArrow) window.draw(*rightArrow);
}
