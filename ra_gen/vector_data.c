/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI5 RXI (Receive data full) */
            [1] = sci_uart_txi_isr, /* SCI5 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI5 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI5 ERI (Receive error) */
            [4] = dmac_int_isr, /* DMAC1 INT (DMAC1 transfer end) */
            [5] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [6] = sci_uart_rxi_isr, /* SCI2 RXI (Receive data full) */
            [7] = sci_uart_txi_isr, /* SCI2 TXI (Transmit data empty) */
            [8] = sci_uart_tei_isr, /* SCI2 TEI (Transmit end) */
            [9] = sci_uart_eri_isr, /* SCI2 ERI (Receive error) */
            [10] = dmac_int_isr, /* DMAC3 INT (DMAC3 transfer end) */
            [11] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [12] = sci_uart_rxi_isr, /* SCI3 RXI (Receive data full) */
            [13] = sci_uart_txi_isr, /* SCI3 TXI (Transmit data empty) */
            [14] = sci_uart_tei_isr, /* SCI3 TEI (Transmit end) */
            [15] = sci_uart_eri_isr, /* SCI3 ERI (Receive error) */
            [16] = dmac_int_isr, /* DMAC5 INT (DMAC5 transfer end) */
            [17] = sci_uart_rxi_isr, /* SCI8 RXI (Receive data full) */
            [18] = sci_uart_txi_isr, /* SCI8 TXI (Transmit data empty) */
            [19] = sci_uart_tei_isr, /* SCI8 TEI (Transmit end) */
            [20] = sci_uart_eri_isr, /* SCI8 ERI (Receive error) */
            [21] = dmac_int_isr, /* DMAC7 INT (DMAC7 transfer end) */
            [22] = sci_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [23] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [24] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [25] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [26] = dmac_int_isr, /* DMAC2 INT (DMAC2 transfer end) */
            [27] = sci_spi_rxi_isr, /* SCI0 RXI (Receive data full) */
            [28] = sci_spi_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [29] = sci_spi_tei_isr, /* SCI0 TEI (Transmit end) */
            [30] = sci_spi_eri_isr, /* SCI0 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI5_RXI,GROUP0), /* SCI5 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI5_TXI,GROUP1), /* SCI5 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI5_TEI,GROUP2), /* SCI5 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI5_ERI,GROUP3), /* SCI5 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_DMAC1_INT,GROUP4), /* DMAC1 INT (DMAC1 transfer end) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP5), /* ADC0 SCAN END (End of A/D scanning operation) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI2_RXI,GROUP6), /* SCI2 RXI (Receive data full) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI2_TXI,GROUP7), /* SCI2 TXI (Transmit data empty) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_SCI2_TEI,GROUP0), /* SCI2 TEI (Transmit end) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_SCI2_ERI,GROUP1), /* SCI2 ERI (Receive error) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_DMAC3_INT,GROUP2), /* DMAC3 INT (DMAC3 transfer end) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP3), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_SCI3_RXI,GROUP4), /* SCI3 RXI (Receive data full) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_SCI3_TXI,GROUP5), /* SCI3 TXI (Transmit data empty) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_SCI3_TEI,GROUP6), /* SCI3 TEI (Transmit end) */
            [15] = BSP_PRV_VECT_ENUM(EVENT_SCI3_ERI,GROUP7), /* SCI3 ERI (Receive error) */
            [16] = BSP_PRV_VECT_ENUM(EVENT_DMAC5_INT,GROUP0), /* DMAC5 INT (DMAC5 transfer end) */
            [17] = BSP_PRV_VECT_ENUM(EVENT_SCI8_RXI,GROUP1), /* SCI8 RXI (Receive data full) */
            [18] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TXI,GROUP2), /* SCI8 TXI (Transmit data empty) */
            [19] = BSP_PRV_VECT_ENUM(EVENT_SCI8_TEI,GROUP3), /* SCI8 TEI (Transmit end) */
            [20] = BSP_PRV_VECT_ENUM(EVENT_SCI8_ERI,GROUP4), /* SCI8 ERI (Receive error) */
            [21] = BSP_PRV_VECT_ENUM(EVENT_DMAC7_INT,GROUP5), /* DMAC7 INT (DMAC7 transfer end) */
            [22] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP6), /* SCI9 RXI (Receive data full) */
            [23] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP7), /* SCI9 TXI (Transmit data empty) */
            [24] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP0), /* SCI9 TEI (Transmit end) */
            [25] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP1), /* SCI9 ERI (Receive error) */
            [26] = BSP_PRV_VECT_ENUM(EVENT_DMAC2_INT,GROUP2), /* DMAC2 INT (DMAC2 transfer end) */
            [27] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP3), /* SCI0 RXI (Receive data full) */
            [28] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP4), /* SCI0 TXI (Transmit data empty) */
            [29] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP5), /* SCI0 TEI (Transmit end) */
            [30] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP6), /* SCI0 ERI (Receive error) */
        };
        #endif
        #endif