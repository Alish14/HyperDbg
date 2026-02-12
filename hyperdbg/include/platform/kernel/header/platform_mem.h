/**
* @file platform_mem.h
 * @brief Cross-platform memory allocation API definition.
 * @details This header defines the unified interface for memory operations
 *          on Windows and Linux kernels.
 */
#pragma once

//////////////////////////////////////////////////
//                  Types                       //
//////////////////////////////////////////////////

#if defined(_WIN32)
    #include <ntddk.h>
    // Pool Tag 'gmEM' (reversed for Little Endian readability in dump)
    #ifndef POOLTAG
    #define POOLTAG 'gmEM'
    #endif

    typedef PVOID       PLAT_PTR;
typedef SIZE_T      PLAT_SIZE;
typedef NTSTATUS    PLAT_STATUS;

#define PLAT_SUCCESS STATUS_SUCCESS
#define PLAT_FAIL    STATUS_UNSUCCESSFUL

#elif defined(__linux__) || defined(linux)
#include <linux/types.h>
#include <linux/string.h>
#include <linux/slab.h>

typedef void*       PLAT_PTR;
typedef size_t      PLAT_SIZE;
typedef int         PLAT_STATUS;

#define PLAT_SUCCESS 0
#define PLAT_FAIL    -1
#else
#error "Unsupported Platform"
#endif

//////////////////////////////////////////////////
//                API Prototypes                //
//////////////////////////////////////////////////

/**
 * @brief Allocates a contiguous block of zeroed memory.
 */
PLAT_PTR PlatformAllocateMemory(PLAT_SIZE Size);

/**
 * @brief Frees a previously allocated memory block.
 */
void PlatformFreeMemory(PLAT_PTR Memory);

/**
 * @brief Writes data from a source buffer to a destination address.
 * @param Address Destination (Write Target)
 * @param Buffer Source (Data to write)
 * @param Size Number of bytes
 */
PLAT_STATUS PlatformWriteMemory(PLAT_PTR Address, PLAT_PTR Buffer, PLAT_SIZE Size);

/**
 * @brief Sets a block of memory to a specific value.
 */
void PlatformSetMemory(PLAT_PTR Destination, int Value, PLAT_SIZE Size);
