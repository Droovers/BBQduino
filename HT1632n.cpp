/*  Last edit: Dec 23, 2014
 * HT1632c support files for Adafruit 16x24 LED matrix panels
 * originally from Adafruit Industries
 *  https://github.com/adafruit/HT1632
 *
 * modifications Copyright (c) 2013-2014
 *    by B. Tod Cox <btodcox@users.sourceforge.net>
 *    and provided under GPL v2 License
 * 
 * modifications allow for compiling with avr-gcc >= 4.6.1,
 * support for >4 LED panels attached,
 * support for over-writing display without needing to call clearScreen,
 * support for functions to make vertical and horizontal scrolling easier
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 *
 */
#include "HT1632n.h"
#include "glcdfontn.c"


#define swap(a, b) { uint16_t t = a; a = b; b = t; }

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, uint8_t cs1) {
  matrices = (HT1632 *)malloc(sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrixNum  = 1;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
				 uint8_t cs1, uint8_t cs2) {
  matrices = (HT1632 *)malloc(2 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrixNum  = 2;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
				 uint8_t cs1, uint8_t cs2, uint8_t cs3) {
  matrices = (HT1632 *)malloc(3 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrixNum  = 3;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
				 uint8_t cs1, uint8_t cs2, 
				 uint8_t cs3, uint8_t cs4) {
  matrices = (HT1632 *)malloc(4 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrices[3] = HT1632(data, wr, cs4);
  matrixNum  = 4;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
         uint8_t cs1, uint8_t cs2, 
         uint8_t cs3, uint8_t cs4,
         uint8_t cs5) {
  matrices = (HT1632 *)malloc(5 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrices[3] = HT1632(data, wr, cs4);
  matrices[4] = HT1632(data, wr, cs5);
  matrixNum  = 5;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
         uint8_t cs1, uint8_t cs2, 
         uint8_t cs3, uint8_t cs4,
         uint8_t cs5, uint8_t cs6) {
  matrices = (HT1632 *)malloc(6 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrices[3] = HT1632(data, wr, cs4);
  matrices[4] = HT1632(data, wr, cs5);
  matrices[5] = HT1632(data, wr, cs6);
  matrixNum  = 6;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
         uint8_t cs1, uint8_t cs2, 
         uint8_t cs3, uint8_t cs4,
         uint8_t cs5, uint8_t cs6,
         uint8_t cs7) {
  matrices = (HT1632 *)malloc(7 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrices[3] = HT1632(data, wr, cs4);
  matrices[4] = HT1632(data, wr, cs5);
  matrices[5] = HT1632(data, wr, cs6);
  matrices[6] = HT1632(data, wr, cs7);
  matrixNum  = 7;
  _width = 24 * matrixNum;
  _height = 16;
}

HT1632LEDMatrix::HT1632LEDMatrix(uint8_t data, uint8_t wr, 
         uint8_t cs1, uint8_t cs2, 
         uint8_t cs3, uint8_t cs4,
         uint8_t cs5, uint8_t cs6,
         uint8_t cs7, uint8_t cs8) {
  matrices = (HT1632 *)malloc(8 * sizeof(HT1632));

  matrices[0] = HT1632(data, wr, cs1);
  matrices[1] = HT1632(data, wr, cs2);
  matrices[2] = HT1632(data, wr, cs3);
  matrices[3] = HT1632(data, wr, cs4);
  matrices[4] = HT1632(data, wr, cs5);
  matrices[5] = HT1632(data, wr, cs6);
  matrices[6] = HT1632(data, wr, cs7);
  matrices[7] = HT1632(data, wr, cs8);
  matrixNum  = 8;
  _width = 24 * matrixNum;
  _height = 16;
}

void HT1632LEDMatrix::setPixel(uint8_t x, uint8_t y) {
  drawPixel(x, y, 1);
}
void HT1632LEDMatrix::clrPixel(uint8_t x, uint8_t y) {
  drawPixel(x, y, 0);
}

void HT1632LEDMatrix::drawPixel(uint8_t x, uint8_t y, uint8_t color) {
  if (y >= _height) return;
  if (x >= _width) return;

  uint8_t m;
  // figure out which matrix controller it is
  m = x / 24;
  x %= 24;

  uint16_t i;

  if (x < 8) {
    i = 7;
  } else if (x < 16) {
    i = 128 + 7;
  } else {
    i = 256 + 7;
  }
  i -= (x % 8);

  if (y < 8) {
    y *= 2;
  } else {
    y = (y-8) * 2 + 1;
  } 

  i += y * 8;

  if (color) 
    matrices[m].setPixel(i);
  else
    matrices[m].clrPixel(i);
}


uint8_t HT1632LEDMatrix::width() {
  return _width;
}

uint8_t HT1632LEDMatrix::height() {
  return _height;
}

/* modifed from Adafruit library; original code placed all matrices
in RC master mode.  The resuting signals on OSC and SYNC were not
pretty due to multiple active drivers on each signal.*/
void HT1632LEDMatrix::begin(uint8_t type) {
  for (uint8_t i=0; i<matrixNum; i++) {
    if (i==0) {   
       matrices[i].begin(type); 
    } else {
      matrices[i].beginSlave(type);
    }
  }
}

void HT1632LEDMatrix::clearScreen() {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].clearScreen();
  }
}

void HT1632LEDMatrix::clearBuffer() {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].clearBuffer();
  }
}

void HT1632LEDMatrix::fillScreen() {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].fillScreen();
  }
}

void HT1632LEDMatrix::setBrightness(uint8_t b) {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].setBrightness(b);
  }
}

