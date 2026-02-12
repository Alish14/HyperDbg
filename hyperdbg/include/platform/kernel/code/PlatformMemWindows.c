/**
* @file mem.c
 * @author Behrooz Abbassi (BehroozAbbassi@hyperdbg.org)
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief Implementation of cross APIs for different platforms for memory allocation
 * @details
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "platform_mem.h"


/**
 * @brief Allocate a contiguous zeroed memory
 *
 * @param NumberOfBytes
 * @return PVOID
 */
PLAT_PTR
PlatformMemAllocateContiguousZeroedMemory(PLAT_PTR NumberOfBytes)
{
    PLAT_PTR            Result          = NULL;
    PHYSICAL_ADDRESS MaxPhysicalAddr = {.QuadPart = MAXULONG64};

    Result = MmAllocateContiguousMemory(NumberOfBytes, MaxPhysicalAddr);
    if (Result != NULL)
        RtlSecureZeroMemory(Result, NumberOfBytes);

    return Result;
}

/**
 * @brief Allocate a non-paged buffer
 *
 * @param NumberOfBytes
 * @return PVOID
 */
PLAT_PTR
PlatformAllocateMemory(
    PLAT_SIZE Size
)
{

    PLAT_PTR Result = ExAllocatePoolWithTag(NonPagedPool, Size, POOLTAG);

    if (Result != NULL) {
        RtlSecureZeroMemory(Result, Size);
    }

    return Result;
}

/**
 * @brief Allocate a non-paged buffer (use QUOTA)
 *
 * @param NumberOfBytes
 * @return PVOID
 */
PLAT_PTR
PlatformMemAllocateNonPagedPoolWithQuota(PLAT_SIZE NumberOfBytes)
{
    PLAT_PTR Result = ExAllocatePool2(POOL_FLAG_NON_PAGED | POOL_FLAG_USE_QUOTA, NumberOfBytes, POOLTAG);

    return Result;
}

/**
 * @brief Allocate a non-paged buffer (zeroed)
 *
 * @param NumberOfBytes
 * @return PVOID
 */
PLAT_PTR
PlatformMemAllocateZeroedNonPagedPool(PLAT_SIZE  NumberOfBytes)
{
    PLAT_PTR Result = ExAllocatePoolWithTag(NonPagedPool, NumberOfBytes, POOLTAG);

    if (Result != NULL)
        RtlSecureZeroMemory(Result, NumberOfBytes);

    return Result;
}

/**
 * @brief Free (dellocate) a non-paged buffer
 *
 * @param BufferAddress
 * @return VOID
 */
void
PlatformFreeMemory(
    PLAT_PTR Memory
)
{
    if (Memory) {
        ExFreePoolWithTag(Memory, POOLTAG);
    }
}


PLAT_STATUS
PlatformWriteMemory(
    PLAT_PTR Address,
    PLAT_PTR Buffer,
    PLAT_SIZE Size
)
{
    if (!Address || !Buffer) {
        return PLAT_FAIL;
    }

    RtlCopyMemory(Address, Buffer, Size);
    return PLAT_SUCCESS;
}

void
PlatformSetMemory(
    PLAT_PTR Destination,
    int Value,
    PLAT_SIZE Size
)
{
    if (Destination) {
        RtlFillMemory(Destination, Size, Value);
    }
}