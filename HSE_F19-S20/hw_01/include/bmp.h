#ifndef __BMP_H
#define __BMP_H

#include <stdint.h>

#define SIGNATURE_1 0x4D42
#define SIGNATURE_2 0x424D

#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t
#define LONG int32_t

#pragma pack(push)
#pragma pack(1)

struct BITMAPFILEHEADER
{
  WORD Type;
  DWORD Size;
  WORD Reserved1, 
    Reserved2;
  DWORD OffBits;
};

struct BITMAPINFO
{
  DWORD Size; 
  LONG Width, 
    Height;
  WORD Planes, 
    BitCount;
  DWORD Compression,
    SizeImage;
  LONG XPels,
    YPels;
  DWORD ClrUsed,
    ClrImportant;
};

#pragma pack(pop)

typedef struct BITMAPFILEHEADER BMPHEADER;
typedef struct BITMAPINFO BMPINFO;

int load_bmp(char *FileName, BMPHEADER *Header, BMPINFO *Info, char **Pixels);

int save_bmp(char *FileName, BMPHEADER *Header, BMPINFO *Info, char **Pixels);

int crop(BMPINFO *Info, char **Src, char **Dst, int x, int y, int w, int h);

int rotate(BMPINFO *Info, char **Pixels);

#endif //__BMP_H