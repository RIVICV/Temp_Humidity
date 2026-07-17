# 温湿度传感器采集系统 (STM32)

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![Platform](https://img.shields.io/badge/platform-STM32-brightgreen.svg)](https://www.st.com/)
[![IDE](https://img.shields.io/badge/IDE-Keil%20MDK-orange.svg)](https://www.keil.com/)

---

## 📋 项目简介

本项目是一个基于 **STM32F103C8T6** 微控制器的**温湿度数据采集与监控系统**。系统通过 DHT11 数字温湿度传感器采集环境数据，并在 OLED 显示屏上实时显示，同时支持通过 USART 串口与上位机进行数据交互和参数设置。

### 主要功能

- **温湿度采集**：通过 DHT11 传感器采集环境温度（-20℃ ~ 60℃）和湿度（5% ~ 95%RH）
- **实时显示**：128×32 OLED 显示屏实时显示温湿度数值
- **串口通信**：USART1 与上位机通信，支持数据输出和参数配置
- **报警功能**：可通过串口设置温度和湿度阈值，超限时驱动蜂鸣器报警
- **按键控制**：预留按键接口，支持本地交互（可扩展）

---

## 🎯 适用场景

- 环境监测系统
- 智能家居控制
- 实验室数据采集
- 物联网终端节点
- 嵌入式教学实训

---

## 🛠 硬件平台

| 组件 | 型号/规格 |
|------|-----------|
| MCU | STM32F103C8T6 (Cortex-M3, 72MHz) |
| 温湿度传感器 | DHT11 (数字信号输出) |
| 显示模块 | 0.96英寸 OLED (128×64, SPI接口) |
| 通信接口 | USART1 (TTL电平, 115200bps) |
| 报警模块 | 有源蜂鸣器 (GPIO控制) |
| 按键 | 2× 独立按键 (预留) |
| 供电 | 3.3V / 5V DC |

---

## 📁 项目结构

```
Temp_Humidity/
├── Core/
│   ├── Inc/                    # 头文件目录
│   │   ├── main.h              # 主程序头文件
│   │   ├── gpio.h              # GPIO配置
│   │   ├── usart.h             # 串口配置
│   │   ├── adc.h               # ADC配置
│   │   ├── tim.h               # 定时器配置
│   │   ├── delay.h             # 延时函数
│   │   ├── dht11.h             # DHT11驱动
│   │   ├── oled.h              # OLED驱动
│   │   ├── key.h               # 按键驱动
│   │   └── stm32f1xx_it.h      # 中断服务头文件
│   └── Src/                    # 源文件目录
│       ├── main.c              # 主程序
│       ├── gpio.c              # GPIO初始化
│       ├── usart.c             # 串口初始化与回调
│       ├── adc.c               # ADC初始化与采集
│       ├── tim.c               # 定时器配置 (PWM)
│       ├── delay.c             # 延时实现
│       ├── dht11.c             # DHT11协议实现
│       ├── oled.c              # OLED显示驱动
│       ├── key.c               # 按键扫描
│       ├── stm32f1xx_it.c      # 中断服务函数
│       ├── stm32f1xx_hal_msp.c # HAL硬件初始化
│       └── system_stm32f1xx.c  # 系统时钟配置
├── Drivers/                    # 硬件驱动层 (CMSIS & HAL)
│   ├── CMSIS/                  # ARM Cortex-M3 CMSIS库
│   └── STM32F1xx_HAL_Driver/   # STM32 HAL库
├── MDK-ARM/                    # Keil工程文件
│   ├── UART.uvprojx            # Keil项目文件
│   ├── UART.uvoptx             # 项目选项配置
│   └── RTE/                    # 运行时环境
├── Docs/                       # 文档目录 (可选)
└── README.md                   # 项目说明文档
```

---

## ⚙️ 开发环境

| 工具 | 版本 |
|------|------|
| IDE | Keil MDK v5.34 及以上 |
| 编译器 | ARM Compiler v6.10.1 |
| 调试器 | ST-Link / J-Link |
| 固件库 | STM32CubeF1 V1.8.0 |
| 烧录工具 | STM32CubeProgrammer |

---

## 🔌 引脚连接

| 外设 | 引脚 | 说明 |
|------|------|------|
| **DHT11** | PA0 | 数据线（双向） |
| **OLED_CS** | PB10 | SPI片选 |
| **OLED_DC** | PB11 | 数据/命令选择 |
| **OLED_RST**| PB12 | 复位 |
| **OLED_SCK**| PB13 | SPI时钟 |
| **OLED_MOSI**| PB14 | SPI数据 |
| **USART1_TX**| PA9 | 串口发送 |
| **USART1_RX**| PA10| 串口接收 |
| **BEEP** | PA8 | 蜂鸣器控制 |
| **LED** | PA1 | 指示灯 |
| **KEY1** | PB0 | 按键1 |
| **KEY2** | PB1 | 按键2 |

---

## 📡 串口通信协议

### 基本参数
- 波特率：`115200 bps`
- 数据位：`8 位`
- 停止位：`1 位`
- 校验位：`无`
- 流控制：`无`

### 数据格式
```c
// 自动上报温湿度数据 (每500ms)
温度：26.5℃ 湿度：62.3%
```

### 指令配置
通过串口发送以下格式数据设置报警阈值：
```
<温度阈值> <湿度阈值>
```
**示例**：发送 `30 80` 表示当温度 ≥ 30℃ 或湿度 ≥ 80% 时触发蜂鸣器报警。

---

## 🔧 编译与烧录

### 1. 导入工程
- 使用 Keil MDK 打开 `MDK-ARM/UART.uvprojx`

### 2. 编译
- 选择芯片型号：`STM32F103C8`
- 点击 `Build` (F7) 编译工程

### 3. 烧录
- 连接 ST-Link 调试器
- 点击 `Load` (F8) 下载程序到 MCU

### 4. 调试
- 点击 `Debug` (Ctrl+F5) 进入调试模式
- 可使用串口助手查看输出信息

---

## 🔄 代码流程图

```
系统上电
    ↓
HAL初始化 & 时钟配置
    ↓
外设初始化 (GPIO, USART, ADC, OLED)
    ↓
OLED显示欢迎界面
    ↓
开启USART接收中断
    ↓
进入主循环 (while(1))
    ↓
├── 每500ms采集DHT11数据
├── OLED更新显示温度/湿度
├── 串口数据解析与阈值更新
├── 温度/湿度阈值判断
└── 蜂鸣器报警控制
```

---

## 📊 中断资源

| 中断 | 优先级 | 功能 |
|------|--------|------|
| USART1_IRQn | 0 | 串口数据接收 (非阻塞) |
| TIM2_IRQn | 2 | 定时器中断 (预留) |

---

## ⚠️ 注意事项

1. **供电稳定性**：DHT11 对电源波动敏感，建议使用 3.3V LDO 稳压
2. **时序要求**：DHT11 通信时序较严格，延时函数已优化 (基于 SysTick)
3. **串口电平**：USART1 为 TTL 电平，与上位机通信需使用 USB-TTL 转换模块
4. **OLED 初始化**：若显示异常，可调整对比度寄存器 (0x81) 或检查 SPI 时序
5. **蜂鸣器驱动**：PA8 输出高电平触发，注意电流驱动能力

---


*本项目仅供学习和参考，用于实际产品前请进行充分的测试和验证。*
