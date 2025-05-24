/**
 * @file temel.h
 * @brief Temel inşaat ve yardımcı fonksiyonlar başlık dosyası
 * @details Apartman temel inşaatı, görsel çıktı fonksiyonları ve renk tanımlamalarını içerir.
 *          Ayrıca semafor işlemleri için yardımcı fonksiyonlar sağlar.
 * 
 * @author İnşaat Simülasyon Sistemi
 * @date 2025
 */

#ifndef TEMEL_H
#define TEMEL_H

#include <semaphore.h>

/**
 * @brief Apartman temel inşaatını gerçekleştirir
 * @details Hafriyat, kalıp, demir ve beton işlemlerini sırasıyla gerçekleştirir.
 *          Her aşama için görsel ilerleme çubuğu gösterir.
 * 
 * @return void
 * 
 * @note Bu fonksiyon main() tarafından ilk olarak çağrılır
 * @see loading_bar() - İlerleme çubuğu gösterimi için
 */
void temel_insaat();

/**
 * @brief Animasyonlu ilerleme çubuğu gösterir
 * @details Verilen mesaj ile birlikte yüzdelik ilerleme çubuğu animasyonu gösterir.
 *          Terminal ekranını temizler ve görsel bir deneyim sağlar.
 * 
 * @param mesaj Gösterilecek işlem mesajı
 * @return void
 * 
 * @note ANSI escape kodları kullanır
 */
void loading_bar(const char* mesaj);

/**
 * @defgroup renk_tanimlari Renk Tanımlamaları
 * @brief Terminal çıktısı için ANSI renk kodları
 * @details Renkli ve görsel çıktı için kullanılan ANSI escape kodları.
 *          Tüm modern terminal emülatörleri tarafından desteklenir.
 * @{
 */

/** @brief Kırmızı renk kodu - Hata ve uyarılar için */
#define RED     "\033[0;31m"

/** @brief Yeşil renk kodu - Başarılı işlemler için */
#define GREEN   "\033[0;32m"

/** @brief Sarı renk kodu - Bekleme durumları için */
#define YELLOW  "\033[0;33m"

/** @brief Mavi renk kodu - Bilgi mesajları için */
#define BLUE    "\033[0;34m"

/** @brief Mor renk kodu - Özel durumlar için */
#define PURPLE  "\033[0;35m"

/** @brief Cyan renk kodu - Vurgulama için */
#define CYAN    "\033[0;36m"

/** @brief Renk sıfırlama kodu - Normal renge dönüş */
#define RESET   "\033[0m"

/** @brief Kalın yazı kodu - Önemli metinler için */
#define BOLD    "\033[1m"

/** @} */ // renk_tanimlari grubu sonu

/**
 * @defgroup semafor_yardimci Semafor Yardımcı Fonksiyonları
 * @brief Semafor işlemleri için yardımcı fonksiyonlar
 * @details Tekrarlayan semafor bekleme ve bırakma işlemlerini kolaylaştıran
 *          ve görsel log mesajları üreten yardımcı fonksiyonlar.
 * @{
 */

/**
 * @brief Semafor bekler ve bekleme mesajı gösterir
 * @details Belirtilen semafor üzerinde sem_wait() yapar ve renkli bekleme mesajı gösterir.
 *          Yarış koşullarını görselleştirmek için kullanılır.
 * 
 * @param rol İşçi veya mühendis rolü (örn: "Elektrikçi", "İnşaat Mühendisi")
 * @param semafor Beklenecek semafor pointer'ı
 * @param daire_str Daire bilgisi string'i (örn: "Kat 3, Daire 2")
 * @param emoji Görsel emoji karakteri
 * @return void
 * 
 * @note Thread-safe değildir, printf kullanır
 */
void bekle_ve_mesaj(const char* rol, sem_t* semafor, const char* daire_str, const char* emoji);

/**
 * @brief İşlem yapar, mesaj gösterir ve semaforu bırakır
 * @details İşlem tamamlandığında renkli tamamlanma mesajı gösterir ve sem_post() yapar.
 *          İşlem simülasyonu için sleep() kullanır.
 * 
 * @param rol İşçi veya mühendis rolü
 * @param daire_str Daire bilgisi string'i
 * @param emoji Görsel emoji karakteri
 * @param semafor Bırakılacak semafor pointer'ı
 * @return void
 * 
 * @note Thread-safe değildir, printf kullanır
 * @see bekle_ve_mesaj()
 */
void yap_ve_mesaj(const char* rol, const char* daire_str, const char* emoji, sem_t* semafor);

/** @} */ // semafor_yardimci grubu sonu

#endif /* TEMEL_H */
