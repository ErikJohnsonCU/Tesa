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
#define   DataLED     11  // will be changed for Atmega32u4
#define   ClkLED      13  // will be changed for Atmega32u4

/*************  IMPORTS  *************/
#include "TLC59711.h"

/*************  GLOBAL VBLES  *************/ // Boo! Hiss!


/*************  SETUP  *************/
void setup()
{
  // Setup settings
#ifdef DEBUG
  Serial.begin(9600);
#endif // end if DEBUG defined
  
  // Setup the pins
  
  // Initialize variables
  
  // Pre-loop activity
  delay(2500);
  TLC59711 LEDs = TLC59711(DataLED, ClkLED);
  LEDs.ConfigFC(true, false, true, true, false);
  uint16_t array[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  LEDs.ConfigAllLEDs(array);
  LEDs.SendLEDCommand();
}

/*************  LOOP  *************/
void loop()
{
  
}

/*************  FUNCTIONS  *************/

