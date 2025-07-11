#include "stdafx.h"
#include "ZoomUI.h"

void ZoomUI::Init(const sf::Texture& texture, const sf::Vector2f& windowCenter)
{
    sprite.setTexture(texture);
    sprite.setPosition(windowCenter.x - texture.getSize().x / 2.f, windowCenter.y - texture.getSize().y / 2.f);
}

void ZoomUI::SetClickableArea(const sf::FloatRect& rect)
{
    clickableArea = rect;
}

bool ZoomUI::CheckClick(const sf::Vector2f& point)
{
    return clickableArea.contains(point);
}

void ZoomUI::Draw(sf::RenderWindow& window)
{
    if (isVisible)
    {
        std::cout << "ZoomUI drwaing\n";
        window.draw(sprite);
    }
    else
    {
        std::cout << "ZoomUI hided\n";
    }
}