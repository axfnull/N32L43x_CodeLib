1、功能说明
    1、通过RTC闹钟来唤醒SLEEP。
    2、串口打印进入退出状态

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XML-STB V1.0开发
        2、MCU：N32L436MB


3、使用说明
    
    系统配置：
        1、RTC时钟源：LSI
        2、低功耗模式：SLEEP
        3、串口配置：
            - 串口为USART1（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 

    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表，PC串口工具连接上评估板。上电后串口打印：“MCU Prepare Enter Stop Mode Core Stop Run”,
	MCU进入STOP模式内核停止运行电流明显变小(5.4mA左右)。RTC间隔1min产生闹钟中断唤醒MCU，串口打印:
	“RTC 时间“、“MCU Run In Run Mode Sysclock From PLL(108MHz)” 电流变大(11.5mA左右),如此重复以上实验现象。


4、注意事项
    在评估功耗的时候，要注意去掉LED去测


1. Function description
    1. Wake up SLEEP through the RTC alarm clock.
    2. Serial port printing enters the exit state

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. based on the evaluation board N32L43XML-STB V1.0 development
	2. MCU: N32L436MB

3. Instructions for use    
    System configuration:
	1. RTC clock source: LSI
	2. low power mode: SLEEP
	3. Serial port configuration
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, and connect the evaluation board with PC serial tool. After the system is powered on, the serial port displays "MCU Prepare Enter Stop Mode Core Stop Run". When the MCU enters the Stop Mode, the kernel stopping current decreases (about 5.4mA). RTC interval 1min alarm interrupt is generated to wake up MCU, serial port printing: "RTC time", "MCU Run In Run Mode Sysclock From PLL(108MHz)" current increases (about 11.5mA), so repeat the above experiment phenomenon.

4. Matters needing attention
     When evaluating power consumption, take care to remove the LED before testing.