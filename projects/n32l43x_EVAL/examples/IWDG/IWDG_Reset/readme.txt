1、功能说明
    1、IWDG复位功能。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XML-STB V1.0开发
        2、MCU：N32L436MBL7


3、使用说明
    
    系统配置；
        1、IWDG时钟源：LSI/32
        2、超时时间值：250ms
        3、指示灯：LED1(PA8) LED3(PB5)
            

    使用方法：
           1、在KEIL下编译后烧录到评估板，上电后，指示灯LED3不停的闪烁。说明IWDG正常喂狗，代码正常运行。
               2、把Delay(249)函数参数改成250以上，整个系统将一直处于复位状态，LED1、LED3长亮。


4、注意事项
     如果通过烧录器仿真，需要开启DBG_ConfigPeriph(DBG_IWDG_STOP,ENABLE);

1. Function description
    1. IWDG reset function.
	
2. Use environment
    Software development environment: KEIL MDK-ARM V5.25.0.0
	
    Hardware environment: 
		1.Developed based on the evaluation board N32L43XML-STB V1.0
		2.MCU：N32L436MBL7
	
3. Instructions for use
    System Configuration;
        1. IWDG clock source: LSI/32

		2. Timeout value: 250ms

		3. Indicator light: LED1(PA8) LED3(PB5)

    Instructions:
        1. After compiling in KEIL, it was burned to the evaluation board. After powering on,the indicator controled by PB5 pin kept flashing. The IWDG feeds the dog properly and the code runs properly.
		2. When the parameter of Delay(249) function is changed to more than 250, the entire system will always be reset. LED1,LED3 are always on.
		
4. Matters needing attention
    If you simulate through the burner, you need to turn on DBG_ ConfigPeriph(DBG_IWDG_STOP,ENABLE).