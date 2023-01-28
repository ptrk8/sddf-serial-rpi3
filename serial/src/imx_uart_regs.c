#include "imx_uart_regs.h"

imx_uart_regs_t *imx_uart_regs_get(uintptr_t base_vaddr) {
    return (imx_uart_regs_t *) base_vaddr;
}

bool imx_uart_regs_is_tx_fifo_busy(
        imx_uart_regs_t *regs
) {
    return !(regs->mu_lsr & MU_LSR_TXEMPTY);
}

void imx_uart_regs_disable_rx_irq(
        imx_uart_regs_t *regs
) {
    regs->mu_ier &= ~MU_IER_ENA_RX_IRQ;
}

void imx_uart_regs_disable(
        imx_uart_regs_t *regs
) {
    regs->mu_cntl &= ~(MU_CNTL_RXE | MU_CNTL_TXE);
}

void imx_uart_regs_enable(
        imx_uart_regs_t *regs
) {
    regs->mu_cntl |= (MU_CNTL_RXE | MU_CNTL_TXE);
}

void imx_uart_regs_enable_rx_irq(
        imx_uart_regs_t *regs
) {
    regs->mu_ier |= MU_IER_ENA_RX_IRQ;
}

void imx_uart_regs_tx_char(
        imx_uart_regs_t *regs,
        int ch
) {
    regs->mu_io = (ch & MASK_UNSAFE(8));
}
