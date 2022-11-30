1������˵��
    1��SLEEPģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL
        2��ʱ��Ƶ�ʣ�108Mz/0MHz
        3���������ã�
            - ����ΪUSART1��TX��PA9  RX��PA10��:
            - ����λ��  8
            - ֹͣλ��  1
            - ��żУ�飺��
            - �����ʣ�  115200 


    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�����PC���ڹ��������������塣�ϵ�󴮿ڴ�ӡ����MCU Prepare Enter Sleep Mode Core Stop Run��,
        MCU����SLEEPģʽ�ں�ֹͣ���е������Ա�С(4.65mA����)�����»��Ѱ���PA0�������жϻ���MCU�����ڴ�ӡ:
        ��MCU Run In Run Mode Sysclock From PLL(108MHz)�� �������(4.97mA����),����ظ�����ʵ������

4��ע������
    ��



1. Function description
    1. Enter and exit the SLEEP mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. based on the evaluation board N32L43XML-STB V1.0 development
	2. MCU: N32L436MBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2. Clock frequency: 108MHz
	3. Serial port configuration:
	    - Serial port: USART1 (TX: PA9 RX: PA10) :
	    - Data bit: 8
	    - Stop bit: 1
	    - Parity check: None
	    - Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn it to the evaluation board, connect ammeter in series, and connect the evaluation board with PC serial tool. After the power-on, the serial port displays "MCU Prepare Enter Sleep Mode Core Stop Run". When the MCU enters Sleep Mode, the current of the kernel stopping becomes smaller (about 4.65mA). Press the wake button PA0 to interrupt MCU and wake up. The serial port prints: "MCU Run In Run Mode Sysclock From PLL(108MHz)" The current increases (about 4.97mA), so repeat the above experiment phenomenon.

4. Matters needing attention
    None

