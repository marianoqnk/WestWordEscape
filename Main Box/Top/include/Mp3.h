#include "Pines.h"
#include <Arduino.h>
#include <DFMiniMp3.h>
#include "SoftwareSerial.h"

class Mp3Notify;
SoftwareSerial secondarySerial(PIN_MP3_RX, PIN_MP3_TX); // RX, TX
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3;
DfMp3 dfmp3(secondarySerial);
bool musicaSonando=false;
class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char *action)
  {
    if (source & DfMp3_PlaySources_Sd)
    {
      Serial.print(F("SD Card, "));
    }
    if (source & DfMp3_PlaySources_Usb)
    {
      Serial.print(F("USB Disk, "));
    }
    if (source & DfMp3_PlaySources_Flash)
    {
      Serial.print(F("Flash, "));
    }
    Serial.println(action);
  }
  static void OnError(DfMp3 &mp3, uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print(F("Com Error "));
    Serial.println(errorCode);
  }
  static void OnPlayFinished(DfMp3 &mp3, DfMp3_PlaySources source, uint16_t track)
  {
   // Serial.print("Play finished for #");
    //Serial.println(track);
    musicaSonando=false;
  }
  static void OnPlaySourceOnline(DfMp3 &mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3 &mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3 &mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};

void iniDFPlayer()
{
  secondarySerial.begin(9600);
  dfmp3.begin();
  //dfmp3.reset();
  delay(100);
  dfmp3.setVolume(6);
  // show some properties and set the volume
  uint16_t volume = dfmp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);


  /*uint16_t count = dfmp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);

  uint16_t mode = dfmp3.getPlaybackMode();
  Serial.print("playback mode ");
  Serial.println(mode);*/
  dfmp3.playAdvertisement(2);//quita dindong 
  Serial.println(F("starting sounds..."));

  //dfmp3.playRandomTrackFromAll(); // random of all folders on sd
}