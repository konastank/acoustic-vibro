#include "NoiseBox.h"

_CURRENT_PAGE PAGE;

uint32_t NoiseBox::db_values[10];
uint32_t NoiseBox::barht[128];
int32_t NoiseBox::page_value = 25;
#ifdef DEBUG
  int32_t NoiseBox::DEBUG_page_value;
#endif  
uint8_t NoiseBox::page_value_8;

NoiseBox::NoiseBox(){
  #ifdef DISPLAY_SIDE_CONTROLLER
    nexInit(115200);
    Wire.begin(8);
    Wire.onRequest(PageListenerSlave); 
    Wire.onReceive(ReceiveDataFromMaster);
  #endif

  #ifdef MASTER_SIDE_CONTROLLER
    Wire.begin();
  #endif
}

//---------------------------SLAVE(DISPLAY) SIDE-----------------------------//

#ifdef DISPLAY_SIDE_CONTROLLER
  NexPage MENU_PAGE(0, 0, "page3");
  NexPage DB_PAGE(0, 0, "page0");
  NexPage VIBRO_PAGE(0,0,"page2");
  NexPage SPECTRUM_PAGE(0,0,"page1");

  NexVariable NexPAGE = NexVariable(0,11,"pageval",&MENU_PAGE);
  NexNumber n0 = NexNumber(0,42,"n0",&DB_PAGE);
  NexNumber n1 = NexNumber(0,39,"n10",&DB_PAGE); // yea, there should be 10
  NexNumber n2 = NexNumber(0,31,"n1",&DB_PAGE);
  NexNumber n3 = NexNumber(0,32,"n2",&DB_PAGE);
  NexNumber n4 = NexNumber(0,33,"n3",&DB_PAGE);
  NexNumber n5 = NexNumber(0,34,"n4",&DB_PAGE);
  NexNumber n6 = NexNumber(0,35,"n5",&DB_PAGE);
  NexNumber n7 = NexNumber(0,36,"n6",&DB_PAGE);
  NexNumber n8 = NexNumber(0,37,"n7",&DB_PAGE);
  NexNumber n9 = NexNumber(0,38,"n8",&DB_PAGE);

  NexNumber n0_1 = NexNumber(1,19,"n0_1",&SPECTRUM_PAGE);
  NexNumber n1_1 = NexNumber(1,20,"n1_1",&SPECTRUM_PAGE); 
  NexNumber n2_1 = NexNumber(1,21,"n2_1",&SPECTRUM_PAGE);
  NexNumber n3_1 = NexNumber(1,22,"n3_1",&SPECTRUM_PAGE);
  NexNumber n4_1 = NexNumber(1,23,"n4_1",&SPECTRUM_PAGE);
  NexNumber n5_1 = NexNumber(1,24,"n5_1",&SPECTRUM_PAGE);
  NexNumber n6_1 = NexNumber(1,25,"n6_1",&SPECTRUM_PAGE);
  NexNumber n7_1 = NexNumber(1,26,"n7_1",&SPECTRUM_PAGE);
  NexNumber n8_1 = NexNumber(1,27,"n8_1",&SPECTRUM_PAGE);
  NexNumber n9_1 = NexNumber(1,28,"n9_1",&SPECTRUM_PAGE);
  NexNumber n10_1 = NexNumber(1,29,"n10_1",&SPECTRUM_PAGE);
  NexNumber n11_1 = NexNumber(1,30,"n11_1",&SPECTRUM_PAGE);
  NexNumber n12_1 = NexNumber(1,31,"n12_1",&SPECTRUM_PAGE);
  NexNumber n13_1 = NexNumber(1,32,"n13_1",&SPECTRUM_PAGE);
  NexNumber n14_1 = NexNumber(1,33,"n14_1",&SPECTRUM_PAGE);
  NexNumber n15_1 = NexNumber(1,34,"n15_1",&SPECTRUM_PAGE);
  NexNumber n16_1 = NexNumber(1,35,"n16_1",&SPECTRUM_PAGE);


  void NoiseBox::ReceiveDataFromMaster(int empty){
    uint8_t buffer_value;
    uint32_t additional_value;
    uint8_t destination;
    destination = Wire.read();  
    while (0 < Wire.available()){
      if (destination == 10){
        for (int i = 0; i < destination; i++){
          db_values[i] = Wire.read();
                  #ifdef DEBUG
                    Serial.print("db_value first step = ");
                    Serial.println(db_values[i]);
                  #endif
          db_values[i] <<= 8;
                  #ifdef DEBUG
                    Serial.print("db_value second step = ");
                    Serial.println(db_values[i]);
                  #endif
          additional_value = db_values[i] | 255;
                  #ifdef DEBUG
                    Serial.print("additional value third step = ");
                    Serial.println(db_values[i]);
                  #endif
          buffer_value = Wire.read();
                  #ifdef DEBUG
                    Serial.print("buffer_value fourth step = ");
                    Serial.println(db_values[i]);
                  #endif
          db_values[i] |= buffer_value;
                  #ifdef DEBUG
                    Serial.print("db_value fifth step = ");
                    Serial.println(db_values[i]);
                  #endif
          db_values[i] &= additional_value;
                  #ifdef DEBUG
                    Serial.print("db_value sixth step = ");
                    Serial.println(db_values[i]);
                  #endif
        }
        for (int i = 0; i < destination; i++){
        Serial.println(db_values[i]);
      }
      }
      else if (destination == 17){
        for (int i = 0; i < destination; i++){
          barht[i] = Wire.read();
          barht[i] << 8;
          additional_value = barht[i] | 255;
          buffer_value = Wire.read();
          barht[i] |= buffer_value;
          barht[i] &= additional_value;
        }
      }
    }
  }
  
  void NoiseBox::DataTransferToScreen(){
    NexPAGE.getValue(&page_value);
    if (page_value == 0){
      n0.setValue(db_values[0]);
      n1.setValue(db_values[1]);
      n2.setValue(db_values[2]);
      n3.setValue(db_values[3]);
      n4.setValue(db_values[4]);
      n5.setValue(db_values[5]);
      n6.setValue(db_values[6]);
      n7.setValue(db_values[7]);
      n8.setValue(db_values[8]);
      n9.setValue(db_values[9]);
    }
    else if (page_value == 1){
      n0_1.setValue(barht[1]);
      n1_1.setValue(barht[2]);
      n2_1.setValue(barht[3]);
      n3_1.setValue(barht[4]);
      n4_1.setValue(barht[5]);
      n5_1.setValue(barht[6]);
      n6_1.setValue(barht[7]);
      n7_1.setValue(barht[8]);
      n8_1.setValue(barht[9]);
      n9_1.setValue(barht[10]);
      n10_1.setValue(barht[11]);
      n11_1.setValue(barht[12]);
      n12_1.setValue(barht[13]);
      n13_1.setValue(barht[14]);
      n14_1.setValue(barht[15]);
      n15_1.setValue(barht[16]);
      n16_1.setValue(barht[17]);
    }
  }

  void NoiseBox::PageListenerSlave(){
    #ifdef DEBUG
      DEBUG_page_value = page_value;
      Serial.print("page_value: ");
      Serial.println(DEBUG_page_value);
    #endif
      page_value_8 = page_value;      
      Wire.write(page_value_8);
     
  }

