#ifndef BYTETYPE_H
#define BYTETYPE_H

#include <stdbool.h>

struct BYTE_TYPE
{
  bool bits[8];
};

bool getBit(int target, struct BYTE_TYPE input)
{
  return(input.bits[target]);
}

struct BYTE_TYPE returnMask(int mask, struct BYTE_TYPE input)
{
  struct BYTE_TYPE retval;
  int i;

  for(i = 0; i < 8; i++)
  {
    retval.bits[i] = input.bits[i] & mask;
  }

  return retval;
}

void applyMask(int mask, struct BYTE_TYPE *input)
{
  int i;

  for(i = 0; i < 8; i++)
  {
    input->bits[i] = input->bits[i] & mask;
  }
}

typedef struct byte BYTE_TYPE;

#endif
