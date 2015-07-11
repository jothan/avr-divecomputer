#ifndef DEPTH_H
#define DEPTH_H

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_spi.h>

#include "timer.h"
#include <time.h> 
#include "types.h"

enum DepthSampling : unsigned {
    OSR_256 = 0,
    OSR_512 = 1,
    OSR_1024 = 2,
    OSR_2048 = 3,
    OSR_4096 = 4,
};


extern "C" void DMA1_Stream3_IRQHandler(void);
extern "C" void DMA1_Stream4_IRQHandler(void);

class PressureSensor {

    enum State {
        UNINIT, WAIT_RESET, WAIT_PROM, WAIT_SAMPLE_SEND, WAIT_SAMPLE_ADC, WAIT_SAMPLE_RECV, NOPROM, READY, ERROR
    };
public:
    PressureSensor();
    ~PressureSensor();
    void enable(void);
    void disable(void);
    void reset(void);
    static u8 crc4(const u8 *data, size_t size);
    void convert_values(u32 pressure_in, u32 temperature_in, i32 &pressure_out, i32 &temperature_out);

    bool wait(void) {
        for (;;) {
            FULL_BARRIER();
            if (state == ERROR)
                return false;
            else if (state == READY)
                return true;

            __WFI();
        }

    }
    void sample(DepthSampling osr);
    float get_depth();
    float get_rate();
    void capture_data();
    float get_atm_pressure();
    float get_pressure_bar();
    float get_temperature_celcius();
protected:
    static const size_t PROM_SIZE = 8;
    float atm_pressure;
    u32 start_time = 0;
    u32 end_time = 0;
    u8 sample_cmd;
    DepthSampling sample_osr;
    u8 prom[PROM_SIZE * 2];
    u8 prom_idx;
    u8 dma_tx_buf[4];
    u8 dma_rx_buf[4];
    u32 raw_pressure;
    u32 raw_temperature;
    time_t start;
    time_t end;
    float last_pressure;
    float current_pressure;
    float current_temperature;
    SPI_HandleTypeDef spi;
    DMA_HandleTypeDef dma_rx;
    DMA_HandleTypeDef dma_tx;
    TimerItem timer;
    void pin_enable(void);
    void pin_disable(void);

    void cs(bool);
    static void callback_timer(void *arg);
    void callback_reset_tx(void);
    void callback_reset_wait(void);
    void read_prom(void);
    void callback_read_prom(void);
    void callback_dma_complete(void);
    void callback_dma_error(void);
    void sample_start(u32 cmd, DepthSampling osr);
    void callback_sample_sent(void);
    void callback_sample_sampled(void);
    void callback_sample_done(void);
    State state;
    friend void DMA1_Stream3_IRQHandler(void);
    friend void DMA1_Stream4_IRQHandler(void);
    friend void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *spi);
    friend void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *spi);
    friend void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *spi);
    friend void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *spi);
};

extern PressureSensor pressureSensor;

#endif
