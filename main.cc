#include "bits/stdc++.h"
using namespace std;

using color = array<double, 3>;
color BLACK = {0, 0, 0};
color WHITE = {1, 1, 1};
color RED = {1, 0, 0};
color GREEN = {0, 1, 0};
color BLUE = {0, 0, 1};

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

int main() {
    const int HEIGHT = 256;
    const int WIDTH = 256;
    array<array<color, WIDTH>, HEIGHT> image{};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j] = WHITE;
        }
    }

    write_image(image, "output/image.ppm");
}
