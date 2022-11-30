1������˵��
    1��STOP2ģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL
        2��ʱ��Ƶ�ʣ�108MHz(RUN Mode)/0MHz(STOP2 Mode)
        3���������ã�
            - ����ΪUSART2��TX��PA9  RX��PA10��:
            - ����λ��8
            - ֹͣλ��1
            - ��żУ�飺��
            - �����ʣ� 115200 

    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�����,PC���ڹ��������������壬������λ����ӡ:
        �� MCU Prepare Enter Stop2 Mode Core Stop Run��   MCU׼������STOP2ģʽ����������õ�����С(8.7mA����),
        ���»��Ѱ���PA0,����ӡ:"MCU Run In Run Mode Sysclock From PLL(108MHz)" 
        MCU��STOP2ģʽ�л�������ģʽ���������õ������(340uA����)������ظ�����ʵ������                    


4��ע������
    �����������ĵ�ʱ��Ҫע��ȥ��LEDȥ��
    ��SRAM1��SRAM2������


1. Function description
    1. Enter and exit STOP2 mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32L43XML-STB V1.0
	2. MCU: N32L436MBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2. Clock frequency: 108MHz(RUN Mode)/0MHz(STOP2 Mode)
	3. Serial port configuration:
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
               
    Instructions:
	After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, connect the PC serial port tool to the evaluation board, and print it on the serial port PC: "MCU Prepare Enter Stop2 Mode Core Stop Run" MCU Prepare to Enter Stop2 Mode the current measured by the ammeter decreases (about 8.7mA), Press the wake up button PA0, and then print :"MCU Run In Run Mode Sysclock From PLL(108MHz)" when MCU switches From STOP2 Mode to operation Mode, the current measured by the ammeter increases (about 340uA), thus repeating the above experimental phenomenon.After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, connect the PC serial port tool to the evaluation board, and print it on the serial port PC: "MCU Prepare Enter Stop2 Mode Core Stop Run" MCU Prepare to Enter Stop2 Mode the current measured by the ammeter decreases (about 8.7mA), Press the wake up button PA0, and then print :"MCU Run In Run Mode Sysclock From PLL(108MHz)" when MCU switches From STOP2 Mode to operation Mode, the current measured by the ammeter increases (about 340uA), thus repeating the above experimental phenomenon.

4. Precautions
    ��When evaluating power consumption, we should pay attention to removing LED to measure
    ��SRAM1 and SRAM2 are configurable

