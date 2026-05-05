🏎️ Görev 00: VCU Mimarisi, 10 Kural ve Protokol Tasarımı
📚 Gerekli Konseptler
Modular C: .c ve .h ayrımı.

Pointer & Struct: Veri paketleme ve adrese dayalı erişim.

State Machine Logic: Birbirini etkileyen durumların yönetimi.

Infinite Loop: Gömülü sistemlerin sonsuz çalışma döngüsü.

🎯 Amaç
Bu görevin amacı, Spaghetti Code yazmadan, karmaşık bir karar mekanizmasını yönetebilecek Modüler Bir Mimari kurmaktır. Sizden, "Sanal VCU" sistemini simüle eden; 10 farklı senaryoyu hatasız işleyen ve tertemiz bir Main dosyasına sahip olan bir proje bekliyoruz.

💡 İnsiyatif Alanı ve Protokol Tasarımı (ÖNEMLİ)
Bu görevde size hazır bir "CAN ID Listesi" vermiyoruz. Mühendislik, belirsizlik içinde sistem kurmaktır. Aracın iletişim dilini (Protokolü) SİZ tasarlayacaksınız.

Adresleme (CAN IDs): Hangi verinin hangi Hex adresten geleceğine karar verin.

Mantıklı Olmalı: Rastgele sayılar yerine gruplama yapın. (Örn: Motor verileri 0x100 serisinde, Batarya 0x200 serisinde gibi.)

İsimlendirme: Fonksiyon ve değişken isimleri size aittir.

Anlaşılır Olmalı: fonksiyon1() yerine Calculate_Torque_Limit() gibi ne iş yaptığı belli olan isimler kullanın.

Dokümantasyon Şartı: Tasarladığınız bu ID'leri ve kuralları README.md dosyasında bizimle paylaşmak zorundasınız. (Yoksa kodunuzu test edemeyiz!)

⚙️ Çalışma Mantığı (Sonsuz Döngü)
Programınız başladığında bir kez kurulum yapacak, ardından sonsuz bir döngüye (while(1)) girecektir. Bu döngüde sürekli olarak kullanıcıdan (Terminalden) veri bekleyecek, veriyi işleyip kuralları uygulayacak ve sonucu raporlayacaktır.

Örnek Main Akışı (İstenen):

C

int main() {
    Vehicle arac;
    VCU_Init(&arac); // Başlangıç ayarları (Her şey 0)

    printf("--- SANAL VCU BASLATILDI ---\n");

    while(1) {
        // 1. ADIM: Sensör verisi bekle (Kullanıcıdan al)
        // Örn: scanf ile ID ve DATA iste
        Input_Handler(&arac); 

        // 2. ADIM: Tüm güvenlik ve kontrol kurallarını işlet
        // 10 maddelik senaryo burada kontrol edilecek
        Process_Safety_Logic(&arac);
        Process_Motor_Logic(&arac);
        Process_BMS_Logic(&arac); // Fonksiyon isimleri temsilidir, değiştirebilirsiniz.

        // 3. ADIM: Son durumu ekrana bas
        Print_System_Status(&arac);
    }
    return 0;
}
🚦 Senaryo ve Tepki Matrisi (10 Zorunlu Kural)
Tasarladığınız protokol ne olursa olsun, VCU yazılımınızın aşağıdaki 10 duruma doğru tepkiyi vermesi zorunludur.

[Grup A] Güvenlik Kritik (Safety Critical)
Start Button: Araç açıldığında "BOŞTA" (Idle) modundadır. Kullanıcı Start komutunu (Sizin belirlediğiniz ID ile) göndermeden gaz pedalı çalışmamalıdır.

Fren ve Gaz Çakışması (APPS Plausibility): Fren basılıyken (brake > 0) Gaz pedalı %5'ten fazlaysa -> Tork derhal 0 yapılmalı ve Hata mesajı basılmalıdır.

BMS Acil Durum: Batarya sıcaklığı 60°C'yi geçerse -> Sistem "SHUTDOWN" moduna girmeli, araç tamamen durmalı ve tekrar başlatılana kadar tepki vermemelidir.

[Grup B] Motor ve Performans
Tork Sınırı (Saturation): İstenen tork 100 Nm'yi geçerse -> Değer 100 Nm'ye sabitlenmelidir.

Düşük Pil (Limp Mode): Batarya şarjı (SoC) %20'nin altına düşerse -> Maksimum tork otomatik olarak %50 ile sınırlandırılmalıdır.

Geri Vites Koruması: Araç ileri giderken (Hız > 0) Geri Vites komutu gelirse -> Komut reddedilmeli, vites değişmemelidir.

[Grup C] Soğutma ve Enerji
Fan Kontrolü: Motor sıcaklığı 80°C'yi geçerse -> Soğutma Fanı (fan_status) 1 (AÇIK) yapılmalı, altına düşerse 0 (KAPALI) olmalıdır.

Rejenerasyon İptali: Batarya tamamen doluysa (SoC > %95) -> Rejeneratif frenleme (Negatif Tork) devre dışı bırakılmalıdır.

[Grup D] Aero ve Gövde
DRS ve Fren: Fren basılıyken DRS (Kanat) açma komutu gelirse -> DRS açılmamalıdır.

DRS ve Direksiyon: Direksiyon açısı kritik seviyeden (örn: 45°) fazlaysa -> DRS otomatik olarak kapanmalıdır (Yol tutuş kaybını önlemek için).

🛠️ Dosya ve Kod Mimarisi
1. Modüler Yapı (Zorunlu)
Projeniz tek dosya olamaz. Aşağıdaki gibi parçalanmalıdır (Dosya isimlerini işlevlerine uygun olarak siz belirleyebilirsiniz):

main.c: Döngü yöneticisi.

vcu_defines.h: Vehicle struct tanımı ve sabitler.

input_output.c / .h: scanf ve printf işlemleri.

logic_powertrain.c / .h: Motor ve vites kuralları.

logic_safety.c / .h: Güvenlik ve BMS kuralları.

2. Clean Code & Dokümantasyon
main.c içinde mantıksal işlem (if, while, matematik) yasaktır.

Her fonksiyonun üzerinde ne iş yaptığını anlatan yorum bloğu olmak zorundadır.

📄 Proje Dokümantasyonu (README.md - ÇOK KRİTİK)
Tasarımı size bıraktığımız için, kodunuzu nasıl kullanacağımızı anlatan bir kılavuz yazmanız şarttır. README.md dosyasında şunlar olmalıdır:

Başlık: Proje İsmi.

Protokol Tablosu (Sizin Tasarımınız):

Örn: 0x100 -> Gaz Pedalı (0-100)

Örn: 0xA01 -> Start Butonu (0-1)

Özellikler: 10 kuralın listesi.

Mimari: Dosya yapısının şeması.

Nasıl Test Edilir?: "Önce 0xA01 ile aracı başlatın, sonra 0x100 ile gaz verin..." gibi kısa bir rehber.

📤 Teslim Formatı
Klasör: Team-Submissions/TeamTask-00-ProjectCortex-[GrupIsmi]

İçerik: Kaynak kodlar (.c, .h) ve README.md.

Kanıt: Terminal ekranında 10 kuralın da çalıştığını (Limp mode'a girmesi, Fan açması, DRS kapatması vb.) gösteren kesintisiz bir ekran kaydı (Video/GIF).

Commit Mesajı: feat: vcu architecture and protocol design
