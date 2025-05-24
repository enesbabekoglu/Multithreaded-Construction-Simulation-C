/**
 * İşçi ve mühendis kaynak yönetimi modülü
 * Semaforlar kullanarak sınırlı kaynakların yönetimini sağlar
 * Yarış koşullarını (race condition) önler
 */

#include "isci.h"
#include <fcntl.h>
#include <stdio.h>

// İşçi semaforları - sınırlı sayıda işçi kaynağı
sem_t *elektrikci_sem, *su_sem, *dogalgaz_sem;

// Mühendis semaforları - tek mühendis kaynağı (mutex gibi çalışır)
sem_t *insaat_muh_sem, *elektrik_muh_sem, *makine_muh_sem;

// Ortak kaynak semaforları
sem_t *vinc_sem;  // Sadece 1 vinç var - yarış koşulu örneği
pthread_mutex_t asansor_mutex;  // Asansör için mutex

/**
 * Tüm semaforları başlatan fonksiyon
 * Program başlangıcında çağrılır
 * 
 * Semafor değerleri:
 * - İşçiler: 3 (aynı anda 3 işçi çalışabilir)
 * - Mühendisler: 1 (aynı anda sadece 1 mühendis çalışabilir)
 * - Vinç: 1 (tüm daireler ortak kullanır - yarış koşulu riski)
 * 
 * Bu değerler yarış koşullarını önler ve kaynakların adil paylaşımını sağlar
 */
void isci_semaforlarini_baslat() {
    // Named semaforları sil (eğer varsa)
    sem_unlink("/elektrikci_sem");
    sem_unlink("/su_sem");
    sem_unlink("/dogalgaz_sem");
    sem_unlink("/insaat_muh_sem");
    sem_unlink("/elektrik_muh_sem");
    sem_unlink("/makine_muh_sem");
    sem_unlink("/vinc_sem");
    
    // İşçi semaforları - 3 işçi mevcut
    // Named semafor kullanarak process'ler arası paylaşım sağla
    elektrikci_sem = sem_open("/elektrikci_sem", O_CREAT, 0644, 3);
    su_sem = sem_open("/su_sem", O_CREAT, 0644, 3);
    dogalgaz_sem = sem_open("/dogalgaz_sem", O_CREAT, 0644, 3);

    // Mühendis semaforları - sadece 1 mühendis mevcut
    insaat_muh_sem = sem_open("/insaat_muh_sem", O_CREAT, 0644, 1);
    elektrik_muh_sem = sem_open("/elektrik_muh_sem", O_CREAT, 0644, 1);
    makine_muh_sem = sem_open("/makine_muh_sem", O_CREAT, 0644, 1);
    
    // Ortak kaynak semaforları
    vinc_sem = sem_open("/vinc_sem", O_CREAT, 0644, 1);
    
    // Asansör mutex'i başlat
    pthread_mutex_init(&asansor_mutex, NULL);
}

/**
 * Tüm semaforları temizleyen fonksiyon
 * Program sonunda çağrılır
 * Sistem kaynaklarını serbest bırakır
 */
void isci_semaforlarini_sil() {
    // Named semaforları kapat
    sem_close(elektrikci_sem);
    sem_close(su_sem);
    sem_close(dogalgaz_sem);
    sem_close(insaat_muh_sem);
    sem_close(elektrik_muh_sem);
    sem_close(makine_muh_sem);
    sem_close(vinc_sem);
    
    // Named semaforları sistemden sil
    sem_unlink("/elektrikci_sem");
    sem_unlink("/su_sem");
    sem_unlink("/dogalgaz_sem");
    sem_unlink("/insaat_muh_sem");
    sem_unlink("/elektrik_muh_sem");
    sem_unlink("/makine_muh_sem");
    sem_unlink("/vinc_sem");
    
    // Mutex'i temizle
    pthread_mutex_destroy(&asansor_mutex);
}
