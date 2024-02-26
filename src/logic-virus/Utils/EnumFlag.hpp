#pragma once

#include <type_traits>

template<typename T>
constexpr bool IsEnumFlag(T) { return false; }

#define DEFINE_ENUM_FLAG(enumType) constexpr bool IsEnumFlag(enumType) { return true; }

namespace enum_traits
{
    template<typename T>
    using IsFlag = std::conjunction < std::is_enum<T>, std::integral_constant<bool, IsEnumFlag(T{}) >> ;
}

template<typename T, std::enable_if_t<enum_traits::IsFlag<T>::value, std::nullptr_t> = nullptr>
inline constexpr T operator&(T left, T right)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(left) & static_cast<std::underlying_type_t<T>>(right));
}

template<typename T, std::enable_if_t<enum_traits::IsFlag<T>::value, std::nullptr_t> = nullptr>
inline constexpr T& operator&=(T& left, T right)
{
    return left = left & right;
}

template<typename T, std::enable_if_t<enum_traits::IsFlag<T>::value, std::nullptr_t> = nullptr>
inline constexpr T operator|(T left, T right)
{
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(left) | static_cast<std::underlying_type_t<T>>(right));
}

template<typename T, std::enable_if_t<enum_traits::IsFlag<T>::value, std::nullptr_t> = nullptr>
inline constexpr T& operator|=(T& left, T right)
{
    return left = left | right;
}

template<typename T, std::enable_if_t<enum_traits::IsFlag<T>::value, std::nullptr_t> = nullptr>
inline constexpr T operator~(T value)
{
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(value));
}

template<typename T>
class enum_flag
{
    static_assert(enum_traits::IsFlag<T>::value, "EnumFlag must be used only with enums that are marked as flags by DEFINE_ENUM_FLAG macro");

public:
    /*implicit*/ constexpr enum_flag(T value) : _value(value)
    {
    }

    constexpr enum_flag& operator&=(enum_flag right)
    {
        _value &= right._value;
        return *this;
    }

    constexpr friend enum_flag operator&(enum_flag left, enum_flag right)
    {
        return left &= right;
    }

    constexpr enum_flag& operator|=(enum_flag right)
    {
        _value |= right._value;
        return *this;
    }

    constexpr friend enum_flag operator|(enum_flag left, enum_flag right)
    {
        return left |= right;
    }

    constexpr enum_flag operator~() const
    {
        return static_cast<T>(~static_cast<std::underlying_type_t<T>>(_value));
    }

    constexpr void RemoveFlag(enum_flag flag)
    {
        _value &= ~flag._value;
    }

    constexpr bool HasFlag(T flag) const
    {
        using i = std::underlying_type_t<T>;
        return static_cast<i>(_value & flag) != static_cast<i>(0);
    }

    constexpr bool HasAllFlags(T flags) const
    {
        return (_value & flags) == flags;
    }

    constexpr operator T() const
    {
        return _value;
    }

    constexpr std::underlying_type_t<T> AsUnderlyingType() const
    {
        return static_cast<std::underlying_type_t<T>>(_value);
    }

private:
    T _value;
};