void HT1632LEDMatrix::blink(boolean b) {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].blink(b);
  }
}

void HT1632LEDMatrix::writeScreen() {
  for (uint8_t i=0; i<matrixNum; i++) {
    matrices[i].writeScreen();
  }
}

// bresenham's algorithm - thx wikpedia
void HT1632LEDMatrix::drawLine(int8_t x0, int8_t y0, int8_t x1, int8_t y1, 
		      uint8_t color) {
  uint16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// draw a rectangle
void HT1632LEDMatrix::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		      uint8_t color) {
  drawLine(x, y, x+w-1, y, color);
  drawLine(x, y+h-1, x+w-1, y+h-1, color);

  drawLine(x, y, x, y+h-1, color);
  drawLine(x+w-1, y, x+w-1, y+h-1, color);
}

// fill a rectangle
void HT1632LEDMatrix::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		      uint8_t color) {
  for (uint8_t i=x; i<x+w; i++) {
    for (uint8_t j=y; j<y+h; j++) {
      drawPixel(i, j, color);
    }
  }
}



// draw a circle outline
void HT1632LEDMatrix::drawCircle(uint8_t x0, uint8_t y0, uint8_t r, 
			uint8_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0, y0+r, color);
  drawPixel(x0, y0-r, color);
  drawPixel(x0+r, y0, color);
  drawPixel(x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
    
  }
}


// fill a circle
void HT1632LEDMatrix::fillCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawLine(x0, y0-r, x0, y0+r+1, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawLine(x0+x, y0-y, x0+x, y0+y+1, color);
    drawLine(x0-x, y0-y, x0-x, y0+y+1, color);
    drawLine(x0+y, y0-x, x0+y, y0+x+1, color);
    drawLine(x0-y, y0-x, x0-y, y0+x+1, color);
  }
}

void HT1632LEDMatrix::setCursor(uint8_t x, uint8_t y) {
  cursor_x = x; 
  cursor_y = y;
}

void HT1632LEDMatrix::setTextSize(uint8_t s) {
  textsize = s;
}

void HT1632LEDMatrix::setTextColor(uint8_t c) {
  textcolor = c;
}

