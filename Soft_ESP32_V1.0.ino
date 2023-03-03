#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else
#include "USB.h"

#if ARDUINO_USB_CDC_ON_BOOT
#define LSerial Serial0   //UART0 
#define RSerial Serial1   //UART1
#define USBSerial Serial  //USB
#else
#define HWSerial Serial
USBCDC USBSerial;
#endif

byte valor = 0;
String hola = "EuroPie";


static void usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
  if(event_base == ARDUINO_USB_EVENTS){
    arduino_usb_event_data_t * data = (arduino_usb_event_data_t*)event_data;
    switch (event_id){
      case ARDUINO_USB_STARTED_EVENT:
        HWSerial.println("USB PLUGGED");
        break;
      case ARDUINO_USB_STOPPED_EVENT:
        HWSerial.println("USB UNPLUGGED");
        break;
      case ARDUINO_USB_SUSPEND_EVENT:
        HWSerial.printf("USB SUSPENDED: remote_wakeup_en: %u\n", data->suspend.remote_wakeup_en);
        break;
      case ARDUINO_USB_RESUME_EVENT:
        HWSerial.println("USB RESUMED");
        break;
      
      default:
        break;
    }
  } else if(event_base == ARDUINO_USB_CDC_EVENTS){
    arduino_usb_cdc_event_data_t * data = (arduino_usb_cdc_event_data_t*)event_data;
    switch (event_id){
      case ARDUINO_USB_CDC_CONNECTED_EVENT:
        HWSerial.println("CDC CONNECTED");
        break;
      case ARDUINO_USB_CDC_DISCONNECTED_EVENT:
        HWSerial.println("CDC DISCONNECTED");
        break;
      case ARDUINO_USB_CDC_LINE_STATE_EVENT:
        HWSerial.printf("CDC LINE STATE: dtr: %u, rts: %u\n", data->line_state.dtr, data->line_state.rts);
        break;
      case ARDUINO_USB_CDC_LINE_CODING_EVENT:
        HWSerial.printf("CDC LINE CODING: bit_rate: %u, data_bits: %u, stop_bits: %u, parity: %u\n", data->line_coding.bit_rate, data->line_coding.data_bits, data->line_coding.stop_bits, data->line_coding.parity);
        break;
      case ARDUINO_USB_CDC_RX_EVENT:
        HWSerial.printf("CDC RX [%u]:", data->rx.len);
        {
            uint8_t buf[data->rx.len];
            size_t len = USBSerial.read(buf, data->rx.len);
            HWSerial.write(buf, len);
        }
        HWSerial.println();
        break;
       case ARDUINO_USB_CDC_RX_OVERFLOW_EVENT:
        HWSerial.printf("CDC RX Overflow of %d bytes", data->rx_overflow.dropped_bytes);
        break;
     
      default:
        break;
    }
  }
}


void setup() {
  HWSerial.begin(115200);
  HWSerial.setDebugOutput(true);
  
  USB.onEvent(usbEventCallback);
  USBSerial.onEvent(usbEventCallback);
  
  USBSerial.begin();
  USB.begin();
  
  LSerial.begin(962100);  //usa pines TX RX para UART0 
  RSerial.begin(962100, SERIAL_8N1, 17,18); //defino los GPIO para UART1

  USBSerial.setSpeed(USB_SPEED_HIGH); // pasa a usar velocidad USB 2.0 

  xTaskCreatePinnedToCore(enviarData,"enviar",10000,NULL,0,&enviar,0);  //esto seria para usar el segundo core (comentar para deshabilitar)

  //USBSerial.write(hola);
}


void enviarData (int val) {
  USBSerial.write(val);
}


void loop() {
  while (USBSerial.read() == 0){
    //queda a la espera del software de la PC
  }
  
  LSerial.write(1);
  RSerial.write(1);

  for (int i = 0; i <= 1600; i++){
    if (LSerial.available() != 0){
    valor = LSerial.read();
    enviarData(valor);
    }
    
    if (RSerial.available() != 0){
    valor = RSerial.read();
    enviarData(valor);
    }
  }
}
#endif /* ARDUINO_USB_MODE */
