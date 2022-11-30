1������˵��
    1��PVD���õ�ѹ������Ӧ���жϡ�


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L43XML-STB V1.0����
        2��MCU��N32L436MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL




    ʹ�÷�����
        ��KEIL�±������¼�������壬ͨ���������������ģʽ����PVD_IRQHandler()�����öϵ㡣
                ȫ�����С�Ȼ���ٰѵ�ѹ����PVD���õ�ѹ���£���ʱ�����ͣ�ڶϵ㴦���������������У�
                �ѵ�ѹ���ߵ�PVD���õ�ѹ���ϣ������ٴ�ͣ���ڶϵ㴦��


4��ע������
    ��


1. Function description
    1. PVD configuration voltage produces the corresponding interrupt.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32L43XML-STB V1.0
	2. MCU: N32L436MBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
    Instructions:
	After compiling under KEIL, burn to the evaluation board, go into debug mode through the emulator, and set breakpoint in PVD_IRQHandler(). Run at full speed. Then turn the voltage below the PVD setting voltage and the program will stop at the breakpoint. Click the program to continue, increase the voltage above the PVD setting voltage, and the program stays at the breakpoint again.

4. Matters needing attention
    None

