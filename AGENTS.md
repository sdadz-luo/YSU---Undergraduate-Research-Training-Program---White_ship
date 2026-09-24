# AGENTS.md — boat (RA6M5 UART-DMA)

## 项目标识

- **MCU**: Renesas RA6M5 (R7FA6M5BF2CBG), Cortex-M33, 1MB ROM / 512KB RAM
- **FSP**: v6.4.0，通过 Renesas Smart Configurator (RASC) 配置
- **工具链**: ARM Compiler (armclang) via Keil uVision (`UART_DMA.uvprojx`)
- **无 RTOS** — 裸机超级循环，入口在 `hal_entry()`
- **TrustZone** 已启用（安全世界），仅使用 core 0

## 目录结构

```
src/                          # 用户代码 — 唯一可编辑的目录
  hal_entry.c                 # 入口：初始化后进入 while(1) 循环
  hal_warmstart.c             # BSP 温启动钩子
  debug_uart/                 # UART + DMA 初始化（5 个端口）
  debug_adc/                  # ADC 读取（PH、TDS、浊度、溶解氧）
  debug_dht11/                # DHT11 温湿度
  debug_ds18b20/              # DS18B20 温度传感器
  debug_pwm_gpt_control/      # PWM 电机控制 + PID
  debug_ws2812/               # WS2812 RGB LED 驱动
ra_gen/                       # RASC 自动生成 — 不要编辑
ra_cfg/                       # 自动生成的 FSP 配置 — 不要编辑
ra/                           # FSP 库源码 — 不要编辑
```

## 关键规则

1. **永远不要编辑 `ra_gen/`、`ra_cfg/`、`ra/` 下的文件。** 这些文件由 Smart Configurator 重新生成，编辑会丢失。
2. **修改引脚/外设/时钟后需要重新生成代码**：在 RASC 或 Keil 中打开 `UART_DMA.uvprojx`，重新配置并生成。`configuration.xml` 驱动代码生成。
3. **用户代码只能放在 `src/` 下。** 按外设/子系统分模块子目录管理。

## 外设与 HAL 实例名（来自 FSP 配置）

| 实例 | 类型 | 通道 | 用途 | 回调函数 |
|----------|------|---------|---------|----------|
| `g_uart5` | SCI UART | 5 | IMU (printf) | `uart5_callback` |
| `g_uart2` | SCI UART | 2 | LoRa | `uart2_callback` |
| `g_uart3` | SCI UART | 3 | 雷达 | `uart3_callback` |
| `g_uart8` | SCI UART | 8 | 4G 雷达 | `uart8_callback` |
| `g_uart9` | SCI UART | 9 | 4G/GPS | `uart9_callback` |
| `g_transfer_dmac_rx` | DMAC ch1 | — | SCI5 DMA RX | `transfer_dmac_rx_callback` |
| `g2_transfer_dmac_rx` | DMAC ch3 | — | SCI2 DMA RX | `transfer2_dmac_rx_callback` |
| `g3_transfer_dmac_rx` | DMAC ch5 | — | SCI3 DMA RX | `transfer3_dmac_rx_callback` |
| `g8_transfer_dmac_rx` | DMAC ch7 | — | SCI8 DMA RX | `transfer8_dmac_rx_callback` |
| `g9_transfer_dmac_rx` | DMAC ? | — | SCI9 DMA RX | `transfer9_dmac_rx_callback` |
| `g_adc0` | ADC | 0 | 12 位，通道 2/4/5 | `ADC0_callback` |
| `time0` | GPT0 | 0 | 1ms 周期时钟 | `time0_callback`（优先级 0 最高） |
| `pwm` | GPT8 | 8 | 50Hz 电机 PWM | NULL |
| `g_spi0` | SCI SPI | — | WS2812 LED 控制 | `sci_spi_callback` |

## UART DMA RX — 重要模式

每个 UART 使用 DMAC 将接收到的字节从 SCI RDR 寄存器传输到固定缓冲区：

```
#define size   22   // SCI5 RX 缓冲区（IMU）
#define size2  6    // SCI2 RX 缓冲区（LoRa）
#define size3  58   // SCI3 RX 缓冲区（雷达）
#define size8  100  // SCI8 RX 缓冲区（4G 雷达）
#define size9  39   // SCI9 RX 缓冲区（4G/GPS）
```

`hal_entry()` 中的初始化顺序：
1. `UARTx_Init()` — 打开每个 UART
2. 清除 ICU IELSR（处理虚假中断的 workaround）
3. `set_transfer_dst_src_address()` — 将 DMAC 指向 SCI RDR + 缓冲区
4. `set_transfer_length()` — 配置传输计数
5. `DMACx_Init()` — 启用 DMAC 通道

## 时钟树

- XTAL: 24 MHz → PLL (/3 × 25) → **ICLK = 200 MHz**
- PCLKA = 100 MHz, PCLKB = 50 MHz, PCLKC = 50 MHz, PCLKD = 100 MHz
- FCLK = 50 MHz
- 所有 UART 波特率 115200

## 主循环 (hal_entry.c)

超级循环按固定顺序执行，各步骤间用 `R_BSP_SoftwareDelay()` 延迟：
1. `analyze_chuli()` — 解析接收到的 UART 数据
2. 读取 ADC（PH、TDS、浊度、溶解氧）
3. 读取 DHT11（温度、湿度）
4. 通过 `printf()`（→ UART5）打印 JSON 遥测数据：
   - GPS 经度/纬度
   - DHT11 温度、湿度
   - IMU Z 轴角度
   - PH、电导率、浊度、溶解氧
5. 循环间 `R_BSP_SoftwareDelay(1000)`

## 本项目可用的 Skills

以下用户安装的 skills 直接适用于 RA6M5 开发：

- `ra-uart-dma` — RA6M5 上的 SCI UART + DMA
- `ra-pwm-gpt` — RA6M5 上的 GPT 定时器 PWM
- `copilot-embedded` — 嵌入式 C 编码规范（volatile、ISR、静态内存）
- `copilot-cpp` — C/C++ 编码规范
- `embedded-engineer` — 通用嵌入式系统专业知识
- `embedded-review` — 固件代码审查
- `firmware-debugger` — GDB/串口调试

加载方式：`skill(name="ra-uart-dma")` 或在 task 委托中传入 `load_skills=["ra-uart-dma", ...]`。

## 特别注意

- **`printf()` 输出到 UART5（IMU 端口）** — 通过重定向机制实现。不要在高频或中断上下文中使用 printf。
- **UART 回调中不要处理 RX 数据** — 回调只设置 `TX_COMPLETE` 标志。所有 RX 数据通过 DMAC 到达固定缓冲区。
- **启动时清除 ICU IELSR** — `R_ICU->IELSR[SCIx_RXI_IRQn]=0U` 是解决 `R_SCI_UART_Open()` 后虚假 RX 中断的已知 workaround。
- **DMAC 传输长度在运行时设置**，而非通过 FSP 配置 — `set_transfer_length()` 允许在代码生成后动态调整大小。
- **所有 DMAC 传输为 1 字节、Normal 模式、目标地址递增、源地址固定**（SCI RDR 是固定地址）。
- **解析后的数据使用全局变量** — 例如 `GPS_LNG_USE`、`GPS_LAT_USE`、`gyro`、`angle`、`MY_data` 是跨模块共享的全局变量。
- **无调度器/RTOS** — 主循环全程使用忙等延迟。迁移到事件驱动或定时器驱动架构需要重大重构。
- **WS2812 使用 SPI（g_spi0）而非位操作协议** — SPI 外设被配置为生成 WS2812 所需的时序。