#if ARDUINO >= 100
size_t HT1632LEDMatrix::write(uint8_t c) {
#else
void HT1632LEDMatrix::write(uint8_t c) {
#endif
  if (c == '\n') {
    cursor_y += textsize*8;
    cursor_x = 0;
  } else if (c == '\r') {
    // skip em
  } else {
    drawChar(cursor_x, cursor_y, c, textcolor, textsize);
    cursor_x += textsize*6;
  }
#if ARDUINO >= 100
  return 1;
#endif
}


// draw a character
// modified from Adafruit code to support writing blank pixels
// of characters.  Previously, writing two chars to same location
// results in a logical ORing of all on pixels in the two chars
void HT1632LEDMatrix::drawChar(uint8_t x, uint8_t y, char c,
               uint16_t color, uint8_t size) {
  for (uint8_t i =0; i<5; i++ ) {
    uint8_t line = pgm_read_byte(font+(c*5)+i);
    for (uint8_t j = 0; j<8; j++) {
      if (true) {
   if (size == 1) // default size
     drawPixel(x+i, y+j, ((line&0x1)?color:0));
   else {  // big size
     fillRect(x+i*size, y+j*size, size, size, ((line&0x1)?color:0));
   }
      }
      line >>= 1;
    }
  }
}


void HT1632LEDMatrix::drawBitmap(uint8_t x, uint8_t y, 
			const uint8_t *bitmap, uint8_t w, uint8_t h,
			uint8_t color) {
  for (uint8_t j=0; j<h; j++) {
    for (uint8_t i=0; i<w; i++ ) {
      if (pgm_read_byte(bitmap + i + (j/8)*w) & _BV(j%8)) {
	drawPixel(x+i, y+j, color);
      }
    }
  }
}

void HT1632LEDMatrix::drawBitmapLeft(uint8_t x, uint8_t y, 
			const uint8_t *bitmap, uint8_t w, uint8_t h,
			uint8_t color) {
  for (uint8_t j=0; j<h; j++) {
    for (uint8_t i=0; i<w; i++ ) {
      uint16_t n = (j * (uint16_t)w) + i;
      if (pgm_read_byte(bitmap + (n>>3)) & (1<<(7-(n&7)))) {
	      drawPixel(x+j, y+w-1-i, color);
      } else {
        drawPixel(x+j, y+w-1-i, 0);
      }
    }
  }
}

void HT1632LEDMatrix::drawBitmapRight(uint8_t x, uint8_t y, 
			const uint8_t *bitmap, uint8_t w, uint8_t h,
			uint8_t color) {
  for (uint8_t j=0; j<h; j++) {
    for (uint8_t i=0; i<w; i++ ) {
      uint16_t n = (j * (uint16_t)w) + i;
      if (pgm_read_byte(bitmap + (n>>3)) & (1<<(7-(n&7)))) {
	      drawPixel(x+h-1-j, y+i, color);
      } else {
        drawPixel(x+h-1-j, y+i, 0);
      }
    }
  }
}


//////////////////////////////////////////////////////////////////////////


HT1632::HT1632(int8_t data, int8_t wr, int8_t cs, int8_t rd) {
  _data = data;
  _wr = wr;
  _cs = cs;
  _rd = rd;

  for (uint8_t i=0; i<48; i++) {
    ledmatrix[i] = 0;
  }
}

void HT1632::begin(uint8_t type) {
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  pinMode(_wr, OUTPUT);
  digitalWrite(_wr, HIGH);
  pinMode(_data, OUTPUT);
  
  if (_rd >= 0) {
    pinMode(_rd, OUTPUT);
    digitalWrite(_rd, HIGH);
  }
  
  sendcommand(HT1632_SYS_DIS);  //following recommendation from http://forums.parallax.com/showthread.php/117423-Electronics-I-O-(outputs-to-common-anode-RGB-LED-matrix)-question/page4
  sendcommand(HT1632_LED_ON);
  sendcommand(HT1632_BLINK_OFF);
//  sendcommand(HT1632_MASTER_MODE);  //bogus command
  sendcommand(HT1632_INT_RC);  //this actually enables RC_Master_Mode
  sendcommand(type);
  sendcommand(HT1632_SYS_EN);
  sendcommand(HT1632_PWM_CONTROL | 0xF);
  
  WIDTH = 24;
  HEIGHT = 16;
}

void HT1632::beginSlave(uint8_t type) {
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  pinMode(_wr, OUTPUT);
  digitalWrite(_wr, HIGH);
  pinMode(_data, OUTPUT);
  
  if (_rd >= 0) {
    pinMode(_rd, OUTPUT);
    digitalWrite(_rd, HIGH);
  }
  
  sendcommand(HT1632_SYS_DIS);  //following recommendation from http://forums.parallax.com/showthread.php/117423-Electronics-I-O-(outputs-to-common-anode-RGB-LED-matrix)-question/page4
  sendcommand(HT1632_LED_ON);
  sendcommand(HT1632_BLINK_OFF);
//  sendcommand(HT1632_MASTER_MODE);  //bogus command
//  sendcommand(HT1632_INT_RC);  //this actually enables RC_Master_Mode
  sendcommand(HT1632_SLAVE_MODE);
  sendcommand(type);
  sendcommand(HT1632_SYS_EN);
  sendcommand(HT1632_PWM_CONTROL | 0xF);
  
  WIDTH = 24;
  HEIGHT = 16;
}

void HT1632::setBrightness(uint8_t pwm) {
  if (pwm > 15) pwm = 15;
  sendcommand(HT1632_PWM_CONTROL | pwm);
}

void HT1632::blink(boolean blinky) {
  if (blinky) 
    sendcommand(HT1632_BLINK_ON);
  else
    sendcommand(HT1632_BLINK_OFF);
}

void HT1632::setPixel(uint16_t i) {
  ledmatrix[i/8] |= _BV(i%8); 
}

void HT1632::clrPixel(uint16_t i) {
  ledmatrix[i/8] &= ~_BV(i%8); 
}

void HT1632::dumpScreen() {
  Serial.println("---------------------------------------");

  for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i++) {
    Serial.print("0x");
    Serial.print(ledmatrix[i], HEX);
    Serial.print(" ");
    if (i % 3 == 2) Serial.println();
  }

  Serial.println("\n---------------------------------------");
}

