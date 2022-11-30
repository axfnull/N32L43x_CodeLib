1、功能说明
    1、LP SLEEP模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XML-STB V1.0开发
        2、MCU：N32L436MBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、时钟频率：108MHz/0MHz
        3、串口配置：
            - 串口为USART1（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 



    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表，PC串口工具连接上评估板。上电后串口打印：“MCU Prepare Enter LP Sleep Mode Core Stop Run”,
        MCU进入LP SLEEP模式内核停止运行电流明显变小(198uA左右)。按下唤醒按键PA0，产生中断唤醒MCU，串口打印:
        “MCU Run In Run Mode Sysclock From PLL(108MHz)” 电流变大(520uA左右),如此重复以上实验现象。
        
                
            


4、注意事项
    LP SLEEP模式唤醒后会先进入LP RUN，再由LP RUN退出到RUN模式



1. Function description
    1. Enter and exit LP SLEEP mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32G43XRL-STB V1.0
	2. MCU: N32G435RBL7

3. Instructions for use   
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2. Clock frequency: 108MHz/0MHz
	3. Serial port configuration
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, and connect the evaluation board with PC serial tool. After the system is powered on, the serial port displays "MCU Prepare Enter LP Sleep Mode Core Stop Run". When the MCU enters LP Sleep Mode, the kernel Stop current becomes smaller (about 198uA). Press the wake button PA0 to interrupt MCU and wake up. The serial port prints "MCU Run In Run Mode Sysclock From PLL(108MHz)", and the current increases (about 520uA), thus repeating the above experimental phenomenon.
            
4. Matters needing attention
    After waking up from LP SLEEP, the system enters LP RUN and exits the RUN mode from LP RUN

