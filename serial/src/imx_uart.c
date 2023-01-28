#include "imx_uart.h"


bool imx_uart_init(
        imx_uart_t *imx_uart,
        uintptr_t base_vaddr,
        bool auto_insert_carriage_return
) {
    if (imx_uart == NULL) {
        return false;
    }
    /* Save pointer to the registers. */
    imx_uart->regs = imx_uart_regs_get(base_vaddr);
    /* Save user's auto carriage return preference. */
    imx_uart->auto_insert_carriage_return = auto_insert_carriage_return;
    /* Disable RX interrupts */
    imx_uart_regs_disable_rx_irq(imx_uart->regs);
    /* Disable RX and TX */
    imx_uart_regs_disable(imx_uart->regs);
    /* TODO: line configuration? */
    /* Enable RX and TX */
    imx_uart_regs_enable(imx_uart->regs);
    /* Enable receive interrupts */
    imx_uart_regs_enable_rx_irq(imx_uart->regs);
    /* Return true for successful initialisation. */
    return true;
}


int imx_uart_put_char(
        imx_uart_t *imx_uart,
        int c
) {
    imx_uart_regs_t *regs = imx_uart->regs;

    if (imx_uart_regs_is_tx_fifo_busy(regs)) {
        return -1;
    }
    /* If `auto_insert_carriage_return` is enabled, we first set the `\r`
     * character and then set the `\n` character. */
    if (c == '\n' && imx_uart->auto_insert_carriage_return) {
        /* Write carriage return first */
        imx_uart_regs_tx_char(regs, '\r');
        /* if we transform a '\n' (LF) into '\r\n' (CR+LF) this shall become an
         * atom, ie we don't want CR to be sent and then fail at sending LF
         * because the TX FIFO is full. Basically there are two options:
         *   - check if the FIFO can hold CR+LF and either send both or none
         *   - send CR, then block until the FIFO has space and send LF.
         * Assuming that if SERIAL_AUTO_CR is set, it's likely this is a serial
         * console for logging, so blocking seems acceptable in this special
         * case.
         */
        while (imx_uart_regs_is_tx_fifo_busy(regs)) {
            /* busy loop */
        }
    }

    imx_uart_regs_tx_char(regs, c);
    return c;
}

int imx_uart_get_char(
        imx_uart_t *imx_uart
) {
    imx_uart_regs_t *regs = imx_uart->regs;
    uint32_t reg = 0;
    int c = -1;

//    if (regs->sr2 & UART_SR2_RXFIFO_RDR) {
//        reg = regs->rxd;
//        if (reg & UART_URXD_READY_MASK) {
//            c = reg & UART_BYTE_MASK;
//        }
//    }
    return c;
}



