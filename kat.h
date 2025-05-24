/**
 * @file kat.h
 * @brief Kat inşaat yönetimi başlık dosyası
 * @details Multi-process yapıda her katın inşaatını yöneten ana fonksiyonun
 *          prototipini içerir. Fork() sistem çağrısı ile process oluşturma
 *          işlemlerini koordine eder.
 * 
 * @author İnşaat Simülasyon Sistemi
 * @date 2025
 */

#ifndef KAT_H
#define KAT_H

/**
 * @brief Tüm katların inşaat sürecini başlatır ve yönetir
 * @details 10 katlı apartman için her katı ayrı bir process olarak fork() ile oluşturur.
 *          Her kat process'i kendi içinde 4 daire için thread'ler oluşturur.
 *          Parent process tüm child process'lerin tamamlanmasını bekler.
 * 
 * @return void
 * 
 * @note Bu fonksiyon main() tarafından temel inşaatından sonra çağrılır
 * @warning Fork() başarısız olursa program hata ile sonlanır
 * 
 * @code
 * // İşleyiş akışı:
 * // 1. Her kat için fork() ile yeni process oluştur
 * // 2. Child process: kat_insaat() fonksiyonunu çalıştır
 * // 3. Parent process: Tüm child'ları bekle (waitpid)
 * // 4. Tüm katlar tamamlandığında fonksiyon döner
 * @endcode
 * 
 * @see kat_insaat() - Her kat için çalıştırılan fonksiyon
 * @see daire_gorevleri() - Her daire için thread olarak çalışan fonksiyon
 */
void insaat_katlarini_baslat();

#endif /* KAT_H */