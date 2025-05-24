/**
 * @file daire.h
 * @brief Daire inşaat işlemleri başlık dosyası
 * @details Her dairenin inşaat sürecini yöneten fonksiyonların prototiplerini içerir.
 *          Multi-thread yapıda her daire ayrı bir thread olarak çalışır.
 * 
 * @author İnşaat Simülasyon Sistemi
 * @date 2025
 */

#ifndef DAIRE_H
#define DAIRE_H

/**
 * @brief Daire inşaat görevlerini gerçekleştirir
 * @details Her daire için sırasıyla elektrik, su ve doğalgaz tesisatı işlemlerini yürütür.
 *          İşçi ve mühendis kaynaklarını semaforlar ile yönetir.
 *          Thread-safe bir şekilde çalışır ve yarış koşullarını önler.
 * 
 * @param daire_no Daire numarası (1-4 arası)
 * @return void
 * 
 * @note Bu fonksiyon pthread_create() ile thread olarak çalıştırılır
 * @warning Semafor işlemleri sırasında deadlock oluşmaması için dikkatli olunmalıdır
 */
void daire_gorevleri(int daire_no);

#endif /* DAIRE_H */