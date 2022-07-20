#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <variant>
// Singelton

const auto RADIUS = 50.f;//think on better Name
const auto MAX_REFLECTION = 255;
const auto MIN_REFLECTION = 0;
const auto MAX_COLOR = sf::Uint8(255);




sf::String getKeyString(const sf::Keyboard::Key& key);
sf::Keyboard::Key getKey(const std::string& string);

template <class T>
void setOriginCenter(T& shape) {
	const auto rect = shape.getGlobalBounds();
	shape.setOrigin(rect.width / 2, rect.height / 2);
}

template <class A, class B>
void zip(const std::vector<A>& a, const std::vector<B>& b, std::vector<std::pair<A, B>>& zipped)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        zipped.push_back(std::make_pair(a[i], b[i]));
    }
}

sf::Uint8 setReflection(int &reflection, int & speed);

bool isContainByRadius(const sf::Vector2f& p1, const sf::Vector2f& p2, float radius);