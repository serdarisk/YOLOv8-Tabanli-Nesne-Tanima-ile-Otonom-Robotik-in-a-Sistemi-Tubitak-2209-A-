Özet ve Amaç: Bu çalışmanın temel amacı, geleneksel bir robot kola "bilgisayarlı görü (computer vision)" yeteneği kazandırarak, insan-makine etkileşimini (HMI) görsel veriler üzerinden sağlamaktır. 
Sistem, önceden tanımlanmış yapıların (bloklar, kuleler vb.) görsellerini veya şemalarını kamera aracılığıyla algılayarak, bu yapıları fiziksel dünyada otonom olarak inşa edebilecek şekilde tasarlanmıştır. 
Proje; derin öğrenme algoritmaları, gömülü sistem haberleşmesi ve robotik manipülasyon disiplinlerini kapsamaktadır.

Sistem, yüksek işlem gücü gerektiren görüntü işleme görevleri ile gerçek zamanlı motor kontrol görevlerini ayrıştıran çift katmanlı bir donanım mimarisi üzerine kurulmuştur.

Ana İşlemci (Görüntü İşleme): Raspberry Pi 5: YOLOv8 modelinin gerçek zamanlı çalıştırılması ve karar mekanizmasının yönetilmesi için kullanılmıştır.

Alt Kontrolcü (Motor Kontrolü): Arduino Uno: Robot kolun eklem hareketlerinin hesaplanması ve servo motorların senkronizasyonu için tercih edilmiştir.

Görüntüleme Birimi: Raspberry Pi Camera Module 3: Yüksek çözünürlük ve oto-odaklama özellikleri sayesinde hedef görsellerin hassas taranması sağlanmıştır.

Sürücü Katı: PCA9685 16-Kanal I2C PWM Sürücü: Arduino üzerindeki işlem yükünü hafifletmek ve çoklu servo motor kontrolünü tek bir I2C hattı üzerinden stabil bir 
güç yönetimiyle sağlamak amacıyla kullanılmıştır.

Projenin "görme" yetisi, Nesne Tespiti (Object Detection) algoritmaları kullanılarak geliştirilmiştir.

Veri Seti Hazırlama: Sisteme tanıtılacak 3 farklı yapı tipi için, farklı açılardan ve ışık koşullarından çekilmiş yaklaşık 240 adet (her yapı için ~80 adet) görsel toplanmıştır. Bu görseller Roboflow platformu kullanılarak etiketlenmiş ve veri seti, modelin doğruluğunu artırmak adına ön işleme (preprocessing) adımlarından geçirilmiştir.

Model Eğitimi (Training): Oluşturulan veri seti, Google Colab üzerindeki T4 GPU sunucuları kullanılarak YOLOv8 mimarisi üzerinde eğitilmiştir. Eğitim sonucunda modelin kayıp (loss) grafikleri optimize edilmiş ve yüksek doğruluk oranına (mAP) ulaşılmıştır.

Algoritma: Python tabanlı yazılım, kamera görüntüsünden gelen veriyi anlık olarak işleyerek referans yapıyı tanır ve ilgili yapının "inşa reçetesini" (step-by-step instructions) belleğinden çağırır.

Algılama: Raspberry Pi 5, kamera aracılığıyla kullanıcı tarafından gösterilen hedef yapıyı veya fotoğrafı tarar.

Anlamlandırma: Eğitilmiş YOLOv8 modeli, gösterilen görselin veritabanındaki hangi yapı olduğunu tespit ede

Haberleşme: Tespit edilen yapıya ait komut seti, Raspberry Pi tarafından seri port üzerinden Arduino'ya iletilir.

Eylem: Arduino, gelen veriyi işleyerek PCA9685 sürücüsü üzerinden robot kolun servolarını koordine eder ve parçaları sırasıyla yerleştirerek yapıyı inşa eder.
