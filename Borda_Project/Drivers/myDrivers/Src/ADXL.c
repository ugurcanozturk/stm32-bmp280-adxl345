


#include "ADXL.h"




extern int16_t Raw_X, Raw_Y, Raw_Z;
float result_BufferX[10];
 float result_BufferY[10];
 float result_BufferZ[10];
int buffer_CounterX = 0;
int buffer_CounterY = 0;
int buffer_CounterZ = 0;


void ADXL345_Init()  // Değer okumak için gerekli ayarlar yapılıyor ve taskta verilen gerekliliklerin ayarlamaları yapılıyor.
{
     uint8_t data;
     data = 0xB;  // 1Hz olarak ayarlıyoruz bir ve ikinci bitlere bir yazıyoruz ayrıca measure aktif hala getiriyoruz.
     uint8_t dataFormat;
     dataFormat = 0x01; // +-4g ayarı
     HAL_I2C_Mem_Write(&hi2c1,(ADXL_I2C_ADDR_AD0 <<1), ADXL_POWER_CTL_ADDR, 1, &data, 1, 100); // Ölçüm yapan ve 1hz olacak şekilde ayarladık.

     HAL_I2C_Mem_Write(&hi2c1, (ADXL_I2C_ADDR_AD0<<1), ADXL_DATA_FORMAT_ADRR, 1, &dataFormat, 1, 100); // +-4g ile ölçüm yapma ayarını yaptık.
}

void ADXL345_Read() // Ham X,Y,Z eksenlerinin ham değerlerinin okunması ve verilerin birleştirilip oluşturulması.
{
	uint8_t buffer[6];


	HAL_I2C_Mem_Read(&hi2c1, (ADXL_I2C_ADDR_AD0 <<1), ADXL_DATAX0_ADDR  , 1, buffer, 6, 100);

   Raw_X = (int16_t)((buffer[1] << 8) | buffer[0]); // 8 bitlik iki veri yüksek ve düşük anlamlı olmalarına göre kaydırılarak 16 bitlik bir veri oluşturuluyor.
   Raw_Y = (int16_t)((buffer[3] << 8) | buffer[2]); // Bu işlem sonucunda ham değerler oluşturulmuş olur.
   Raw_Z = (int16_t)((buffer[5] << 8) | buffer[4]);
}

float ADXL345_BufferX(float data) // X ekseni değerleri taskta verilen gereklilikler ölçüsünde burada tutuluyor.
{                                 // LIFO metoduna uygun şekilde son gelen veri ilk çıkacak şekilde tutuluyor.
	  if(buffer_CounterX == 10) { // En eski veri siliniyor yeni veri geldikçe

	        for(uint8_t i = 0; i < 10 - 1; i++) {
	            result_BufferX[i] = result_BufferX[i+1]; // Silme ve kaydırma işlemi for döngüsü içinde sağlanıyor.
	        }
	        buffer_CounterX--;
	    }
	    result_BufferX[buffer_CounterX++] = data; // Taşma olmadığı durumda veriler sırayla yerleşiyor bu şekilde.
     }


float ADXL345_BufferY(float data){  // X ekseni buffer'ı için yapılan işlemlerin aynısı
	if(buffer_CounterY == 10) {

		        for(uint8_t i = 0; i < 10 - 1; i++) {
		            result_BufferY[i] = result_BufferY[i+1];
		        }
		        buffer_CounterY--;
		    }
		    result_BufferY[buffer_CounterY++] = data;

}

float ADXL345_BufferZ(float data){ // X bufferında durum ve algoritma açıklanmıştır.

	if(buffer_CounterZ == 10) {

		        for(uint8_t i = 0; i < 10 - 1; i++) {
		            result_BufferZ[i] = result_BufferZ[i+1];
		        }
		        buffer_CounterZ--;
		    }
		    result_BufferZ[buffer_CounterZ++] = data;
}



int16_t ADXL_I2C(){ // I2C adresinin doğru olup olmadığı ve iletişim kontrolü
	HAL_StatusTypeDef tempValue;
	tempValue = HAL_I2C_IsDeviceReady(&hi2c1, (ADXL_I2C_ADDR_AD0 << 1), 4, 100);

	if(tempValue == HAL_OK){
			return 1;
		}
		else{
			return 0;
		}
}

int32_t ADXL_IDCheck(){  // ID registerı okuma kontrolü.

    uint8_t idBuffer[1];

	HAL_StatusTypeDef tempValue;

    tempValue = HAL_I2C_Mem_Read(&hi2c1,(ADXL_I2C_ADDR_AD0<<1) , ADXL_ID_ADDR, 1, idBuffer, 1, 100);

	if(tempValue != HAL_OK){

	}
	if( 0xE5 == idBuffer[0]){
		return 1;
	}
	else{
		return 0;
	}
}




