

#ifndef MYDRIVERS_INC_BMP280_H_
#define MYDRIVERS_INC_BMP280_H_

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"


#define BMP280_I2C_SD0_0            (0x76)  /* SD0 pini low iken I2C adresi             */
#define BMP280_I2C_SD0_1            (0x77)  /* SD0 pini high iken I2C adresi            */
#define BMP280_ID_ADDR              (0xD0)  /* BMP280 ID register adresi                */
#define BMP280_RESET_ADDR           (0xE0)  /* BMP280 Reset register adresi             */
#define BMP280_STATUS_ADDR          (0xF3)  /* BMP280 Status register adresi            */
#define BMP280_CTRL_MEAS_ADDR       (0xF4)  /* BMP280 Control Measure register adresi   */
#define BMP280_CONFIG_ADDR          (0xF5)  /* BMP280'nin Config register adresi        */
#define BMP280_PRESS_MSB_ADDR       (0xF7)  /* BMP280'nin preassure MSB register adresi */
#define BMP280_PRESS_LSB_ADDR       (0xF8)  /**/
#define BMP280_PRESS_XLSB_ADDR      (0xF9)  /**/
#define BMP280_TEMP_MSB_ADDR        (0xFA)  /**/
#define BMP280_TEMP_LSB_ADDR        (0xFB)  /**/
#define BMP280_TEMP_XLSB_ADDR       (0xFC)  /**/

extern I2C_HandleTypeDef hi2c1;



int32_t BMP280_IdCheck();  // BMP280'nin ID registerında doğru değeri okuyabiliyormuyuz diye oluşturduğum fonksiyon.
int16_t BMP280_I2C();      // BMP280'nin I2C adresini kontrol ettiğim fonksiyon.
void BMP280_Init();        // BMP280'den verileri okuyabilmek için gerekli register-bit ayarlamalarının yapıldığı fonksiyon.
void TrimRead(void);       // BMP280'nin Trimming Parametrelerini aldığım fonksiyon.
int32_t BMP280_compensate_T_int32(int32_t adc_T);  // Ham sıcaklık verisini oluşturan default üretici firmanın verdiği fonksiyon.
void BMP280_BufferData(int data);  // Task'ta istenen verileri tutmak için oluşturduğum buffer fonksiyon.

#endif /* MYDRIVERS_INC_BMP280_H_ */
