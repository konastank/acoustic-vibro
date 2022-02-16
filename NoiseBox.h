/*---Unmute following #define to debug in Arduino IDE----*/
//#define DEBUG

/*----Select MASTER/DISPLAY before program each controller----*/

#define MASTER_SIDE_CONTROLLER 
//#define DISPLAY_SIDE_CONTROLLER 

/*------------------------------------------------------------*/

#include "Arduino.h"
#include "Nextion.h"
#include "fix_fft.h"
#include "Wire.h"

#define SPECTRUM_SAMPLES 128
#define SPECTRUM_PIN A3
#define ADDRESS 8

typedef enum CURRENT_PAGE{
	_DB_PAGE,
	_SPECTRUM_PAGE,
	_VIBRO_PAGE,
	_MENU_PAGE
} _CURRENT_PAGE;

class NoiseBox{
	private:
    	const int sampleWindow = 25; // Samp    	
    	static uint32_t db_values[10];
    	static uint32_t barht[128];
	    void DbMeasure();
	    void SpectrumAnalyzer();
	    void VibroAnalyzer();
	    void DataTransferToSlave(uint32_t data[], _CURRENT_PAGE _PAGE);    	
	  	static int32_t page_value;
	  	static uint8_t page_value_8;
    public:
    	NoiseBox();
    	void PageListenerMaster();  
    	static void PageListenerSlave();
    	static void ReceiveDataFromMaster(int empty);
    	void DataTransferToScreen();
    	uint8_t temp[8] = {0}; 
    	#ifdef DEBUG  	
    		static int32_t DEBUG_page_value;
    	#endif
};
