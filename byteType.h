#ifndef BYTETYPE_H
#define BYTETYPE_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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
    int current, powr = 7;

    for(int i = 0; i < 8; i++)
    {
      current = pow(2, powr);
      input->bit[i] = value / current;

      if(value >= current)
      {
        value -= current;
      }
      powr -= 1;
    }
}

int byteToInt(struct BYTE_TYPE input)
{
  int total = 0, powr = 7;

  for(int i = 0; i < 8; i++)
  {
    if(input.bit[i])
    {
      total += pow(2, powr);
    }

    powr -= 1;
  }

  return total;
}

bool getBit(int target, struct BYTE_TYPE input)
{
  return(input.bit[target]);
}

struct BYTE_TYPE addBytes(struct BYTE_TYPE inputL, struct BYTE_TYPE inputR)
{
  struct BYTE_TYPE returnValue;
  int i;

  assignByteByInt(0x00, &returnValue);

  for(i = 7; i > 0; i--)
  {
    returnValue.bit[i] = inputL.bit[i] + inputR.bit[i];
  }

  return returnValue;
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
