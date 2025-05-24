/**
 * Temel inşaat modülü
 * Yardımcı fonksiyonlar ve temel inşaat işlemleri
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "temel.h"

/**
 * Görsel ilerleme çubuğu gösteren fonksiyon
 * İnşaat aşamalarının ilerlemesini görselleştirir
 * 
 * @param mesaj Gösterilecek ilerleme mesajı
 */
void loading_bar(const char* mesaj) {
    printf("%s%s%s ", BLUE, mesaj, RESET);
    fflush(stdout);
    
    // İlerleme çubuğu animasyonu
    for (int i = 0; i < 20; i++) {
        printf("█");
        fflush(stdout);
        usleep(40000); // 40ms bekle (toplam 800ms)
    }
    
    printf(" ✅\n");
}

/**
 * Semafor bekleme ve mesaj gösterme fonksiyonu
 * Kaynak meşgulse bekleme mesajı gösterir
 * 
 * @param isci_tipi İşçi veya mühendis tipi
 * @param sem Beklenecek semafor
 * @param daire_str Daire bilgisi
 * @param emoji İşçi tipine uygun emoji
 */
void bekle_ve_mesaj(const char* isci_tipi, sem_t* sem, const char* daire_str, const char* emoji) {
    sem_wait(sem); // Semafor müsait olana kadar bekle
    printf("%s[%s] [%s] %s MÜSAİT, BAŞLANIYOR...\n%s", YELLOW, daire_str, isci_tipi, emoji, RESET);
}

/**
 * İşlem yapma ve semafor serbest bırakma fonksiyonu
 * İşlem tamamlandıktan sonra kaynağı serbest bırakır
 * 
 * @param isci_tipi İşçi veya mühendis tipi
 * @param daire_str Daire bilgisi
 * @param emoji İşçi tipine uygun emoji
 * @param sem Serbest bırakılacak semafor
 */
void yap_ve_mesaj(const char* isci_tipi, const char* daire_str, const char* emoji, sem_t* sem) {
    sleep(1); // İşlem süresi simülasyonu
    printf("%s[%s] [%s] %s TAMAMLANDI ✅\n%s", GREEN, daire_str, isci_tipi, emoji, RESET);
    sem_post(sem); // Semaforu serbest bırak
}

/**
 * Temel inşaat aşamalarını gerçekleştiren fonksiyon
 * Zemin hazırlığından su yalıtımına kadar tüm temel işlemlerini içerir
 * Her aşama görsel olarak gösterilir
 */
void temel_insaat() {
    printf("\n");
    
    // Temel inşaat aşamaları
    loading_bar("1. Zemin Etüdü başlıyor...");
    loading_bar("2. Hafriyat ve Kazı işlemleri yapılıyor...");
    loading_bar("3. Zemin Düzenleme ve Sıkıştırma tamamlanıyor...");
    loading_bar("4. Grobeton Dökümü yapılıyor...");
    loading_bar("5. Kalıp ve Donatı Hazırlığı yapılıyor...");
    loading_bar("6. Temel Altı Tesisatlar yerleştiriliyor...");
    loading_bar("7. Temel Beton Dökümü ve Sıkıştırma tamamlanıyor...");
    loading_bar("8. Kür ve Bakım Süreci uygulanıyor...");
    loading_bar("9. Kalıp Sökümü ve Yüzey Kontrolü...");
    loading_bar("10. Su Yalıtımı ve Drenaj Sistemi kuruluyor...");
    
    printf("\n%s✅ Temel inşaatı tamamlandı. Kat inşaatlarına geçilebilir.%s\n\n", GREEN, RESET);
}
