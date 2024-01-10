#### 一、统一引脚定义

​	各自测试时请确认好连接的引脚，防止代码跑不通。

**GY86**

SCL————PB8

SDA————PB9

*模拟IIC信号，只需要初始化GPIO*

GPIOB——AHB1

**HM-10**

RX————PB6

TX————PB7

USART1——APB2

GPIOB——AHB1

**电调**

TIM3_CH1————PC6

TIM3_CH2————PC7

TIM3_CH3————PC8

TIM3_CH4————PC9

TIM3——APB1

GPIOC——AHB1

**接收机**

TIM1_CH1————PA8

TIM1_CH2————PA9

TIM1_CH3————PA10

TIM1_CH4————PA11

**OLED**



​	![img_v3_026v_b318c8e2-9f7e-4712-8a14-50f1a52a20eg](https://harderheng-blog.oss-cn-chengdu.aliyuncs.com/blogimage/img_v3_026v_b318c8e2-9f7e-4712-8a14-50f1a52a20eg.jpg)

#### 二、调试代码

调试代码时请严格按照引脚定义进行接线，并且使用好调试工具。

**Led.h**有点亮LD2灯的函数，可以使用这个函数来调试代码。
