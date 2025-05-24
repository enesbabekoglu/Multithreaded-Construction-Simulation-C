#include <stdio.h>
#include <unistd.h>
#include "temel.h"
#include "final.h"

/**
 * Çatı inşa etme fonksiyonu
 * Apartmanın çatı kısmının inşasını simüle eder
 */
void cati_insa_et() {
    // Çatı inşaatı için loading bar kullanarak adımları göster
    loading_bar("Çatı iskelesi kuruluyor...");
    loading_bar("Çatı kirişleri yerleştiriliyor...");
    loading_bar("Çatı kaplaması yapılıyor...");
    loading_bar("Yağmur oluğu montajı yapılıyor...");
    loading_bar("Çatı izolasyonu tamamlanıyor...");
    
    printf("%s✅ Çatı inşaatı başarıyla tamamlandı!%s\n\n", GREEN, RESET);
}

/**
 * Dış cephe işlemleri fonksiyonu
 * Apartmanın dış cephe işlemlerini simüle eder
 */
void dis_cephe_islemleri() {
    // Dış cephe işlemleri için loading bar kullanarak adımları göster
    loading_bar("Dış cephe iskelesi kuruluyor...");
    loading_bar("Mantolama işlemi yapılıyor...");
    loading_bar("Dış cephe sıvası atılıyor...");
    loading_bar("Dış cephe boyası yapılıyor...");
    loading_bar("Pencere ve kapı montajı tamamlanıyor...");
    loading_bar("Balkon korkulukları takılıyor...");
    
    printf("%s✅ Dış cephe işlemleri başarıyla tamamlandı!%s\n\n", GREEN, RESET);
}
