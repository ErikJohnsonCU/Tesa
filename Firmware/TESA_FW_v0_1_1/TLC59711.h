  /******************************************************
  Header file for interfacing with the TLC59711.
  
  Licence TBD.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  *****************************************************/

// Don't allow it to be added more than once!
#ifndef TLC59711_H
#define TLC59711_H

#include <Arduino.h>

class TLC59711 {
public:
  // Initializes variables and prepares the interface to the TLC59711
  TLC59711(uint8_t dataPin, uint8_t clkPin);
  
  // Configures one LED channel to the desired brightness (min = 0, max = 65535)
  void ConfigOneLED(uint8_t LEDn, uint16_t pwm);
  
  // Configures all LED channels to desired brightnesses (min = 0, max = 65535)
  void ConfigAllLEDs(uint16_t pwm[12]);
  
  // Configure the function controls for the device (see DS for description of functions)
  void ConfigFC(boolean OUTTMG, boolean EXTGCK,
                  boolean TMGRST, boolean DSPRT,
                  boolean BLANK);
                  
  // All values should be stored in the global vbles; now send them on their way!
  void SendLEDCommand();

private:
  uint32_t FControl; // the function code to send (includes secrt write command key)
  uint8_t BCr, BCg, BCb; // RBG brightness controls (will be set to same values)
  uint16_t LEDLevels[12]; // individual LED PWM controls (R0 is [0] and B3 is [11])
  uint8_t data; // the pin on which to place data
  uint8_t clk; // the pin to toggle as the clock
  
  // Sends 32 bits over SPI (either using custom SPI or the Arduino SPI lib)
  void Send32MSBs(uint32_t toSend);
};

#endif // case TLC59711_H
