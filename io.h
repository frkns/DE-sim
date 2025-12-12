#pragma once
#include "bits/stdc++.h"
#include "color.h"
using namespace std;

inline void write_header(ofstream& fout, int height, int width) {
    fout << "P3\n" << width << ' ' << height << "\n255\n";
}

inline void write_color(ofstream& fout, const color& col) {
    auto [r, g, b] = col;
    r = int(r * 255.999);
    g = int(g * 255.999);
    b = int(b * 255.999);
    fout << r << ' ' << g << ' ' << b << '\n';
}

template <size_t D1, size_t D2>
void write_image(const array<array<color, D2>, D1>& image, const string& file_path) {
    ofstream fout(file_path);
    fout << "P3\n" << D2 << ' ' << D1 << "\n255\n";
    for (int i = 0; i < D1; i++) {
        for (int j = 0; j < D2; j++) {
            auto [r, g, b] = image[i][j];
            r = int(r * 255.999);
            g = int(g * 255.999);
            b = int(b * 255.999);
            fout << r << ' ' << g << ' ' << b << '\n';
        }
    }
}
