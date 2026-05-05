#include <stdio.h>
#include "vcu-define.h"

// Terminalden gelen "ID DEGER" formatýndaki veriyi okur
void Veri_Girisi_Isle(Arac* a) {
    int id, deger;
    printf("\nCAN Mesaji Girin (ID Deger): ");
    if (scanf("%d %d", &id, &deger) != 2) return;

    switch (id) {
    case 1:  a->basladi_mi = (bool)deger; break;
    case 16: a->gaz_pedali = deger; break;
    case 17: a->fren_durumu = deger; break;
    case 18: a->vites_durumu = deger; break;
    case 32: a->batarya_sicakligi = (float)deger; break;
    case 33: a->batarya_dolulugu = deger; break;
    case 48: a->motor_sicakligi = (float)deger; break;
    case 49: a->direksiyon_acisi = deger; break;
    case 64: a->drs_durumu = (bool)deger; break;
    default: printf("Bilinmeyen CAN ID!\n");
    }
}

// Aracýn durumunu ekrana tablo gibi basar
void Dashboard_Goster(Arac* a) {
    printf("\n--- ARAÇ GÖSTERGE PANELÝ ---\n");
    printf("Durum: %s | Vites: %d | Hýz: %d km/s\n", a->basladi_mi ? "READY" : "IDLE", a->vites_durumu, a->arac_surati);
    printf("Gaz: %%%d | Tork: %d Nm | Fren: %s\n", a->gaz_pedali, a->motor_torku, a->fren_durumu ? "BASILI" : "SERBEST");
    printf("Batarya: %%%d (%0.1f C) | Fan: %s\n", a->batarya_dolulugu, a->batarya_sicakligi, a->fan_durumu ? "ACIK" : "KAPALI");
    printf("DRS: %s (%s)\n", a->drs_durumu ? "ACIK" : "KAPALI", a->drs_musaade ? "UYGUN" : "YASAK");
    printf("----------------------------\n");
}


