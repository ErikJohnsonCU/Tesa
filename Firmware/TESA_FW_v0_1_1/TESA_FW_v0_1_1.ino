  /******************************************************
  Running FW for TESA. Current working version is 0.1.1
  
  As of July 31st, 2014: the only part in here is support for
  interfacing with the LED driver. Adapted from code written 
  by Limor Fried/Ladyada for Adafruit Industries.
  
  Licence TBD.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  *****************************************************/

/*************  PREPROC DIRS  *************/
#define   DEBUG           // if running FW in debug mode
//#define   PRO             // if the FW is to be built for a pro device
#define   PROTO           // if the FW is to be built for a prototype device
#define   CUSTOM_SPI      // if we wish to use the custom SPI as used by Adafruit example
#define   DataLED     11  // will be changed for Atmega32u4
#define   ClkLED      13  // will be changed for Atmega32u4

/*************  IMPORTS  *************/
#ifndef CUSTOM_SPI
#include <SPI.h>
#endif

/*************  GLOBAL VBLES  *************/ // Boo! Hiss!
int8_t BCr, BCg, BCb; // RBG brightness controls (will be set to same values)
uint16_t LEDLevels[12]; // individual LED PWM controls (R0 is [0] and B3 is [11])
uint32_t FControl; // the function code to send (includes secrt write command key)

/*************  SETUP  *************/
void setup()
{
  // Setup settings
#ifdef DEBUG
  Serial.begin(9600);
#endif // end if DEBUG defined
#ifndef CUSTOM_SPI
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
#endif // end if CUSTOM_SPI not defined
  
  // Setup the pins
  pinMode(DataLED, OUTPUT);
  pinMode(ClkLED, OUTPUT);
  
  // Initialize variables
  BCr = BCg = BCb = 0x65; // less than max (cuz I killed a couple LEDs at max)
      // 0x65 gives 12 mA with a 3.3k res
      // 0x7F gives 15 mA with a 3.3k res (was too much)
  for (int8_t i=0; i<12; i++)
  {
    LEDLevels[i] = 0xC001; // 75% brightness
  }
  FControl = 0x96DFFFFF; // the default FC from the Adafruit example
  
  // Pre-loop activity
  delay(2500);
  SendLEDCommand();
}


/*************  LOOP  *************/
void loop()
{
  
}

/*************  FUNCTIONS  *************/
// Configures one LED channel to the desired brightness (min = 0, max = 65535)
inline void ConfigOneLED(uint8_t LEDn, uint16_t pwm)
{
  if (LEDn > 12) return; // defensive coding
  LEDLevels[LEDn-1] = pwm;
}

// Configures all LED channels to desired brightnesses (min = 0, max = 65535)
inline void ConfigAllLEDs(uint16_t pwm[12])
{
  for (int i=0; i<12; i++) // over all the LED channels
  {
    LEDLevels[i] = pwm[i];
  }
}

// Configure the function controls for the device (see DS for description of functions)
void ConfigFC(boolean OUTTMG, boolean EXTGCK,
                boolean TMGRST, boolean DSPRT,
                boolean BLANK)
{
  uint32_t desiredFC = 0x25; // the secret code to save data
  desiredFC <<= 5;
  if (OUTTMG) desiredFC |= B10000;
  if (EXTGCK) desiredFC |= B1000;
  if (TMGRST) desiredFC |= B100;
  if (DSPRT) desiredFC |= B10;
  if (BLANK) desiredFC |= B1;
  desiredFC <<= 7;
  desiredFC |= BCr;
  desiredFC <<= 7;
  desiredFC |= BCg;
  desiredFC <<= 7;
  desiredFC |= BCb;
  FControl = desiredFC;
#if defined DEBUG
  Serial.println(desiredFC, BIN);
#endif
}

// All values should be stored in the global vbles; now send them on their way!
void SendLEDCommand()
{
  Send32MSBs(FControl);
#if defined DEBUG
  Serial.println("===================================================");
  Serial.println("Sending Data:");
  Serial.println(FControl, BIN);
#endif
  uint32_t toSend;
  for (int i = 11; i > 0; i = i-2)
  {
    toSend = LEDLevels[i]<<16 | LEDLevels[i-1];
    Send32MSBs(toSend);
#if defined DEBUG
    Serial.println(LEDLevels[i]<<16 | LEDLevels[i-1], BIN);
#endif
  }
#if defined DEBUG
    Serial.println("===================================================");
#endif
}

// Sends 32 bits over SPI
void Send32MSBs(uint32_t toSend)
{
#if defined CUSTOM_SPI
  uint32_t sweep = 0x80000000; // so named as it sweeps along toWrite from the left
  for (; sweep>0 ; sweep >>= 1) // until the one in sweep disappears off the right end
  {
    digitalWrite(ClkLED, LOW);
    if (sweep & toSend) // as we sweep, check the overlapping bit of toWrite...
      digitalWrite(DataLED, HIGH); // then express this bit value (0 or 1) on Data pin
    else
      digitalWrite(DataLED, LOW);
    digitalWrite(ClkLED, HIGH); // Clk rising edge causes shift reg to latch bit on Data
  }
#else // CUSTOM_SPI not defined
  SPI.transfer(toSend >> 24); // each call transfers one byte MSB SPIily
  SPI.transfer(toSend >> 16);
  SPI.transfer(toSend >> 8);
  SPI.transfer(toSend);
#endif // end case CUSTOM_SPI
}
