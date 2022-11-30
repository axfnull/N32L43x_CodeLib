1、功能说明
	1、通过RTC闹钟来唤醒SLEEP。
	2、串口打印进入退出状态

2、使用环境

	软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
		1、基于评估板N32L43XM-STB V1.0开发
		2、MCU：N32L436MB


3、使用说明
	
	系统配置；
		1、RTC时钟源：LSI
		2、低功耗模式：SLEEP
		3、串口配置：
				 - 串口为    USART1（TX：PA9  RX：PA10）:
				 - 数据位：  8
				 - 停止位：  1
				 - 奇偶校验：无
				 - 波特率：  115200 

	使用方法：
		在KEIL下编译后烧录到评估板，串接电流表，PC串口工具连接上评估板。上电后串口打印：“MCU Prepare Enter Stop Mode Core Stop Run”,
		MCU进入STOP模式内核停止运行电流明显变小(5.4mA左右)。RTC间隔1min产生闹钟中断唤醒MCU，串口打印:
		“RTC 时间“、“MCU Run In Run Mode Sysclock From PLL(108MHz)” 电流变大(11.5mA左右),如此重复以上实验现象。


4、注意事项
	在评估功耗的时候，要注意去掉LED去测