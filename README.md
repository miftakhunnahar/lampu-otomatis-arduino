# bahan-bahan:
1. arduino nano
2. rtc DS3231
3. relay 5v 1 chanel output 250v
4. kabel jumper

# cara pemasangan
  Sambungan Pin (Wiring) ke Arduino Nano
   1. Modul RTC DS3231 (Jam Digital):
     a. VCC sambungkan ke pin 3V3 di Arduino.
     b. GND sambungkan ke pin GND.
     c. SDA sambungkan ke pin A4 (jalur komunikasi data I2C).
     d. SCL sambungkan ke pin A5 (jalur clock I2C).
   2. Modul Relay 1-Channel:
      a. VCC / DC+ sambungkan ke pin 5V di Arduino.
      b. GND / DC- sambungkan ke pin GND (Nano memiliki dua pin GND, gunakan salah satu yang kosong).
      c. IN sambungkan ke pin D8 (pin digital pembawa sinyal sakelar).
