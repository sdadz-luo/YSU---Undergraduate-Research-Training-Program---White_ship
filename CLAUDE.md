# CLAUDE.md — White Ship（RA6M5 多传感器无人船）

供 Claude Code 使用的项目说明。面向人的介绍见 `README.md`。

## 项目身份

- **MCU**：Renesas RA6M5（R7FA6M5BF2CBG），Cortex-M33，1 MB ROM / 512 KB RAM
- **FSP**：v6.4.0，经 RASC（Renesas Smart Configurator）配置生成
- **工具链**：Keil MDK + ARMClang，工程文件 `UART_DMA.uvprojx`
- **架构**：裸机超级循环，无 RTOS，入口 `hal_entry()`
- **TrustZone**：已启用（安全世界），仅使用 core 0

## 构建

Keil 打开 `UART_DMA.uvprojx` 后 Build。无 Makefile / CMake / CI。

修改引脚、外设或时钟后，用 RASC 打开 `configuration.xml` 重新生成代码。

## 目录结构

```text
src/                          用户代码 — 唯一可编辑目录
├── hal_entry.c               入口：初始化 + 主循环
├── hal_warmstart.c           BSP 温启动钩子
├── debug_uart/               UART 初始化（5 路）+ DMAC 收发
├── debug_adc/                ADC 读取（PH、TDS、浊度、溶解氧）
├── debug_dht11/              DHT11 温湿度
├── debug_ds18b20/            DS18B20 温度
├── debug_pwm_gpt_control/    PWM 电机控制 + PID + GPT
└── debug_ws2812/             WS2812 RGB 灯带
ra_gen/  ra_cfg/  ra/          FSP 生成代码与 SDK — 不要编辑
```

## 外设实例与引脚

| 实例 | 外设 | 引脚 | 用途 |
| --- | --- | --- | --- |
| `g_uart5` | SCI5 | P501(TX) / P502(RX) | `printf` 输出（JSON 上报） |
| `g_uart2` | SCI2 | P301(RX) / P302(TX) | LoRa 遥控 |
| `g_uart3` | SCI3 | P706(RX) / P707(TX) | 雷达 |
| `g_uart8` | SCI8 | P607(RX) | 4G 模块 |
| `g_uart9` | SCI9 | P202(RX) / P203(TX) | GPS |
| `g_adc0` | ADC0 | P002 / P004 / P005 / P010 | 水质传感器（AN002/004/005/010） |
| `g_spi0` | SCI0 (SPI) | P100 / P102 / P411 | WS2812 灯带 |
| `pwm` | GPT8 | P605(GTIOC8A) / P106(GTIOC8B) | 电机 PWM |
| `time0` | GPT | — | 周期定时 |

DMAC 接收实例与 SCI 一一对应：`g_transfer_dmac_rx`(SCI5)、
`g2_transfer_dmac_rx`(SCI2)、`g3_transfer_dmac_rx`(SCI3)、
`g8_transfer_dmac_rx`(SCI8)、`g9_transfer_dmac_rx`(SCI9)。
缓冲区长度由 `set_transfer*_length()` 在运行时设置，不靠 FSP 配置。

## 时钟

XTAL 24 MHz → PLL（÷3 ×25）= 200 MHz：

| 时钟 | 分频 | 频率 |
| --- | --- | --- |
| ICLK | /1 | 200 MHz |
| PCLKA、PCLKD | /2 | 100 MHz |
| PCLKB | /4 | 50 MHz |

## 主循环行为

`hal_entry()` 依次初始化 5 路 UART、DMAC、ADC、PWM、GPT、SPI 与 DS18B20，
随后进入无限循环。每轮循环：

1. `analyze_chuli()` — 解析各 UART 收到的数据
2. `Read_adc_value()` — 读取水质 ADC
3. `DHT11_Read()` — 读取温湿度
4. 依次用 `printf` 输出 JSON（重定向到 UART5），条间约 100 ms

上报字段：`X`（GPS 经度）、`Y`（GPS 纬度）、`dht11`（温度）、`humidity`、
`imu_z`、`PH`、`conductivity`（TDS）、`turbidity`（浊度）、`aaa`（溶解氧）。

## 已知问题

| 现象 | 说明 |
| --- | --- |
| WS2812 不亮 | `hal_entry.c` 中所有 WS2812 调用被注释掉，驱动本身在 `debug_ws2812/` 中完好 |
| DS18B20 无数据 | 只调用了 `ds18b20_init()`，主循环未读取 |
| 模板残留 | `hal_entry.c` 顶部有 RASC 模板的 `TODO: add your own code here` |
| 上报周期偏长 | 主循环用 `R_BSP_SoftwareDelay` 阻塞延时，一轮约 2 s |

## 源码编码

源文件为 **GBK**。编辑时必须用能保持原编码的工具——按 UTF-8 读写会把
中文注释变成替换字符。

## 约定

- 注释与交流用中文，标识符用英文
- 模块目录用 `debug_` 前缀，每模块一对 `.c` / `.h`

## 测试

无自动化测试。验证方式：Keil 编译通过 + 烧录实测。
