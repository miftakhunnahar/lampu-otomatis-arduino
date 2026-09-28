#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
const int relayPin = 8; // Pin Arduino yang tersambung ke pin IN pada relay

// =================== ATUR JADWAL DI SINI ===================
// Ganti angka jam dan menit sesuai keinginanmu
const int jamHidup = 18;    // Lampu mulai NYALA jam berapa? (0 - 23)
const int menitHidup = 56;   // Lampu mulai NYALA lewat berapa menit? (0 - 59)

const int jamMati = 18;      // Lampu mulai MATI jam berapa? (0 - 23)
const int menitMati = 57;   // Lampu mulai MATI lewat berapa menit? (0 - 59)
// ==========================================================

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);

  // Mencegah relay tiba-tiba menyala saat Arduino baru dinyalakan
  digitalWrite(relayPin, HIGH); 

  // Mengecek apakah modul RTC sudah terhubung dengan benar
  if (!rtc.begin()) {
    Serial.println("Modul RTC tidak ditemukan! Cek kembali kabel SDA dan SCL.");
    while (1) delay(10); 
  }

  // Baris ini akan otomatis menyamakan jam di modul RTC dengan jam di laptop kamu saat proses upload.
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();

  // Menampilkan jam di Serial Monitor
  Serial.print("Jam saat ini: ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.println(now.second());

  // Mengubah waktu saat ini ke dalam format total menit dari jam 00:00 supaya gampang dibandingkan
  int waktuSekarang = now.hour() * 60 + now.minute();
  int waktuMulai   = jamHidup * 60 + menitHidup;
  int waktuSelesai = jamMati * 60 + menitMati;

  // Logika otomatis: Mendukung jadwal yang melewati tengah malam (misal nyala malam, mati pagi)
  bool kondisiNyala = false;
  if (waktuMulai < waktuSelesai) {
    kondisiNyala = (waktuSekarang >= waktuMulai && waktuSekarang < waktuSelesai);
  } else {
    // Jika jam nyala malam hari dan mati keesokan harinya (contoh: 18:00 sampai 05:30)
    kondisiNyala = (waktuSekarang >= waktuMulai || waktuSekarang < waktuSelesai);
  }

  if (kondisiNyala) {
    digitalWrite(relayPin, LOW);  // Lampu HIDUP (Active LOW)
  } else {
    digitalWrite(relayPin, HIGH); // Lampu MATI (Active LOW)
  }

  delay(1000); // Tunggu 1 detik sebelum mengecek jam lagi
}