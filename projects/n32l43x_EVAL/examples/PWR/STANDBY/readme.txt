1、功能说明
    1、STANDBY模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XML-STB V1.0开发
        2、MCU：N32L436MBL7


3、使用说明
    
    系统配置；
        1、时钟源：  HSE+PLL/MSI
        2、时钟频率：108MHz(Run Mode)/0MHz(Standby Mode)
        3、串口配置：
                 - 串口为    USART2（TX：PA9  RX：PA10）:
                 - 数据位：  8
                 - 停止位：  1
                 - 奇偶校验：无
                 - 波特率：  115200 

    使用方法：
        在KEIL下编译后烧录到评估板，接上电流表，上电后发现电流由mA降到了uA级别，MCU打印“MCU Goto Standby!”
        按下唤醒按键(PA0),电流又回到了mA级别，过了一会又降到uA,并打印“MCU Reset”。
                     
                 
4、注意事项
    在评估功耗的时候，要注意去掉LED去测

