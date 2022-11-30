1������˵��
    1��STANDBYģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��  HSE+PLL/MSI
        2��ʱ��Ƶ�ʣ�108MHz(Run Mode)/0MHz(Standby Mode)
        3���������ã�
            - ����Ϊ    USART2��TX��PA9  RX��PA10��:
            - ����λ��  8
            - ֹͣλ��  1
            - ��żУ�飺��
            - �����ʣ�  115200 

    ʹ�÷�����
        ��KEIL�±������¼�������壬���ϵ������ϵ���ֵ�����mA������uA����MCU��ӡ��MCU Goto Standby!��
        ���»��Ѱ���(PA0),�����ֻص���mA���𣬹���һ���ֽ���uA,����ӡ��MCU Reset����
                     
                 
4��ע������
    ���������ĵ�ʱ��Ҫע��ȥ��LEDȥ��


1. Function description
    1. Enter and exit STANDBY mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Based on the evaluation board N32L43XML-STB V1.0 development
	2. MCU: N32L436MBL7

3. Instructions for use   
    System configuration;
	1. Clock source: HSE+PLL
	2. Clock frequency: 108MHz(Run Mode)/0MHz(Standby Mode)
	3. Serial port configuration:
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
               
    Instructions:
	After compiling under KEIL, it was burned to the evaluation board, connected to the ammeter, and found that the current dropped from mA to uA level after powering on, and THE MCU printed "MCU Goto Standby!"
	Press the wake up button (PA0), and the current returns to mA level. After a while, it drops to uA and prints "MCU Reset".

4. Matters needing attention
    When evaluating power consumption, take care to remove the LED to measure

