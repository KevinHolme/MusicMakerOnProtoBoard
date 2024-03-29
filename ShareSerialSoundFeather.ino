#include <SPI.h>
#include <Wire.h>
#define LED 13
#include <SD.h>
#include <Adafruit_VS1053.h>
//#include <EasyTransferI2C.h>
#include <EasyTransfer.h>

//==============================================================EasyTransfer ==========
//create object
//EasyTransferI2C ET; 
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t data1;
 };

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

//----------------------------------------Time--------------
unsigned long CurrentMillis = 0;
unsigned long PreviousDisplayMillis = 0;
unsigned long PreviousReadMillis = 0;
unsigned long PreviousReceiveMillis = 0;
unsigned long PreviousSendMillis = 0;
unsigned long PreviousHistoryMillis = 0;
unsigned long PreviousPlayMillis = 0;
unsigned long PreviousCheckMillis = 0;
unsigned long PreviousStanceMillis = 0;
unsigned long PreviousMoveMillis = 0;
unsigned long PreviousShowMillis = 0;
unsigned long PreviousLoopMillis = 0;
unsigned long PreviousRadioMillis = 0;
unsigned long ShowTime = 0;
const long DisplayInterval = 1000;
const long ReadInterval = 50;
const long ReceiveInterval = 50;
const long SendInterval = 250; 
const long ResetHistoryInterval = 250; 
const long PlayInterval = 100; 
const long CheckInterval = 500; 
const long StanceInterval = 100; 
const long MoveInterval = 75; 
const long LoopInterval = 100;
const long ShowInterval = 75; 
const long RadioInterval = 75; 
//-----------------------------Constant (Never Change)---------------------------

//============================== variable (will Change)==============
int IncomingInt;
int whis = 0;
int whishist = 0;
int song = 0;
int songhist = 0;
int sad = 0;
int sadhist = 0;
int ala = 0;
int alahist = 0;
int sngalo = 0;
int sngalohist = 0;
int chat = 0;
int chathist = 0;
int ack = 0;
int hum = 0;
int humhist = 0;
int ackhist = 0;
int razz = 0;
int razzhist = 0;
int scrm = 0;
int scrmhist = 0;
int TCode =0;
int CurrentSong = 0;
int LastSong = 0;
int IncomingHist = 0;
int Int1 = 0;
int Int2 = 0;
int Int3 = 0;
int Show = 0;
String Recieved;
String Incoming1;
String Incoming2;
String Incoming3;
String Incoming4;
String Incoming5;
String Incoming6;
String Incoming7;
String Incoming8;
String Incoming9;
String IncomingMsg;



//==================================================Sound ===============================
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
#define VS1053_CS       6     // VS1053 chip select pin (output)
  #define VS1053_DCS     10     // VS1053 Data/command select pin (output)
  #define CARDCS          5     // Card chip select pin
  // DREQ should be an Int pin *if possible* (not possible on 32u4)
  #define VS1053_DREQ     9     // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);
//------------------------------------------------------------------------------------------------
//==========================================================Setup=============================


void setup(){
 delay(500);
  Serial.begin(115200);
  Serial1.begin(115200);
pinMode(8, INPUT_PULLUP);

  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 

   ET.begin(details(mydata), &Serial1);
  //define handler function on receiving data

//========================================Sound===========================
 
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }

  Serial.println(F("VS1053 found"));
 
 // musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
  
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");
 //===========================================================Random seed gen==================== 
 uint32_t seed = 0;  // Generate random see start
  for ( uint8_t i = 10 ; i ; i-- ) {
    seed = ( seed << 5 ) + ( analogRead( 0 ) * 3 );
  }
  randomSeed( seed );  //set random seed
  Serial.println("Adafruit VS1053 Library Test");
  Serial.print("RandomSeed value = ");
  Serial.println(seed); 
  
  
  
