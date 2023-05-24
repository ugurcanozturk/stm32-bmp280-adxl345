


#include "BMP280.h"


uint16_t dig_T1;        // Veri türleri datasheet'de belirtilme durumlarına göre seçilmiştir.
int16_t dig_T2, dig_T3; // Trimming parametrelerini ölçekleyip tutmak için.
int32_t tempRaw;
int16_t result_Buffer[10];
int buffer_Counter = 0;


void TrimRead(void){   // Trimming Paramater okuması yapılıyor.Alınan verilerin kalibrasyonunun doğru şekilde yapılmasını sağlıyor.

	uint8_t trimData[6];

	HAL_I2C_Mem_Read(&hi2c1, (BMP280_I2C_SD0_0 << 1 ), 0x88, 1, trimData, 6, 100);

      dig_T1 = (trimData[1] << 8) | trimData[0]; /* 16 bit tamsayı olarak tutulan Trimming parametrelerinin LSB ve MSB bitleri 8 bit kaydırılarak sola doğru ortaya anlamlı bir sayı çıkarılır.*/
      dig_T2 = (trimData[3] << 8) | trimData[2]; // Daha sonra oluşan bu değerler int16_t türünde değişkenlere atanır.
      dig_T3 = (trimData[5] << 8) | trimData[4];


}

int BMP280_ReadRaw(){  // Ham sıcaklık verisi okuması yapılır burada.

	uint8_t RawData[3];
	HAL_I2C_Mem_Read(&hi2c1,(BMP280_I2C_SD0_0 << 1), BMP280_TEMP_MSB_ADDR , 1, RawData, 3, 100);

	tempRaw = (RawData[0]<<12)|(RawData[1]<<4)|(RawData[2]>>4); // tempRaw değişkenine atamadan önce RawData'nın 3byte'ı birleştirilir.
}  /* BMP280 sıcaklık değerini 3 byte şeklinde depolar.MSB,LSB ve XLSB şeklinde bunların birleştirilme işlemi yapılır aslında.*/

int32_t t_fine;
int32_t BMP280_compensate_T_int32(int32_t adc_T)  // Okuması yapılan ham sıcaklık değerleri bu fonksiyon ile düzeltilir ve buna değer döndürülür.
{                                                 /* Bu fonksiyon üretici firmanın datasheet dosyasında paylaştığı ve kullanılmasını istediği fonksiyondur.*/
	int32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1)))>> 12) *((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}



void BMP280_Init(){  // Okuma yapabilmek için 0xF4 ve 0xF5 adresli registerlara gerekli ve istenilen değerler girilir.
                     // Bit ayarlamaları için hesaplamalar yapılmış ve hex karşılıkları o adreslere girilmiştir.
	uint8_t measure; // Gerekli bilgiler dökümantasyon kısmında paylaşılmıştır.
	measure = 0xE3;

	uint8_t standBy;
	standBy = 0x60;

	HAL_I2C_Mem_Write(&hi2c1, (BMP280_I2C_SD0_0 << 1), BMP280_CTRL_MEAS_ADDR, 1, &measure, 1, 100); // Sampling ayarı girildi.
	HAL_Delay(100);
	HAL_I2C_Mem_Write(&hi2c1, (BMP280_I2C_SD0_0 << 1), BMP280_CONFIG_ADDR, 1, &standBy, 1, 100); // StandBy 250 ms olarak ayarlandı.

}

void BMP280_BufferData(int data){ // Taskta istenen verilerin tutulması için bir buffer oluşturulmuştur.
                                  // Counter ve bu algoritma sayesinde taşma durumunda eski veriler silinip yerlerine yeni veriler ekleniyor.
	if(buffer_Counter == 10) {    // LIFO metodu da sağlanıyor bu algoritma ile.
		        for(uint8_t i = 0; i < 10 - 1; i++) {
		            result_Buffer[i] = result_Buffer[i+1];  // Taşma durumunda ise bir alt veriye düşüyor ve en eski olan siliniyor.
		        }
		        buffer_Counter--;
		    }
		    result_Buffer[buffer_Counter++] = data;  // Taşma durumuna olmadan önce sırayla veriler yerleşiyor
}


int32_t BMP280_IdCheck(){ // ID registerında bulunan değeri okuyabiliyor muyum diye oluşturduğum bir fonksiyon.

	uint8_t IdBuffer[1];
	HAL_StatusTypeDef tempValue;

	tempValue = HAL_I2C_Mem_Read(&hi2c1, (0x76<<1), 0xD0, 1,IdBuffer , 1, 100);

	if(tempValue != HAL_OK){

	}
	if(0x58 == IdBuffer[0]){
		return 1;
	}
	else{
		return 0;
	}

}

int16_t BMP280_I2C(){ // I2C adresi doğrulaması ve iletişim sağlanıp sağlanmadığının kontrolü.

	HAL_StatusTypeDef tempValue;
	tempValue = HAL_I2C_IsDeviceReady(&hi2c1, (0x76 << 1), 4, 100);

	if(tempValue == HAL_OK){
		return 1;
	}
	else{
		return 0;
	}
}



