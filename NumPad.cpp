#include "stdafx.h"
#include "NumPad.h"


void NumPad::Init(const sf::Vector2f& position, const sf::Vector2f& buttonSize)
{
    this->position = position;
    this->buttonSize = buttonSize;

    if (!font.loadFromFile("fonts/DS-DIGIT.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    labels = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "C", "0", "OK"
    };

    for (int i = 0; i < 12; ++i)
    {
        sf::RectangleShape button(buttonSize);
        int row = i / 3;
        int col = i % 3;
        button.setPosition(position.x + col * (buttonSize.x + 10.f), position.y + row * (buttonSize.y + 10.f));
        button.setFillColor(sf::Color::Yellow);
        buttons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(button.getPosition().x + 30.f, button.getPosition().y + 20.f);
        texts.push_back(text);
    }
}

void NumPad::Draw(sf::RenderWindow& window)
{
    if (!visible) return;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        window.draw(buttons[i]);
        window.draw(texts[i]);
    }
}

void NumPad::HandleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (!visible || event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i].getGlobalBounds().contains(mousePos))
        {
            std::string label = labels[i];
            if (label == "C")
            {
                ClearInput();
            }
            else if (label == "OK")
            {
                if (IsPasswordCorrect())
                {
                    std::cout << "Correct password!" << std::endl;
                    visible = false; // or some success action
                }
                else
                {
                    std::cout << "Wrong password" << std::endl;
                }
            }
            else
            {
                input += label;
                std::cout << "Input: " << input << std::endl;
            }
            break;
        }
    }
}

void NumPad::Update(float dt)
{
    // If needed for animation
}

void NumPad::SetVisible(bool v)
{
    visible = v;
}

bool NumPad::IsVisible() const
{
    return visible;
}

void NumPad::SetPassword(const std::string& pw)
{
    password = pw;
}

bool NumPad::IsPasswordCorrect() const
{
    return input == password;
}

void NumPad::ClearInput()
{
    input.clear();
}

const std::string& NumPad::GetInput() const
{
    return input;
}