//list files
  printDirectory(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

 musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  Serial.println(F("Playing full track 001"));
  musicPlayer.playFullFile("track001.mp3");

  Serial.println(F("Playing track 002"));
  musicPlayer.startPlayingFile("track002.mp3");
//musicPlayer.playFullFile("sad/sad4.mp3");
//musicPlayer.playFullFile("track001.mp3");
  
}
 
//==============================================Random Song====================
void RandSong(){


  do {
   song = random(4);
   } while (song == songhist);
   songhist = song;
   
   Serial.println(" Song " );
   delay(100);
    Serial.println(song); 
    delay(100);
      switch(song){
 case 0:
  Serial.println(" 0 " );
       
       musicPlayer.startPlayingFile("Songs/song1.mp3");
       break;
case 1:
 Serial.println(" 1 " );
       musicPlayer.startPlayingFile("Songs/song2.mp3");
       break;
case 2:
 Serial.println(" 2 " );
       musicPlayer.startPlayingFile("Songs/song3.mp3");
       break;
case 3:
 Serial.println(" 3 " );
       musicPlayer.startPlayingFile("Songs/song4.mp3");
       break;
      }
}



//==============================================Random Razzberry====================
void RandRazz(){
   do {
   razz = random(20);
   } while (razz == razzhist);
   razzhist = razz;
   
   Serial.println(" Razzberry " );
    Serial.println(razz);
  switch(razz){  
 case 0:
        musicPlayer.playFullFile("Razz/razz1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Razz/razz2.mp3");
       break;
 case 2:
        musicPlayer.playFullFile("Razz/razz3.mp3"); 
       break; 
 case 3:
       musicPlayer.playFullFile("Razz/razz4.mp3");
       break; 
 case 4:
        musicPlayer.playFullFile("Razz/razz5.mp3");
       break; 
 case 5:
        musicPlayer.playFullFile("Razz/razz6.mp3"); 
       break;  
 case 6:
        musicPlayer.playFullFile("Razz/razz7.mp3"); 
       break; 
 case 7:
        musicPlayer.playFullFile("Razz/razz8.mp3"); 
       break;  
 case 8:
       musicPlayer.playFullFile("Razz/razz9.mp3");
       break;  
 case 9:
        musicPlayer.playFullFile("Razz/razz10.mp3"); 
       break; 
 case 10:
        musicPlayer.playFullFile("Razz/razz11.mp3");
       break; 
 case 11:
       musicPlayer.playFullFile("Razz/razz12.mp3");
       break; 
  case 12:
        musicPlayer.playFullFile("Razz/razz13.mp3"); 
       break; 
  case 13:
        musicPlayer.playFullFile("Razz/razz14.mp3");
       break; 
 case 14:
        musicPlayer.playFullFile("Razz/razz15.mp3");
       break;  
 case 15:
        musicPlayer.playFullFile("Razz/razz16.mp3"); 
       break;                                                                                                                                                                                                                                                                                                                
case 16:
        musicPlayer.playFullFile("Razz/razz17.mp3"); 
       break;                                                                                                                                                                                                                                                                                                                
case 17:
        musicPlayer.playFullFile("Razz/razz18.mp3"); 
       break;                                                                                                                                                                                                                                                                                                                
case 18:
        musicPlayer.playFullFile("Razz/razz19.mp3"); 
       break;                                                                                                                                                                                                                                                                                                                
case 19:
        musicPlayer.playFullFile("Razz/razz20.mp3"); 
       break;                                                                                                                                                                                                                                                                                                                
      }
}

