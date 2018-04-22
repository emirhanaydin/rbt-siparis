Sakarya Üniversitesi
Bilgisayar ve Bilişim Bilimleri Fakültesi 
Bilgisayar Mühendisliği Bölümü

Sistem Programlama
Proje Çalışması

21.04.2018

ÖNEMLİ: Programın derlenebilmesi için libfdr.a dosyası lib dizininde bulunmalıdır.
Bkz: https://bitbucket.org/jimplank/cs360-lecture-notes/src/139bd33f7f29/Libfdr/


Program, standart girişten verilen komutlara göre 5 farklı işlem yapar:


1. Sipariş Ekleme

Girilen anahtar değeri baz alınarak verinin tamamı bir yapının içerisinde RBT'ye eklenir.

Kullanım
    add|anahtar|ad|malzeme|renk



2. Sipariş Arama

Girilen anahtar değerine sahip olan sipariş yapısını RBT'den alır ve ekrana yazar.

Kullanım
    search|anahtar



3. Siparişleri Dosyaya Yazdırma

Programın çalışması süresince belleğe alınmış olan tüm sipariş kayıtlarını belirtilen dosyaya yazar.

Kullanım
    write|dosya_adi



4. Siparişleri Ekrana Yazdırma

Kullanım
    print

Programın çalışması süresince belleğe alınmış olan tüm sipariş kayıtlarını ekrana yazar.



5. Çıkış

Programın çalışması süresince dinamik olarak oluşturulmuş tüm bellek ögelerini bellekten temizler ve programı
sonlandırır.

Kullanım
    quit
