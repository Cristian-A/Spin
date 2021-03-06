
#include "Header.hpp"

#ifndef SPIN_INTERFACE_PURE
#define SPIN_INTERFACE_PURE

	#include <iomanip>

	enum ExitCodes: Int32 {
		success = 0,
		failure = 1
	};

	#define IStream std::cin
	#define OStream std::cout

	#define endLine std::endl

	#define padding(n) std::setw(n) << std::setfill('0')
	#define upperCase std::uppercase
	#define hexadecimal std::hex
	#define decimal std::dec

	inline String getInput() {
		String input;
		std::getline(std::cin, input);
		return input;
	}

	inline void waitKeyPress() {
		std::cin.get();
	}

#endif
