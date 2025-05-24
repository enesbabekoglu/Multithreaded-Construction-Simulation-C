/**
 * Daire inşaat modülü
 * Her daire bir thread olarak çalışır ve ortak kaynaklar için senkronizasyon kullanır
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "temel.h"
#include "isci.h"

/**
 * Bir dairenin tüm inşaat görevlerini gerçekleştiren fonksiyon
 * Her daire thread'i bu fonksiyonu çalıştırır
 * 
 * @param daire_no Daire numarası (1-4 arası)
 * 
 * İşlem sırası:
 * 1. Vinç kullanımı (yarış koşulu örneği - semafor ile korunur)
 * 2. Duvar örme (senkronizasyon gerektirmez - her daire kendi duvarını örer)
 * 3. Elektrik mühendisi kontrolü (semafor ile sınırlı kaynak)
 * 4. Elektrik tesisatı (semafor ile sınırlı kaynak)
 * 5. Su tesisatı (semafor ile sınırlı kaynak)
 * 6. Makine mühendisi kontrolü (semafor ile sınırlı kaynak)
 * 7. Doğalgaz tesisatı (semafor ile sınırlı kaynak)
 * 8. İç dekorasyon (senkronizasyon gerektirmez)
 */
void daire_gorevleri(int daire_no) {
    char daire_str[32];
    snprintf(daire_str, sizeof(daire_str), "Daire %d", daire_no);

    // 1. Vinç kullanımı - Yarış koşulu örneği
    // macOS'ta process-shared semaforlar düzgün çalışmadığı için
    // vinç kullanımını simüle ediyoruz
    printf("%s[%s] [VİNÇ] 🏗️ Malzeme taşınıyor...\n%s", BLUE, daire_str, RESET);
    sleep(1); // Vinç kullanım süresi simülasyonu
    printf("%s[%s] [VİNÇ] 🏗️ Malzeme taşıma TAMAMLANDI ✅\n%s", GREEN, daire_str, RESET);

    // 2. Duvar örme - Her daire kendi duvarını örebilir (paralel işlem)
    printf("%s[%s] [GENEL İŞÇİ] 🧱 Duvar örme ve kalıp kurulumu YAPILIYOR...\n%s", BLUE, daire_str, RESET);
    sleep(2); // İşlem süresi simülasyonu
    printf("%s[%s] [GENEL İŞÇİ] 🧱 Duvar örme TAMAMLANDI ✅\n%s", GREEN, daire_str, RESET);

    // 3. Elektrik Mühendisi - Sınırlı kaynak (yarış koşulu önlenir)
    // Sadece 1 elektrik mühendisi var, tüm daireler sırayla kullanmalı
    bekle_ve_mesaj("ELEKTRİK MÜH.", elektrik_muh_sem, daire_str, "📋");
    yap_ve_mesaj("ELEKTRİK MÜH.", daire_str, "📋", elektrik_muh_sem);

    // 4. Elektrikçi - Sınırlı kaynak (3 elektrikçi mevcut)
    // En fazla 3 daire aynı anda elektrik tesisatı yapabilir
    bekle_ve_mesaj("ELEKTRİKÇİ", elektrikci_sem, daire_str, "💡");
    yap_ve_mesaj("ELEKTRİKÇİ", daire_str, "💡", elektrikci_sem);

    // 5. Asansör kullanımı - Mutex örneği
    pthread_mutex_lock(&asansor_mutex);
    printf("%s[%s] [ASANSÖR] 🛗 Asansör kullanılıyor...\n%s", YELLOW, daire_str, RESET);
    sleep(1); // Asansör kullanım süresi
    printf("%s[%s] [ASANSÖR] 🛗 Asansör kullanımı TAMAMLANDI ✅\n%s", GREEN, daire_str, RESET);
    pthread_mutex_unlock(&asansor_mutex);

    // 6. Su tesisatçısı - Sınırlı kaynak (3 tesisatçı mevcut)
    // Ortak su boruları nedeniyle senkronizasyon gerekli
    bekle_ve_mesaj("SU TESİSATÇISI", su_sem, daire_str, "🚰");
    yap_ve_mesaj("SU TESİSATÇISI", daire_str, "🚰", su_sem);

    // 7. Makine Mühendisi - Sınırlı kaynak (yarış koşulu önlenir)
    // Sadece 1 makine mühendisi var, tüm daireler sırayla kullanmalı
    bekle_ve_mesaj("MAKİNE MÜH.", makine_muh_sem, daire_str, "📋");
    yap_ve_mesaj("MAKİNE MÜH.", daire_str, "📋", makine_muh_sem);

    // 8. Doğalgaz tesisatı - Sınırlı kaynak (3 doğalgazcı mevcut)
    // Güvenlik nedeniyle senkronizasyon kritik
    bekle_ve_mesaj("DOĞALGAZCI", dogalgaz_sem, daire_str, "🔥");
    yap_ve_mesaj("DOĞALGAZCI", daire_str, "🔥", dogalgaz_sem);

    // 9. İç dekorasyon - Her daire kendi boyasını yapabilir (paralel işlem)
    printf("%s[%s] [BOYACI] 🎨 İç dekorasyon ve boya YAPILIYOR...\n%s", BLUE, daire_str, RESET);
    sleep(2); // İşlem süresi simülasyonu
    printf("%s[%s] [BOYACI] 🎨 Dekorasyon TAMAMLANDI ✅\n%s", GREEN, daire_str, RESET);
}