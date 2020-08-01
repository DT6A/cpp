#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bmp.h"
#include "error.h"

int get_alignment(BMPINFO *Info)
{
  return (4 - (3 * Info->Width) % 4) % 4;
}

int load_bmp(char *FileName, BMPHEADER *Header, BMPINFO *Info, char **Pixels)
{
  assert(FileName != NULL && Header != NULL && Info != NULL);

  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return E_FOPEN;

  if (fread(Header, sizeof(BMPHEADER), 1, F) != 1 || fread(Info, sizeof(BMPINFO), 1, F) != 1)
  {
    fclose(F);
    return E_FREAD;
  }

  if (Header->Type != SIGNATURE_1 && Header->Type != SIGNATURE_2)
  {
    fclose(F);
    return E_WRONG_FORMAT;
  }

  if (Info->SizeImage == 0)
    Info->SizeImage = Info->Width * Info->Height;

  *Pixels = malloc(Info->SizeImage);

  if (*Pixels == NULL)
  {
    fclose(F);
    return E_MALLOC;
  }
  if (fread(*Pixels, 1, Info->SizeImage, F) != Info->SizeImage)
  {
    fclose(F);
    free(*Pixels);
    *Pixels = NULL;
    return E_FREAD;
  }

  if (Info->Width % 4 != 0)
  {
    int alignment = get_alignment(Info);
    char *Tmp = malloc(Info->Width * Info->Height * 3);

    if (Tmp == NULL)
    {
      fclose(F);
      return E_MALLOC;
    }

    for (int i = 0; i < Info->Height; ++i)
      memcpy(Tmp + Info->Width * 3 * i, (*Pixels) + Info->Width * 3 * i + alignment * i, Info->Width * 3);

    free(*Pixels);
    *Pixels = Tmp;
  }

  fclose(F);
  return 1;
}

int save_bmp(char *FileName, BMPHEADER *Header, BMPINFO *Info, char **Pixels)
{
  assert(FileName != NULL && Header != NULL && Info != NULL && Pixels != NULL);


  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return E_FOPEN;

  int alignment = get_alignment(Info);
  Info->SizeImage = 3 * Info->Height * Info->Width + Info->Height * alignment; 
  Header->Size = sizeof(*Header) + sizeof(*Info) + Info->SizeImage;

  if (fwrite(Header, sizeof(BMPHEADER), 1, F) != 1 || fwrite(Info, sizeof(BMPINFO), 1, F) != 1)
  {
    fclose(F);
    return E_FWRITE;
  }

  if (Info->Width % 4 != 0)
  { 
    char *Tmp = malloc(Info->SizeImage);

    if (Tmp == NULL)
    {
      fclose(F);
      return E_MALLOC;
    }
    memset(Tmp, 0, Info->SizeImage);
    for (int i = 0; i < Info->Height; ++i)
      memcpy(Tmp + Info->Width * 3 * i + alignment * i, (*Pixels) + Info->Width * 3 * i, Info->Width * 3);

    free(*Pixels);
    *Pixels = Tmp;
  }
  
  if (fwrite(*Pixels, 1, Info->SizeImage, F) != Info->SizeImage)
  {
    fclose(F);
    return E_FWRITE;
  }

  fclose(F);
  return 1;
}

int crop(BMPINFO *Info, char **Src, char **Dst, int x, int y, int w, int h)
{
  assert(Info != NULL && Src != NULL && Dst != NULL);
    
  if (w <= 0 || h <= 0 || x < 0 || y < 0 || x + w > Info->Width || y + h > Info->Height)
    return E_CROP_PARAMS;

  *Dst = malloc(w * h * 3);

  if (*Dst == NULL)
    return E_MALLOC;

  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      memcpy((*Dst) + (h - 1 - i) * 3 * w + j * 3, (*Src) + (Info->Height - 1 - y - i) * 3 * Info->Width + (x + j) * 3, 3);
      

  Info->Width = w;
  Info->Height = h;
  Info->SizeImage = w * h * 3;

  return 1;
}

int rotate(BMPINFO *Info, char **Pixels)
{
  assert(Info != NULL && Pixels != NULL);
  
  char *Tmp;

  Tmp = malloc(Info->SizeImage);
  if (Tmp == NULL)
    return E_MALLOC;

  
  for (int i = 0; i < Info->Height; ++i)
    for (int j = 0; j < Info->Width; ++j)
      memcpy(Tmp + j * 3 * Info->Height + i * 3, (*Pixels) + i * 3 * Info->Width + j * 3, 3);
      

  {
    int tw = Info->Width;
    Info->Width = Info->Height;
    Info->Height = tw;
  }
  
  for (int i = 0; i < Info->Height; ++i)
    for (int j = 0; j < Info->Width; ++j)
      memcpy((*Pixels) + i * 3 * Info->Width + j * 3, Tmp + (Info->Height - 1 - i) * 3 * Info->Width + j * 3, 3);
 
  free(Tmp);

  return 1;
}