#pragma once
#include <string>
#include <vector>

// 64 KB
#define RAM_SIZE	0xFFFF
#define STACK_START 0x0100
#define STACK_SIZE	0xFF


namespace NintendoES {
	class CPU
	{
	public:

		uint8_t RAM[RAM_SIZE];


#pragma region Registers
		// Status Register
		union Flags {
			struct {
				uint8_t C : 1;	// Carry Bit 
				uint8_t Z : 1;	// Zero
				uint8_t I : 1;	// Disable Interrupts
				uint8_t D : 1;	// Decimal Mode (unused in NES)
				uint8_t B : 1;	// Break
				uint8_t U : 1;	// Unused
				uint8_t V : 1;	// Overflow
				uint8_t N : 1;	// Negative
			};
			uint8_t Flags;
		};

		uint8_t A = 0x00;		// Accumulator Register
		uint8_t X = 0x00;		// X Register
		uint8_t Y = 0x00;		// Y Register
		uint8_t STKP = 0x00;	// Stack Pointer (points to location on bus)
		uint16_t PC = 0x0000;	// Program Counter
		Flags Status = {0x00};	// Status Register

		void ResetStatusFlags() { Status.Flags = 0x00; }
#pragma endregion


#pragma region Instructions

	private:
		uint8_t  fetched = 0x00;			// Represents the working input value to the ALU
		uint16_t temp = 0x0000;				// A convenience variable used everywhere
		uint16_t addr_abs = 0x0000;			// All used memory addresses end up in here
		uint16_t addr_rel = 0x00;			// Represents absolute address following a branch
		uint8_t  opcode = 0x00;				// Is the instruction byte
		uint8_t  cycles = 0;				// Counts how many cycles the instruction has remaining
		uint32_t clock_count = 0;			// A global accumulation of the number of clocks

		uint8_t fetch();
		
#pragma endregion

		uint8_t read(uint16_t addr);
	};
}