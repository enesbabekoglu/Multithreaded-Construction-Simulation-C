/**
 * @file final.h
 * @brief Final inşaat işlemleri başlık dosyası
 * @details Apartman inşaatının son aşamalarını (çatı ve dış cephe) yöneten fonksiyonların
 *          prototiplerini içerir.
 * 
 * @author İnşaat Simülasyon Sistemi
 * @date 2025
 */

#ifndef FINAL_H
#define FINAL_H

/**
 * @brief Çatı inşaat işlemlerini gerçekleştirir
 * @details Apartmanın çatı yapısını inşa eder. Bu işlem tüm katların tamamlanmasından
 *          sonra gerçekleştirilir. İnşaat mühendisi ve işçi kaynaklarını kullanır.
 * 
 * @return void
 * 
 * @note Bu fonksiyon main process tarafından çağrılır
 * @see dis_cephe_islemleri()
 */
void cati_insa_et();

/**
 * @brief Dış cephe işlemlerini gerçekleştirir
 * @details Apartmanın dış cephe kaplama, boyama ve yalıtım işlemlerini yapar.
 *          Çatı inşaatından sonra gerçekleştirilir ve inşaatın son aşamasıdır.
 * 
 * @return void
 * 
 * @note Bu fonksiyon main process tarafından çağrılır
 * @see cati_insa_et()
 */
void dis_cephe_islemleri();

#endif /* FINAL_H */