//==============================================Random Scream====================
void RandScream(){
   do {
   scrm = random(11);
   } while (scrm == scrmhist);
   scrmhist = scrm;
   
   Serial.println(" Scream " );
    Serial.println(scrm);
  switch(scrm){  
 case 0:
        musicPlayer.playFullFile("Scream/scrm1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Scream/scrm2.mp3");
       break;
 case 2:
       musicPlayer.playFullFile("Scream/scrm3.mp3");
       break; 
 case 3:
      musicPlayer.playFullFile("Scream/scrm4.mp3");
       break; 
 case 4:
       musicPlayer.playFullFile("Scream/scrm5.mp3");
       break; 
 case 5:
       musicPlayer.playFullFile("Scream/scrm6.mp3");
       break;  
 case 6:
       musicPlayer.playFullFile("Scream/scrm7.mp3");
       break; 
 case 7:
       musicPlayer.playFullFile("Scream/scrm8.mp3");
       break;  
 case 8:
       musicPlayer.playFullFile("Scream/scrm9.mp3");
       break;  
 case 9:
       musicPlayer.playFullFile("Scream/scrm10.mp3");
       break; 
 case 10:
        musicPlayer.playFullFile("Scream/scrm11.mp3");
       break; 
                                                                                                                                                                                                                                                                                       
      }
}

//==============================================Random Chat====================
void RandChatty(){
   do {
   chat = random(20);
   } while (chat == chathist);
   chathist = chat;
   
   Serial.println(" Chatty " );
    Serial.println(chat);
  switch(scrm){  
 case 0:
        musicPlayer.playFullFile("Chat/chat1.mp3");
       break;
 case 1:
      musicPlayer.playFullFile("Chat/chat2.mp3");
       break;
 case 2:
      musicPlayer.playFullFile("Chat/chat3.mp3");
       break; 
 case 3:
      musicPlayer.playFullFile("Chat/chat4.mp3");
       break; 
 case 4:
       musicPlayer.playFullFile("Chat/chat5.mp3");
       break; 
 case 5:
       musicPlayer.playFullFile("Chat/chat6.mp3");
       break;  
 case 6:
       musicPlayer.playFullFile("Chat/chat7.mp3");
       break; 
 case 7:
       musicPlayer.playFullFile("Chat/chat8.mp3");
       break;  
 case 8:
       musicPlayer.playFullFile("Chat/chat9.mp3");
       break;  
 case 9:
       musicPlayer.playFullFile("Chat/chat10.mp3");
       break; 
case 10:
        musicPlayer.playFullFile("chat/chat11.mp3");
       break; 
case 11:
        musicPlayer.playFullFile("Chat/chat12.mp3");
       break;  
case 12:
        musicPlayer.playFullFile("Chat/chat13.mp3");
       break; 
case 13:
        musicPlayer.playFullFile("chat/chat14.mp3");
       break; 
case 14:
        musicPlayer.playFullFile("Chat/chat15.mp3");
       break;  
case 15:
        musicPlayer.playFullFile("Chat/chat16.mp3");
       break; 
case 16:
        musicPlayer.playFullFile("chat/chat17.mp3");
       break; 
case 17:
        musicPlayer.playFullFile("Chat/chat18.mp3");
       break;  
case 18:
        musicPlayer.playFullFile("Chat/chat19.mp3");
       break;  
case 19:
        musicPlayer.playFullFile("chat/chat20.mp3");
       break; 
                                                                                                                                                                  
      }
}



