/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_sci_spi.h"
#include "r_spi_api.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer7;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer7_ctrl;
extern const timer_cfg_t g_timer7_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer1;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer1_ctrl;
extern const transfer_cfg_t g_transfer1_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer0;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer0_ctrl;
extern const transfer_cfg_t g_transfer0_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_spi0;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_spi0_ctrl;
extern const spi_cfg_t g_spi0_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi_callback
void sci_spi_callback(spi_callback_args_t * p_args);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g9_transfer_dmac_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g9_transfer_dmac_rx_ctrl;
extern const transfer_cfg_t g9_transfer_dmac_rx_cfg;

#ifndef transfer9_dmac_rx_callback
void transfer9_dmac_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart9;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart9_ctrl;
            extern const uart_cfg_t g_uart9_cfg;
            extern const sci_uart_extended_cfg_t g_uart9_cfg_extend;

            #ifndef uart9_callback
            void uart9_callback(uart_callback_args_t * p_args);
            #endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g8_transfer_dmac_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g8_transfer_dmac_rx_ctrl;
extern const transfer_cfg_t g8_transfer_dmac_rx_cfg;

#ifndef transfer8_dmac_rx_callback
void transfer8_dmac_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart8;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart8_ctrl;
            extern const uart_cfg_t g_uart8_cfg;
            extern const sci_uart_extended_cfg_t g_uart8_cfg_extend;

            #ifndef uart8_callback
            void uart8_callback(uart_callback_args_t * p_args);
            #endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g3_transfer_dmac_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g3_transfer_dmac_rx_ctrl;
extern const transfer_cfg_t g3_transfer_dmac_rx_cfg;

#ifndef transfer3_dmac_rx_callback
void transfer3_dmac_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart3;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart3_ctrl;
            extern const uart_cfg_t g_uart3_cfg;
            extern const sci_uart_extended_cfg_t g_uart3_cfg_extend;

            #ifndef uart3_callback
            void uart3_callback(uart_callback_args_t * p_args);
            #endif
/** Timer on GPT Instance. */
extern const timer_instance_t pwm;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t pwm_ctrl;
extern const timer_cfg_t pwm_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t time0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t time0_ctrl;
extern const timer_cfg_t time0_cfg;

#ifndef time0_callback
void time0_callback(timer_callback_args_t * p_args);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g2_transfer_dmac_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g2_transfer_dmac_rx_ctrl;
extern const transfer_cfg_t g2_transfer_dmac_rx_cfg;

#ifndef transfer2_dmac_rx_callback
void transfer2_dmac_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart2;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart2_ctrl;
            extern const uart_cfg_t g_uart2_cfg;
            extern const sci_uart_extended_cfg_t g_uart2_cfg_extend;

            #ifndef uart2_callback
            void uart2_callback(uart_callback_args_t * p_args);
            #endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;

/** Access the ADC instance using these structures when calling API functions directly (::p_api is not used). */
extern adc_instance_ctrl_t g_adc0_ctrl;
extern const adc_cfg_t g_adc0_cfg;
extern const adc_channel_cfg_t g_adc0_channel_cfg;

#ifndef ADC0_callback
void ADC0_callback(adc_callback_args_t * p_args);
#endif

#ifndef NULL
#define ADC_DMAC_CHANNELS_PER_BLOCK_NULL  3
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer_dmac_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer_dmac_rx_ctrl;
extern const transfer_cfg_t g_transfer_dmac_rx_cfg;

#ifndef transfer_dmac_rx_callback
void transfer_dmac_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart5;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart5_ctrl;
            extern const uart_cfg_t g_uart5_cfg;
            extern const sci_uart_extended_cfg_t g_uart5_cfg_extend;

            #ifndef uart5_callback
            void uart5_callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
