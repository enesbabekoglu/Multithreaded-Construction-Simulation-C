/**
 * İŞLETİM SİSTEMLERİ DÖNEM ÖDEVİ - 2024-2025 BAHAR DÖNEMİ
 * 
 * Konu: Çok Katlı Bir Apartmanın İnşası Üzerinden Process, Thread ve 
 * Senkronizasyon Kavramlarının Modellenmesi
 * 
 * Bu program 10 katlı, her katta 4 daire bulunan bir apartmanın inşa sürecini
 * simüle eder. İşletim sistemlerindeki process, thread ve senkronizasyon
 * kavramlarını modellemek için kullanılır.
 */

#include <stdio.h>
#include "temel.h"
#include "kat.h"
#include "isci.h"
#include "final.h"

#define PURPLE "\033[1;35m"
#define RESET  "\033[0m"

/**
 * Ana fonksiyon - Apartman inşaat sürecini başlatır ve yönetir
 * 
 * İnşaat süreci şu sırayla gerçekleşir:
 * 1. İşçi semaforlarının başlatılması (kaynak yönetimi için)
 * 2. Temel atma işlemleri
 * 3. Kat inşaatları (her kat bir process, her daire bir thread)
 * 4. Çatı inşaatı
 * 5. Dış cephe işlemleri
 * 6. Semaforların temizlenmesi
 */
int main() {
    printf("%s🔧 İnşaat Başlıyor...%s\n\n", PURPLE, RESET);
    
    // Semaforları başlat - işçi ve mühendis kaynaklarını yönetmek için
    isci_semaforlarini_baslat();

    // Temel atma işlemleri - tüm katlar için önkoşul
    temel_insaat();
    
    // Her kat için ayrı process oluştur ve sırayla inşa et
    insaat_katlarini_baslat();

    // Çatı inşaatı - tüm katlar bittikten sonra
    printf("%s🏗️  Çatı inşa ediliyor...%s\n", PURPLE, RESET);
    cati_insa_et();

    // Dış cephe işlemleri - son aşama
    printf("%s🎨 Dış cephe işlemleri başlatılıyor...%s\n", PURPLE, RESET);
    dis_cephe_islemleri();

    // Semaforları temizle - kaynak yönetimi temizliği
    isci_semaforlarini_sil();
    
    printf("%s🎉 Apartman inşaatı TAMAMLANDI.%s\n", PURPLE, RESET);
    return 0;
}
