#pragma once

#include <sel4cp.h>
#include <sel4/sel4.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "shared_ringbuffer.h"
#include "shared_dma.h"

#define SERIAL_CLIENT_TO_SERIAL_DRIVER_PRINTF_CHANNEL (3)
#define SERIAL_CLIENT_TO_SERIAL_DRIVER_GETCHAR_CHANNEL (5)

typedef struct serial_client serial_client_t;
struct serial_client {
    /* Transmit ring buffer handle. This is a convenience `struct` that contains
     * all the pointers to the relevant Transmit "available" and "used" buffers.
     * */
    ring_handle_t tx_ring_buf_handle;
    /* Receive ring buffer handle. This is a convenience `struct` that contains
     * all the pointers to the relevant Receive "available" and "used" buffers. */
    ring_handle_t rx_ring_buf_handle;
};


