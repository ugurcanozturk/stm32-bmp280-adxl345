# stm32-bmp280-adxl345
 bmp280 and adxl345 drivers for stm32
 
 The raw data obtained from BMP280 through I2C communication using STM32F407 has been converted into temperature data. 
 Additionally, the acquired data has been stored in a buffer following the Last-In-First-Out (LIFO) method.
 
Additionally, the raw data obtained from the ADXL345 3-axis accelerometer sensor has been converted into the mg/LSB unit through I2C communication. 
It is then stored in a buffer following the Last-In-First-Out (LIFO) method. You can modify the size of the buffer according to your own usage.
