
#include "../Common/Header.hpp"

#ifndef SPIN_MANAGER_HPP
#define SPIN_MANAGER_HPP

#include <fstream>
#include <sstream>

using StringStream = std::stringstream;
using IFStream = std::ifstream;
using OFStream = std::ofstream;

namespace Spin {

	class Manager {
		public:
		class BadFileException: public Exception {
			private:
			const String path;
			public:
			BadFileException(const String & path);
			const String & getPath() const;
		};
		Manager() = delete;
		static UInt64 getLine(String * input, SizeType cursor);
		static String * stringFromFile(String path);
		static void createNewFile(String path, String content = String());
		static void writeBuffer(String path, Buffer * buffer);
		static Buffer * readBuffer(String path);
	};

}

#endif
