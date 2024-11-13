
// camera.h

#pragma once

#include "util.h"
#include "vector2.h"

class Camera
{
public:
    Camera()  = default;
    ~Camera() = default;

    void
    set_size(const Vector2 size)
    {
        this->size = size;
    }

    const Vector2&
    get_size() const
    {
        return size;
    }

    void
    set_position(const Vector2 position)
    {
        this->position = position;
    }

    const Vector2&
    get_position() const
    {
        return position;
    }

    void
    look_at(const Vector2 target)
    {
        position = target - (size * 0.5f);
    }

    Vector2
    tanslate(const Vector2& v) const
    {
        return Vector2(tanslate_x(v.vx), tanslate_y(v.vy));
    }

    float
    tanslate_x(float x) const
    {
        return x - position.vx;
    }

    float
    tanslate_y(float y) const
    {
        return y - position.vy;
    }

private:
    Vector2 size;
    Vector2 position;
};
