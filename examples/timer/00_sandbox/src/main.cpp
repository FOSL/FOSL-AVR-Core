#include <core/gpio.h>
#include <core/timer/timer1.h>

using namespace Core;

Gpio<GPIO::PORT::B, 5> led(GPIO::MODE::OUTPUT);

void initialize(void)
{
	{
		using namespace Timer;
		using namespace TIMER;

		Spec spec;
		spec.mode                                 = MODE::FAST_PWM;
		spec.top                                  = TOP::INPUT_CAPTURE_VALUE;
		spec.pin_action_on_output_compare_match_A = PIN_ACTION_ON_OUTPUT_COMPARE_MATCH::CLEAR;
		spec.pin_action_on_output_compare_match_B = PIN_ACTION_ON_OUTPUT_COMPARE_MATCH::CLEAR;
		spec.clock_source                         = CLOCK_SOURCE::IO_CLK_OVER_8;
		timer1.initialize(spec);
		timer1.input_capture_value(20000);
	}

	sei();
}

int main(void)
{
	initialize();

	while (true)
	{
		led.toggle();
		_delay_ms(1000);
	}
}
