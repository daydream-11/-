/* 7zCrc.c -- CRC32 init
2010-12-01 : Igor Pavlov : Public domain */

#include "stdafx.h"
#include "7zCrc.h"
#include "CpuArch.h"

#define kCrcPoly 0xEDB88320

#ifdef MY_CPU_X86_OR_AMD64
  #define CRC_NUM_TABLES 8
  uint32_t MY_FAST_CALL CrcUpdateT8(uint32_t v, const void *data, size_t size, const uint32_t *table);
#elif defined(MY_CPU_LE)
  #define CRC_NUM_TABLES 4
#else
  #define CRC_NUM_TABLES 5
  #define CRC_UINT32_SWAP(v) ((v >> 24) | ((v >> 8) & 0xFF00) | ((v << 8) & 0xFF0000) | (v << 24))
  uint32_t MY_FAST_CALL CrcUpdateT1_BeT4(uint32_t v, const void *data, size_t size, const uint32_t *table);
#endif

#ifndef MY_CPU_BE
  uint32_t MY_FAST_CALL CrcUpdateT4(uint32_t v, const void *data, size_t size, const uint32_t *table);
#endif

typedef uint32_t (MY_FAST_CALL *CRC_FUNC)(uint32_t v, const void *data, size_t size, const uint32_t *table);

static CRC_FUNC g_CrcUpdate;
uint32_t g_CrcTable[256 * CRC_NUM_TABLES];

uint32_t MY_FAST_CALL CrcUpdate(uint32_t v, const void *data, size_t size)
{
  return g_CrcUpdate(v, data, size, g_CrcTable);
}

uint32_t MY_FAST_CALL CrcCalc(const void *data, size_t size)
{
  return g_CrcUpdate(CRC_INIT_VAL, data, size, g_CrcTable) ^ CRC_INIT_VAL;
}

void MY_FAST_CALL CrcGenerateTable()
{
  uint32_t i;
  for (i = 0; i < 256; i++)
  {
    uint32_t r = i;
    unsigned j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ~((r & 1) - 1));
    g_CrcTable[i] = r;
  }
  for (; i < 256 * CRC_NUM_TABLES; i++)
  {
    uint32_t r = g_CrcTable[i - 256];
    g_CrcTable[i] = g_CrcTable[r & 0xFF] ^ (r >> 8);
  }
  
  #ifdef MY_CPU_LE

  g_CrcUpdate = CrcUpdateT4;
  
  #if CRC_NUM_TABLES == 8
  if (!CPU_Is_InOrder())
    g_CrcUpdate = CrcUpdateT8;
  #endif

  #else
  {
    #ifndef MY_CPU_BE
    uint32_t k = 1;
    if (*(const BYTE *)&k == 1)
      g_CrcUpdate = CrcUpdateT4;
    else
    #endif
    {
      for (i = 256 * CRC_NUM_TABLES - 1; i >= 256; i--)
      {
        uint32_t x = g_CrcTable[i - 256];
        g_CrcTable[i] = CRC_UINT32_SWAP(x);
      }
      g_CrcUpdate = CrcUpdateT1_BeT4;
    }
  }
  #endif
}
