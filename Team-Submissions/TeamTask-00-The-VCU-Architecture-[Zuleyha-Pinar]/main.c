#include <stdio.h>
#include <stdbool.h>
#include "vcu-define.h"

// Diğer dosyalardaki fonksiyonları burada tanıtıyoruz (Extern)
extern void Guvenlik_Denetimi(Arac* a);              
extern void Performans_Ve_Aero_Yonetimi(Arac* a);    
extern void Veri_Girisi_Isle(Arac* a);              
extern void Dashboard_Goster(Arac* a);              

int main() {
    // 1. ARACI BAŞLAT (İlk değerleri sıfırla)
    Arac formula_araci = { 0 };

    // Başlangıç için bazı varsayılan değerler
    formula_araci.batarya_dolulugu = 100;
    formula_araci.basladi_mi = false;
    formula_araci.acil_durum = false;

    printf("Project Cortex: VCU Simülasyonu Başlatıldı...\n");
    printf("Yardım: Veri girmek için 'ID DEGER' yazın (Örn: 1 1).\n");

    // 2. ANA DÖNGÜ (Sonsuz Döngü)
    while (1) {
        // ADIM 1: Dashboard'u Güncelle (Ekranı Yazdır)
        Dashboard_Goster(&formula_araci);

        // ADIM 2: Kullanıcıdan Veri Al (Sensör/CAN Verisi Simülasyonu)
        Veri_Girisi_Isle(&formula_araci);

        // ADIM 3: GÜVENLİK DENETİMİ (Senin Kuralların)
        // Her şeyden önce güvenlik! Eğer bir tehlike varsa tork kesilir.
        Guvenlik_Denetimi(&formula_araci);

        // ADIM 4: MOTOR VE AERO YÖNETİMİ (Arkadaşının Kuralları)
        // Güvenlik onayı verirse tork hesaplanır ve DRS kontrol edilir.
        Performans_Ve_Aero_Yonetimi(&formula_araci);

        // Not: Gerçek bir sistemde burada 'delay' (bekleme) olurdu, 
        // ama simülasyonda her veri girişinden sonra döngü döner.
    }

    return 0;

}
