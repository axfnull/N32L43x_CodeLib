1������˵��
    1��LP RUNģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
	2��MCU��N32L436MBL7


3��ʹ��˵��
	
    ϵͳ���ã�
        1��ʱ��Դ��  HSE+PLL/MSI
	2��ʱ��Ƶ�ʣ�108MHz(Run Mode)/4MHz(LP RUN Mode)
	3���������ã�
            - ����ΪUSART2��TX��PA9  RX��PA10��:
            - ����λ��8
            - ֹͣλ��1
            - ��żУ�飺��
            - �����ʣ� 115200 


    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�����,PC���ڹ��������������壬������λ����ӡ:
	�� MCU Prepare Enter Low Power Run Mode Sysclock From MSI(4MHz)�� MCU׼������͹���ģʽ
	����������õ�����С(0.46mA����), ����ӡ:"MCU Run In Run Mode Sysclock From PLL(108MHz)" 
	MCU�ӵ͹�������ģʽ�л�������ģʽ���������õ������(10mA����)������ظ�����ʵ������
            


4��ע������
    ������LP RUNģʽʱ��ϵͳʱ���л�����MSI�����˳�ʱ����Ҫ�л��û�Ĭ��ϵͳʱ��


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

