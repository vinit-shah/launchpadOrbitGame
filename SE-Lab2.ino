// Test of display
extern "C" {
#include <delay.h>
#include <FillPat.h>
#include <I2CEEPROM.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
}
#include <string.h>

/* ------------------------------------------------------------ */
/*				Local Type Definitions		*/
/* ------------------------------------------------------------ */
#define DEMO_0		0
#define DEMO_1		2
#define DEMO_2		1
#define DEMO_3		3
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3


/* ------------------------------------------------------------ */
/*				Global Variables		*/
/* ------------------------------------------------------------ */
extern int xchOledMax; // defined in OrbitOled.c
extern int ychOledMax; // defined in OrbitOled.c

/* ------------------------------------------------------------ */
/*				Local Variables			*/
//* ------------------------------------------------------------ */
char	chSwtCur;
char	chSwtPrev;
bool	fClearOled;

void DeviceInit();
// 0x0 is black, 0xFF is white
char ground[] = {
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 1, row 1 col 1
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Block 2, row 1, col 2
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // 0x07

char blankScreen[] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char block1[8] {
 0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF,0xFF, 0xFF
};

char block2[8] {
  0xC0, 0xF0, 0xFC, 0xFF, 0xFF, 0xFC, 0xF0, 0xC0
};

char block3[8] {
 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80
};

char hole[8] {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

char negativePlayerSprite[8] = {
  0x76, 0xF7, 0x04, 0xC0, 0x04, 0xF7, 0x76, 0x00
};

struct Obstacle{
	int y = 16;
	int x = 120;
	char sprite[8];
};

struct Person{
	int y = 16;
	int x = 16;
	char sprite[8] = {
	 0x08, 0x08, 0xFB, 0x3F, 0xFB, 0x08, 0x08, 0x00
	};
};

struct Obstacle obstacles[3] = {Obstacle(), Obstacle(), Obstacle()}; //size of 3

// For potentiometer
 uint32_t	ulAIN0;
  long 			lBtn1;
  long 			lBtn2;
  char			szAIN[6] = {
    0            };
 char			cMSB = 0x00;
  char			cMIDB = 0x00;
  char			cLSB = 0x00;
int invincibleTimer = 0;
int flashTime = 4;
int dir = -1;
bool jumping = true;
int score = 0;
int v = -8, a = 2;
int lives = 4;
struct Person player = Person();
const int OBSTACLE_WIDTH = 8;
const int OBSTACLE_HEIGHT = 8;
const int PLAYER_WIDTH = 8;
const int PLAYER_HEIGHT = 8;
const int GROUND_WIDTH = 128;
const int GROUND_HEIGHT = 8;
int PIXEL_INCREMENT = 4; // change for speeding up
const int SLEEP_TIME = 1;
void setup()
{
  // put your setup code here, to run once:

	// For debugging
	Serial.begin(9600);
	Serial.println("Ready to go!");

    DeviceInit();
 	for (int i = 0; i < 3; i++)
		obstacles[i] = Obstacle();

	for (int i = 0; i < 3; i++)
		obstacles[i] = generateObstacle();

	printStartScreen();
	updateLEDS();
}



void loop()
{
   tick();
   render();
   sleep(SLEEP_TIME);
}

void reset(){
  printStartScreen();
	// reset obstacles
for (int i = 0; i < 3; i++)
		obstacles[i] = generateObstacle();
	score = 0;
	lives = 4;
	updateLEDS();
}

void clearScreen(){
  OrbitOledSetCursor(0, 0);
  OrbitOledPutBmp(128, 32, blankScreen);
}

void tick(){
   if(isButtonPressed() || player.y != 16){
    if(player.y == 16){
      v = -8;
    }
    player.y += v;
    v += a;
  }
 
   for (int i = 0; i < 3; i++) {
		obstacles[i].x -= PIXEL_INCREMENT;
		if (obstacles[i].x < 0) {
			obstacles[i] = generateObstacle();
				if (!invincibleTimer)
                        score++;
              }
	}

if(invincibleTimer){
    invincibleTimer--; 
  }

  if(isCollided() && !invincibleTimer){
	lives--;
	updateLEDS();	
	if(lives > 0){
           invincibleTimer = 20;
    } else {
      printGameOverMsg();
      reset();
    }
  } 

	updatePixelIncrement();
	}

bool isCollided(){
  for(int i = 0; i < 3; i++){
    if(obstacles[i].sprite[0] == hole[0]){
      if(player.x + PLAYER_WIDTH > obstacles[i].x && player.x < obstacles[i].x + OBSTACLE_WIDTH && player.y + PLAYER_HEIGHT + 1 > obstacles[i].y && player.y < obstacles[i].y + OBSTACLE_HEIGHT){
       return true;

      }
    } else {
      if(player.x + PLAYER_WIDTH > obstacles[i].x && player.x < obstacles[i].x + OBSTACLE_WIDTH && player.y + PLAYER_HEIGHT > obstacles[i].y && player.y < obstacles[i].y + OBSTACLE_HEIGHT){
	  return true;
      }
    }
  }
  return false;
}

void updateLEDS() {
			GPIOPinWrite(LED4Port, LED4, LOW);
			GPIOPinWrite(LED3Port, LED3, LOW);
			GPIOPinWrite(LED2Port, LED2, LOW);
			GPIOPinWrite(LED1Port, LED1, LOW);
	switch (lives) {
		case 4:
			GPIOPinWrite(LED4Port, LED4, LED4);
		case 3:
			GPIOPinWrite(LED3Port, LED3, LED3);
		case 2:
			GPIOPinWrite(LED2Port, LED2, LED2);
		case 1: 
			GPIOPinWrite(LED1Port, LED1, LED1);
}	
}

void render(){
  clearScreen();
   //render ground, must be done first
  OrbitOledSetCursor(0,3);
  OrbitOledPutBmp(GROUND_WIDTH, GROUND_HEIGHT, ground);
  //rendre objects, if object over ground then will overwrite
  for(int i = 0; i < 3; i++){
    Obstacle obs = obstacles[i];
      OrbitOledMoveTo(obs.x,obs.y);
	  OrbitOledPutBmp(OBSTACLE_WIDTH, OBSTACLE_HEIGHT, obs.sprite);
  }
  //render player
  OrbitOledMoveTo(player.x,player.y);

if(invincibleTimer){
    if(invincibleTimer / flashTime % 2 == 0){
      OrbitOledPutBmp(PLAYER_WIDTH, PLAYER_HEIGHT, player.sprite);
    } else {
      OrbitOledPutBmp(PLAYER_WIDTH, PLAYER_HEIGHT, negativePlayerSprite);
    }
  } else {
    OrbitOledPutBmp(PLAYER_WIDTH, PLAYER_HEIGHT, player.sprite);
  }
  
printScore();
  OrbitOledUpdate();
}

struct Obstacle generateObstacle() {
	struct Obstacle o = Obstacle();
	//o.x += random(0, 6) * 8;
	// Note: you can't actually assign char arrays to eachother, need to copy elements directly. :(
	int b = random(0,4);
	switch (b) { // can up from 4 depending on the number of block sprites (4 is exclusive)
		case 0:
			for(int i = 0; i < 8; i++)
				 o.sprite[i] = block1[i];
			break;
		case 1:
			for(int i = 0; i < 8; i++)
				 o.sprite[i] = block2[i];
			break;
		case 2:
			 for(int i = 0; i < 8; i++)
				 o.sprite[i] = block2[i];
			break;
		case 3:
			o.y += OBSTACLE_HEIGHT; // set to ground by adding its width to its current y position
			for(int i = 0; i < 8; i++)
				 o.sprite[i] = hole[i];
			break;
		default:
			Serial.println("Uhhhh... this shouldn't print...ask Stephen.\n");
	}
	while(isColOccupied(o.x))
		o.x = random(12, 29) * 8;
	

	return o;
}

// Helper function for generating obstacles away from eachother.
bool isColOccupied(int c) {
	for (int i = 0; i < 3; i++)
		if (obstacles[i].x == c || obstacles[i].x == c+OBSTACLE_WIDTH || obstacles[i].x == c-OBSTACLE_WIDTH || obstacles[i].x == c+OBSTACLE_WIDTH*2 || obstacles[i].x == c-OBSTACLE_WIDTH*2  )
			return true;
	return false;
}

void printGameOverMsg() {
    char buffer[5];
    itoa (score,buffer,10);
    char str[] = {'Y', 'o', 'u', ' ', '$','&','@','%','e', 'd', ' ', 'U', 'p', '!', '\0'};
	char str2[] = { 'S', 'c', 'o', 'r', 'e', ':', '\0'};
    strcat(str2, buffer);
    clearScreen();
    OrbitOledSetCursor(0, 1);
    OrbitOledPutString(str);
	OrbitOledSetCursor(0,3);
	OrbitOledPutString(str2);
    sleep (2000);
}

void printStartScreen() {
	char *msg = "Welcome! Press  button\n to start the game!";
	clearScreen();
	OrbitOledMoveTo(0,0);
	OrbitOledPutString(msg);
	waitUntilButtonPressed();
	sleep(500);
}

void printScore() {
    int score2 = score;
    //adjust the position of the score cursor based on how many digits the score is
    int pixOff = 0;
    while (score2) {
      score2 /= 10;
      pixOff++;
    }
	OrbitOledSetCursor(16-pixOff, 0);
    //max num of digits for score is 5. That's like 99999.... which is a lot
    char buffer[5];
    itoa (score,buffer,10);
	OrbitOledPutString(buffer);
}

void updatePixelIncrement() {
	long int currentReading = potentionmeterReading();
	if (currentReading < 800) {
		PIXEL_INCREMENT = 4;
	} else if( currentReading < 1600) {
	PIXEL_INCREMENT = 6;
} else  if (currentReading < 2400){
	PIXEL_INCREMENT = 8;
} else if (currentReading < 3200) {
	PIXEL_INCREMENT = 10;
} else if (currentReading < 4200) {
	PIXEL_INCREMENT = 12;
} else {
	PIXEL_INCREMENT = 1;
}
}

long int potentionmeterReading() {
 /*
   * Initiate ADC Conversion and update the OLED
   */
  ADCProcessorTrigger(ADC0_BASE, 0);

  while(!ADCIntStatus(ADC0_BASE, 0, false));

  ADCSequenceDataGet(ADC0_BASE, 0, &ulAIN0);

  /*
   * Process data
   */
  cMSB = (0xF00 & ulAIN0) >> 8;
  cMIDB = (0x0F0 & ulAIN0) >> 4;
  cLSB = (0x00F & ulAIN0);

  szAIN[0] = '0';
  szAIN[1] = 'x';
  szAIN[2] = (cMSB > 9) ? 'A' + (cMSB - 10) : '0' + cMSB;
  szAIN[3] = (cMIDB > 9) ? 'A' + (cMIDB - 10) : '0' + cMIDB;
  szAIN[4] = (cLSB > 9) ? 'A' + (cLSB - 10) : '0' + cLSB;
  szAIN[5] = '\0';


	return strtol(szAIN, NULL, 16);
}
 
boolean isButtonPressed() {
  long lBtn1 = GPIOPinRead(BTN1Port, BTN1);
   return lBtn1 == BTN1;
}

void waitUntilButtonPressed() {
	while(true) {
	 if (GPIOPinRead(BTN1Port, BTN1) == BTN1 || GPIOPinRead(BTN2Port, BTN2) == BTN2)
		return;
	}
}

/* ------------------------------------------------------------ */
/***	DeviceInit
 **
 **	Parameters:
 **		none
 **
 **	Return Value:
 **		none
 **
 **	Errors:
 **		none
 **
 **	Description:
 **		Initialize I2C Communication, and GPIO
 */
void DeviceInit()
{
  /*
   * First, Set Up the Clock.
   * Main OSC		  -> SYSCTL_OSC_MAIN
   * Runs off 16MHz clock -> SYSCTL_XTAL_16MHZ
   * Use PLL		  -> SYSCTL_USE_PLL
   * Divide by 4	  -> SYSCTL_SYSDIV_4
   */
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);

  /*
   * Enable and Power On All GPIO Ports
   */
  //SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA | SYSCTL_PERIPH_GPIOB | SYSCTL_PERIPH_GPIOC |
  //						SYSCTL_PERIPH_GPIOD | SYSCTL_PERIPH_GPIOE | SYSCTL_PERIPH_GPIOF);

  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOF );
  /*
   * Pad Configure.. Setting as per the Button Pullups on
   * the Launch pad (active low).. changing to pulldowns for Orbit
   */
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  /*
   * Initialize Switches as Input
   */
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  /*
   * Initialize Buttons as Input
   */
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);

  /*
   * Initialize LEDs as Output
   */
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  /*
   * Enable ADC Periph
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

  GPIOPinTypeADC(AINPort, AIN);

  /*
   * Enable ADC with this Sequence
   * 1. ADCSequenceConfigure()
   * 2. ADCSequenceStepConfigure()
   * 3. ADCSequenceEnable()
   * 4. ADCProcessorTrigger();
   * 5. Wait for sample sequence ADCIntStatus();
   * 6. Read From ADC
   */
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  /*
   * Initialize the OLED
   */
  OrbitOledInit();

  /*
   * Reset flags
   */
  chSwtCur = 0;
  chSwtPrev = 0;
  fClearOled = true;

}

