#include <stdio.h>
#include "vcu-define.h"

// Güvenlik ve Performans kurallarını denetleyen ana fonksiyon.
void Motor_Kontrol_Merkezi(Arac *a) {
    
    if (a->acil_durum == true) return;

    // Önce Sürücü İsteğini Hesapla
    a->motor_torku = a->gaz_pedali;

    // KURAL 4: TORK SINIRI (Maks 100 Nm)
    if (a->motor_torku > 100) {
        a->motor_torku = 100;
    }

    // KURAL 5: LIMP MODE (Düşük Pil)
    if (a->batarya_dolulugu < 20) {
        a->motor_torku = a->motor_torku * 0.5; // Gücü yarıya düşür
    }

    // KURAL 6: GERİ VİTES KORUMASI
    if (a->arac_surati > 0 && a->vites_durumu == 2) {
        a->vites_durumu = 1; // Hata yapma, ileri viteste kal
        printf("[SISTEM] Hareket halindeyken geri vites engellendi!\n");
    }

    // KURAL 9 & 10: DRS GÜVENLİĞİ
    if (a->fren_durumu == 1 || a->direksiyon_acisi > 45 || a->direksiyon_acisi < -45) {
        a->drs_durumu = false; // Güvenlik için kanadı kapat/açtırma
    }
}