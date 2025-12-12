#include "bits/stdc++.h"
#include "color.h"
#include "io.h"
#include "vec2.h"
using namespace std;

const double ki = 0.5;  // mass
const double c = 0.01;  // drag
const double dt = 0.01; // simulation timestep
const vector<color> base_colors = {red,  green,   yellow, blue,
                                   cyan, magenta, orange, purple};

vector<point> planets;
vector<color> planet_colors;

int init_planets() {
    int64_t seed = time(nullptr);
    clog << "using seed " << seed << '\n';
    mt19937 rng(seed);
    uniform_real_distribution<double> dist_x(-8.0, 8.0);
    uniform_real_distribution<double> dist_y(-4.5, 4.5);
    const int n = base_colors.size();
    for (int i = 0; i < n; i++) {
        double x = dist_x(rng);
        double y = dist_y(rng);
        planets.push_back({x, y});
        planet_colors.push_back(base_colors[i % base_colors.size()]);
    }
    return 0;
}
int _ = init_planets();
const vector<double> k(planets.size(), ki);

void step_(vec2& x, vec2& v, vec2& a) {
    // non-synchronous updates are purportedly better
    v += a * dt;
    x += v * dt; // updated v trick
    a = {0, 0};
    for (int i = 0; i < planets.size(); i++) {
        vec2 diff = x - planets[i];
        a -= k[i] / (pow(diff.norm(), 3) + 1e-9) * diff;
    }
    a -= c * v;
}

color simulate(vec2 x) {
    static const int max_iter = 50'000;

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
                return max(1 - double(it) / (max_iter / 2.), 0.3) * planet_colors[i];
        // return planet_colors[i];
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
        if (sqr(x - px) + sqr(y - py) < sqr(0.077))
            return gray;

    vec2 X = {x, y};
    return simulate(X);
}

int main() {
    const double viewport_height = 9; // viewport centered at (0,0)
    const double viewport_width = 16;

    const int im_height = 9 * 10;
    const int im_width = 16 * 10;
    const double dy = viewport_height / im_height;
    const double dx = viewport_width / im_width;

    // array<array<color, im_width>, im_height> image1{};

    ofstream fout("output/image.ppm");
    write_header(fout, im_height, im_width);

    for (int i = 0; i < im_height; i++) {
        clog << '\r' << i + 1 << '/' << im_height;
        for (int j = 0; j < im_width; j++) {
            double y = viewport_height / 2 - i * dy;
            double x = -viewport_width / 2 + j * dx;
            color col = point_color(x, y);
            write_color(fout, col);
        }
    }
    clog << "\ndone first part.\n";

    // write_image(image1, "output/image.ppm");
}
