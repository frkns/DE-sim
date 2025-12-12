#pragma once
#include "bits/stdc++.h"
using namespace std;

using color = array<double, 3>;
const color black = {0, 0, 0};
const color white = {1, 1, 1};
const color red = {1, 0, 0};
const color green = {0, 1, 0};
const color blue = {0, 0, 1};

inline color operator*(const color& c, double k) {
    return {c[0] * k, c[1] * k, c[2] * k};
}
inline color operator*(double k, const color& c) {
    return c * k;
}
