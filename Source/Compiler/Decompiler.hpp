
#include "../Common/Header.hpp"

#ifndef SPIN_DECOMPILER_HPP
#define SPIN_DECOMPILER_HPP

#include "Program.hpp"

namespace Spin {

	class Decompiler {

		private:

		static const String colours[];

		enum Colour {
			red,
			yellow,
			white,
			black,
			orange,
			blue,
			green,
			purple,
			pink,
			gray,
			acqua,
		};

		static void aloneOP(String o, Colour c);
		static void indexOP(String o, Int64 i, Colour c);
		static void typesOP(String o, Types x, Colour c);
		static void unaryOP(String o, Type x, Colour c);
		
		static String resolve(Type type);

		public:

		Decompiler() = delete;

		static void decompile(ByteCode byte);
		static void decompile(Array<ByteCode> source);

	};

}

#endif
