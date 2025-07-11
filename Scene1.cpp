#include "stdafx.h"
#include "Scene1.h"
Scene1::Scene1()
	: Scene(SceneIds::Scene1)
{
}

void Scene1::Init()
{
	TEXTURE_MGR.Load(texIds);

	background1.setPosition(0.f, 0.f);

	background1.setTexture(TEXTURE_MGR.Get(texId), true);

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
}

void Scene1::Update(float dt)
{
	Scene::Update(dt);

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

void Scene1::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background1);
}
