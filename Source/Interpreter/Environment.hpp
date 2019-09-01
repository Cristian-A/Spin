
/*!
 *
 *    + --------------------------------------- +
 *    |  Environment.hpp                        |
 *    |                                         |
 *    |            Stack Environment            |
 *    |                                         |
 *    |  Created by Cristian A.                 |
 *    |  Copyright © MIT. All rights reserved.  |
 *    + --------------------------------------- +
 *
 *    Note: This software is licensed under
 *          the (MIT) Massachusetts Institute
 *          of Technology License.
 *
 */

#ifndef STACKENVIRONMENT
#define STACKENVIRONMENT

#include "../Aliases/Aliases.hpp"
#include "../Types/Object.hpp"

namespace Stack {

	class VariableRedefinitionException: public Exception {
		private:
		const String _type;
		public:
		const String & getType() const { return _type; }
		VariableRedefinitionException(String type):
		Exception(), _type(type) { }
	};

	class VariableNotFoundException: public Exception {
		public: VariableNotFoundException(): Exception() { }
	};

	class Environment {

		private:

		Dictionary<String, Object *> values = { };

		public:

		Environment() { }

		void define(String & name, Object * value) {
			auto search = values.find(name);
			if (search != values.end()) {
				throw VariableRedefinitionException(
					(search -> second) -> getObjectName()
				);
			} else values.insert({ name, value });
		}

		Object * getReference(String & name) {
			auto search = values.find(name);
			if (search != values.end()) {
				return search -> second;
			}
			throw VariableNotFoundException();
		}

		Object * getValue(String & name) {
			auto search = values.find(name);
			if (search != values.end()) {
				return (search -> second) -> copy();
			}
			throw VariableNotFoundException();
		}

	};

}

#endif
