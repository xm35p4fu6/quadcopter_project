/*----------------------------------------------------------------------
  File Name          : ADXL345.h
  Author             : MPD Application Team
  Version            : V0.0.1
  Date               : 25/09/2009
  Description        : XL345 Registers and bits values
  File ID            : $Id: xl345.h,v 1.1.1.1 2008/11/10 19:45:46 jlee11 Exp $

  Analog Devices ADXL 345 digital output accellerometer 
  with advanced digital features.

  Based on preliminary data sheet Rev 12b

  (c) 2009 Analog Devices application support team.
  xxx@analog.com

  ----------------------------------------------------------------------

  The present firmware which is for guidance only aims at providing
  customers with coding information regarding their products in order
  for them to save time.  As a result, Analog Devices shall not be
  held liable for any direct, indirect or consequential damages with
  respect to any claims arising from the content of such firmware and/or
  the use made by customers of the coding information contained herein
  in connection with their products.

----------------------------------------------------------------------*/




/* ------- Register names ------- */
#define XL345_DEVID           0x00
#define XL345_RESERVED1       0x01
#define XL345_THRESH_TAP      0x1d
#define XL345_OFSX            0x1e
#define XL345_OFSY            0x1f
#define XL345_OFSZ            0x20
#define XL345_DUR             0x21
#define XL345_LATENT          0x22
#define XL345_WINDOW          0x23
#define XL345_THRESH_ACT      0x24
#define XL345_THRESH_INACT    0x25
#define XL345_TIME_INACT      0x26
#define XL345_ACT_INACT_CTL   0x27
#define XL345_THRESH_FF       0x28
#define XL345_TIME_FF         0x29
#define XL345_TAP_AXES        0x2a
#define XL345_ACT_TAP_STATUS  0x2b
#define XL345_BW_RATE         0x2c
#define XL345_POWER_CTL       0x2d
#define XL345_INT_ENABLE      0x2e
#define XL345_INT_MAP         0x2f
#define XL345_INT_SOURCE      0x30
#define XL345_DATA_FORMAT     0x31
#define XL345_DATAX0          0x32
#define XL345_DATAX1          0x33
#define XL345_DATAY0          0x34
#define XL345_DATAY1          0x35
#define XL345_DATAZ0          0x36
#define XL345_DATAZ1          0x37
#define XL345_FIFO_CTL        0x38
#define XL345_FIFO_STATUS     0x39

