1、功能说明
    1、STOP2模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L43XM-STB V1.0开发
        2、MCU：N32G435VBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、时钟频率：108MHz(RUN Mode)/0MHz(STOP2 Mode)
        3、串口配置：
                     - 串口为USART2（TX：PA9  RX：PA10）:
                     - 数据位：8
                     - 停止位：1
                     - 奇偶校验：无
                     - 波特率： 115200 

    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表,PC串口工具连接上评估板，串口上位机打印:
        “ MCU Prepare Enter Stop2 Mode Core Stop Run”   MCU准备进入STOP2模式电流表测量得电流变小(8.7mA左右),
        按下唤醒按键PA0,随后打印:"MCU Run In Run Mode Sysclock From PLL(108MHz)" 
        MCU从STOP2模式切换到运行模式，电流表测得电流变大(340uA左右)，如此重复上述实验现象。                    


4、注意事项
    ①在评估功耗的时候，要注意去掉LED去测
    ②SRAM1和SRAM2可配置

