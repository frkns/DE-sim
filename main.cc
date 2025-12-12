#include "bits/stdc++.h"
#include "color.h"
#include "io.h"
#include "vec2.h"
using namespace std;

const vector<point> planets = {{0, 2}, {-1, -1}, {1, -2}};
const vector<color> planet_colors = {red, green, blue};

double masses = 0.5;
const vector<double> k = {masses, masses, masses}; // mass

const double c = 0.05; // drag

const double dt = 0.05; // simulation timestep

void step_(vec2& x, vec2& v, vec2& a) {
    auto old_x = x;
    auto old_v = v;
    auto old_a = a;

    x += old_v * dt;
    v += old_a * dt;
    a = {0, 0};
    for (int i = 0; i < planets.size(); i++) {
        vec2 diff = old_x - planets[i];
        a -= k[i] / (pow(diff.norm(), 3) + 1e-9) * diff;
    }
    a -= c * old_v;
}

color simulate(vec2 x) {
    static const int max_iter = 10000;

    vec2 v = {0, 0};
    vec2 a = {0, 0};

    for (int it = 1; it < max_iter; it++) {
        step_(x, v, a);

        // if (it % 2222 == 333)
            // clog << x.norm() << ' ' << v.norm() << ' ' << a.norm() << '\n';

        // if (v.norm() > 1)
        //     continue;

        for (int i = 0; i < planets.size(); i++)
            if ((x - planets[i]).norm() < 0.15)
                return  (1 - double(it) / max_iter) * planet_colors[i];
    }
    // clog << "DONE!\n";

    assert(!isnan(x.x));
    assert(!isnan(v.x));
    assert(!isnan(a.x));
    assert(!isnan(x.y));
    assert(!isnan(v.y));
    assert(!isnan(a.y));
    return white;
}

double sqr(double x) {
    return x * x;
}

color point_color(double x, double y) {
    for (auto& [px, py] : planets)
        if (sqr(x - px) + sqr(y - py) < sqr(0.1))
            return black;

    vec2 X = {x, y};
    return simulate(X);

    return white;
}

int main() {
    const double viewport_height = 9; // viewport centered at (0,0)
    const double viewport_width = 16;

    const int im_height = 90;
    const int im_width = 160;
    const double dy = viewport_height / im_height;
    const double dx = viewport_width / im_width;

    array<array<color, im_width>, im_height> image{};

    for (int i = 0; i < im_height; i++) {
        clog << '\r' << i + 1 << '/' << im_height;
        for (int j = 0; j < im_width; j++) {
            double y = viewport_height / 2 - i * dy;
            double x = -viewport_width / 2 + j * dx;
            image[i][j] = point_color(x, y);
        }
    }
    write_image(image, "output/image.ppm");
}
