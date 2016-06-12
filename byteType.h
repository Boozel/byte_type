#ifndef BYTETYPE_H
#define BYTETYPE_H

#include <stdbool.h>
#include <stdio.h>

/*
    ENDIAN-NESS:

    BITS:

   MSB           LSB
    |             |
    V             V
    0 0 0 0 0 0 0 0

    0 1 2 3 4 5 6 7
*/

struct BYTE_TYPE
{
  bool bit[8];
};
void printByte(struct BYTE_TYPE input);

void assignByteByInt(int value, struct BYTE_TYPE *input)
{
  input->bit[0] = value / 128;
  if(value >= 128)
  {
    value -= 128;
  }
  input->bit[1] = value / 64;
  if(value >= 64)
  {
    value -= 64;
  }
  input->bit[2] = value / 32;
  if(value >= 32)
  {
    value -= 32;
  }
  input->bit[3] = value / 16;
  if(value >= 16)
  {
    value -= 16;
  }
  input->bit[4] = value / 8;
  if(value >= 8)
  {
    value -= 8;
  }
  input->bit[5] = value / 4;
  if(value >= 4)
  {
    value -= 4;
  }
  input->bit[6] = value / 2;
  if(value >= 2)
  {
    value -= 2;
  }
  input->bit[7] = value / 1;
  if(value >= 1)
  {
    value -= 1;
  }
}

bool getBit(int target, struct BYTE_TYPE input)
{
  return(input.bit[target]);
}

void copyByte(struct BYTE_TYPE *dest, struct BYTE_TYPE input)
{
  //I believe doing this by hand will be faster than
  // using a for loop (eww jumps!)

  dest->bit[0] = input.bit[0];
  dest->bit[1] = input.bit[1];
  dest->bit[2] = input.bit[2];
  dest->bit[3] = input.bit[3];
  dest->bit[4] = input.bit[4];
  dest->bit[5] = input.bit[5];
  dest->bit[6] = input.bit[6];
  dest->bit[7] = input.bit[7];
}

struct BYTE_TYPE returnMaskedValue(int mask, struct BYTE_TYPE input)
{
  struct BYTE_TYPE retval;
  int i;

  for(i = 0; i < 8; i++)
  {
    retval.bit[i] = input.bit[i] & mask;
  }

  return retval;
}

void applyMask(int mask, struct BYTE_TYPE *input)
{
  int i;
  struct BYTE_TYPE maskBits;

  assignByteByInt(mask, &maskBits);

  for(i = 0; i < 8; i++)
  {
    input->bit[i] = input->bit[i] & maskBits.bit[i];
  }
}

void arithShiftL(int numShifts, struct BYTE_TYPE *input)
{
  int i, q;
  bool carry;

  for(i = 0; i < numShifts; i++)
  {
    carry = input->bit[0];

    for(q = 0; q < 7; q++)
    {
      input->bit[q] = input->bit[q + 1];
    }

    input->bit[7] = carry;
  }
}

void arithShiftR(int numShifts, struct BYTE_TYPE *input)
{
  int i, q;
  bool carry;

  for(i = 0; i < numShifts; i++)
  {
    carry = input->bit[7];

    for(q = 7; q > 0; q--)
    {
      input->bit[q] = input->bit[q - 1];
    }

    input->bit[0] = carry;
  }
}

void f0LogicalShiftL(int numShifts, struct BYTE_TYPE *input)
{
  struct BYTE_TYPE carboncopy;
  int i, q = 0, z;

  assignByteByInt(0x00, &carboncopy);
  copyByte(&carboncopy, *input);

  for( i = numShifts; i < 8; i++)
  {
    input->bit[q] = carboncopy.bit[i];
    q++;
  }

  //Fill 0s into remaining spots
  for(z = q; z < 8; z++)
  {
    input->bit[z] = 0;
  }
}

void f1LogicalShiftL(int numShifts, struct BYTE_TYPE *input)
{
  struct BYTE_TYPE carboncopy;
  int i, q = 0, z;

  assignByteByInt(0x00, &carboncopy);
  copyByte(&carboncopy, *input);

  for( i = numShifts; i < 8; i++)
  {
    input->bit[q] = carboncopy.bit[i];
    q++;
  }

  //Fill 0s into remaining spots
  for(z = q; z < 8; z++)
  {
    input->bit[z] = 1;
  }
}

void f0LogicalShiftR(int numShifts, struct BYTE_TYPE *input)
{
  struct BYTE_TYPE carboncopy;
  int i, q = 0;

  assignByteByInt(0x00, &carboncopy);
  copyByte(&carboncopy, *input);

  for( i = numShifts; i < 8; i++)
  {
    input->bit[i] = carboncopy.bit[q];
    q++;
  }

  //Fill 0s into remaining spots
  for(q = 0; q < numShifts; q++)
  {
    input->bit[q] = 0;
  }
}

void f1LogicalShiftR(int numShifts, struct BYTE_TYPE *input)
{
  struct BYTE_TYPE carboncopy;
  int i, q = 0;

  assignByteByInt(0x00, &carboncopy);
  copyByte(&carboncopy, *input);

  for( i = numShifts; i < 8; i++)
  {
    input->bit[i] = carboncopy.bit[q];
    q++;
  }

  //Fill 0s into remaining spots
  for(q = 0; q < numShifts; q++)
  {
    input->bit[q] = 1;
  }
}

void printByte(struct BYTE_TYPE input)
{
  printf("%d%d%d%d%d%d%d%d", input.bit[0],
                             input.bit[1],
                             input.bit[2],
                             input.bit[3],
                             input.bit[4],
                             input.bit[5],
                             input.bit[6],
                             input.bit[7]);
}

#endif
