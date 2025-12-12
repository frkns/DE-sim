#pragma once
#include "bits/stdc++.h"
using namespace std;

struct vec2 {
    double x, y;

    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    vec2& operator+=(double k) {
        x += k;
        y += k;
        return *this;
    }
    vec2& operator-=(const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    vec2& operator*=(double k) {
        x *= k;
        y *= k;
        return *this;
    }
    vec2& operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }

    friend vec2 operator*(double k, vec2 vec) {
        vec *= k;
        return vec;
    }
    friend vec2 operator*(vec2 vec, double k) {
        vec *= k;
        return vec;
    }
    friend vec2 operator+(double k, vec2 vec) {
        vec += k;
        return vec;
    }
    friend vec2 operator+(vec2 vec, double k) {
        vec += k;
        return vec;
    }
    friend vec2 operator+(vec2 u, const vec2& v) {
        u += v;
        return u;
    }
    friend vec2 operator-(vec2 u, const vec2& v) {
        u -= v;
        return u;
    }

    double length_squared() const {
        return x * x + y * y;
    }
    double norm() const {
        return sqrt(length_squared());
    }
};
using point = vec2;
