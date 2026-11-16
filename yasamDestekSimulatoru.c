#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Durum değişkenleri
int saglik = 100;
int enerji = 100;
int oksijen = 100;
int su_miktari = 5;
int yedek_parca = 2;
int modul_hasari = 20;
int kilit_muhurlu = 0;

// Zaman ve Tur Sayaçları
int gun = 1;
int tur = 0;
int hedef_gun = 15;
int simulasyon_devam = 1;

// Zorluk Seviyesi Parametreleri
char zorluk_secimi;

// Fonksiyon Prototipleri
void sinirlari_kontrol_et();
void durum_raporu_goster();
void hareket_yapildi();
void gun_ve_zaman_kontrolu();
void kesif_yap();
void oksijen_uret();
void tamir_et();
void uyu_dinlen();
void kum_firtinasi_simule_et();
void hava_kilidi_sifresi();

int main() {
    srand(time(NULL));
    char komut;

    printf("       MARS KOLONİSİ YAŞAM DESTEK SİPÜLATÖRÜNE HOŞGELDİNİZ\n");

    // Zorluk Seviyesi Seçimi (Switch-Case)
    do {
        printf("\nZorluk Seviyesi Seçiniz (K: Kolay, N: Normal, Z: Zor): ");
        if (scanf(" %c", &zorluk_secimi) != 1) { zorluk_secimi = 'N'; }
        zorluk_secimi = toupper(zorluk_secimi);

        switch (zorluk_secimi) {
            case 'K':
                su_miktari = 8;
                yedek_parca = 4;
                modul_hasari = 10;
                printf("Zorluk: KOLAY seçildi. Başlangıç kaynakları bol.\n");
                break;
            case 'N':
                su_miktari = 5;
                yedek_parca = 2;
                modul_hasari = 20;
                printf("Zorluk: NORMAL seçildi. Standart Mars koşulları.\n");
                break;
            case 'Z':
                su_miktari = 3;
                yedek_parca = 1;
                modul_hasari = 40;
                printf("Zorluk: ZOR seçildi. Kaynaklar kısıtlı, hasar yüksek!\n");
                break;
            default:
                printf("Geçersiz seçim! Lütfen K, N veya Z harflerini giriniz.\n");
                zorluk_secimi = ' ';
        }
    } while (zorluk_secimi == ' ');

    // Komut Rehberi
    printf("\nKOMUTLAR \n");
    printf(" G : Keşif yap (Enerji ve oksijen harcar; su veya yedek parça bulunabilir)\n");
    printf(" O : Oksijen üret (Su ve enerji harcayarak oksijen üretir)\n");
    printf(" T : Tamir et (Yedek parça harcayarak modül hasarını azaltır)\n");
    printf(" D : Durum raporunu göster (Süre harcamaz)\n");
    printf(" U : Uyu / Dinlen (Enerji ve sağlık yeniler)\n");
    printf(" K : Kum fırtınasını simüle et (FOR döngüsü)\n");
    printf(" H : Hava kilidi şifresi (DO-WHILE döngüsü ile kilidi mühürle)\n");
    printf(" Q : Çıkış yap\n");

    // Ana Oyun Döngüsü (Do-While)
    do {
        sinirlari_kontrol_et();

        // ÖLÜM KONTROLÜ
        if (saglik <= 0 || oksijen <= 0) {
            printf("\n!!! HAYATİ DEĞERLER TÜKENDİ. MARS'TA HAYATTA KALAMADINIZ! OYUN BİTTİ !!!\n");
            simulasyon_devam = 0;
            break;
        }

        // KAZANMA KONTROLÜ (15. Gün)
        if (gun > hedef_gun) {
            printf("\nTEBRİKLER! 15 GÜNÜ TAMAMLADINIZ, KURTARMA EKİBİ ULAŞTI!\n");
            simulasyon_devam = 0;
            break;
        }
        printf("GÜN: %d/%d | TUR: %d | Komut giriniz (D: Durum, Q: Çıkış): ", gun, hedef_gun, tur);
        
        if (scanf(" %c", &komut) != 1) { komut = ' '; }
        char kucuk_komut = tolower(komut);

        // Switch-Case Komut Yönetimi (Fall-through kullanımı ile büyük/küçük harf duyarsızlığı)
        switch (kucuk_komut) {
            case 'g':
                kesif_yap();
                hareket_yapildi();
                break;
            case 'o':
                oksijen_uret();
                hareket_yapildi();
                break;
            case 't':
                tamir_et();
                hareket_yapildi();
                break;
            case 'd':
                durum_raporu_goster();
                // D komutu tur harcamaz
                continue;
            case 'u':
                uyu_dinlen();
                hareket_yapildi();
                break;
            case 'k':
                kum_firtinasi_simule_et();
                hareket_yapildi();
                break;
            case 'h':
                hava_kilidi_sifresi();
                hareket_yapildi();
                break;
            case 'q':
                printf("\nSimülasyon kullanıcı tarafından sonlandırıldı.\n");
                simulasyon_devam = 0;
                break;
            default:
                printf(" Geçersiz komut! Lütfen rehberdeki harflerden birini girin. (Süre harcanmadı)\n");
                continue; // Tanımsız komut tur/süre harcamaz
        }

        // Her geçerli komut sonrası gün/zaman kontrolü çalışır
        if (simulasyon_devam) {
            gun_ve_zaman_kontrolu();
        }

    } while (simulasyon_devam);

    // --- SONUÇ RAPORU VE PUANLAMA ---
    int puan = (gun * 100) + saglik + oksijen - modul_hasari;
    if (puan < 0) puan = 0;

    printf("\nOYUN SONU RAPORU\n");
    printf("Hayatta Kalınan Gün : %d\n", gun > hedef_gun ? hedef_gun : gun);
    printf("Toplam Tur Sayısı   : %d\n", tur);
    printf("Son Sağlık Seviyesi : %d/100\n", saglik);
    printf("Son Oksijen Seviyesi: %d/100\n", oksijen);
    printf("Son Modül Hasarı    : %d/100\n", modul_hasari);
    printf("Kalan Su Miktarı    : %d birim\n", su_miktari);
    printf("Kalan Yedek Parça   : %d\n", yedek_parca);
    printf("TOPLAM PUANINIZ     : %d Puan\n", puan);

    return 0;
}

