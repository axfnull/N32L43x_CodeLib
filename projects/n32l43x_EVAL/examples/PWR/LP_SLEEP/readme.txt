1������˵��
    1��LP SLEEPģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL
        2��ʱ��Ƶ�ʣ�108MHz/0MHz
        3���������ã�
            - ����ΪUSART1��TX��PA9  RX��PA10��:
            - ����λ��8
            - ֹͣλ��1
            - ��żУ�飺��
            - �����ʣ� 115200 



    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�����PC���ڹ��������������塣�ϵ�󴮿ڴ�ӡ����MCU Prepare Enter LP Sleep Mode Core Stop Run��,
        MCU����LP SLEEPģʽ�ں�ֹͣ���е������Ա�С(198uA����)�����»��Ѱ���PA0�������жϻ���MCU�����ڴ�ӡ:
        ��MCU Run In Run Mode Sysclock From PLL(108MHz)�� �������(520uA����),����ظ�����ʵ������
        
                
            


4��ע������
    LP SLEEPģʽ���Ѻ���Ƚ���LP RUN������LP RUN�˳���RUNģʽ



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

