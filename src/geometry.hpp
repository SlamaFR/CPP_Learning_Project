#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>

template <typename type, int dim> struct Point
{
    std::array<type, dim> values {};

    Point() = default;

    template <typename... N>
    explicit Point(N&&... numbers) : values { std::forward<type>(static_cast<type>(numbers))... }
    {
        static_assert(sizeof...(numbers) == dim);
    }

    template <int i> type& get() { return values[i]; }

    template <int i> type get() const { return values[i]; }

    type& x()
    {
        static_assert(dim >= 1, "x() is not defined for this point");
        return get<0>();
    }

    type x() const
    {
        static_assert(dim >= 1, "x() is not defined for this point");
        return get<0>();
    }

    type& y()
    {
        static_assert(dim >= 2, "y() is not defined for this point");
        return get<1>();
    }

    type y() const
    {
        static_assert(dim >= 2, "y() is not defined for this point");
        return get<1>();
    }

    type& z()
    {
        static_assert(dim >= 3, "z() is not defined for this point");
        return get<2>();
    }

    type z() const
    {
        static_assert(dim >= 3, "z() is not defined for this point");
        return get<2>();
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), std::plus<type>());
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<type>());
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::multiplies<type>());
        return *this;
    }

    Point& operator*=(const type scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(), [scalar](type v) { return v * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const type scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const
    {
        Point result = *this;
        std::transform(result.values.begin(), result.values.end(), result.values.begin(),
                       [](type v) { return -v; });
        return result;
    }

    type length() const
    {
        return std::sqrt(std::reduce(values.begin(), values.end(), 0.0,
                                     [](type acc, type cur) { return acc + (cur * cur); }));
    }

    type distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const type target_len = 1.0f)
    {
        const type current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const type max_len)
    {
        assert(max_len > 0);

        const type current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

using Point2D = Point<float, 2>;
using Point3D = Point<float, 3>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return Point2D { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