//==============================================Random Whistle====================
void RandWhistle(){
  
   do {
   whis = random(20);
   } while (whis == whishist);
   whishist = whis;
   
   Serial.println(" Whistle " );
    Serial.println(whis);
      switch(whis){
 case 0:
       musicPlayer.playFullFile("Whistles/whis1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Whistles/whis2.mp3");
       break;
 case 2:
       musicPlayer.playFullFile("Whistles/whis3.mp3");
       break; 
 case 3:
       musicPlayer.playFullFile("Whistles/whis4.mp3");
       break; 
 case 4:
      musicPlayer.playFullFile("Whistles/whis5.mp3");
      break; 
 case 5:
      musicPlayer.playFullFile("Whistles/whis6.mp3");
      break;  
 case 6:
       musicPlayer.playFullFile("Whistles/whis7.mp3");
       break; 
 case 7:
       musicPlayer.playFullFile("Whistles/whis8.mp3");
       break;  
 case 8:
       musicPlayer.playFullFile("Whistles/whis9.mp3");
       break;  
 case 9:
       musicPlayer.playFullFile("Whistles/whis10.mp3"); 
       break;
 case 10:
       musicPlayer.playFullFile("Whistles/whis11"); 
       break;
 case 11:
       musicPlayer.playFullFile("Whistles/whis12.mp3");
       break; 
 case 12:
       musicPlayer.playFullFile("Whistles/whis13.mp3");
       break; 
 case 13:
      musicPlayer.playFullFile("Whistles/whis14.mp3");
       break; 
 case 14:
      musicPlayer.playFullFile("Whistles/whis15.mp3");
       break;  
 case 15:
       musicPlayer.playFullFile("Whistles/whis16.mp3");
       break; 
 case 16:
       musicPlayer.playFullFile("Whistles/whis17.mp3");
       break;  
 case 17:
       musicPlayer.playFullFile("Whistles/whis18.mp3");
       break;  
 case 18:
       musicPlayer.playFullFile("Whistles/whis19.mp3");
       break;  
 case 19:
       musicPlayer.playFullFile("Whistles/whis20.mp3");
       break;  
}}



