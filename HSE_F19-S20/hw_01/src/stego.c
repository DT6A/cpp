#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stego.h"
#include "error.h"

int EncodeSymb(char c)
{
  if ('A' <= c && c <= 'Z')
    return c - 'A';
  else if (c == ' ')
    return 26;
  else if (c == '.')
    return 27;
  else if (c == ',')
    return 28;
  else
    return -1;
}

char DecodeSymb(int n)
{
  if (n < 26)
    return n + 'A';
  else if (n == 26)
    return ' ';
  else if (n == 27)
    return '.';
  else if (n == 28)
    return ',';
  else
    return -1;
}

int EncodeColor(char c)
{
  if (c == 'R')
    return 2;
  if (c == 'G')
    return 1;
  if (c == 'B')
    return 0;

  return -1;
}

void set_last_bit(char **Pixels, int W, int H, int x, int y, int color, int n)
{
  y = H - y - 1; // (0, 0) is upper left corner

  (*Pixels)[y * W * 3 + x * 3 + color] |= (n & 1);
  (*Pixels)[y * W * 3 + x * 3 + color] &= 254 + (n & 1);        
}

int reset_last_bit(char **Pixels, int W, int H, int x, int y, int color)
{
  y = H - y - 1; // (0, 0) is upper left corner
  
  return (*Pixels)[y * W * 3 + x * 3 + color] & 1;        
}

int EncodeMessage(char *KeyFN, char *MsgFN, char **Pixels, int W, int H)
{
  assert(KeyFN != NULL && MsgFN != NULL && Pixels != NULL);

  FILE *KeyF = NULL, *MsgF = NULL;

  if ((KeyF = fopen(KeyFN, "r")) == NULL || (MsgF = fopen(MsgFN, "r")) == NULL)
  {
    fclose(KeyF);
    return E_FOPEN;
  }

  int x, y;
  char c, ch;

  while (fscanf(MsgF, "%c", &ch) != EOF)
  {
    int n = EncodeSymb(ch);

    if (n != -1)
    {
      for (int i = 0; i < 5; ++i)
        if (fscanf(KeyF, "%d %d %c", &x, &y, &c) != 3 || x < 0 || x > W || y < 0 || y > H)
        {
          fclose(KeyF);
          fclose(MsgF);
          return E_STEGO;
        }
        else
        {
          int color = EncodeColor(c);

          if (color == -1)
          {
            fclose(KeyF);
            fclose(MsgF);
            return E_STEGO;
          }

          set_last_bit(Pixels, W, H, x, y, color, n);

          n >>= 1;
        }
    }
  }

  fclose(KeyF);
  fclose(MsgF);

  return 1;
}

int DecodeMessage(char *KeyFN, char *MsgFN, char **Pixels, int W, int H)
{
  assert(KeyFN != NULL && MsgFN != NULL && Pixels != NULL);

  FILE *KeyF = NULL, *MsgF = NULL;

  if ((KeyF = fopen(KeyFN, "r")) == NULL || (MsgF = fopen(MsgFN, "w")) == NULL)
  {
    fclose(KeyF);
    return E_FOPEN;
  }

  int x, y, n = 0, len = 0;
  char c;

  while (fscanf(KeyF, "%d %d %c", &x, &y, &c) == 3)
  {
    if (x < 0 || x > W || y < 0 || y > H)
    {
      fclose(KeyF);
      fclose(MsgF);
      return E_STEGO;
    }

    int color = EncodeColor(c);
    if (color == -1)
    {
      fclose(KeyF);
      fclose(MsgF);
      return E_STEGO;
    }

          
    n <<= 1;
    n |= reset_last_bit(Pixels, W, H, x, y, color);
    ++len;

    if (len == 5)
    {
      int res = 0;
      for (int i = 0; i < 5; ++i)
      {
        res <<= 1;
        res |= n & 1;
        n >>= 1;
      }
      
      fprintf(MsgF, "%c", DecodeSymb(res));
      n = len = 0;
    }
  }
    
  fclose(KeyF);
  fclose(MsgF);
  
  return 1;
}