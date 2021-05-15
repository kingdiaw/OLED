#include "picuno.h"
#include "OLED.h"         
#include "font.h"
#include "Wire.h"

//Function to Send command byte to OLED, passed byte
void Oled_command( uint8_t command )
{
  uint8_t data_I2C[2];
  
  data_I2C[0] = SSD1306_COMMAND ; 
  data_I2C[1] = command; 
  Wire_beginTransmission(SSD1306_ADDR);
  Wire_writeNBytes(data_I2C,2);
  Wire_endTransmission();
}

//Function to Send data byte to OLED, passed byte
void Oled_data( uint8_t value )
{
  uint8_t data_I2C[2];
  
  data_I2C[0] =SSD1306_DATA_CONTINUE ; 
  data_I2C[1] = value; 

  Wire_beginTransmission(SSD1306_ADDR);
  Wire_writeNBytes(data_I2C,2);
  Wire_endTransmission();
 
}

//Function to init OLED
void Oled_init(void)
{
  Oled_command( SSD1306_DISPLAY_OFF);
  Oled_command( SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
  Oled_command( 0x80);
  Oled_command( SSD1306_SET_MULTIPLEX_RATIO );
  Oled_command( SSD1306_LCDHEIGHT - 1 );
  Oled_command( SSD1306_SET_DISPLAY_OFFSET );
  Oled_command(0x00);
  Oled_command( SSD1306_SET_START_LINE|0x00);  // Line: 0
  Oled_command( SSD1306_CHARGE_PUMP );
  Oled_command(0x14);
  Oled_command( SSD1306_MEMORY_ADDR_MODE );
  Oled_command(0x00);  //Hor Addressing Mode is Used (02 is Ver)
  Oled_command( SSD1306_SET_SEGMENT_REMAP| 0x01);
  Oled_command( SSD1306_COM_SCAN_DIR_DEC );
  Oled_command( SSD1306_SET_COM_PINS );
  Oled_command( 0x02 );
  Oled_command( SSD1306_SET_CONTRAST_CONTROL );
  Oled_command(0x8F);
  Oled_command( SSD1306_SET_PRECHARGE_PERIOD );
  Oled_command( 0xF1 );
  Oled_command( SSD1306_SET_VCOM_DESELECT );
  Oled_command( 0x40 );
  Oled_command( SSD1306_DISPLAY_ALL_ON_RESUME );
  Oled_command( SSD1306_NORMAL_DISPLAY );
  Oled_command( SSD1306_DEACTIVATE_SCROLL );
  Oled_command( SSD1306_DISPLAY_ON );
}

//function to write a string to OLED, passed string
void Oled_writeString(char *characters)
{
  while (*characters) Oled_writeCharacter(*characters++);
}

//function to write a character, passed character
void Oled_writeCharacter(char character)
{
  for (int i=0; i<5; i++) Oled_data((ASCII[character - 0x20][i]));
  Oled_data(0x00);
}

void Oled_setContrast( uint8_t contrast )
{
  Oled_command(SSD1306_SET_CONTRAST_CONTROL );
  Oled_command(contrast);
}

//function to clear OLED by writing to it.
void Oled_clear(void)
{
  int i =0;
    // OLED 128* 32 pixels = total pixels -> (4096 / 1 byte) = 512 passes.
    // SSD1306_CLEAR_SIZE  = 512 for 128* 32 or 1024  for 128*64
    for (i; i<SSD1306_CLEAR_SIZE ; i++) 
    {
      Oled_data(0x00); // clear oled screen  
    }
}

//function to clear OLED  line passed page number
void Oled_clearLine(uint8_t page_num)
{
    Oled_selectPage(page_num);
    int i =0;
  // Clear line of 128 pixels of current page
    for (i; i<128 ; i++) 
    {
      Oled_data(0x00); // clear oled screen  
    }
}

// Function to select [page] i.e. row or line number
// 128*32 has page 0-3
// 128* 64 has page 0-7
// Passed page num / byte
// page 0   8 
// page 1   16
// page 2   24
// page 3   32
// page 4   40
// page 5   48
// page 6   56
// page 7   64

void Oled_selectPage(uint8_t page_num)
{
 uint8_t Result =0xB0 | page_num; // Mask or with zero lets everything thru
 Oled_command(Result); 
 Oled_command(SSD1306_SET_LOWER_COLUMN);
 Oled_command(SSD1306_SET_HIGHER_COLUMN); 
}