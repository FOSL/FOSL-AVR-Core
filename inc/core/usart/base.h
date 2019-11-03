#ifndef _USART_BASE_H_
#define _USART_BASE_H_

#include <stdio.h>
#undef getchar
#undef putchar

#include "core/usart/queue.h"

namespace Core
{
	namespace Usart
	{
		struct Spec
		{
			uint16_t baud_rate;
			bool     x2                = true;
			bool     rx                = true;
			bool     tx                = true;
			uint8_t  character_size    = 8;
			uint8_t  stop_bit_count    = 1;
			uint8_t  output_queue_size = 8;
		};

		class Base
		{
			public: // CONSTRUCTORS
				Base(void) = default;
			public: // DESTRUCTOR
				virtual ~Base(void) = default;

			public: // GETTERS
				virtual FILE* stream(void) = 0;
			public: // SETTERS
				void x2(bool new_x2) = 0;
				void rx(bool new_rx) = 0;
				void tx(bool new_tx) = 0;
				void character_size(uint8_t new_character_size) = 0;
				void stop_bit_count(uint8_t new_stop_bit_count) = 0;

			public: // METHODS
				initialize(const Spec^)
				//
				virtual void putchar(char c) = 0;
				virtual char getchar(void  ) = 0;
				virtual void flush  (void  ) = 0;

			public:
				Queue output_queue;
		};
	}
}

#endif
