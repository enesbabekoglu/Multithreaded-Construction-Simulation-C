# Multithreaded-Construction-Simulation-C
C diliyle yazılmış, apartman inşaatı üzerinden process, thread ve senkronizasyon kavramlarını simüle eden çok süreçli işletim sistemi projesi.

# Apartman İnşaat Simülasyonu - İşletim Sistemleri Dönem Ödevi

## Hazırlayanlar
- **Enes Babekoğlu** - 20360859113
- **Hakan Celasun** - 21360859215

## Proje Hakkında

Bu proje, 10 katlı ve her katta 4 daire bulunan bir apartmanın inşa sürecini simüle ederek işletim sistemlerindeki **process**, **thread** ve **senkronizasyon** kavramlarını modellemektedir.

### Proje Özellikleri

- **10 Kat**: Her kat ayrı bir process olarak modellenir
- **40 Daire**: Her daire bir thread olarak çalışır (kat başına 4 thread)
- **Senkronizasyon**: Semaforlar kullanılarak kaynak yönetimi ve yarış koşullarının önlenmesi
- **Sıralı İşlemler**: Katlar sırayla inşa edilir (process senkronizasyonu)
- **Paralel İşlemler**: Aynı kattaki daireler eş zamanlı inşa edilebilir (thread paralelizmi)
- **macOS Uyumluluğu**: Named semaforlar kullanılarak macOS desteği sağlanmıştır

## Kurulum ve Gereksinimler

### Sistem Gereksinimleri
- **İşletim Sistemi**: macOS, Linux veya Unix benzeri sistem
- **Derleyici**: GCC veya Clang (C11 desteği)
- **Kütüphaneler**: 
  - POSIX thread kütüphanesi (pthread)
  - POSIX semafor desteği
  - ANSI terminal desteği (renkli çıktı için)

### Kurulum Adımları

1. **Projeyi İndirin**
   ```bash
   git clone <proje-url>
   cd "Insaat 2"
   ```

2. **Gerekli Araçları Kontrol Edin**
   ```bash
   # GCC/Clang kontrolü
   gcc --version
   # veya
   clang --version
   ```

3. **Projeyi Derleyin**
   ```bash
   make
   ```

4. **Programı Çalıştırın**
   ```bash
   make run
   # veya doğrudan
   ./apartman_insaat
   ```

### Makefile Komutları

- `make` - Projeyi derler
- `make run` - Derler ve çalıştırır
- `make clean` - Derleme dosyalarını temizler
- `make rebuild` - Temizler ve yeniden derler

## Sistem Mimarisi

### Process Yapısı
- Her kat için `fork()` ile yeni process oluşturulur
- Katlar sırayla inşa edilir (`waitpid()` ile senkronizasyon)
- Process ID'leri ekranda gösterilir

### Thread Yapısı
- Her kattaki 4 daire için `pthread_create()` ile thread oluşturulur
- Thread'ler paralel çalışabilir
- `pthread_join()` ile thread'lerin tamamlanması beklenir

### Senkronizasyon Mekanizmaları

#### Named Semaforlar (macOS Uyumlu)
1. **İşçi Semaforları**:
   - Elektrikçi (3 adet) - `/elektrikci_sem`
   - Su tesisatçısı (2 adet) - `/su_sem`
   - Doğalgazcı (2 adet) - `/dogalgaz_sem`

2. **Mühendis Semaforları**:
   - İnşaat mühendisi (2 adet) - `/insaat_muh_sem`
   - Elektrik mühendisi (1 adet) - `/elektrik_muh_sem`
   - Makine mühendisi (1 adet) - `/makine_muh_sem`

3. **Ortak Kaynaklar**:
   - Vinç (1 adet) - `/vinc_sem`
   - Asansör (1 adet) - `pthread_mutex`

### İnşaat Aşamaları

1. **Temel Atma**: 
   - Hafriyat işlemleri
   - Kalıp hazırlama
   - Demir döşeme
   - Beton dökme

