
## 🏎️ Aracın Sinir Sistemi: CAN Bus Araştırması

### 🎯 Görevin Amacı
Bir Formula Student aracında onlarca sensör, motor sürücü ve kontrolcü bulunur. Eğer her birim için ayrı kablo çekseydik, araç bakır yığınına döner ve ağırlığı iki katına çıkardı. İşte burada modern otomotivin mucizesi olan **CAN Bus** devreye giriyor.

Bu görevde kod yazmayacaksın. Bir **Gömülü Sistem Mühendisi** gibi teknik doküman okuyacak, analiz edecek ve öğrendiklerini profesyonel bir rapor haline getireceksiniz.

> **Motto:** "Arabanın tekerleği dönsün istiyorsan, önce beyninin nasıl konuştuğunu öğrenmelisin."

---

## 📚 Araştırma Müfredatı
Raporunda aşağıdaki başlıkların teknik ve şematik cevapları yer almalıdır.

### 1. Temeller ve Fiziksel Katman (Hardware)
* **CAN Bus Nedir?** Tarihçesi ve Bosch'un bu protokolü geliştirme nedenleri.
* **Diferansiyel Sinyal (Differential Signaling):** `CAN_H` ve `CAN_L` nedir?
* **Twisted Pair (Bükümlü Tel):** Neden tek kablo değil de birbirine dolanmış iki kablo kullanıyoruz? Bu yapı "Gürültüye" (Noise) karşı nasıl bir koruma kalkanı oluşturur?
* **Sonlandırma Direnci (Termination Resistor):**
    * Hattın iki ucuna neden **120 Ohm** direnç takılır?
    * Takmazsak ne olur? (**Yansıma/Reflection** kavramını açıkla).

---

### 2. Protokol ve Veri Yapısı (Data Link Layer)
Bir CAN mesaj paketinin (**Frame**) anatomisini incele:

* **SOF (Start of Frame):** Mesajın başlangıcı.
* **Arbitration Field (ID):** Standart (11-bit) ile Extended (29-bit) arasındaki fark.
* **Control Field (DLC):** Bir pakette en fazla kaç byte veri taşınabilir?
* **Data Field:** Verinin asıl yükü.
* **CRC Field:** Hata kontrol mekanizması.
* **ACK Field:** Mesajın yerine ulaştığını nasıl teyit ederiz?

---

### 3. Trafik Yönetimi (Arbitration) 🚦
CAN Bus'ta bir "Master" (Merkezi Yönetici) yoktur; bu bir **Multi-Master** sistemidir.

* **Arbitrasyon (Önceliklendirme):** İki modül (Örn: Motor ve Klima) aynı anda konuşmaya başlarsa hat nasıl karar verir?
* **ID Önceliği:** Düşük ID (Örn: `0x100`) mi yoksa yüksek ID (Örn: `0x500`) mi daha baskındır? Neden?
* **Senaryo:** Acil Fren Mesajı ile Klima Mesajı çakışırsa yarışı kim kazanır?

---

### 4. Formula Student ve Pratik Uygulama
* **Neden Ethernet veya USB değil de CAN Bus?** (Hız, güvenlik ve mesafe kıyaslaması).
* **DBC Dosyası Nedir?** Bir CAN veritabanı dosyası, yazılım ekibi için neden **"Kutsal Kitap"** niteliğindedir?

---

## 📝 Teslim Formatı

### İstenen Dosya Yapısı
* **Başlık:** `Task-03-[Ad]-[Soyad]`
* **Görsellik:** Anlattığınız konuları destekleyen şemalar ekleyin (Referans vererek veya kendiniz çizerek).
* **Kaynaklar:** En altta yararlandığınız teknik kaynakları (Vector, TI, Kvaser vb.) listeleyin.

### 📤 Teslim Adımları (Git Workflow)

1.  **Klasör:** `Submissions/Task-03-[Ad]-[Soyad]/` dizinizi oluşturun.
2.  **Dosya:** Raporunuzu bu klasörün içine `README.md` adıyla kaydedin.
3.  **Commit:** `docs: Task-03 CAN Bus arastirmasi tamamlandi`
4.  **Pull Request:** Ana repoya PR açın.

---

## 💡 İpuçları ve Kaynaklar
Araştırmaya başlarken şu anahtar kelimeler sana kapı açacaktır:
* Bosch CAN Specification 2.0
* Vector CAN Protocol Tutorial
* Texas Instruments CAN Physical Layer (SLLA337)
* Kvaser CAN Bus Explained