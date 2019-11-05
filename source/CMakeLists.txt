project(core)

add_avr_library(
	${PROJECT_NAME}

	# ./Core/adc.h
	# ./Core/eeprom.cpp
	# ./Core/eeprom.h
	# ./Core/external_interrupt.cpp
	# ./Core/external_interrupt.h
	./Core/GPIO.cpp
	./Core/GPIO.h
	./Core.h
	# ./Core/spi.cpp
	# ./Core/spi.h
	# ./Core/timer/base.cpp
	# ./Core/timer/base.h
	# ./Core/timer/timer0.cpp
	# ./Core/timer/timer0.h
	# ./Core/timer/timer1.cpp
	# ./Core/timer/timer1.h
	# ./Core/timer/timer2.cpp
	# ./Core/timer/timer2.h
	# ./Core/usart/base.cpp
	# ./Core/usart/base.h
	# ./Core/usart/queue.cpp
	# ./Core/usart/queue.h
	# ./Core/usart/usart0.cpp
	# ./Core/usart/usart0.h
)

target_include_directories(
	${PROJECT_NAME} PUBLIC

	${PROJECT_SOURCE_DIR}

	${util_SOURCE_DIR}
	${math_SOURCE_DIR}
)
