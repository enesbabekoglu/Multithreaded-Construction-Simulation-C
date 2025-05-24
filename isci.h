/**
 * @file isci.h
 * @brief İşçi ve mühendis kaynak yönetimi başlık dosyası
 * @details Multi-process ve multi-thread ortamda kaynak yönetimi için semafor ve mutex
 *          tanımlamalarını içerir. Yarış koşullarını önlemek için senkronizasyon
 *          mekanizmaları sağlar.
 * 
 * @author İnşaat Simülasyon Sistemi
 * @date 2025
 * 
 * @note macOS uyumluluğu için named semaforlar kullanılır (sem_open)
 */

#ifndef ISCI_H
#define ISCI_H

#include <semaphore.h>
#include <pthread.h>

/**
 * @defgroup isci_semaforlari İşçi Semaforları
 * @brief Farklı işçi tiplerinin kaynak yönetimi için kullanılan semaforlar
 * @details Her işçi tipi için ayrı bir semafor tanımlanır. Bu semaforlar process'ler
 *          arası paylaşımlı olarak kullanılır.
 * @{
 */

/** @brief Elektrikçi işçileri için semafor (3 adet elektrikçi) */
extern sem_t *elektrikci_sem;

/** @brief Su tesisatı işçileri için semafor (2 adet su tesisatçısı) */
extern sem_t *su_sem;

/** @brief Doğalgaz tesisatı işçileri için semafor (2 adet doğalgaz tesisatçısı) */
extern sem_t *dogalgaz_sem;

/** @} */ // isci_semaforlari grubu sonu

/**
 * @defgroup muhendis_semaforlari Mühendis Semaforları
 * @brief Farklı mühendis tiplerinin kaynak yönetimi için kullanılan semaforlar
 * @details Her mühendis tipi için ayrı bir semafor tanımlanır. Mühendisler işçilere
 *          göre daha kısıtlı kaynaklardır.
 * @{
 */

/** @brief İnşaat mühendisleri için semafor (2 adet inşaat mühendisi) */
extern sem_t *insaat_muh_sem;

/** @brief Elektrik mühendisleri için semafor (1 adet elektrik mühendisi) */
extern sem_t *elektrik_muh_sem;

/** @brief Makine mühendisleri için semafor (1 adet makine mühendisi) */
extern sem_t *makine_muh_sem;

/** @} */ // muhendis_semaforlari grubu sonu

/**
 * @defgroup ortak_kaynaklar Ortak Kaynaklar
 * @brief Tüm process ve thread'ler tarafından paylaşılan ortak kaynaklar
 * @details Yarış koşulu örnekleri için kullanılan kritik kaynaklar
 * @{
 */

/** @brief Vinç kullanımı için semafor (1 adet vinç - yarış koşulu örneği) */
extern sem_t *vinc_sem;

/** @brief Asansör kullanımı için mutex (1 adet asansör - yarış koşulu örneği) */
extern pthread_mutex_t asansor_mutex;

/** @} */ // ortak_kaynaklar grubu sonu

/**
 * @brief Tüm semaforları ve mutex'leri başlatır
 * @details Named semaforları oluşturur ve başlangıç değerlerini ayarlar.
 *          macOS uyumluluğu için sem_open() kullanır.
 * 
 * @return void
 * 
 * @note Bu fonksiyon programın başında bir kez çağrılmalıdır
 * @warning Semafor isimleri benzersiz olmalıdır
 * 
 * @code
 * // Kullanım örneği:
 * isci_semaforlarini_baslat();
 * // ... program çalışır ...
 * isci_semaforlarini_sil();
 * @endcode
 */
void isci_semaforlarini_baslat();

/**
 * @brief Tüm semaforları temizler ve siler
 * @details Named semaforları kapatır (sem_close) ve sistemden kaldırır (sem_unlink).
 *          Mutex'i yok eder (pthread_mutex_destroy).
 * 
 * @return void
 * 
 * @note Bu fonksiyon programın sonunda çağrılmalıdır
 * @warning Temizleme yapılmazsa sistem kaynaklarında sızıntı olabilir
 * 
 * @see isci_semaforlarini_baslat()
 */
void isci_semaforlarini_sil();

#endif /* ISCI_H */