//==============================================Random Ackn====================
void RandAckn(){
    do {
   ack= random(20);
   } while (ack == ackhist);
   ackhist = ack;
   
   Serial.println(" Acknoledge " );
    Serial.println(ack);
      switch(ack){
 case 0:
        musicPlayer.playFullFile("Ack/ack1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Ack/ack2.mp3");
       break;
 case 2:
        musicPlayer.playFullFile("Ack/ack3.mp3");
       break; 
 case 3:
        musicPlayer.playFullFile("Ack/ack4.mp3");
       break; 
 case 4:
       musicPlayer.playFullFile("Ack/ack5.mp3");
       break; 
 case 5:
      musicPlayer.playFullFile("Ack/ack6.mp3");
       break;  
 case 6:
        musicPlayer.playFullFile("Ack/ack7.mp3");
       break; 
 case 7:
        musicPlayer.playFullFile("Ack/ack8.mp3");
       break;  
 case 8:
        musicPlayer.playFullFile("Ack/ack9.mp3");
       break;  
 case 9:
       musicPlayer.playFullFile("Ack/ack10.mp3");
       break; 
case 10:
     musicPlayer.playFullFile("Ack/ack11.mp3");
       break;
case 11:
        musicPlayer.playFullFile("Ack/ack12.mp3");
       break; 
case 12:
        musicPlayer.playFullFile("Ack/ack13.mp3");
       break;  
case 13:
        musicPlayer.playFullFile("Ack/ack14.mp3");
       break;   
case 14:
       musicPlayer.playFullFile("Ack/ack15.mp3");
       break;  
case 15:
        musicPlayer.playFullFile("Ack/ack16.mp3");
       break;  
case 16:
        musicPlayer.playFullFile("Ack/ack17.mp3");
       break;  
case 17:
        musicPlayer.playFullFile("Ack/ack18.mp3");
       break;   
case 18:
        musicPlayer.playFullFile("Ack/ack19.mp3");
       break; 
case 19:
        musicPlayer.playFullFile("Ack/ack20.mp3");
       break;                                                                                                                                                                                                                                                                                                                                                                                                         
      }
}
//==============================================Random Hum====================
void RandHum(){
    do {
   hum= random(20);
   } while (hum == humhist);
   humhist = hum;
   
   Serial.println(" Hum " );
    Serial.println(hum);
      switch(hum){
 case 0:
        musicPlayer.playFullFile("Hums/hum1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Hums/hum2.mp3");
       break;
 case 2:
       musicPlayer.playFullFile("Hums/hum3.mp3");
       break; 
 case 3:
        musicPlayer.playFullFile("Hums/hum4.mp3");
       break; 
 case 4:
      musicPlayer.playFullFile("Hums/hum5.mp3");
       break; 
 case 5:
      musicPlayer.playFullFile("Hums/hum6.mp3");
       break;  
 case 6:
       musicPlayer.playFullFile("Hums/hum7.mp3");
       break; 
 case 7:
        musicPlayer.playFullFile("Hums/hum8.mp3");
       break;  
 case 8:
       musicPlayer.playFullFile("Hums/hum9.mp3");
       break;  
 case 9:
      musicPlayer.playFullFile("Hums/hum10.mp3");
       break; 
case 10:
     musicPlayer.playFullFile("Hums/hum11.mp3");
       break;
case 11:
       musicPlayer.playFullFile("Hums/hum12.mp3");
       break; 
case 12:
       musicPlayer.playFullFile("Hums/hum13.mp3");
       break;  
case 13:
       musicPlayer.playFullFile("Hums/hum14.mp3");
       break;   
case 14:
       musicPlayer.playFullFile("Hums/hum15.mp3");
       break;  
case 15:
       musicPlayer.playFullFile("Hums/hum16.mp3");
       break;  
case 16:
      musicPlayer.playFullFile("Hums/hum17.mp3");
       break;  
case 17:
      musicPlayer.playFullFile("Hums/hum18.mp3");
       break;   
case 18:
       musicPlayer.playFullFile("Hums/hum19.mp3");
       break; 
case 19:
       musicPlayer.playFullFile("Hums/hum20.mp3");
       break;                                                                                                                                                                                                                                                                                                                                                                                                         
      }
}
//==============================================Random Sad====================
void RandSad(){
    do {
   sad = random(15);
   } while (sad == sadhist);
   sadhist = sad;
   
   Serial.println(" Sad " );
    Serial.println(sad);
      switch(sad){
 case 0:
        musicPlayer.playFullFile("Sad/sad1.mp3");
       break;
 case 1:
       musicPlayer.playFullFile("Sad/sad2.mp3");
       break;
 case 2:
        musicPlayer.playFullFile("Sad/sad3.mp3");
       break; 
 case 3:
        musicPlayer.playFullFile("Sad/sad4.mp3");
       break; 
 case 4:
       musicPlayer.playFullFile("Sad/sad5.mp3");
       break; 
 case 5:
       musicPlayer.playFullFile("Sad/sad6.mp3");
       break;  
 case 6:
        musicPlayer.playFullFile("Sad/sad7.mp3");
       break; 
 case 7:
        musicPlayer.playFullFile("Sad/sad8.mp3");
       break;  
 case 8:
        musicPlayer.playFullFile("Sad/sad9.mp3");
       break;  
 case 9:
       musicPlayer.playFullFile("Sad/sad10.mp3");
       break; 
case 10:
        musicPlayer.playFullFile("Sad/sad11.mp3");
       break;
case 11:
        musicPlayer.playFullFile("Sad/sad12.mp3");
       break; 
case 12:
        musicPlayer.playFullFile("Sad/sad13.mp3");
       break;  
case 13:
        musicPlayer.playFullFile("Sad/sad14.mp3");
       break;   
case 14:
        musicPlayer.playFullFile("Sad/sad15.mp3");
       break;  
                                                                                                                                                                                                                                                                                                                                                                 
      }
}

