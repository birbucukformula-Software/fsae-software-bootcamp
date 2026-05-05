#include <stdio.h>
#include "vcu-define.h"

// Güvenlik ve Soğutma kurallarını denetleyen ana fonksiyon.

void Guvenlik_Denetimi(Arac *a) {

    // KURAL 3: BMS ACİL DURUM
    if (a->batarya_sicakligi > 60.0) {
        a->acil_durum = true;
        a->motor_torku = 0;
        printf("\nACIL DURUM: Batarya cok sicak (%0.1f C)! Sistem kilitlendi !\n", a->batarya_sicakligi);
    }

    // Sistem kilitliyse diğer kuralları işletmeye gerek yok, fonksiyonu bitir.
    if (a->acil_durum == true) {
        a->motor_torku = 0;
        return; 
    }

    // KURAL 1: BAŞLATMA KONTROLÜ
    if (a->basladi_mi == false) {
        a->motor_torku = 0;
    }

    // KURAL 2: FREN/GAZ ÇAKIŞMASI 
    if (a->fren_durumu == 1 && a->gaz_pedali > 5) {
        a->motor_torku = 0;
        printf("[UYARI] Fren basiliyken gaza basamazsin! Tork kesildi.\n");
    }

    // KURAL 7: AKILLI FAN KONTROLÜ (Grup C)
    if (a->motor_sicakligi > 80.0) {
        a->fan_durumu = true;
    } else {
        a->fan_durumu = false;
    }
}
