#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "stego.h"
#include "error.h"

void ErrorProc(int err)
{
  switch (err)
  {
    case E_FOPEN:
      printf("Failed to open file\n");
      break;
    case E_FREAD:
      printf("Failed to read data\n");
      break;  
    case E_FWRITE:
      printf("Failed to write data\n");
      break;
    case E_MALLOC:
      printf("Failed to allocate memory\n");
      break;
    case E_WRONG_FORMAT:
      printf("Wrong file format\n");
      break;
    case E_CROP_PARAMS:
      printf("Wrong params for the crop\n");
      break;
    case E_STEGO:
      printf("Stego error\n");
      break;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 5)
    return 30;

  char *Pixels = NULL, *NewPicture = NULL;
  BMPHEADER Header;
  BMPINFO Info;
  int err = 1, IsInsert = 0;
  int ReqSave = 1;

  err = load_bmp(argv[2], &Header, &Info, &Pixels);
  if (err != 1)
  {
    ErrorProc(err);
    free(Pixels);
    return 30;
  }
  if (strcmp(argv[1], "crop-rotate") == 0)
  {
    if (argc < 7 || 
      (err = crop(&Info, &Pixels, &NewPicture, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]))) != 1 ||
      (err = rotate(&Info, &NewPicture)) != 1)
    {
      ErrorProc(err);
      free(Pixels);
      free(NewPicture);    
      return 30;
    }

  }
  else if (strcmp(argv[1], "insert") == 0)
  {
    if (argc < 6 || (err = EncodeMessage(argv[4], argv[5], &Pixels, Info.Width, Info.Height)) != 1)
    {
      ErrorProc(err);
      free(Pixels);
      return 30;
    }
    IsInsert = 1;
    NewPicture = Pixels;
  }
  
  else if (strcmp(argv[1], "extract") == 0)
  {
    if (argc < 5 || (err = DecodeMessage(argv[3], argv[4], &Pixels, Info.Width, Info.Height)) != 1)
    {
      ErrorProc(err);
      free(Pixels);
      return 30;
    }
    ReqSave = 0;
  }

  if (ReqSave)
  {
    err = save_bmp(argv[3], &Header, &Info, &NewPicture);
  
    if (err != 1)
    {
      ErrorProc(err);
      free(Pixels);
      free(NewPicture);
      return 30;
    }
  }

  free(Pixels);
  if (!IsInsert)
    free(NewPicture);
  return 0;
}