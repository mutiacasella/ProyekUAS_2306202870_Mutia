# Optimasi Waktu Pengisian Baterai Ponsel Menggunakan Metode Brent

```
Nama  : Mutia Casella
NPM   : 2306202870
```

## Deskripsi Program

Program ini menggunakan metode numerik Brent untuk menghitung waktu yang dibutuhkan dalam proses pengisian baterai ponsel hingga mencapai tegangan target. Model pengisian diasumsikan mengikuti fungsi eksponensial yang merepresentasikan pertumbuhan tegangan terhadap waktu, dengan mempertimbangkan faktor resistansi dan efisiensi sistem pengisian.

Jenis baterai yang dimodelkan dalam program ini adalah baterai lithium-ion (Li-ion), yaitu tipe baterai yang paling umum digunakan pada perangkat ponsel saat ini. Tujuan utama dari program ini adalah untuk menentukan durasi pengisian agar baterai dapat mencapai tegangan tertentu. Sebagai contoh, dari 0 V hingga 4.0 V, dengan batas maksimum tegangan 4.2 V, serta konstanta pengisian yang telah ditentukan.

Metode Brent dipilih karena merupakan metode hibrida yang menggabungkan keandalan metode biseksi dengan kecepatan metode secant dan interpolasi kuadrat. Metode ini sangat efisien dan stabil untuk menyelesaikan persamaan nonlinear satu variabel tanpa memerlukan turunan fungsi secara eksplisit. Program ditulis dalam bahasa pemrograman C, dan dijalankan melalui terminal. Seluruh parameter simulasi, termasuk batas bawah dan atas waktu pengisian, telah ditentukan langsung di dalam program. Program akan menampilkan proses iterasi dan hasil akhir berupa estimasi waktu pengisian yang dibutuhkan hingga tegangan baterai mencapai nilai target.