//==============================================Random Alarm====================
void RandAlarm(){
    do {
   ala = random(14);
   } while (ala == alahist);
   alahist = ala;
   
   Serial.println(" Alarm " );
    Serial.println(ala);
      switch(ala){
 case 0:
        musicPlayer.playFullFile("Alarm/alarm1.mp3");
       break;
 case 1:
      musicPlayer.playFullFile("Alarm/alarm2.mp3");
       break;
 case 2:
       musicPlayer.playFullFile("Alarm/alarm3.mp3");
       break; 
 case 3:
      musicPlayer.playFullFile("Alarm/alarm4.mp3");
       break; 
 case 4:
       musicPlayer.playFullFile("Alarm/alarm5.mp3");
       break; 
 case 5:
      musicPlayer.playFullFile("Alarm/alarm6.mp3");
       break;  
 case 6:
      musicPlayer.playFullFile("Alarm/alarm7.mp3");
       break; 
 case 7:
      musicPlayer.playFullFile("Alarm/alarm8.mp3");
       break;  
 case 8:
       musicPlayer.playFullFile("Alarm/alarm9.mp3");
       break;  
 case 9:
      musicPlayer.playFullFile("Alarm/alarm10.mp3");
       break; 
case 10:
      musicPlayer.playFullFile("Alarm/alarm11.mp3");
       break;
case 11:
      musicPlayer.playFullFile("Alarm/alarm12.mp3");
       break; 
case 12:
      musicPlayer.playFullFile("Alarm/alarm13.mp3");
       break;  
case 13:
      musicPlayer.playFullFile("Alarm/alarm14.mp3");
       break;   
                                                                                                                                                                                                                                                                                                                                                                 
      }
}
//==============================================Random SingAlong====================
void RandSingAlong(){
  do {
   sngalo = random(11);
   } while (sngalo == sngalohist);
   sngalohist = sngalo;
   
   Serial.println(" Sing Along " );
    Serial.println(sngalo);
      switch(sngalo){
 case 0:
       musicPlayer.startPlayingFile("SngAlo/song1.mp3");
       return;
       break;
case 1:
       musicPlayer.startPlayingFile("SngAlo/song2.mp3");
       return;
       break;
case 2:
      musicPlayer.startPlayingFile("SngAlo/song3.mp3");
      return;
       break;
case 3:
       musicPlayer.startPlayingFile("SngAlo/song4.mp3");
       break;
case 4:
       musicPlayer.startPlayingFile("SngAlo/song5.mp3");
       break;
case 5:
       musicPlayer.startPlayingFile("SngAlo/song6.mp3");
       break;
case 6:
      musicPlayer.startPlayingFile("SngAlo/song7.mp3");
       break;
case 7:
       musicPlayer.startPlayingFile("SngAlo/song8.mp3");
       break;
case 8:
       musicPlayer.startPlayingFile("SngAlo/song9.mp3");
       break;
case 9:
       musicPlayer.startPlayingFile("SngAlo/song10.mp3");
       break;
case 10:
      musicPlayer.startPlayingFile("SngAlo/song11.mp3");
       break;
      }
}
//=====================================================Rocket Man===========================
void RocketMan(){
musicPlayer.startPlayingFile("SngAlo/song7.mp3");
Show = 0;  
}
//=====================================================Leia Speach===========================
void LeiasSpeach(){
musicPlayer.startPlayingFile("Special/LEIAHO~1.mp3");
Show = 0;  
}
//=====================================================Everyyhing awe===========================
void R2Awe(){
musicPlayer.startPlayingFile("Songs/R2AWE.mp3");
Show = 0;  
}
//=====================================================Fav Things===========================
void FavThings(){
musicPlayer.startPlayingFile("Songs/FAVTHI~1.mp3");
Show = 0;  
}
//-----------------------------------------Apply Incoming Message---------------------
void ApplyIncoming(){

//CurrentSong = IncomingInt;
  
switch(CurrentSong){
  case 10://stop
   break;
  case 11://Random Whistle
   RandWhistle();
     break;
  case 12://Random Sad
  RandSad();
    break;
  case 13:
  RandChatty();
    break;
 case 14:
  RandAckn();
  break;
 case 15:
 RandRazz();
  break;
 case 16:
  RandScream();
  break;
 case 17:
  RandAlarm();
  break;
 case 18:
 RandHum();
  break;

 case 31:
 musicPlayer.startPlayingFile("SngAlo/song7.mp3");
  break;
  case 32:
 musicPlayer.startPlayingFile("Special/LEIAHO~1.mp3");
  break;
 case 33:
 musicPlayer.startPlayingFile("Songs/R2AWE2.mp3");
  break;
  case 34:
 musicPlayer.startPlayingFile("SngAlo/song10.mp3");
  break;
 case 35:
 musicPlayer.startPlayingFile("Songs/FAVTHI~1.mp3");
  break;  
  case 36:
 musicPlayer.startPlayingFile("Songs/CANT2.mp3");
  break;  
  case 37:
  musicPlayer.startPlayingFile("SngAlo/song6.mp3");
  break;  
   case 38:
  musicPlayer.startPlayingFile("Songs/song1.mp3");
  break;  
 case 111:
 musicPlayer.startPlayingFile("Songs/song2.mp3");
break;
 case 112:
 musicPlayer.startPlayingFile("Songs/song3.mp3");
break;
case 113:
 musicPlayer.startPlayingFile("SngAlo/song8.mp3");
break;
case 114:
 musicPlayer.startPlayingFile("Songs/song1.mp3");
break;
case 115:
 musicPlayer.startPlayingFile("SngAlo/song1.mp3");
break;
case 116:
 musicPlayer.startPlayingFile("SngAlo/song2.mp3");
break;
case 117:
 musicPlayer.startPlayingFile("SngAlo/song4.mp3");
break;
case 118:
 musicPlayer.startPlayingFile("Songs/song4.mp3");
break;
 case 121:
 musicPlayer.startPlayingFile("SngAlo/song3.mp3");
break;
case 122:
 musicPlayer.startPlayingFile("SngAlo/song5.mp3");
break;
case 123:
 musicPlayer.startPlayingFile("SngAlo/song6.mp3");
break;
case 124:
 musicPlayer.startPlayingFile("SngAlo/song7.mp3");
break;
case 125:
 musicPlayer.startPlayingFile("SngAlo/song9.mp3");
break;
case 126:
 musicPlayer.startPlayingFile("SngAlo/song10.mp3");
break;
case 127:
 musicPlayer.startPlayingFile("SngAlo/song11.mp3");
break;
case 128:
 
break;

}
}

