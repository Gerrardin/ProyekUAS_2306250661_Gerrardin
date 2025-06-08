#include <stdio.h>
#include <math.h>

#define EPSILON 0.001
#define MAX_ITER 100

// Konstanta R dan C
#define R 1000.0       // Ohm
#define C 0.000001     // Farad

// Hitung frekuensi cut-off teoritis
double fc() {
    return 1.0 / (2.0 * M_PI * R * C);
}

// Fungsi g(f) = 1/sqrt(1 + (f/fc)^2) - 0.707
double g(double f) {
    double fc_val = fc();
    double ratio = f / fc_val;
    return 1.0 / sqrt(1.0 + ratio * ratio) - 0.707;
}

// Implementasi metode Bisection
void bisection(double a, double b) {
    if (g(a) * g(b) >= 0) {
        printf("Tidak ada perubahan tanda di interval [%.4f, %.4f]\n", a, b);
        return;
    }

    double c;
    int iter = 0;

    printf("Iterasi\t a\t\t b\t\t c\t\t g(c)\n");
    while ((b - a) >= EPSILON && iter < MAX_ITER) {
        c = (a + b) / 2.0;
        printf("%d\t %.4f\t %.4f\t %.4f\t %.4f\n", iter, a, b, c, g(c));

        if (fabs(g(c)) <= EPSILON) {
            break;
        } else if (g(a) * g(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        iter++;
    }

    printf("\nFrekuensi cut-off numerik: %.4f Hz\n", c);
}

int main() {
    double a = 100.0, b = 300.0;
    printf("Frekuensi cut-off teoritis: %.4f Hz\n\n", fc());
    bisection(a, b);
    return 0;
}
