# YasamDestekSimulatoru# Mars Kolonisi Yaşam Destek Simülatörü

C programlama dili ile geliştirilmiş, metin tabanlı ve tek karakterli komutlarla kontrol edilen bir hayatta kalma simülasyonu projesidir. Oyuncu, Mars'taki bir araştırma istasyonunda tek başına kalan bir mühendisi yönetir ve kurtarma ekibi gelene kadar (15 gün boyunca) hayatta kalmaya çalışır.

## Proje Özellikleri

- **Zorluk Seviyesi Seçimi:** Kolay (K), Normal (N) ve Zor (Z) olmak üzere farklı başlangıç kaynaklarına ve fırtına sürelerine sahip zorluk modları (`switch-case` yapısı ile).
- **Komut Sistemi (`switch-case` & Fall-through):** Büyük/küçük harf duyarsız komut yönetimi. Tanımsız komutlar tur/zaman harcamaz.
- **Kaynak Yönetimi & Aritmetik İşlemler:**
  - Keşif (`G`), Oksijen Üretimi (`O` - mod operatörü ile su/oksijen dönüşümü ve artık su takibi), Tamir (`T` - kademeli if-else mimarisi) ve Dinlenme (`U` - iç içe if yapıları ile düşük oksijen kontrolü).
- **Kum Fırtınası Simülasyonu (`for` döngüsü):** Zorluk derecesine göre tur sayısı belirlenen, çift turlarda şiddetlenen (mod operatörü), hava kilidi mühürlüyse `continue` ile oksijen sızıntısı atlanan ve kritik durumlarda `break` ile sonlandırılan fırtına mekanizması.
- **Hava Kilidi Şifre Mekanizması (`do-while` döngüsü):** Gün sayısına bağlı olarak dinamik türetilen şifre (`'A' + (gun % 26)`), 3 deneme hakkı ve yönlendirici ipuçları.
- **Oyun Sonu ve Puanlama:** Hayatta kalınan gün, tur sayısı, sağlık ve modül hasarına göre dinamik puan hesaplama.

## Komut Rehberi

| Komut | İşlev |
| :---: | :--- |
| **G** | Keşif görevi yap (Enerji/oksijen harcar, su veya yedek parça buldurur) |
| **O** | Oksijen üret (Su ve enerji harcayarak oksijen üretir) |
| **T** | Tamir et (Yedek parça harcayarak modül hasarını azaltır) |
| **D** | Durum raporunu göster (Süre harcamaz) |
| **U** | Uyu / Dinlen (Enerji ve sağlık yeniler) |
| **K** | Kum fırtınasını simüle et (`for` döngüsü) |
| **H** | Hava kilidi şifresi (`do-while` döngüsü ile mühürleme) |
| **Q** | Çıkış yap |

## Derleme ve Çalıştırma

Projeyi derlemek ve çalıştırmak için terminal üzerinde şu komutları kullanabilirsiniz:

```bash
gcc main.c -o mars_simulator
./mars_simulator
```