//===================================================Run Shows===========================
void RunShows(){
Serial.print (" Run Shows" );
switch (Show){
 case 31:
 RocketMan();
 break;
  case 32:
  Serial.print (" LS" );
 LeiasSpeach();
 break;
  case 33:
 R2Awe();
 break;
  case 35:
 FavThings();
 break;
  case 36:
// Cantina();
 break;
   default:
  case 0:// No Show Now
          Show = 0; 
}
}
//_______________________________________________________Receive_________________________________
void  Receive(){
    //check and see if a data packet has come in. 
   (ET.receiveData());
   Int1 = (mydata.data1);

 
   Serial.println(IncomingInt);

}
void Display(){
    Serial.print(" Int1 ");
   Serial.println(Int1);
    Serial.print(" LastSong ");
   Serial.println(LastSong);
    Serial.print(" CurrentSong ");
   Serial.println(CurrentSong);
}
//--------------------------------------------------We Got One-----------------
void WeGotOne(){
if(LastSong != Int1){ 
Serial.println("WE GOT ONE");
CurrentSong = Int1;
 ShowTime = 0;
 LastSong = CurrentSong;
 ApplyIncoming(); 
}}
//=================================================================loop=====================
void loop() {   
    CurrentMillis = millis();
     (ET.receiveData());
  Int1 = (mydata.data1);

WeGotOne();

 if (CurrentMillis - PreviousLoopMillis >= LoopInterval){
    PreviousLoopMillis = CurrentMillis;
  Display();
       Receive();
      }

 if (CurrentMillis - PreviousDisplayMillis >= DisplayInterval){
    PreviousDisplayMillis = CurrentMillis;
 // PrintIncoming();
    }
 
}
//=================================================FDH===================
/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}



void receive(int numBytes) {}