void HT1632::writeScreen() {

  digitalWrite(_cs, LOW);

  writedata(HT1632_WRITE, 3);
  // send with address 0
  writedata(0, 7);

  for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i+=2) {
    uint16_t d = ledmatrix[i];
    d <<= 8;
    d |= ledmatrix[i+1];

    writedata(d, 16);
  }
  digitalWrite(_cs, HIGH);
}

void HT1632::clearBuffer(){
  for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i++) {
    ledmatrix[i] = 0;
  }
}

void HT1632::clearScreen() {
  for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i++) {
    ledmatrix[i] = 0;
  }
  writeScreen();
}


void HT1632::writedata(uint16_t d, uint8_t bits) {
  pinMode(_data, OUTPUT);
  for (uint8_t i=bits; i > 0; i--) {
    digitalWrite(_wr, LOW);
   if (d & _BV(i-1)) {
     digitalWrite(_data, HIGH);
   } else {
     digitalWrite(_data, LOW);
   }
  digitalWrite(_wr, HIGH);
  }
  pinMode(_data, INPUT);
}




void HT1632::writeRAM(uint8_t addr, uint8_t data) {
  //Serial.print("Writing 0x"); Serial.print(data&0xF, HEX);
  //Serial.print(" to 0x"); Serial.println(addr & 0x7F, HEX);

  uint16_t d = HT1632_WRITE;
  d <<= 7;
  d |= addr & 0x7F;
  d <<= 4;
  d |= data & 0xF;
 
  digitalWrite(_cs, LOW);
  writedata(d, 14);
  digitalWrite(_cs, HIGH);
}


void HT1632::sendcommand(uint8_t cmd) {
  uint16_t data = 0;
  data = HT1632_COMMAND;
  data <<= 8;
  data |= cmd;
  data <<= 1;
  
  digitalWrite(_cs, LOW);
  writedata(data, 12);
  digitalWrite(_cs, HIGH);  
}


void HT1632::fillScreen() {
  for (uint8_t i=0; i<(WIDTH*HEIGHT/8); i++) {
    ledmatrix[i] = 0xFF;
  }
  writeScreen();
}
