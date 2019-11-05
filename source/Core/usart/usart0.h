#ifndef _USART_USART0_H_
#define _USART_USART0_H_

#include "core/usart/base.h"

#ifndef F_CPU
#define F_CPU 16000000 // SUPPRESS COMPILER ERROR
#endif

namespace Usart
{
	class Usart0: public Usart::Base
	{
		public: // CONSTRUCTORS
			Usart0(void) = default;
			Usart0(const Spec& spec);
		public: // DESTRUCTOR
			~Usart0(void) = default;

		public: // GETTERS
			FILE* stream(void) override;

		public: // METHODS
			void initialize(const Spec& spec);
			//
			void putchar(char c) override;
			char getchar(void  ) override;
			void flush  (void  ) override;

		public: // OPERATORS
			Usart0& operator<<(      char  c);
			Usart0& operator<<(const char* s);
			Usart0& operator>>(      char& c);
			Usart0& operator>>(      char* s);

		private:
			void initialize_pipeline(const Spec& initialize);
	};

	inline void Usart0::initialize(const Spec& spec)
	{
		switch (spec.x2)
		{
			case X2::ENABLED:
				SET(UCSR0A, U2X0);
				UBRR0 = F_CPU/8/spec.baud - 1;
				break;
			case X2::DISSABLED:
				CLEAR(UCSR0A, U2X0);
				UBRR0 = F_CPU/16/spec.baud - 1;
				break;
		}

		switch (spec.rx)
		{
			case RX::ENABLED:   SET  (UCSR0B, RXEN0); break;
			case RX::DISSABLED: CLEAR(UCSR0B, RXEN0); break;
		}

		switch (spec.tx)
		{
			case TX::ENABLED:   SET  (UCSR0B, TXEN0); break;
			case TX::DISSABLED: CLEAR(UCSR0B, TXEN0); break;
		}

		switch (spec.stop_bit_select)
		{
			case STOP_BIT_SELECT::S1: SET  (UCSR0C, USBS0); break;
			case STOP_BIT_SELECT::S2: CLEAR(UCSR0C, USBS0); break;
		}

		switch (spec.character_size)
		{
			case CHARACTER_SIZE::S5:
				CLEAR(UCSR0C, UCSZ00);
				CLEAR(UCSR0C, UCSZ01);
				CLEAR(UCSR0B, UCSZ02);
				break;
			case CHARACTER_SIZE::S6:
				SET  (UCSR0C, UCSZ00);
				CLEAR(UCSR0C, UCSZ01);
				CLEAR(UCSR0B, UCSZ02);
				break;
			case CHARACTER_SIZE::S7:
				CLEAR(UCSR0C, UCSZ00);
				SET  (UCSR0C, UCSZ01);
				CLEAR(UCSR0B, UCSZ02);
				break;
			case CHARACTER_SIZE::S8:
				CLEAR(UCSR0C, UCSZ00);
				SET  (UCSR0C, UCSZ01);
				SET  (UCSR0B, UCSZ02);
				break;
			case CHARACTER_SIZE::S9:
				SET  (UCSR0C, UCSZ00);
				SET  (UCSR0C, UCSZ01);
				SET  (UCSR0B, UCSZ02);
				break;
		}

		SET(UCSR0B, UDRIE0);
		// SET(UCSR0B, TXCIE0);
		// SET(UCSR0B, RXCIE0);

		initialize_pipeline(spec);
	}

	inline void Usart0::putchar(char c)
	{
		if (IS_SET(UCSR0A, UDRE0))
			UDR0 = c;
		else
			output_queue << c;
	}
	inline char Usart0::getchar(void)
	{
		while (IS_CLEAR(UCSR0A, RXC0)) {}
		return UDR0;
	}

	inline void Usart0::flush(void)
	{
		uint8_t sreg_save = SREG;
		cli();
		while (!output_queue.is_empty())
		{
			while (IS_CLEAR(UCSR0A, UDRE0)) {}
			output_queue >> UDR0;
		}
		SREG = sreg_save;
	}

	inline Usart0& Usart0::operator<<(char c)
	{
		putchar(c);

		return *this;
	}
	inline Usart0& Usart0::operator<<(const char* s)
	{
		while (*s) putchar(*s++);

		return *this;
	}

	inline Usart0& Usart0::operator>>(char& c)
	{
		c = getchar();

		return *this;
	}

	extern Usart0 usart0;
}

#endif
