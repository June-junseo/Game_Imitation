#pragma once
#include "Scene.h"
class Scene1 :
    public Scene
{
protected:
	sf::Sprite background1;
	std::string texId = "graphics/scene1_bg.png";
	/*sf::CircleShape moveShape;*/

public:
	Scene1();

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void ResourceLoad();
	void SetUpViews();
	void Draw(sf::RenderWindow& window) override;
};