// --- YARDIMCI FONKSİYONLAR ---

void sinirlari_kontrol_et() {
    if (saglik < 0) saglik = 0;
    if (saglik > 100) saglik = 100;
    if (enerji < 0) enerji = 0;
    if (enerji > 100) enerji > 100 ? enerji = 100 : enerji; // Düzeltme
    if (enerji > 100) enerji = 100;
    if (oksijen < 0) oksijen = 0;
    if (oksijen > 100) oksijen = 100;
    if (modul_hasari < 0) modul_hasari = 0;
    if (modul_hasari > 100) modul_hasari = 100;
}

void durum_raporu_goster() {
    printf("\n DURUM RAPORU \n");
    printf("Gün: %d | Tur: %d | Zorluk: %c\n", gun, tur, zorluk_secimi);
    printf("Sağlık : %d/100\n", saglik);
    printf("Enerji : %d/100\n", enerji);
    printf("Oksijen: %d/100\n", oksijen);
    printf("Su     : %d birim\n", su_miktari);
    printf("Parça  : %d adet\n", yedek_parca);
    printf("Hasar  : %d/100\n", modul_hasari);
    printf("Kilit  : %s\n", kilit_muhurlu ? "MÜHÜRLÜ" : "AÇIK");

    // Kritik Uyarılar
    int kritik_var = 0;
    if (oksijen < 25) { printf(" * KRİTİK UYARI: Oksijen seviyesi çok düşük (<25)!\n"); kritik_var = 1; }
    if (saglik < 30)  { printf(" * KRİTİK UYARI: Sağlık durumu kritik (<30)!\n"); kritik_var = 1; }
    if (modul_hasari > 70) { printf(" * KRİTİK UYARI: Modül hasarı çok yüksek (>70)!\n"); kritik_var = 1; }
    if (enerji < 20)  { printf(" * KRİTİK UYARI: Enerjiniz tükeniyor (<20)!\n"); kritik_var = 1; }

    if (!kritik_var) {
        printf(" TÜM SİSTEMLER NORMAL.\n");
    }
}

void hareket_yapildi() {
    tur++;
}

void gun_ve_zaman_kontrolu() {
    // Her 3 turda bir yeni gün başlar
    if (tur % 3 == 0) {
        gun++;
        printf("\n>>> Yeni Bir Gün Başlıyor! Gün: %d <<<\n", gun);
        oksijen -= 8; // Gün başında oksijen azalır

        if (modul_hasari > 70) {
            saglik -= 5;
            printf("Uyarı: Yüksek modül hasarı nedeniyle geceleri 5 sağlık kaybettiniz!\n");
        }
    }
}

// --- KOMUT FONKSİYONLARI ---

