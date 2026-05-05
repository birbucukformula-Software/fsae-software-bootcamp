#ifndef VCU_TANIMLAR_H
#define VCU_TANIMLAR_H
#include <stdbool.h>

typedef struct {
    // Grup A: Güvenlik
    bool basladi_mi;          // Start butonu
    int fren_durumu;          // 0 veya 1 (Fren basılı mı?)
    float batarya_sicakligi;  // 60 derece sınırı
    bool acil_durum;          // Sistem kilitlendi mi?

    // Grup B: Performans 
    int gaz_pedali;           // 0 - 100 arası
    int motor_torku;          // Nm cinsinden hesaplanan tork
    int batarya_dolulugu;     // % SoC
    int maksimum_tork_limiti; // O anki izin verilen maks tork (50 mi 100 mü?)
    int arac_surati;          // km/s
    int vites_durumu;         // 0: Boş, 1: İleri, 2: Geri

    // Grup C: Soğutma 
    float motor_sicakligi;    // 80 derece sınırı
    bool fan_durumu;          // Fan açık mı?

    // Grup D: Aero
    bool drs_durumu;          // Sürücü DRS açmak istiyor mu?
    bool drs_musaade;         // Güvenlik açısından DRS açılabilir mi?
    int direksiyon_acisi;     // 45 derece sınırı
} Arac;

#endif