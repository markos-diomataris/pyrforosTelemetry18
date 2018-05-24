#include <SoftwareSerial.h>
#include"data_state.h"
#include"protocol.h"



SoftwareSerial Serial_piccolo(9 /*RX*/, 10 /*TX*/);
SoftwareSerial Serial_gps(5 /*RX*/, 6 /*TX*/);
int filename_creator();
boolean SD_started = true;
Data_state state;
Protocol protocol;
File dataFile;
char filename[] = "LOGGER00.txt";

void setup() {
  /*
     initialize all serial comms
  */
  //  Serial.begin(115200); //for pro mini
  //  Serial_piccolo.begin(19200);
  //  Serial_gps.begin(19200);

  Serial.begin(9600); //for pro mini
  Serial_gps.begin(9600);
  Serial_piccolo.begin(9600);


  //    Serial_gps.listen();
  /*
     interrupt for piccolo
  */
  attachInterrupt(digitalPinToInterrupt(NEW_DATA_INT_PIN), interrupt_handler , RISING);
  /*
     init SD card
  */
  if (!SD.begin(SD_SELECT)) {
    //    Serial.println("SD begin failed");
    SD_started = false;
  }
  filename_creator();

}
/*
   in the main loop we are waiting for GPS update and
*/
int c;
void loop() {
  c = 0;
  if (!SD_started) {
    if (SD.begin(SD_SELECT)) {
      SD_started=true;
    }
  }
  /*
     check if we need to flush any of flip or flop buffers
  */
  if (state.need_to_flush == FLUSHFLIP) {
    dataFile = SD.open(filename, FILE_WRITE);
    dataFile.println("writing flip buffer");
    state.flush_to_SD(&dataFile, FLIP);
    dataFile.close();
    delay(10);
    state.need_to_flush = NOFLUSH;
  } else if (state.need_to_flush == FLUSHFLOP) {
    dataFile = SD.open(filename, FILE_WRITE);
    dataFile.println("writing flop buffer");
    state.flush_to_SD(&dataFile, FLOP);
    dataFile.close();
    delay(10);
    state.need_to_flush = NOFLUSH;
  }
  if (Serial.available()) {
    dataFile = SD.open(filename, FILE_WRITE);
    while (Serial.available() && c++ < 500) {
      dataFile.print((char)Serial.read());
    }
    dataFile.close();
    delay(10);
  }

  delay(100);
}

int filename_creator() {
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i / 10 + '0';
    filename[7] = i % 10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      dataFile = SD.open(filename, FILE_WRITE);
      Serial.println("file successfully created!");
      //dataFile.println(filename);
      break;  // leave the loop!
    }
  }
  dataFile.close();
  return 0;
}
