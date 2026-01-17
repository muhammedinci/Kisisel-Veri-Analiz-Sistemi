#include <stdio.h>

int gunler[100];
float yemek[100];
float ulasim[100];
int satirSayisi = 0; 

// DOSYA OKUMA FONKSİYONU 
void dosyaOku() {
    FILE *dosya = fopen("data.txt", "r"); 
    if (dosya == NULL) {
        printf("Hata: data.txt dosyasi bulunamadi!\n");
        return;
    }
    while (satirSayisi < 100 && 
            fscanf(dosya, "%d %f %f", 
            &gunler[satirSayisi], 
            &yemek[satirSayisi], 
            &ulasim[satirSayisi]) != EOF) {
        satirSayisi++; 
    }
  
       fclose(dosya);  
}

//  MENÜ GÖSTERME FONKSİYONU 
void menuGoster() {
    printf("\n--- KISISEL VERI ANALIZ SISTEMI ---\n");
    printf("1. Tum veriyi listele\n");
    printf("2. Toplam ve ortalama degerleri goster\n");
    printf("3. En dusuk ve en yuksek degerleri goster\n");
    printf("4. Esik degerine gore gun sayisi analizi yap\n");
    printf("5. Ozel analiz (Harcama orani)\n");
    printf("0. Cikis\n");
    printf("Seciminiz: ");
}

//  VERİLERİ LİSTELEME 
void verileriListele() {
    printf("\nGUN\tYEMEK\tULASIM\n");
    printf("---\t-----\t------\n");
    int i;
    for (i = 0; i < satirSayisi; i++) {
        printf("%d\t%.2f\t%.2f\n", gunler[i], yemek[i], ulasim[i]);
    }
}

//  TOPLAM VE ORTALAMA HESAPLAMA
void toplamVeOrtalama() {
    float toplamYemek = 0;
    float toplamUlasim = 0;
    
    int i;
    for (i = 0; i < satirSayisi; i++) {
        toplamYemek += yemek[i];
        toplamUlasim += ulasim[i];
    }

    float ortalamaYemek = toplamYemek / satirSayisi;
    float ortalamaUlasim = toplamUlasim / satirSayisi;

    printf("\n--- ANALIZ SONUCLARI ---\n");
    printf("Toplam Yemek Harcamasi : %.2f TL\n", toplamYemek);
    printf("Ortalama Gunluk Yemek  : %.2f TL\n", ortalamaYemek);
    printf("\n");
    printf("Toplam Ulasim Harcamasi: %.2f TL\n", toplamUlasim);
    printf("Ortalama Gunluk Ulasim : %.2f TL\n", ortalamaUlasim);
} 

//  MİNİMUM VE MAKSİMUM DEĞERLER 
void minMaxBul() {
    
    float enYuksekYemek = yemek[0];
    int enYuksekYemekGun = gunler[0];

    float enDusukYemek = yemek[0];
    int enDusukYemekGun = gunler[0];
     
    float enYuksekUlasim = ulasim[0];
    int enYuksekUlasimGun = gunler[0];

    float enDusukUlasim = ulasim[0];
    int enDusukUlasimGun = gunler[0];


    int i;
    for (i = 1; i < satirSayisi; i++) {
        
        if (yemek[i] > enYuksekYemek) {
            enYuksekYemek = yemek[i];
            enYuksekYemekGun = gunler[i];
        }
        
        if (yemek[i] < enDusukYemek) {
            enDusukYemek = yemek[i];
            enDusukYemekGun = gunler[i];
        }
    
          if (ulasim[i] > enYuksekUlasim) {
              enYuksekUlasim = ulasim[i];
              enYuksekUlasimGun = gunler[i];
       }

         
         if (ulasim[i] < enDusukUlasim) {
             enDusukUlasim = ulasim[i];
             enDusukUlasimGun = gunler[i];
    }

       }

    printf("\n--- YEMEK HARCAMASI ENLERI ---\n");
    printf("En Yuksek Harcama: %.2f TL (Gun: %d)\n", enYuksekYemek, enYuksekYemekGun);
    printf("En Dusuk Harcama : %.2f TL (Gun: %d)\n", enDusukYemek, enDusukYemekGun);

    printf("\n--- ULASIM HARCAMASI ENLERI ---\n");
    printf("En Yuksek Harcama: %.2f TL (Gun: %d)\n", enYuksekUlasim, enYuksekUlasimGun);
    printf("En Dusuk Harcama : %.2f TL (Gun: %d)\n", enDusukUlasim, enDusukUlasimGun);

}

//  EŞİK DEĞER ANALİZİ 
void esikDegerAnalizi() {
    float limit;
    int sayac = 0; 
    
    printf("\n--- HARCAMA ESIK ANALIZI ---\n");
    printf("Hangi tutarin uzerindeki harcamalari sayalim? (TL): ");
    scanf("%f", &limit);
    
    int i;
    for (i = 0; i < satirSayisi; i++) {
        
        if (yemek[i] > limit) {
            sayac++;
        }
    }
    
    printf("\nSONUC:\n");
    printf("%.2f TL uzerinde harcama yapilan gun sayisi: %d\n", limit, sayac);
    
    
}
//  ÖZEL ANALİZ (BÜTÇE VE ORANSAL DAĞILIM) 
void ozelAnaliz() {
    float toplamYemek = 0;
    float toplamUlasim = 0;
    float genelToplam = 0;
    
   
    int i;
    for (i = 0; i < satirSayisi; i++) {
        toplamYemek += yemek[i];
        toplamUlasim += ulasim[i];
    }
    genelToplam = toplamYemek + toplamUlasim;

   
    float yemekYuzdesi = (toplamYemek / genelToplam) * 100;
    float ulasimYuzdesi = (toplamUlasim / genelToplam) * 100;

    printf("\n--- OZEL ANALIZ: BUTCE VE DAGILIM ---\n");
    printf("Genel Toplam Harcama: %.2f TL\n", genelToplam);
    printf("Harcama Dagilimi:\n");
    printf(" - Yemek : %%%.2f\n", yemekYuzdesi); 
    printf(" - Ulasim: %%%.2f\n", ulasimYuzdesi);

   
    float butce;
    printf("\nBu ay icin hedeflediginiz butce ne kadardi? (TL): ");
    scanf("%f", &butce);

    if (genelToplam > butce) {
        float fark = genelToplam - butce;
        printf("DURUM: KOTU! Butceyi %.2f TL astiniz.\n", fark);
    } else {
        float kalan = butce - genelToplam;
        printf("DURUM: IYI! Butcenin icindesiniz. %.2f TL paraniz artti.\n", kalan);
    }
}


int main() {
    dosyaOku();

    if (satirSayisi == 0) {
        printf("Dosyada okunacak veri bulunamadi.\n");
        return 0;   
    }

    int secim;

    do {
        menuGoster();

        if (scanf("%d", &secim) != 1) {
            printf("Gecersiz giris!\n");
            while (getchar() != '\n');
            secim = -1;
        }

        switch (secim) {
            case 1:
                verileriListele();
                break;
            case 2:
                toplamVeOrtalama();
                break;
            case 3:
                minMaxBul();
                break;
            case 4:
                esikDegerAnalizi();
                break;
            case 5:
                ozelAnaliz();
                break;
            case 0:
                printf("Programdan cikiliyor. Iyi gunler!\n");
                break;
            default:
                printf("Hatali secim! Lutfen tekrar deneyin.\n");
        }

    } while (secim != 0);

    return 0;
}
