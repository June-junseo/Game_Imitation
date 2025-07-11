#pragma once
#include "Scene.h"
class ArrowButton;
class Scene1 :
    public Scene
{
protected:

	ArrowButton* leftArrow = nullptr;
	ArrowButton* rightArrow = nullptr;
	sf::Sprite background1;
	std::string texId = "graphics/scene1_bg.png";

public:
	Scene1();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void ResourceLoad();
	void SetUpViews();
	void Draw(sf::RenderWindow& window) override;
	virtual void HandleEvent(const sf::Event& event) override;
};

