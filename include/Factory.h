#pragma once
//-------------------------------------------//
#include "BaseGameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <iostream>
//-------------------------------------------//
enum class ObjectType
{
    MonkeySymbol = 'M',
    RedBladeSymbol = '*',
    BlackBladeSymbol = '@',
    InvisibleSymbol = 'I',
    StaticNormalFloorSymbol = '_',
    StaticInvisibleFloorSymbol = '~',
    StaticBouncingFloorSymbol = '^',
    StaticCloudFloorSymbol = '#',
    MovingNormalFloorSymbol = '=',
    MovingInvisibleFloorSymbol = '"',
    MovingBouncingFloorSymbol = '%',
    MovingCloudFloorSymbol = '&',
    FinishLineSymbol = 'F',
};
//-------------------------------------------//
template <typename BaseObjectOrMore>
class Factory
{
public:
    static Factory& instance()
    {
        static auto instance = Factory();
        return instance;
    }

    using FuncType = std::unique_ptr<BaseObjectOrMore>(*)(sf::Vector2f position);

    bool registerType(ObjectType t, FuncType f)
    {
        m_map.emplace(t, f);
        return true;
    }

    std::unique_ptr<BaseObjectOrMore> create(ObjectType t, sf::Vector2f position) const
    {
        if (!m_map.contains(t)) return nullptr;

        return m_map.at(t)(position);
    }

    bool IsExist(const char& ObjectSymbol) const;

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<ObjectType, FuncType> m_map;
};
//-------------------------------------------//
template<typename BaseObjectOrMore>
inline bool Factory<BaseObjectOrMore>::IsExist(const char& ObjectSymbol) const
{
    for (auto& pair : m_map)
    {
        if ((char)pair.first == ObjectSymbol) {
            return true;
        }
    }

    return false;
}
//-------------------------------------------//