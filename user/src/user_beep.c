/**
 * @file    user_beep.c
 * @brief   8.7 作业：上电蜂鸣器“长-短-短”三声的实现。
 *          加入 Keil 工程后，复位即可听到效果。
 */
#include "user_beep.h"
#include "buzzer.h"
#include "led.h"
#include "stm32f4xx_hal.h"

#define USER_BEEP_LONG_MS   300U  /* 长音时长 */
#define USER_BEEP_SHORT_MS  100U  /* 短音时长 */
#define USER_BEEP_GAP_MS    100U  /* 两次叫声之间的间隔 */

/* 模式宏定义已移至 user_beep.h */

void user_beep(void)
{
    /* 第一声：长音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_LONG_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);

    /* 第二声：短音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_SHORT_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);

    /* 第三声：短音 */
    buzzer_on();
    HAL_Delay(USER_BEEP_SHORT_MS);
    buzzer_off();
    HAL_Delay(USER_BEEP_GAP_MS);
}
void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
  uint16_t i = 0U; /* 循环计数变量 */

  /* if 判断：LED 编号只允许 1~4 */
  if (led_num > 4U || led_num < 1U)
  {
    return; /* return 直接结束当前函数 */
  }

  /* for 循环：初始化; 判断条件; 每次循环后执行 */
  for (i = 0U; i < times; i++)
  {
    led_on(led_num);          /* 点亮指定 LED */
    HAL_Delay(delay_ms);      /* 延时一段时间 */
    led_off(led_num);         /* 熄灭指定 LED */
    HAL_Delay(delay_ms);
  }
}

void beep(uint32_t beep_ms)
{
  buzzer_on();          /* 打开蜂鸣器 */
  HAL_Delay(beep_ms);   /* 保持响一段时间 */
  buzzer_off();         /* 关闭蜂鸣器*/
}

/**
 * @brief  报警系统主函数，根据模式执行不同行为。
 * @param  alarm_type: alarm_normal(待机) / alarm_work(运行) / alarm_emergency(报警)
 * @retval 无
 */
void alarm_sys_func(uint8_t alarm_type)
{
    uint8_t led; /* 当前 LED 编号 */

    switch (alarm_type)
    {
    case alarm_normal:
        /* 待机：蜂鸣器不响，所有 LED 熄灭 */
        buzzer_off();
        for (led = 1U; led <= 4U; led++)
        {
            led_off(led);
        }
        break;

    case alarm_work:
        /* 运行：流水灯 —— LED1~4 依次各闪一次 */
        for (led = 1U; led <= 4U; led++)
        {
            blink_led(led, 1U, 500U);
        }
        break;

    case alarm_emergency:
        /* 报警：流水灯加速运行 + 蜂鸣器间歇报警 */
        for (led = 1U; led <= 4U; led++)
        {
            blink_led(led, 1U, 150U); /* 加速：延时缩短到 150ms */
        }
        beep(300U);          /* 蜂鸣器响一声 */
        HAL_Delay(100U);     /* 报警间隔 */
        break;

    default:
        break;
    }
}
