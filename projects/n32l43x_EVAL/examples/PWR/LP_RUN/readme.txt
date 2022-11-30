1、功能说明
    1、LP RUN模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XML-STB V1.0开发
	2、MCU：N32L436MBL7


3、使用说明
	
    系统配置；
        1、时钟源：  HSE+PLL/MSI
	2、时钟频率：108MHz(Run Mode)/4MHz(LP RUN Mode)
	3、串口配置：
            - 串口为USART2（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 


    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表,PC串口工具连接上评估板，串口上位机打印:
	“ MCU Prepare Enter Low Power Run Mode Sysclock From MSI(4MHz)” MCU准备进入低功耗模式
	电流表测量得电流变小(0.46mA左右), 随后打印:"MCU Run In Run Mode Sysclock From PLL(108MHz)" 
	MCU从低功耗运行模式切换到运行模式，电流表测得电流变大(10mA左右)，如此重复上述实验现象。
            


4、注意事项
    当进入LP RUN模式时，系统时钟切换到了MSI，当退出时，需要切回用户默认系统时钟


1. Function description
    1. Enter and exit LP RUN mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. based on the evaluation board N32G43XRL-STB V1.0 development
	2. MCU: N32G435RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2. Clock frequency: 108MHz(Run Mode)/4MHz(LP RUN Mode)
	3. Serial port configuration
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, connect the PC serial port tool to the evaluation board, and print it on the serial port PC: MCU Prepare Enter Low Power Run Mode Sysclock From MSI(4MHz), The current measured by the ammeter becomes smaller (about 0.46mA), and then the following print is printed :"MCU Run In Run Mode Sysclock From PLL(108MHz)" MCU switches From the low-power operation Mode to the operation Mode. The increase in current measured by the ammeter (around 10mA) repeats the above experimental phenomenon.
            
4. Matters needing attention
	When enter LP RUN mode, the system clock is switched to MSI. When exit, you need to switch back to the default system clock

