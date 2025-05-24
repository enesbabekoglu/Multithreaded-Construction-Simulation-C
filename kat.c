/**
 * Kat inşaat modülü
 * Her kat bir process olarak çalışır ve her daire bir thread olarak modellenmiştir
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include "kat.h"
#include "daire.h"
#include "temel.h"
#include "isci.h"

#define GREEN   "\033[0;32m"
#define RESET   "\033[0m"

/**
 * Daire inşaat işlerini gerçekleştiren thread fonksiyonu
 * Her daire için ayrı bir thread oluşturulur ve bu fonksiyon çalıştırılır
 * 
 * @param arg Daire numarası (int pointer olarak geçirilir)
 * @return NULL
 */
void* daire_isleri(void* arg) {
    int daire_no = *((int*)arg);
    free(arg); // Dinamik belleği serbest bırak
    
    // Daire görevlerini gerçekleştir
    daire_gorevleri(daire_no);
    
    return NULL;
}

/**
 * Belirli bir katın inşaatını gerçekleştiren fonksiyon
 * Bu fonksiyon her kat için ayrı bir process içinde çalışır
 * 
 * @param kat_no İnşa edilecek kat numarası (1-10 arası)
 */
void kat_insa_et(int kat_no) {
    printf("\n🔨 %d. Kat inşaatı başlatılıyor (Process ID: %d)...\n", kat_no, getpid());

    // İnşaat mühendisi kontrolü - semafor ile senkronizasyon
    sem_wait(insaat_muh_sem); // Mühendis meşgulse bekle
    loading_bar("🧱 İnşaat Mühendisi: Kat yapısal kontrolü...");
    sem_post(insaat_muh_sem); // Mühendisi serbest bırak

    // Her daire için thread oluştur (4 daire = 4 thread)
    pthread_t threadler[4];
    for (int i = 0; i < 4; i++) {
        // Daire numarası için dinamik bellek ayır
        int* no = malloc(sizeof(int));
        *no = i + 1;
        
        // Thread oluştur ve daire işlerini başlat
        pthread_create(&threadler[i], NULL, daire_isleri, no);
    }

    // Tüm daire thread'lerinin bitmesini bekle
    for (int i = 0; i < 4; i++) {
        pthread_join(threadler[i], NULL);
    }

    printf("%s✅ %d. Kat inşaatı tamamlandı.%s\n\n", GREEN, kat_no, RESET);
}

/**
 * Tüm katların inşaatını başlatan ana fonksiyon
 * Her kat için ayrı bir process (fork) oluşturur
 * Katlar sırayla inşa edilir (process senkronizasyonu)
 */
void insaat_katlarini_baslat() {
    // 10 kat için döngü
    for (int kat = 1; kat <= 10; kat++) {
        pid_t pid = fork(); // Yeni process oluştur
        
        if (pid == 0) {
            // Çocuk process - kat inşaatını gerçekleştir
            kat_insa_et(kat);
            exit(0); // Çocuk process'i sonlandır
        } else if (pid > 0) {
            // Ebeveyn process - çocuk process'in bitmesini bekle
            // Bu sayede katlar sırayla inşa edilir
            wait(NULL);
        } else {
            // Fork hatası
            perror("Fork hatası");
            exit(1);
        }
    }
}