void kesif_yap() {
    // Yetersiz kaynak kontrolü
    if (enerji < 15 || oksijen < 10) {
        printf("\n[HATA] Enerji (15) veya Oksijen (10) yetersiz! Keşfe çıkılamaz.\n");
        return;
    }

    enerji -= 15;
    oksijen -= 10;

    printf("\nMars yüzeyinde keşif görevi gerçekleştiriliyor...\n");

    int esik = (enerji > 40 && oksijen > 30) ? 40 : 70;
    int zar = rand() % 100;
    printf("[ZAR KONTROLÜ] Zar: %d / Eşik: %d -> ", zar, esik);

    // Yaralanma kontrolü: (zar < 10 || modul_hasari > 70)
    int yaralanma_zari = rand() % 100;
    if (yaralanma_zari < 10 || modul_hasari > 70) {
        saglik -= 15;
        printf("YARALANMA! Fırtına kalıntısı veya kazadan dolayı 15 sağlık kaybettiniz.\n");
    }

    // Keşif Sonuçları (En az 3 farklı sonuç)
    if (zar < esik) {
        su_miktari += 2;
        printf("BAŞARILI! Yeraltı buzulu bulundu ve 2 birim su elde edildi.\n");
    } else if (zar < esik + 30) {
        yedek_parca += 1;
        printf("BAŞARILI! Eski bir araştırma modülünden 1 yedek parça buldunuz.\n");
    } else {
        printf("ELİ BOŞ DÖNDÜNÜZ. Bölgede kullanılabilir kaynak bulunamadı.\n");
    }
}

void oksijen_uret() {
    if (enerji < 10) {
        printf("\n[HATA] Oksijen üretmek için enerji yetersiz (Min 10 gerekli).\n");
        return;
    }
    if (su_miktari < 2) {
        printf("\n[HATA] Su deposunda yeterli su yok! Oksijen üretimi için en az 2 birim su gerekir.\n");
        return;
    }

    enerji -= 10;
    
    // Her 2 birim su, 3 birim oksijene dönüşür. Mod operatörü ile artık su kontrolü:
    int kullanilan_su = (su_miktari / 2) * 2; // Çift miktar hesaplanır
    int kalan_su_artigi = su_miktari % 2;     // Tekse 1 birim artık kalır

    int uretilen_oksijen = (kullanilan_su / 2) * 3;
    su_miktari = kalan_su_artigi; // Sadece artık depo da kalır
    oksijen += uretilen_oksijen;

    printf("\nOksijen Üretildi: %d birim su harcandı, %d birim oksijen üretildi.\n", kullanilan_su, uretilen_oksijen);
    if (kalan_su_artigi > 0) {
        printf("Not: Tek sayıdaki su kullanımından dolayı depolarımızda 1 birim su artık kaldı.\n");
    }
}

void tamir_et() {
    if (yedek_parca <= 0) {
        printf("\n[HATA] Depoda hiç yedek parça yok! Tamir yapılamaz.\n");
        return;
    }
    if (modul_hasari == 0) {
        printf("\nModül hasarı zaten 0. Tamire gerek yok.\n");
        return;
    }

    yedek_parca--;
    int onarim_miktari = 0;

    // IF-ELSE IF-ELSE zinciri ile hasar kademeleri
    if (modul_hasari <= 30) {
        onarim_miktari = 25;
        printf("Hafif Hasar Bölgesi (0-30): 1 yedek parça harcandı, 25 birim onarıldı.\n");
    } else if (modul_hasari <= 70) {
        onarim_miktari = 20;
        printf("Orta Hasar Bölgesi (31-70): 1 yedek parça harcandı, 20 birim onarıldı.\n");
    } else {
        onarim_miktari = 15;
        printf("Ağır Hasar Bölgesi (71-100): 1 yedek parça harcandı, ağır koşullarda 15 birim onarıldı.\n");
    }

    modul_hasari -= onarim_miktari;
}

void uyu_dinlen() {
    int enerji_kazanci = 25;
    int saglik_kazanci = 10;

    enerji += enerji_kazanci;

    // İç içe IF: Oksijen 20'nin altındaysa sağlık artmaz, aksine azalır!
    if (oksijen < 20) {
        saglik -= 10;
        printf("\nUYARI: Oksijen seviyesi çok düşük (<20)! Dinlenirken boğulma tehlikesi geçirdiniz, 10 sağlık kaybettiniz.\n");
    } else {
        saglik += saglik_kazanci;
        printf("\nDinlenildi: Enerji +%d, Sağlık +%d arttı.\n", enerji_kazanci, saglik_kazanci);
    }
}

