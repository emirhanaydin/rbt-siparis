## SİSTEM PROGRAMLAMA 2018

## PROJE ÇALIŞMASI

**Geri dönüş tarihi: 23 Nisan 2018 Pazartesi 23:**

Projede belirli bir formatta kayıtlı verileri (siparişleri) ve komutları standart input’tan okuyan, red-black ağaç yapısına dolduran
ve istenilen işleri uygun biçimde yapan programı C dilinde geliştirmeniz beklenmektedir. Projede libfdr kütüphanesini
kullanmanız istenilmektedir.

Komutlar:


#### a) Şipariş ekleme: add


> add|-sipKey-|-sipAd-|-sipMalezeme-|-sipRenk-


Şeklinde giriş yapıldığında, ilgili kaydın tüm alanları ağaç yapısına doldurulacaktır. Aynı veriler yönlendirme ile de
okutulabilecektir. Örneğin, test için verilen ir dosya aşağıdaki gibi okutulabilecektir:


> pro < input.txt


Biçim açısından uygun olmayan kayıtlara rastlanırsa ekrana “Biçim uygun değil.” mesajı yazmalı ve tekrar komut
beklemelidir. Bozuk biçimli kayıtları içeri (veri yapısına) almamalıdır.


#### b) Sipariş arama (anahtara göre arama): search


> search|-sipKey-


Arama sonrasında bulunan kayıt ekrana aşağıdaki gibi yazdırılacaktır.


> search|
13, MacBook, Metal, White


Kayıt bulunamaz ise ekrana “Aranan kayıt bulunamadı.” yazmalıdır.


#### c) Siparişleri dosyaya yazdırma: write


> write|fileName


Ağaç yapısına doldurulan veriler, fileName ile verilen dosyaya sıralı biçimde aşağıdaki biçimde kaydedilmelidir.


0, iPhone, Silicon, Rose Gold
1, Car, Metal, Tornado Red
...


#### d) Siparişleri ekrana yazdırma: print


> print


Dosyaya yazdırılan biçimde ağaç içindeki tüm kayıtlar ekrana yazdırılmalıdır.


#### e) Çıkış: quit


> quit


Programdan temiz (kullanılan bellek iade edilmiş, dosyalar kapatılmış vb.) bir şekilde çıkılmalıdır.

**Geri döndürülecekler:** 1) Readme, 2) Kaynak dosyalar (*.h ve *c dosyaları), 3) Makefile. Asla icra edilebilir dosya göndermeyin.


**Örnek giriş dosyası içerikleri:**

add|14|Barbie|Metal|Green  
add|10|Book|Plastic|Green  
add|9|He-Man|Glass|Tornado Red  
add|3|Car|Wooden|Tornado Red  
add|18|iPhone|Wooden|Red  
add|8|Ball|Silicon|Green  
add|11|Ball|Wooden|Red  
add|5|Ball|Wooden|Black  
add|13|MacBook|Metal|White  
add|7|Barbie|Plastic|Tornado Red  
add|2|MacBook|Wooden|White  
add|17|He-Man|Glass|Space Gray  
add|12|MacBook|Glass|Green  
add|15|iPhone|Plastic|Green  
add|1|Car|Metal|Tornado Red  
add|6|Car|Silicon|Red  
add|4|iPhone|Wooden|Red  
add|0|iPhone|Silicon|Rose Gold  
add|16|Ball|Plastic|Green  
add|19|Car|Metal|Black  
