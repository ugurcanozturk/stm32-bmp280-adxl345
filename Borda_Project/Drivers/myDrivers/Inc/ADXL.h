

#ifndef MYDRIVERS_INC_ADXL_H_
#define MYDRIVERS_INC_ADXL_H_
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"

#define ADXL_ID_ADDR              (0X00) // Device ID
#define ADXL_I2C_ADDR_AD0         (0x53) // SD0 pin is low
#define ADXL_I2C_ADDR_AD1         (0x1D) // SD0 pin is high
#define ADXL_THRESH_TAP           (0X1D) // Tap threshold
#define ADXL_OFSX_ADDR            (0x1E) // X axis offset
#define ADXL_OFSY_ADDR            (0x1F) // Y axis offset
#define ADXL_OFSZ_ADDR            (0x20) // Z axis offset
#define ADXL_DUR_ADDR             (0x21) // Tap duration
#define ADXL_LATENT_ADDR          (0x22) // Tap latency
#define ADXL_WINDOW_ADDR          (0x23) // Tap window
#define ADXL_THRESH_ACT_ADDR      (0x24) // Activity threshold
#define ADXL_THRESH_INACT_ADDR    (0x25) // Inactivity threshold
#define ADXL_TIME_INACT_ADDR      (0x26) // Inactivity time
#define ADXL_ACT_INACT_CTL_ADDR   (0x27) // Axis enable control for ACT/INACT
#define ADXL_THRESH_FF _ADDR      (0x28) // Free-fall threshold
#define ADXL_TIME_FF_ADDR         (0x29) // Free-fall time
#define ADXL_TAP_AXES_ADDR        (0x2A) // Axis control for Tap/Double Tap
#define ADXL_ACT_TAP_STATUS_ADDR  (0x2B) // Source of Tap/Double Tap
#define ADXL_BW_RATE_ADDR         (0x2C) // Data Rate and Power Mode control
#define ADXL_POWER_CTL_ADDR       (0x2D) // Power Save features control
#define ADXL_INT_ENABLE_ADDR      (0x2E) // Interrupt enable control
#define ADXL_INT_MAP_ADDR         (0x2F) // Interrupt mapping control
#define ADXL_INT_SOURCE_ADDR      (0x30) // Source of interrupts
#define ADXL_DATA_FORMAT_ADRR     (0x31) // Data format control
#define ADXL_DATAX0_ADDR          (0x32) // X axis data 0
#define ADXL_DATAX1_ADDR          (0x33) // X axis data 1
#define ADXL_DATAY0_ADDR          (0x34) // Y axis data 0
#define ADXL_DATAY1_ADDR          (0x35) // Y axis data 1
#define ADXL_DATAZ0_ADDR          (0x36) // Z axis data 0
#define ADXL_DATAZ1_ADDR          (0x37) // Z axis data 1
#define ADXL_FIFO_CTL_ADDR        (0x38) // FIFO control
#define ADXL_FIFO_STATUS_ADDR     (0x39) // FIFO status




extern I2C_HandleTypeDef hi2c1;




void ADXL345_Init();  // ADXL345'den değer okuyabilmek için gerekli ayarlamaların yapıldığı fonksiyon
void ADXL345_Read();  // Ham değerlerin okunduğu fonksiyon
float ADXL345_BufferX(float data); // X ekseni değerlerinin buffer içinde tutulduğu fonksiyon
float ADXL345_BufferY(float data); // Y ekseni değerlerinin buffer içinde tutulduğu fonksiyon
float ADXL345_BufferZ(float data); // Z ekseni değerlerinin buffer içinde tutulduğu fonksiyon


 int16_t ADXL_I2C(); // I2C adresi üzerinden iletişime geçilip geçilmediğinin kontrol edildiği fonksiyon
 int32_t ADXL_IDCheck(); // ID registerından gerekli değeri okunmasının kontrol edildiği fonksiyon.


#endif /* MYDRIVERS_INC_ADXL_H_ */
