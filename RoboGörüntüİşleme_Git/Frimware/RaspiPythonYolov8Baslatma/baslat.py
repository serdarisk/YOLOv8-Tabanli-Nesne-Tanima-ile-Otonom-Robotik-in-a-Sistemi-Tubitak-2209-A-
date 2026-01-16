import cv2
import time
import serial
from picamera2 import Picamera2
from ultralytics import YOLO
import numpy as np

#AYARLAR

#USB PORT AYARLARI
try:
    ser = serial.Serial(
        port="/dev/ttyACM0",  # Arduino genelde bu porttadır
        baudrate=9600,
        timeout=1
    )
    print("Arduino'ya bağlandı!")
except:
    print("UYARI: Arduino bağlı değil! Kod çalışır ama mesaj gitmez.")
    ser = None

#ZAMAN AYARI
SURE_LIMITI = 3 

TARGET_MAP = {
    "ev":    "ev",
    "kopru": "kopru",
    "kule":  "kule"
}

#SİSTEM KURULUMU

print("Kamera başlatılıyor...")
picam2 = Picamera2()
config = picam2.create_preview_configuration(
    main={"format": "BGR888", "size": (640, 480)}
)
picam2.configure(config)
picam2.start()

print("Model yükleniyor...")
try:
    model = YOLO("best.pt")
except:
    print("HATA: best.pt bulunamadı!")
    exit()

# Zaman sayaçları
object_start_time = {name: None for name in TARGET_MAP.keys()}
object_sent_flag = {name: False for name in TARGET_MAP.keys()}

print("Sistem Hazır! Çıkış için 'q' basın.")

while True:
    try:
        #Görüntü al
        frame = picam2.capture_array()
        
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        results = model(frame_rgb, imgsz=320, conf=0.4, verbose=False)
        
        #Bu karede ne var
        detected_in_this_frame = []

        if results:
            annotated_frame = results[0].plot()
            #Bulunanların isimlerini listeye al
            for box in results[0].boxes:
                cls_id = int(box.cls[0])
                class_name = model.names[cls_id]
                detected_in_this_frame.append(class_name)
        else:
            annotated_frame = frame

        #Zaman Kontrolü
        now = time.time()

        for robo_name, arduino_msg in TARGET_MAP.items():
            
            #Nesne ekranda varsa
            if robo_name in detected_in_this_frame:
                if object_start_time[robo_name] is None:
                    object_start_time[robo_name] = now
                
                elapsed = now - object_start_time[robo_name]

                #Ekrana geri sayımı yaz
                cv2.putText(annotated_frame, f"{robo_name}: {int(elapsed)}s", (10, 50 + 30 * list(TARGET_MAP).index(robo_name)), 
                            cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 0), 2)

                #Süre dolduysa GÖNDER
                if elapsed >= SURE_LIMITI and not object_sent_flag[robo_name]:
                    if ser:
                        ser.write((arduino_msg + "\n").encode('utf-8'))
                        print(f"UART GÖNDERİLDİ: {arduino_msg}")
                    
                    object_sent_flag[robo_name] = True
                    #Ekrana yaz
                    cv2.putText(annotated_frame, "SENT!", (200, 200), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 3)

            #Nesne kaybolduysa sıfırla
            else:
                object_start_time[robo_name] = None
                object_sent_flag[robo_name] = False

        cv2.imshow("Serdar - UART Nesne Takibi", annotated_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    except Exception as e:
        print(f"Hata: {e}")
        time.sleep(0.1)

picam2.stop()
cv2.destroyAllWindows()
if ser:
    ser.close()
