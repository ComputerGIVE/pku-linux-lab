#ifndef _QUIZ1_H_
#define _QUIZ1_H_

#define US_ERROR_SZ 10
#include <linux/delay.h>
inline void us_sleep(int sleep_us)
{
	usleep_range(sleep_us - US_ERROR_SZ, 
		     sleep_us + US_ERROR_SZ);
}

inline void ms_sleep(int sleep_ms)
{
	if (sleep_ms > 10)
		msleep(sleep_ms);
	else 
		usleep_range(sleep_ms * 1000 - US_ERROR_SZ, 
			     sleep_ms * 1000 + US_ERROR_SZ);
}

#endif