2. **Kat İnşaatları**: Sırayla her kat için:
   - Yapısal kontrol (inşaat mühendisi)
   - Daire inşaatları (paralel thread'ler)

3. **Çatı İnşaatı**: Tüm katlar bittikten sonra

4. **Dış Cephe İşlemleri**: Son aşama

### Daire İnşaat Süreci

Her daire thread'i şu işlemleri sırayla gerçekleştirir:

1. **Duvar Örme** (paralel - senkronizasyon gerektirmez)
2. **Elektrik Mühendisi Kontrolü** (semafor ile sınırlı)
3. **Elektrik Tesisatı** (semafor ile sınırlı)
4. **Su Tesisatı** (semafor ile sınırlı)
5. **Makine Mühendisi Kontrolü** (semafor ile sınırlı)
6. **Doğalgaz Tesisatı** (semafor ile sınırlı)
7. **İç Dekorasyon** (paralel - senkronizasyon gerektirmez)

## Yarış Koşulu (Race Condition) Örnekleri

1. **Vinç Kullanımı**: 
   - Problem: Tüm daireler aynı vinci kullanmak isteyebilir
   - Çözüm: Named semafor ile korunur (`/vinc_sem`)

2. **Asansör Kullanımı**: 
   - Problem: Birden fazla işçi aynı anda asansörü kullanmak isteyebilir
   - Çözüm: Mutex ile korunarak aynı anda tek kullanıcı

3. **İşçi Kaynakları**: 
   - Problem: Sınırlı sayıda işçi, çok sayıda daire
   - Çözüm: Semafor ile kaynak havuzu yönetimi

## Dosya Yapısı

```
Insaat 2/
├── main.c          # Ana program dosyası
├── temel.c         # Temel atma işlemleri
├── temel.h         # Temel fonksiyon prototipleri ve renk tanımları
├── kat.c           # Kat inşaat process yönetimi
├── kat.h           # Kat fonksiyon prototipleri
├── daire.c         # Daire inşaat thread yönetimi
├── daire.h         # Daire fonksiyon prototipleri
├── isci.c          # Semafor yönetimi ve kaynak kontrolü
├── isci.h          # Semafor tanımlamaları
├── final.c         # Çatı ve dış cephe işlemleri
├── final.h         # Final işlem prototipleri
├── Makefile        # Derleme otomasyonu
└── README.md       # Bu dosya
```

## Çıktı Formatı

Program, renkli ve emoji destekli çıktılar üretir:
- 🏗️ İnşaat başlangıcı
- 🧱 Yapısal işlemler
- ⚡ Elektrik işlemleri
- 💧 Su tesisatı
- 🔥 Doğalgaz tesisatı
- 🎨 Dekorasyon işlemleri
- ✅ Tamamlanan işlemler
- ⏳ Bekleme durumları

## Teknik Detaylar

### Deadlock Önleme
- Tüm kaynaklar aynı sırada alınır
- Timeout mekanizması yoktur (basitlik için)
- Named semaforlar process'ler arası paylaşım sağlar

### Performans
- Her işlem simülasyon için `sleep()` kullanır
- Gerçek paralelizm thread'ler arasında görülür
- Process'ler sıralı çalışır (kat sıralaması için)

### Hata Yönetimi
- Fork hataları kontrol edilir
- Semafor oluşturma hataları kontrol edilir
- Thread oluşturma hataları kontrol edilir

## Notlar

- macOS'ta `sem_init()` desteklenmediği için named semaforlar kullanılmıştır
- Process ID'leri ve thread bilgileri çıktıda gösterilir
- Kaynak bekleme durumları sarı/kırmızı renkte gösterilir
- Tamamlanan işlemler yeşil renkte gösterilir
- Program sonunda tüm semaforlar temizlenir

## Lisans

Bu proje eğitim amaçlı hazırlanmıştır.

---
*İşletim Sistemleri Dersi - 2025*
