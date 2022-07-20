#include "Utilities.h"
#include <array>

namespace
{
    //array for stiring from key
    const std::array<std::string, sf::Keyboard::Key::KeyCount> KeysStrings
    {
          "A"       ,
          "B"       ,
          "C"       ,
          "D"       ,
          "E"       ,
          "F"       ,
          "G"       ,
          "H"       ,
          "I"       ,
          "J"       ,
          "K"       ,
          "L"       ,
          "M"       ,
          "N"       ,
          "O"       ,
          "P"       ,
          "Q"       ,
          "R"       ,
          "S"       ,
          "T"       ,
          "U"       ,
          "V"       ,
          "W"       ,
          "X"       ,
          "Y"       ,
          "Z"       ,
         "Num0"     ,
         "Num1"     ,
         "Num2"     ,
         "Num3"     ,
         "Num4"     ,
         "Num5"     ,
         "Num6"     ,
         "Num7"     ,
         "Num8"     ,
         "Num9"     ,
         "Escape"   ,
         "LControl" ,
         "LShift"   ,
         "LAlt"     ,
         "LSystem"  ,
         "RControl" ,
         "RShift"   ,
         "RAlt"     ,
         "RSystem"  ,
         "Menu"     ,
         "LBracket" ,
         "RBracket" ,
         "SemiColon",
         "Comma"    ,
         "Period"   ,
         "Quote"    ,
         "Slash"    ,
         "BackSlash",
         "Tilde"    ,
         "Equal"    ,
         "Dash"     ,
         "Space"    ,
         "Return"   ,
         "BackSpace",
         "Tab"      ,
         "PageUp"   ,
         "PageDown" ,
         "End"      ,
         "Home"     ,
         "Insert"   ,
         "Delete"   ,
         "Add"      ,
         "Subtract" ,
         "Multiply" ,
         "Divide"   ,
         "Left"     ,
         "Right"    ,
         "Up"       ,
         "Down"     ,
         "Numpad0"  ,
         "Numpad1"  ,
         "Numpad2"  ,
         "Numpad3"  ,
         "Numpad4"  ,
         "Numpad5"  ,
         "Numpad6"  ,
         "Numpad7"  ,
         "Numpad8"  ,
         "Numpad9"  ,
         "F1"       ,
         "F2"       ,
         "F3"       ,
         "F4"       ,
         "F5"       ,
         "F6"       ,
         "F7"       ,
         "F8"       ,
         "F9"       ,
         "F10"      ,
         "F11"      ,
         "F12"      ,
         "F13"      ,
         "F14"      ,
         "F15"      ,
         "Pause"
    };
    //hash for key from string
    std::unordered_map<std::string, sf::Keyboard::Key> initilizeKeyMap() {
        std::unordered_map<std::string, sf::Keyboard::Key> KeyMap;
        KeyMap.reserve(sf::Keyboard::KeyCount);
        KeyMap.emplace("A", sf::Keyboard::A);
        KeyMap.emplace("B", sf::Keyboard::B);
        KeyMap.emplace("C", sf::Keyboard::C);
        KeyMap.emplace("D", sf::Keyboard::D);
        KeyMap.emplace("E", sf::Keyboard::E);
        KeyMap.emplace("F", sf::Keyboard::F);
        KeyMap.emplace("G", sf::Keyboard::G);
        KeyMap.emplace("H", sf::Keyboard::H);
        KeyMap.emplace("I", sf::Keyboard::I);
        KeyMap.emplace("J", sf::Keyboard::J);
        KeyMap.emplace("K", sf::Keyboard::K);
        KeyMap.emplace("L", sf::Keyboard::L);
        KeyMap.emplace("M", sf::Keyboard::M);
        KeyMap.emplace("N", sf::Keyboard::N);
        KeyMap.emplace("O", sf::Keyboard::O);
        KeyMap.emplace("P", sf::Keyboard::P);
        KeyMap.emplace("Q", sf::Keyboard::Q);
        KeyMap.emplace("R", sf::Keyboard::R);
        KeyMap.emplace("S", sf::Keyboard::S);
        KeyMap.emplace("T", sf::Keyboard::T);
        KeyMap.emplace("U", sf::Keyboard::U);
        KeyMap.emplace("V", sf::Keyboard::V);
        KeyMap.emplace("W", sf::Keyboard::W);
        KeyMap.emplace("X", sf::Keyboard::X);
        KeyMap.emplace("Y", sf::Keyboard::Y);
        KeyMap.emplace("Z", sf::Keyboard::Z);
        KeyMap.emplace("Num0", sf::Keyboard::Num0);
        KeyMap.emplace("Num1", sf::Keyboard::Num1);
        KeyMap.emplace("Num2", sf::Keyboard::Num2);
        KeyMap.emplace("Num3", sf::Keyboard::Num3);
        KeyMap.emplace("Num4", sf::Keyboard::Num4);
        KeyMap.emplace("Num5", sf::Keyboard::Num5);
        KeyMap.emplace("Num6", sf::Keyboard::Num6);
        KeyMap.emplace("Num7", sf::Keyboard::Num7);
        KeyMap.emplace("Num8", sf::Keyboard::Num8);
        KeyMap.emplace("Num9", sf::Keyboard::Num9);
        KeyMap.emplace("Escape", sf::Keyboard::Escape);
        KeyMap.emplace("LControl", sf::Keyboard::LControl);
        KeyMap.emplace("LShift", sf::Keyboard::LShift);
        KeyMap.emplace("LAlt", sf::Keyboard::LAlt);
        KeyMap.emplace("LSystem", sf::Keyboard::LSystem);
        KeyMap.emplace("RControl", sf::Keyboard::RControl);
        KeyMap.emplace("RShift", sf::Keyboard::RShift);
        KeyMap.emplace("RAlt", sf::Keyboard::RAlt);
        KeyMap.emplace("RSystem", sf::Keyboard::RSystem);
        KeyMap.emplace("Menu", sf::Keyboard::Menu);
        KeyMap.emplace("LBracket", sf::Keyboard::LBracket);
        KeyMap.emplace("RBracket", sf::Keyboard::RBracket);
        KeyMap.emplace("SemiColon", sf::Keyboard::SemiColon);
        KeyMap.emplace("Comma", sf::Keyboard::Comma);
        KeyMap.emplace("Period", sf::Keyboard::Period);
        KeyMap.emplace("Quote", sf::Keyboard::Quote);
        KeyMap.emplace("Slash", sf::Keyboard::Slash);
        KeyMap.emplace("BackSlash", sf::Keyboard::BackSlash);
        KeyMap.emplace("Tilde", sf::Keyboard::Tilde);
        KeyMap.emplace("Equal", sf::Keyboard::Equal);
        KeyMap.emplace("Dash", sf::Keyboard::Dash);
        KeyMap.emplace("Space", sf::Keyboard::Space);
        KeyMap.emplace("Return", sf::Keyboard::Return);
        KeyMap.emplace("BackSpace", sf::Keyboard::BackSpace);
        KeyMap.emplace("Tab", sf::Keyboard::Tab);
        KeyMap.emplace("PageUp", sf::Keyboard::PageUp);
        KeyMap.emplace("PageDown", sf::Keyboard::PageDown);
        KeyMap.emplace("End", sf::Keyboard::End);
        KeyMap.emplace("Home", sf::Keyboard::Home);
        KeyMap.emplace("Insert", sf::Keyboard::Insert);
        KeyMap.emplace("Delete", sf::Keyboard::Delete);
        KeyMap.emplace("Add", sf::Keyboard::Add);
        KeyMap.emplace("Subtract", sf::Keyboard::Subtract);
        KeyMap.emplace("Multiply", sf::Keyboard::Multiply);
        KeyMap.emplace("Divide", sf::Keyboard::Divide);
        KeyMap.emplace("Left", sf::Keyboard::Left);
        KeyMap.emplace("Right", sf::Keyboard::Right);
        KeyMap.emplace("Up", sf::Keyboard::Up);
        KeyMap.emplace("Down", sf::Keyboard::Down);
        KeyMap.emplace("Numpad0", sf::Keyboard::Numpad0);
        KeyMap.emplace("Numpad1", sf::Keyboard::Numpad1);
        KeyMap.emplace("Numpad2", sf::Keyboard::Numpad2);
        KeyMap.emplace("Numpad3", sf::Keyboard::Numpad3);
        KeyMap.emplace("Numpad4", sf::Keyboard::Numpad4);
        KeyMap.emplace("Numpad5", sf::Keyboard::Numpad5);
        KeyMap.emplace("Numpad6", sf::Keyboard::Numpad6);
        KeyMap.emplace("Numpad7", sf::Keyboard::Numpad7);
        KeyMap.emplace("Numpad8", sf::Keyboard::Numpad8);
        KeyMap.emplace("Numpad9", sf::Keyboard::Numpad9);
        KeyMap.emplace("F1", sf::Keyboard::F1);
        KeyMap.emplace("F2", sf::Keyboard::F2);
        KeyMap.emplace("F3", sf::Keyboard::F3);
        KeyMap.emplace("F4", sf::Keyboard::F4);
        KeyMap.emplace("F5", sf::Keyboard::F5);
        KeyMap.emplace("F6", sf::Keyboard::F6);
        KeyMap.emplace("F7", sf::Keyboard::F7);
        KeyMap.emplace("F8", sf::Keyboard::F8);
        KeyMap.emplace("F9", sf::Keyboard::F9);
        KeyMap.emplace("F10", sf::Keyboard::F10);
        KeyMap.emplace("F11", sf::Keyboard::F11);
        KeyMap.emplace("F12", sf::Keyboard::F12);
        KeyMap.emplace("F13", sf::Keyboard::F13);
        KeyMap.emplace("F14", sf::Keyboard::F14);
        KeyMap.emplace("F15", sf::Keyboard::F15);
        KeyMap.emplace("Pause", sf::Keyboard::Pause);
        return KeyMap;
    }
}// end namespace
//get string from key
sf::String getKeyString(const sf::Keyboard::Key& key)
{
    return KeysStrings[size_t(key)];
}
//get key from string
sf::Keyboard::Key getKey(const std::string& string)
{
    const static auto keyMap = initilizeKeyMap();
    auto keyEntry = keyMap.find(string);
    if (keyEntry == keyMap.end()) throw std::invalid_argument("Invalid String");
    return keyEntry->second;
}
//set reflection for modes
sf::Uint8 setReflection(int &reflection, int & speed) {
    if (speed > 0) {
        reflection = std::min(reflection + speed, MAX_REFLECTION);
    }
    else {
        reflection = std::max(reflection + speed, MIN_REFLECTION);
    }
    if (reflection == MAX_REFLECTION || reflection == MIN_REFLECTION) {
        speed *= -1;
    }

    return sf::Uint8(reflection);
}
//check if number is contain in a radius
bool isContainByRadius(const sf::Vector2f& p1, const sf::Vector2f& p2, float radius) {
    return std::abs(p1.x - p2.x) < radius && std::abs(p1.y - p2.y) < radius;
}
