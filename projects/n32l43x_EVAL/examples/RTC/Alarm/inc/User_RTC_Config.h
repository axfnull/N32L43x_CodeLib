#ifndef __USER_RTC_CONFIG_H__
#define __USER_RTC_CONFIG_H__

#define  BKP_DAT1     ((uint16_t)0x0000)
#define  BKP_DAT2     ((uint16_t)0x0004)
#define  BKP_DAT3     ((uint16_t)0x0008)
#define  BKP_DAT4     ((uint16_t)0x000C)
#define  BKP_DAT5     ((uint16_t)0x0010)
#define  BKP_DAT6     ((uint16_t)0x0014)
#define  BKP_DAT7     ((uint16_t)0x0018)
#define  BKP_DAT8     ((uint16_t)0x001C)
#define  BKP_DAT9     ((uint16_t)0x0020)
#define  BKP_DAT10    ((uint16_t)0x0024)
#define  BKP_DAT11    ((uint16_t)0x0028)
#define  BKP_DAT12    ((uint16_t)0x002C)
#define  BKP_DAT13    ((uint16_t)0x0030)
#define  BKP_DAT14    ((uint16_t)0x0034)
#define  BKP_DAT15    ((uint16_t)0x0038)
#define  BKP_DAT16    ((uint16_t)0x003C)
#define  BKP_DAT17    ((uint16_t)0x0040)
#define  BKP_DAT18    ((uint16_t)0x0044)
#define  BKP_DAT19    ((uint16_t)0x0048)
#define  BKP_DAT20    ((uint16_t)0x004C)

#define    RTC_ALARM_TEST_TYPE_IRQ        0x01
#define    RTC_ALARM_TEST_TYPE_OUTPUT     0x02
#define    RTC_ALARM_TEST_TYPE            RTC_ALARM_TEST_TYPE_IRQ

#define    RTC_ALARM_OUT_TYPE_OPEN_DRAIN  0x01
#define    RTC_ALARM_OUT_TYPE_PULL_PUSH   0x02
#define    RTC_ALARM_OUT_TYPE             RTC_ALARM_OUT_TYPE_PULL_PUSH
#define    RTC_LSE_TRY_COUNT              250

typedef enum {
    RTC_CLK_SRC_TYPE_HSE_DIV32=0x01,
    RTC_CLK_SRC_TYPE_LSE=0x02,
    RTC_CLK_SRC_TYPE_LSI=0x03,
}RTC_CLK_SRC_TYPE;

extern ErrorStatus RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC);
extern ErrorStatus RTC_TimeRegulate(void);
extern ErrorStatus RTC_DateRegulate(void);
extern ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm);
extern void RTC_DateAndTimeDefaultVale(void);
extern  void RTC_PrescalerConfig(void);

extern void RTC_TimeShow(void);
extern void RTC_DateShow(void);
extern void RTC_AlarmShow(uint8_t AlarmX);
extern void EXTI18_RTCAlarm_Configuration(FunctionalState Cmd);
extern void RTC_CLKSourceConfig1(void);
extern void MCO_Config(void);
#endif/*__USER_RTC_CONFIG_H__*/
