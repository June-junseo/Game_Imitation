#include "stdafx.h"
#include "Scene1.h"
#include "ArrowButton.h"
#include "ZoomUI.h"

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

	// resource loading
	ResourceLoad();
	TEXTURE_MGR.Load(texIds);

	//Background setting 
	background1.setPosition(0.f, 0.f);
	background1.setTexture(TEXTURE_MGR.Get(texId), true);

	//view setting(****)
	SetUpViews();

	// click rect
	sf::FloatRect clickableArea(windowSize.x / 10.f + 165.f, windowSize.y / 2.f - 180.f, 270.f, 250.f);

	// zoomUI reset
	sf::Texture& uiTex = TEXTURE_MGR.Get("graphics/shelf_ui.png");
	if (uiTex.getSize().x == 0 || uiTex.getSize().y == 0)
	{
		std::cout << " graphics/shelf_ui.png 텍스처가 로딩되지 no\n";
	}
	// view need to be init cnetered
	zoomUI.Init(uiTex, uiView.getCenter());
	zoomUI.SetClickableArea(clickableArea);

	//check rect position for programmer
	clickableRect.setSize({ 270.f, 250.f });
	clickableRect.setPosition(clickableArea.left, clickableArea.top);
	clickableRect.setFillColor(sf::Color(255, 0, 0, 100));
	clickableRect.setOutlineThickness(3.f);
	clickableRect.setOutlineColor(sf::Color::Red);

	// arrow click (callabck)
	leftArrow->SetCallBack([this]() {
		std::cout << "왼쪽 화살표 클릭됨\n";
		if (zoomUI.IsVisible())
			zoomUI.Hide();   // UI 닫기
		else
			SCENE_MGR.ChangeScene(SceneIds::Dev2);
		});

	
	rightArrow->SetCallBack([this]() {
		if (zoomUI.IsVisible())
			zoomUI.Hide();   // closed ui
		else
		{
			// next scene
		}
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
	InputMgr::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePosF = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());
		if (zoomUI.CheckClick(mousePosF))
		{
			zoomUI.Show();
			std::cout << "ZoomUI clicked\n";
		}
	}

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
	texIds.push_back("graphics/shelf_ui.png"); 
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
	InputMgr::UpdateEvent(event);

	if (leftArrow)
		leftArrow->HandleEvent(event, FRAMEWORK.GetWindow());

	if (rightArrow)
		rightArrow->HandleEvent(event, FRAMEWORK.GetWindow());
}


void Scene1::Draw(sf::RenderWindow& window)
{
	window.setView(uiView);
	window.draw(background1);
	window.draw(clickableRect);

	zoomUI.Draw(window); 

	if (leftArrow) window.draw(*leftArrow);
	if (rightArrow) window.draw(*rightArrow);

}
