1������˵��
    1��ͨ��RTC����������SLEEP��
    2�����ڴ�ӡ�����˳�״̬

2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MB


3��ʹ��˵��
    
    ϵͳ���ã�
        1��RTCʱ��Դ��LSI
        2���͹���ģʽ��SLEEP
        3���������ã�
            - ����ΪUSART1��TX��PA9  RX��PA10��:
            - ����λ��8
            - ֹͣλ��1
            - ��żУ�飺��
            - �����ʣ� 115200 

    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�����PC���ڹ��������������塣�ϵ�󴮿ڴ�ӡ����MCU Prepare Enter Stop Mode Core Stop Run��,
	MCU����STOPģʽ�ں�ֹͣ���е������Ա�С(5.4mA����)��RTC���1min���������жϻ���MCU�����ڴ�ӡ:
	��RTC ʱ�䡰����MCU Run In Run Mode Sysclock From PLL(108MHz)�� �������(11.5mA����),����ظ�����ʵ������


4��ע������
    ���������ĵ�ʱ��Ҫע��ȥ��LEDȥ��


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