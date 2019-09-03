#ifndef AUTHENTICATION_H_
#define AUTHENTICATION_H_

#include "../IAuthentication.h"
#include <string>
#include <map>
#include <cpprest/http_client.h>

namespace MMOS {
	namespace SDK {
		namespace V2 {
			class Authentication : public MMOS::SDK::IAuthentication{
			private:
				const std::string CONTENT_SEPARATOR = "|";
				const std::string MMOS_SIGNING_ALGORITHM = "MMOS1-HMAC-SHA256";
				uint64_t timeSinceEpochMillisec();
				std::string CreateHmac(std::string key, std::string msg);
			public:
				Authentication();
				std::map<std::string, std::string> prepareHeaders(std::string key, std::string secret, std::string method, std::string path, std::string data);
			};
		}
	}
}

#endif