// FOR DÖNGÜSÜ - Kum Fırtınası Simülasyonu
void kum_firtinasi_simule_et() {
    int firtina_suresi = 3; // Varsayılan Kolay
    if (zorluk_secimi == 'N') firtina_suresi = 5;
    if (zorluk_secimi == 'Z') firtina_suresi = 7;

    printf("\n KUM FIRTINASI BAŞLADI n");
    printf("Fırtına Süresi: %d tur sürecek.\n", firtina_suresi);

    int kaybedilen_saglik_toplam = 0;
    int kaybedilen_oksijen_toplam = 0;
    int hasar_alinan_tur_sayisi = 0;

    for (int i = 1; i <= firtina_suresi; i++) {
        printf("--- Fırtına Turu %d/%d ---\n", i, firtina_suresi);

        // Hava kilidi daha önce H komutu ile mühürlendiyse (kilit_muhurlu == 1) oksijen sızıntısı atlanır (continue)
        if (kilit_muhurlu == 1) {
            printf("Hava kilidi mühürlü olduğu için bu tur oksijen sızıntısı engellendi! (continue çalıştı)\n");
            continue;
        }

        int zar = rand() % 100;
        int esik = 50;
        printf("[ZAR] Zar: %d / Eşik: %d -> ", zar, esik);

        // Çift numaralı turlarda rüzgar şiddetlenir ve hasar iki katına çıkar (mod operatörü ile kontrol)
        int carpan = (i % 2 == 0) ? 2 : 1;
        if (i % 2 == 0) {
            printf("Çift Numaralı Tur! Rüzgar şiddetlendi (Çarpan: 2x).\n");
        } else {
            printf("Normal rüzgar şiddeti (Çarpan: 1x).\n");
        }

        if (zar < esik) {
            int s_kayip = 10 * carpan;
            int o_kayip = 8 * carpan;
            saglik -= s_kayip;
            oksijen -= o_kayip;
            modul_hasari += (5 * carpan);

            kaybedilen_saglik_toplam += s_kayip;
            kaybedilen_oksijen_toplam += o_kayip;
            hasar_alinan_tur_sayisi++;

            printf("HASAR! Fırtına modülü dövdü. Sağlık -%d, Oksijen -%d, Modül Hasarı arttı.\n", s_kayip, o_kayip);
        } else {
            printf("Şanslısınız! İstasyon fırtına direncini korudu, bu tur zarar alınmadı.\n");
        }

        // Sağlık veya oksijen 0'a düşerse döngü break ile derhal sonlandırılır
        if (saglik <= 0 || oksijen <= 0) {
            printf("Fırtına sırasında kritik eşik aşıldı, bayıldınız! (break)\n");
            break;
        }
    }

    printf(" FIRTINA ÖZETİ:\n");
    printf(" Hasar Alınan Tur Sayısı : %d\n", hasar_alinan_tur_sayisi);
    printf(" Toplam Kaybedilen Sağlık : %d\n", kaybedilen_saglik_toplam);
    printf(" Toplam Kaybedilen Oksijen: %d\n", kaybedilen_oksijen_toplam);
}

// DO-WHILE DÖNGÜSÜ - Hava Kilidi Şifresi
void hava_kilidi_sifresi() {
    if (kilit_muhurlu == 1) {
        printf("\nHava kilidi zaten daha önce mühürlenmiş.\n");
        return;
    }

    // Şifre o anki gün sayısından aritmetik olarak türetilir: sifre = 'A' + (gun % 26)
    char dogru_sifre = 'A' + (gun % 26);
    int deneme_hakki = 3;
    char girilen_karakter;

    printf("\n*** HAVA KİLİDİ GÜVENLİK MÜHÜRLEME SİSTEMİ ***\n");
    printf("İpucu: Şifre, alfabede 'A' harfinden bugünün gün sayısı (%d) kadar ilerideki büyük harftir.\n", gun);

    // DO-WHILE döngüsü ve mantıksal operatörle deneme kontrolü
    do {
        printf("Kalan Deneme Hakkı (%d). Şifre harfini girin: ", deneme_hakki);
        if (scanf(" %c", &girilen_karakter) != 1) { girilen_karakter = ' '; }
        girilen_karakter = toupper(girilen_karakter);

        if (girilen_karakter == dogru_sifre) {
            kilit_muhurlu = 1;
            enerji += 15;
            printf("\n TEBRİKLER! Doğru şifre. Hava kilidi başarıyla mühürlendi! (+15 Enerji)\n");
            break;
        } else {
            deneme_hakki--;
            enerji -= 5;
            printf("Yanlış şifre! 5 enerji kaybettiniz.\n");

            if (deneme_hakki > 0) {
                if (girilen_karakter < dogru_sifre) {
                    printf(" İPUCU: Daha İLERİ bir harf girmelisiniz (Alfabetik olarak sonraya git).\n");
                } else {
                    printf(" İPUCU: Daha GERİ bir harf girmelisiniz (Alfabetik olarak önceye git).\n");
                }
            }
        }

    } while (deneme_hakki > 0 && girilen_karakter != dogru_sifre);

    if (kilit_muhurlu == 0) {
        modul_hasari += 20;
        printf("\n Haklarınız bitti! Şifre çözülemedi. Güvenlik açığı nedeniyle modül hasarı +20 arttı.\n");
    }
}
