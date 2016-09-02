
class CTimer
{
public:  
  void Init();
  
  void SetCallback(void (*foo)());
  
  void (*CallBack)();
  
  void SetInterval(int Mili);
  
  void Start();
  
  void Stop();
};

void CTimer::Init()
{
  // Setup and enable clock for TC
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(48) |    // Divide the 48MHz system clock by 48 = 1 MHz
                  GCLK_GENDIV_ID(5);      // Set division on Generic Clock Generator (GCLK) 5
  while (GCLK->STATUS.bit.SYNCBUSY);        // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                   GCLK_GENCTRL_GENEN |         // Enable GCLK 5
                   GCLK_GENCTRL_SRC_DFLL48M |   // Set the clock source to 48MHz
                   GCLK_GENCTRL_ID(5);          // Set clock source on GCLK 5
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable the generic clock...
                  GCLK_CLKCTRL_GEN_GCLK5 |     // ....on GCLK5
                  // Hack to overcome define problem in next line!!!
                  0x1A;                        // Feed the GCLK5 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // The type cast must fit with the selected timer
  Tcc* TC = (Tcc*) TCC0; // get timer struct

  TC->CTRLA.reg &= ~TCC_CTRLA_ENABLE;   // Disable TC
  while (TC->SYNCBUSY.bit.ENABLE == 1); // wait for sync

  TC->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV1;   // Set prescaler

  TC->WAVE.reg |= TCC_WAVE_WAVEGEN_NFRQ;   // Set wave form normal freq.
  while (TC->SYNCBUSY.bit.WAVE == 1); // wait for sync

  // Interrupts
  TC->INTENSET.reg = 0;                 // disable all interrupts
  TC->INTENSET.bit.OVF = 1;          // enable only overfollow

  // Enable InterruptVector
  NVIC_EnableIRQ(TCC0_IRQn);
}

void CTimer::SetCallback(void (*foo)())
{
  CallBack = foo;
}

void CTimer::Start()
{
 Tcc* TC = (Tcc*) TCC0; // get timer struct
  // Enable TC
  TC->CTRLA.reg |= TCC_CTRLA_ENABLE ;
  while (TC->SYNCBUSY.bit.ENABLE == 1); // wait for sync
}
  
void CTimer::Stop()
{
  Tcc* TC = (Tcc*) TCC0; // get timer struct
  // Disable TC
  TC->CTRLA.reg &= ~TCC_CTRLA_ENABLE;
  while (TC->SYNCBUSY.bit.ENABLE == 1); // wait for sync
}

void CTimer::SetInterval(int Mili)
{
  Tcc* TC = (Tcc*) TCC0; // get timer struct
  Stop();
  
  // Clear the OF interrupt. Shouldn't happen, but just in case
  TC->INTFLAG.bit.OVF = 1;    

  TC->PER.reg = Mili * 1000;              // Set counter Top using the PER register
  while (TC->SYNCBUSY.bit.PER == 1); // wait for sync
}
CTimer Timer;

void TCC0_Handler()
{  
  Tcc* TC = (Tcc*) TCC0;       
  
  // Clear the OF flag, which is the only one enabled
  TC->INTFLAG.bit.OVF = 1;    
  // Call the callback funtion
  void (*Temp)() = Timer.CallBack;
  Temp();
}
