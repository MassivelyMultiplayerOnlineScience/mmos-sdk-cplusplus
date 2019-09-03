#ifndef IAUTHENTICATION_H_
#define IAUTHENTICATION_H_

#include <string>
#include <map>

namespace MMOS {
	namespace SDK {
		class IAuthentication {
		public:
			virtual std::map<std::string, std::string> prepareHeaders(std::string key, std::string secret, std::string method, std::string path, std::string data) = 0;
		};
	}
}

#endif