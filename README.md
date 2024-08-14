# Cyclone_V2
基于STM32F4的有感/无感三相无刷电机控制

## 1. 项目简介
本项目是基于STM32F4的有感/无感三相无刷电机控制，主要包括电机驱动、电机控制、电机参数调试、电机速度控制、电机位置控制等功能。
## 2. 项目环境
- 开发环境：gcc-arm-none-eabi
- 开发工具：STM32CubeMX、Clion
- 电机型号：3510无刷电机
- 电机驱动：DRV8302
- 电机控制：FOC（有感/无感）
- 电机参数调试：UART（本项目引出串口1和串口6供用户使用）后期会增加CAN通信（看心情延后版本），串口1用于调试，串口6用于显示电机参数
## 3. 项目结构
```
Cyclone_V2
│  .git
│  Cyclone_V2.ioc // STM32CubeMX工程文件
│  App            // 工作流控制
│  ├─Inc
│  ├─src
│  Bsp            // 板级支持包
│  ├─Inc
│  ├─src
│  Core          // 核心文件
│  ├─Inc
│  ├─src
│  Drivers       // 驱动文件
│  ├─CMSIS
│  ├─STM32F4xx_HAL_Driver
```
## 4. 项目进度
- [ ] 电机驱动
- [ ] 电机控制
- [ ] 电机参数调试
- [ ] 电机速度控制
- [ ] 电机位置控制
- [ ] CAN通信

## 5. 板上硬件说明
左边：
- 串口1：引出,usb亦包含此功能，使用air32作为虚拟串口设备
- 串口6：引出，用于显示电机参数，线序已和TJC串口屏对接
- TYPE-C：供电/下载/串口1
- 绿色端子：供电（理论8~60V），如需使用15V以上电源，需要更换C62/C63/C64电容耐压值，需比实际电机反电动势高1.5倍

右边：
- sh1.0_3pin：编码器接口，用于PWM捕获电机角度，不可设置绝对零点，需在程序中设置，lite版本编码器
- 电机接口：电机U/V/W线
- sh1.0_6pin*2：编码器接口，用于读取电机角度，标准版本编码器（板上接口为I2C接口和SPI接口）


