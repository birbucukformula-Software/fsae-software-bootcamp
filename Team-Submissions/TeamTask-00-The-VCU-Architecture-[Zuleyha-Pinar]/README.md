# 🏎️ Project Cortex: Yerli VCU Yazılım Simülasyonu

Bu proje, bir elektrikli yarış aracının Araç Kontrol Ünitesi (VCU) mimarisini simüle eden modüler bir C yazılımıdır. Sistem, terminal üzerinden gelen sanal CAN mesajlarını işleyerek aracın tork, güvenlik, soğutma ve aerodinamik kararlılığını yönetir.

## 📡 /CAN PROTOKOL TASARIMI/
Sanal VCU, terminalden gelen verileri aşağıdaki ID'lere göre işler. Terminale veri girerken önce **ID**, sonra **Değer** (Örn: `16 50`) yazılmalıdır.

| ID (Hex) | Terminal Giriş (Dec) | Değişken İsmi | Açıklama |
| :--- | :--- | :--- | :--- |
| **0x01** | 1 | `basladi_mi` | 0: IDLE, 1: READY (Start Butonu) |
| **0x10** | 16 | `gaz_pedali` | %0 - %100 arası gaz seviyesi |
| **0x11** | 17 | `fren_durumu` | 0: Serbest, 1: Basılı |
| **0x12** | 18 | `vites_durumu` | 0: Boş (N), 1: İleri (D), 2: Geri (R) |
| **0x20** | 32 | `batarya_sicakligi` | Batarya ısısı (°C) |
| **0x21** | 33 | `battery_dolulugu` | Şarj seviyesi (SoC %) |
| **0x30** | 48 | `motor_sicakligi` | Motor ısısı (°C) |
| **0x31** | 49 | `direksiyon_acis` | -90 ile +90 arası direksiyon açısı |
| **0x40** | 64 | `drs_durumu` | 0: Kapalı, 1: Açık (Sürücü İsteği) |

---

## ⚖️ /MANTIK KURALLARI (10 Zorunlu Kural)/

### -> Grup A: Güvenlik Kritik (Safety Critical)
1. **Başlatma Kontrolü:** `basladi_mi` 1 olmadan gaz pedalı tork üretmez.
2. **Fren/Gaz Çakışması:** `fren_durumu` 1 iken `gaz_pedali` > %5 ise tork 0 Nm yapılır.
3. **BMS Acil Durum:** `batarya_sicakligi` > 60°C ise `acil_durum` aktif olur ve araç kilitlenir.

### -> Grup B: Motor ve Performans
4. **Tork Sınırı (Saturation):** `motor_torku` yazılımsal olarak 100 Nm ile sınırlandırılır.
5. **Limp Mode (Düşük Pil):** `battery_dolulugu` < %20 ise maks tork %50'ye düşürülür.
6. **Geri Vites Koruması:** `arac_sürati` > 0 iken vites R (2) konumuna geçemez.

### -> Grup C: Soğutma ve Enerji
7. **Akıllı Fan:** `motor_sicakligi` > 80°C ise `fan_durumu` 1 olur, altına düşünce 0 olur.
8. **Rejen Engeli:** `battery_dolulugu` > %95 ise negatif tork (şarj) engellenir.

### -> Grup D: Aero ve Gövde
9. **DRS ve Fren:** `fren_durumu` 1 iken DRS açılamaz / otomatik kapanır.
10. **DRS ve Viraj:** `direksiyon_acis` > 45° ise DRS otomatik olarak kapatılır.

---

## 🛠️ /PROJE MİMARİSİ/
Proje modülerliği sağlamak adına şu dosyalara bölünmüştür:
- `vcu_tanimlar.h`: `Arac` struct yapısı ve tüm değişken tanımları.
- `logic_safety.c`: Güvenlik ve Soğutma kuralları yönetimi.
- `logic_motor.c`: Tork, Vites ve Aero kuralları yönetimi.
- `input_output.c`: Terminal haberleşme ve görselleştirme.
- `main.c`: Sistemin beyni ve sonsuz döngü yöneticisi.

---

## 🚀 Nasıl Test Edilir?
1. Programı derleyip çalıştırın.
2. Önce aracı başlatın: `1 1` yazıp Enter'a basın.
3. Gaz vererek torku kontrol edin: `16 50`
4. Güvenlik protokolünü tetikleyin: `32 65` (Sistem kilitlenmelidir!)