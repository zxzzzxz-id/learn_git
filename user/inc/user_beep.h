/**
 * @file    user_beep.h
 * @brief   8.7 作业：上电蜂鸣器“长-短-短”三声的声明。
 *          默认不参与编译，由学员把 user/src/user_beep.c 加入 Keil 工程后生效。
 */
#ifndef USER_BEEP_H
#define USER_BEEP_H

#include <stdint.h>  /* uint8_t, uint16_t, uint32_t */

#ifdef __cplusplus
extern "C"
{
#endif

/* 报警系统模式 */
#define alarm_normal    1  /* 待机：蜂鸣器不响，LED 全灭 */
#define alarm_work      2  /* 运行：流水灯 LED1~4 依次闪烁 */
#define alarm_emergency 3  /* 报警：流水灯加速 + 蜂鸣器间歇报警 */

/* 上电时让蜂鸣器按”长-短-短”响三次 */
    void user_beep(void);
    void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms);
    void beep(uint32_t beep_ms);
    void alarm_sys_func(uint8_t alarm_type);

#ifdef __cplusplus
}
#endif

#endif /* USER_BEEP_H */
