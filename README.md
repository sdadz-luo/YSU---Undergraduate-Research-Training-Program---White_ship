# White Ship — RA6M5 多传感器无人船

燕山大学大学生创新创业训练计划「无人船」项目的白船固件。基于
Renesas RA6M5（Cortex-M33）裸机开发：采集水质、温湿度与 GPS 数据，
经 4G 回传，并按遥控指令驱动电机与灯带。

## 硬件平台

| 组件 | 接口 | 用途 |
| --- | --- | --- |
| Renesas RA6M5（R7FA6M5BF2CBG） | — | 主控，1 MB ROM / 512 KB RAM |
| 水质传感器组 | ADC0 | PH、TDS（电导率）、浊度、溶解氧 |
| DHT11 | GPIO | 温湿度 |
| DS18B20 | GPIO | 温度（已接入，主循环暂未读取） |
| GPS | SCI9 | 定位数据 |
| 4G 模块 | SCI8 | 数据回传 |
| LoRa 模块 | SCI2 | 遥控指令接收 |
| WS2812 灯带 | SCI0（SPI） | RGB 指示 |
| 双电机 | GPT8 | PWM 驱动 |

## 功能

- **多传感器采集**：水质四项 + 温湿度 + GPS，循环更新
- **JSON 上报**：经 `printf`（UART5）逐条输出，适配 4G 透传
- **遥控解析**：`analyze_chuli()` 解析各 UART 收到的数据帧
- **电机与灯带**：PWM 调速；WS2812 驱动已就绪（主循环中调用暂被注释）

## 目录结构

```text
write_boat/
├── src/                         用户代码（唯一可编辑区）
│   ├── hal_entry.c              入口：初始化 + 主循环
│   ├── debug_uart/              UART 初始化（5 路）+ DMAC
│   ├── debug_adc/               ADC 读取与换算
│   ├── debug_dht11/             DHT11 驱动
│   ├── debug_ds18b20/           DS18B20 驱动
│   ├── debug_pwm_gpt_control/   PWM + PID + GPT
│   └── debug_ws2812/            WS2812 驱动
├── ra_gen/  ra_cfg/             RASC 生成（勿手改）
├── ra/                          FSP SDK
├── configuration.xml            RASC 配置源
└── UART_DMA.uvprojx             Keil MDK 工程
```

## 数据流

```text
水质 ADC ──┐
DHT11   ──┤
DS18B20 ──┼──→ 主循环 ──→ printf(JSON) ──→ UART5 ──→ 4G 模块 ──→ 云
GPS     ──┤
IMU     ──┘
                    ↑
              analyze_chuli()  ← UART2/3/8/9 接收
```

主循环每轮依次采集各传感器并逐条打印 JSON，条间延时约 100 ms，一轮约 2 秒。

## 上报格式

```json
{"id":"123","version":"1.0","params":{"PH":{"value":7.123}}}
{"id":"123","version":"1.0","params":{"turbidity":{"value":12.34}}}
```

字段：`X` / `Y`（GPS 经纬度）、`dht11`、`humidity`、`imu_z`、`PH`、
`conductivity`、`turbidity`、`aaa`（溶解氧）。

## 构建

1. 用 Keil MDK 打开 `UART_DMA.uvprojx`
2. Build 并通过 J-Link 烧录

修改引脚 / 外设 / 时钟后，需先用 RASC 打开 `configuration.xml` 重新生成代码。

## 开发环境

- Keil MDK + ARMClang
- Renesas FSP v6.4.0
- Renesas RA Smart Configurator（RASC）

## 相关仓库

同一无人船项目的其他工程：

- [Black_ship][black-ship] — 黑船固件（RA6M5）
- [Host-Computer][host-computer] — 基于串口屏的遥控上位机

[black-ship]: https://github.com/sdadz-luo/YSU---Undergraduate-Research-Training-Program---Black_ship
[host-computer]: https://github.com/sdadz-luo/YSU---Undergraduate-Research-Training-Program---Unmanned-Ship---Host-Computer