#endif

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
//----------------------^----END OF SLAVE(DISPLAY) SIDE-----^-----------------------//
//----------------------------------------------------------------------------------//
//-----------------------------V---MASTER SIDE----V---------------------------------//
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv//

#ifdef MASTER_SIDE_CONTROLLER

  void NoiseBox::DbMeasure(){
  	unsigned int sample;
  	float volts = 0;
  	float dB = 0;
    unsigned int peakToPeak = 0; 
    for (int j = 1; j < 10; j++){
      for (int i = 0; i < 10; i++){  
        peakToPeak = 0; 
        unsigned long startMillis= millis();  // Start of sample window
        unsigned int signalMax = 0;
        unsigned int signalMin = 700;
       
         while (millis() - startMillis < sampleWindow)
          {  
            sample = analogRead(j);
            if (sample < 700)  // toss out spurious readings
              {
                if (sample > signalMax)
                  {
                    signalMax = sample;  // save just the max levels
                  }
                else if (sample < signalMin)
                 {
                    signalMin = sample;  // save just the min levels
                 }
              }
          }
        peakToPeak = signalMax - signalMin;
        volts = (peakToPeak*3.3)/1024;
        dB += 20*log(volts)+100;
      }
      dB /= 10;
        if (dB > 30 && dB <= 38) dB *= 1.25;
          else if (dB > 38 && dB < 40) dB *= 1.2;
          else if (dB >= 40 && dB < 40) dB *= 1.1;
          else if (dB >= 50 && dB <= 60) dB *= 1.05;
          else if (dB > 60 && dB < 72) dB *= 0.95;
          else if (dB >= 72 && dB < 76) dB *= 0.78;
          else if (dB >= 76) dB *= 0.85;
      db_values[j] = dB*100;
    } 
    #ifdef DEBUG  
    for (int i = 0; i < 10; i++){
      db_values[i] = 9999;
        Serial.println(db_values[i]);
      }
    #endif
    DataTransferToSlave(db_values,_DB_PAGE);
  }

  void NoiseBox::SpectrumAnalyzer(){
    char im[128];
    char data[128];
    int val,j,i;

    for(i = 0; i < SPECTRUM_SAMPLES; i++)
    {
      val = analogRead(SPECTRUM_PIN); // 0-1023
      data[i] = (char)(val/3 - 62); // store as char
      im[i] = 0; // init all as 0
    }

    fix_fft(data, im, 7, 0);

    for(i = 0; i < 128/2; i++)
    {
      barht[i] = (int)sqrt(data[i] * data[i] + im[i] * im[i]);
    }

    for(i = 0,j = 0; i < 128/2; i++, j += 2)
    {
      barht[i] = (barht[j] + barht[j + 1])*2 + 2;
    }

    DataTransferToSlave(barht,_SPECTRUM_PAGE);
  }

  void NoiseBox::VibroAnalyzer(){
   /* int sensor_value = 0;
    unsigned long startMillis= millis();  // Start of sample window
      unsigned int signalMax = 0;
      unsigned int signalMin = 1024;
      peakToPeak = 0; 
       while (millis() - startMillis < sampleWindow)
        {  
          sample = analogRead(VIBRO_PIN);
          if (sample < 1024)  // toss out spurious readings
            {
              if (sample > signalMax)
                {
                  signalMax = sample;  // save just the max levels
                }
              else if (sample < signalMin)
               {
                  signalMin = sample;  // save just the min levels
               }
            }
        }
      peakToPeak = signalMax - signalMin;
      amplitude = peakToPeak/2;
      center = signalMax - amplitude;
      frequency = 0;
      bool first_point,second_point = false;
      startMillis= millis();
      while ((millis() - startMillis) < 1000){
        sample = analogRead(VIBRO_PIN);
        if (sample > center) first_point = true;
        if (sample < center && first_point) second_point = true;
        if (sample > center && second_point) {
          first_point = false;
          second_point = false;
          frequency++;   
        }
      }
      speed_value = amplitude * frequency;
    */
  }

  void NoiseBox::DataTransferToSlave(uint32_t data[], _CURRENT_PAGE _PAGE){
    uint8_t size;
    uint8_t buffer_value;
    uint32_t additional_value;
    switch (_PAGE){
      case _DB_PAGE:
        size = 10;
        break;
      case _SPECTRUM_PAGE:
        size = 17;
        break;
      case _VIBRO_PAGE:
        size  = 3;
        break;
      default:
        break;
    }


    Wire.beginTransmission(ADDRESS); 
    Wire.write(size);
    for (int i = 0; i < size; i++){
        buffer_value = data[i] >> 8;
        #ifdef DEBUG
          Serial.print("buffer_value(8bit) left side = ");
          Serial.println(buffer_value);
        #endif
        Wire.write(buffer_value);
        buffer_value = 0;
        buffer_value |= data[i];
         #ifdef DEBUG
          Serial.print("buffer_value(8bit) right side = ");
          Serial.println(buffer_value);
        #endif
        Wire.write(buffer_value);
    }
    Wire.endTransmission(); 
  }


  void NoiseBox::PageListenerMaster(){  
    Wire.requestFrom(ADDRESS, 1);
    while(Wire.available()) page_value = Wire.read();
    #ifdef DEBUG
      DEBUG_page_value = page_value;
      Serial.print("page_value: ");
      Serial.println(DEBUG_page_value);
    #endif

      switch (page_value){
        case 0: 
          PAGE=_DB_PAGE;
          break;
        case 1:
          PAGE = _SPECTRUM_PAGE;
          break;
        case 2:
          PAGE = _VIBRO_PAGE;
          break;
        case 3:
          PAGE = _MENU_PAGE;
          break;
        default:
          break;
      }

      switch (PAGE){
        case _DB_PAGE:
          DbMeasure();
          break;
        case _SPECTRUM_PAGE:
          SpectrumAnalyzer();
          break;
        case _VIBRO_PAGE:
          VibroAnalyzer();
          break;
        default:
          break;


      }

  }
#endif
//---------------------------END OF MASTER SIDE-----------------------------//

/*#include <iostream>
int a[3] = {448771,448771, 448771};
int b[3] = {0};
short c = 0;
int d = 0;
int e =0;
int main() {
for (int i = 0; i < 3; i++){
  c = a[i] >> 16;
  //std::cout << a[i];
  d = c;
  c &= 0;
  c = c | a[i];
  d = d << 16;
  e = d | 65535;
  d |= c;
  d &= e;
  b[i] = d;
  d &= 0;
  e &= 0;
}
  for (int i = 0; i < 3; i++){
  std::cout << b[i] << ' ';
    }
    return 0;
}*/