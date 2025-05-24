#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
    Optimasi Waktu Pengisian Baterai dengan Metode Brent
    Parameter:
    - Tegangan maksimum (V_max) = 4.2 V
    - Tegangan target (V_target) = 4.0 V  
    - Konstanta pengisian (k) = 0.03 s⁻¹
    - Batas waktu awal = [30 s, 120 s]
    - Toleransi error = 10⁻⁵
    - Iterasi maksimum = 50
*/

// Parameter tetap
#define V_MAX 4.2
#define V_TARGET 4.0
#define K 0.03
#define EPSILON 1e-5
#define MAX_ITER 50

// Fungsi yang merepresentasikan tegangan baterai terhadap waktu
double fungsi_pengisian(double t) {
    return V_MAX * (1.0 - exp(-K * t)) - V_TARGET;
}

double metode_brent(double a, double b, double (*f)(double), double tol, int max_iter, int *iter_count) {
    double fa = f(a);
    double fb = f(b);
    
    // Validasi: memastikan interval mengapit akar (fa dan fb berbeda tanda)
    if (fa * fb >= 0.0) {
        printf("Error: Fungsi harus memiliki tanda berbeda di titik a dan b.\n");
        return NAN;
    }
    
    // Memastikan |f(b)| < |f(a)|
    if (fabs(fa) < fabs(fb)) {
        double temp = a;
        a = b;
        b = temp;
        temp = fa;
        fa = fb;
        fb = temp;
    }
    
    // Inisialisasi variabel
    double c = a;              // Nilai sebelumnya dari b
    double fc = fa;            // f(c)
    bool flag_biseksi = true;  // Flag untuk menandai penggunaan biseksi
    double d = 0.0;            // Nilai sebelum c
    double s = 0.0;            // Nilai tebakan akar baru
    double fs = 0.0;           // f(s)
    
    printf("\n=== PROSES ITERASI ===\n");
    printf("Iterasi\t t(dtk)\t\t Selisih Tegangan\n");

    // Mulai iterasi
    for (*iter_count = 1; *iter_count <= max_iter; (*iter_count)++) {
        // Cek kriteria konvergensi
        if (fabs(b - a) < tol) {
            return s;
        }
        
        // Menghitung tebakan baru dengan inverse quadratic interpolation atau false position
        if (fa != fc && fb != fc) {
            // Inverse quadratic interpolation
            s = a * fb * fc / ((fa - fb) * (fa - fc)) + b * fa * fc / ((fb - fa) * (fb - fc)) + c * fa * fb / ((fc - fa) * (fc - fb));
        }
        else {
            // False position (linear interpolation)
            s = b - fb * (b - a) / (fb - fa);
        }
        
        // Cek kondisi untuk menggunakan metode biseksi
        if ((s < (3.0 * a + b) / 4.0 || s > b) ||
            (flag_biseksi && fabs(s - b) >= fabs(b - c) / 2.0) ||
            (!flag_biseksi && fabs(s - b) >= fabs(c - d) / 2.0) ||
            (flag_biseksi && fabs(b - c) < tol) ||
            (!flag_biseksi && fabs(c - d) < tol)) {
            s = (a + b) / 2.0;
            flag_biseksi = true;
        } 
        else {
            flag_biseksi = false;
        }
        
        fs = f(s);
        printf("%d\t %.6f\t %.6f\n", *iter_count, s, fs);

        d = c;       // Simpan nilai c sebelumnya
        c = b;       // Simpan nilai b sebelumnya
        fc = fb;     // Simpan f(b) sebelumnya
        
        // Memperbarui interval [a,b]
        if (fa * fs < 0.0) {
            b = s;
            fb = fs;
        } 
        else {
            a = s;
            fa = fs;
        }
        
        // Memastikan |f(a)| < |f(b)|
        if (fabs(fa) < fabs(fb)) {
            double temp = a;
            a = b;
            b = temp;
            temp = fa;
            fa = fb;
            fb = temp;
        }
        
        // Cek toleransi
        if (fabs(fs) < tol) {
            return s;
        }
    }
    
    printf("Peringatan: Iterasi maksimum tercapai tanpa konvergensi.\n");
    return s;
}

int main() {
    // Batas waktu awal (sekon)
    double a = 30.0;
    double b = 120.0;
    int iter_count = 0;
    
    // Menampilkan parameter simulasi
    printf("\n\n=========================================\n");
    printf(" Optimasi Waktu Pengisian Baterai Ponsel\n");
    printf("        Menggunakan Metode Brent\n");
    printf("=========================================\n");
    printf("\nParameter:\n");
    printf("- Tegangan maksimum (V_max)  : %.2f V\n", V_MAX);
    printf("- Tegangan target (V_target) : %.2f V\n", V_TARGET);
    printf("- Konstanta pengisian (k)    : %.3f s^-1\n", K);
    printf("- Batas waktu awal           : [%.1f, %.1f] s\n", a, b);
    printf("- Toleransi error            : %.0e\n", EPSILON);
    printf("- Iterasi maksimum           : %d\n", MAX_ITER);
    
    // Menghitung waktu pengisian menggunakan metode Brent
    double waktu_pengisian = metode_brent(a, b, fungsi_pengisian, EPSILON, MAX_ITER, &iter_count);
    
    if (!isnan(waktu_pengisian)) {
        // Menghitung tegangan yang dicapai pada waktu tersebut
        double tegangan_akhir = V_MAX * (1.0 - exp(-K * waktu_pengisian));
        
        // Menampilkan hasil
        printf("\n=== HASIL PERHITUNGAN ===\n");
        printf("- Waktu pengisian yang dibutuhkan : %.6f detik\n", waktu_pengisian);
        printf("- Tegangan yang dicapai           : %.6f V\n", tegangan_akhir);
        printf("- Selisih dengan target           : %.6f V\n", fabs(tegangan_akhir - V_TARGET));
        printf("- Jumlah iterasi                  : %d\n\n", iter_count);
    }
    
    return 0;
}