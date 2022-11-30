1������˵��

    /* ���������̹��� */
        ����������ò���ʾCAN�ڻ��ز���ģʽ���շ�CAN�������


2��ʹ�û���

        �������������
        IDE���ߣ�KEIL MDK-ARM 5.26
    
        Ӳ��������
        ������ N32L43XML-STB_V1.0


3��ʹ��˵��
    
    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��108MHz
        USART��TX - PA9�� RX - PA10��������115200
        CAN�� RX - PA11��TX - PA12��������500K�����ز���ģʽ

    /* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�鿴���ڴ�ӡ��Ϣ��CAN�ѷ��͵ı��ĵ������յı��Ĳ����棬
          ÿ��һ��ʱ�䴮�ڴ�ӡ:��Check RX Message Passed����ʾ�ػ�����ͨ����


4��ע������


1. Function description

	/* Briefly describe the project function */
	This routine configures and demonstrates CAN sending and receiving CAN messages in loopback test mode


2. Use environment

	Software development environment:
	IDE tool: KEIL MDK-ARM 5.26
    
	Hardware environment:
	Development Board N32L43XML-STB_V1.0


3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 108MHz
	USART: TX - PA9, RX - PA10, baud rate 115200
	CAN: RX - PA11, TX - PA12, baud rate 500K, loopback test mode

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the serial port printing information, CAN regards the sent message as the received message and saves it, 
	and serial port printing every other period of time:"Check RX Message Passed"indicates that the loopback test is passed;


4. Matters needing attention

