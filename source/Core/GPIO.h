#ifndef _CORE_GPIO_H_
#define _CORE_GPIO_H_

#include <util.h>

namespace Core
{
	namespace GPIO
	{
		enum class PORT : uint8_t { B, C, D };
		enum class MODE : uint8_t { INPUT, OUTPUT };

		template <PORT port, uint8_t index>
		class Handle
		{
			public: // CONSTRUCTORS
				Handle(MODE mode = MODE::OUTPUT);
			public: // DESTRUCTOR
				~Handle(void) = default;

			public: // METHODS
				void set  (void);
				void clear(void);
				void toggle(void);
				bool is_high(void) const;
				bool is_low (void) const;

				void make_input (void);
				void make_output(void);
				bool is_input (void) const;
				bool is_output(void) const;

				void pull_up   (void);
				void disconnect(void);
				bool is_pulled_up   (void) const;
				bool is_disconnected(void) const;

			public: // OPERATORS
				Handle<port, index>& operator=(bool state);
				Handle<port, index>& operator()(MODE mode);
				operator bool(void) const;
		};

		template <PORT port, uint8_t index>
		Handle<port, index>::Handle(MODE mode)
		{
			switch (mode)
			{
				case MODE::OUTPUT: make_output(); break;
				case MODE:: INPUT: make_input (); break;
			}
		}

		template <PORT port, uint8_t index>
		Handle<port, index>& Handle<port, index>::operator=(bool state)
		{
			switch (state)
			{
				case HIGH: set  (); break;
				case LOW:  clear(); break;
			}

			return *this;
		}
		template <PORT port, uint8_t index>
		Handle<port, index>& Handle<port, index>::operator()(MODE mode)
		{
			switch (mode)
			{
				case MODE::OUTPUT: make_output(); break;
				case MODE:: INPUT: make_input (); break;
			}

			return *this;
		}
		template <PORT port, uint8_t index>
		Handle<port, index>::operator bool(void) const
		{
			return is_high();
		}

		template <PORT port, uint8_t index>
		void Handle<port, index>::set(void)
		{
			switch (port)
			{
				case PORT::B: SET(PORTB, index); break;
				case PORT::C: SET(PORTC, index); break;
				case PORT::D: SET(PORTD, index); break;
			}
		}
		template <PORT port, uint8_t index>
		void Handle<port, index>::clear(void)
		{
			switch (port)
			{
				case PORT::B: CLEAR(PORTB, index); break;
				case PORT::C: CLEAR(PORTC, index); break;
				case PORT::D: CLEAR(PORTD, index); break;
			}
		}
		template <PORT port, uint8_t index>
		void Handle<port, index>::toggle(void)
		{
			switch (port)
			{
				case PORT::B: TOGGLE(PORTB, index); break;
				case PORT::C: TOGGLE(PORTC, index); break;
				case PORT::D: TOGGLE(PORTD, index); break;
			}
		}

		template <PORT port, uint8_t index>
		void Handle<port, index>::make_output(void)
		{
			switch (port)
			{
				case PORT::B: SET(DDRB, index); break;
				case PORT::C: SET(DDRC, index); break;
				case PORT::D: SET(DDRD, index); break;
			}
		}
		template <PORT port, uint8_t index>
		void Handle<port, index>::make_input(void)
		{
			switch (port)
			{
				case PORT::B: CLEAR(DDRB, index); break;
				case PORT::C: CLEAR(DDRC, index); break;
				case PORT::D: CLEAR(DDRD, index); break;
			}
		}

		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_high(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_SET(PINB, index);
				case PORT::C: return IS_SET(PINC, index);
				case PORT::D: return IS_SET(PIND, index);
			}
		}
		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_low(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_CLEAR(PINB, index);
				case PORT::C: return IS_CLEAR(PINC, index);
				case PORT::D: return IS_CLEAR(PIND, index);
			}
		}

		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_output(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_SET(DDRB, index);
				case PORT::C: return IS_SET(DDRC, index);
				case PORT::D: return IS_SET(DDRD, index);
			}
		}
		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_input(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_CLEAR(DDRB, index);
				case PORT::C: return IS_CLEAR(DDRC, index);
				case PORT::D: return IS_CLEAR(DDRD, index);
			}
		}

		template <PORT port, uint8_t index>
		void Handle<port, index>::pull_up(void)
		{
			switch (port)
			{
				case PORT::B: SET(PORTB, index);
				case PORT::C: SET(PORTC, index);
				case PORT::D: SET(PORTD, index);
			}
		}
		template <PORT port, uint8_t index>
		void Handle<port, index>::disconnect(void)
		{
			switch (port)
			{
				case PORT::B: CLEAR(PORTB, index);
				case PORT::C: CLEAR(PORTC, index);
				case PORT::D: CLEAR(PORTD, index);
			}
		}
		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_pulled_up(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_SET(PORTB, index);
				case PORT::C: return IS_SET(PORTC, index);
				case PORT::D: return IS_SET(PORTD, index);
			}
		}
		template <PORT port, uint8_t index>
		bool Handle<port, index>::is_disconnected(void) const
		{
			switch (port)
			{
				case PORT::B: return IS_CLEAR(PORTB, index);
				case PORT::C: return IS_CLEAR(PORTC, index);
				case PORT::D: return IS_CLEAR(PORTD, index);
			}
		}
	}
}

#endif
