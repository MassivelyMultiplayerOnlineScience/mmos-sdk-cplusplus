#include "Authentication.h"
#include <chrono>
#include <math.h>
#include <map>
#include <boost/algorithm/string/join.hpp>
#include <openssl/hmac.h>
#include <iomanip>

namespace MMOS {
	namespace SDK {
		namespace V2 {

			Authentication::Authentication() {};

			std::map<std::string, std::string> Authentication::prepareHeaders(std::string key, std::string secret, std::string method, std::string path, std::string data) {
				std::map<std::string, std::string> headers;

				uint64_t timestamp_uint = timeSinceEpochMillisec();
				std::string timestamp = std::to_string(timestamp_uint);
				uint64_t nonceLong = floor(rand() * timestamp_uint) + 1;
				std::string nonce = std::to_string(nonceLong);
				std::string signature;
				std::string contentData = (data.empty()) ? "{}" : data;
				std::vector<std::string> contentParts;

				contentParts.push_back(MMOS_SIGNING_ALGORITHM);
				contentParts.push_back(key);
				contentParts.push_back(timestamp);
				contentParts.push_back(nonce);
				contentParts.push_back(method);
				contentParts.push_back(path);
				contentParts.push_back(contentData);

				std::string contents = boost::algorithm::join(contentParts, CONTENT_SEPARATOR);

				std::string keyHash = CreateHmac(timestamp, secret);
				signature = CreateHmac(keyHash, contents);

				headers["X-MMOS-Algorithm"] = MMOS_SIGNING_ALGORITHM;
				headers["X-MMOS-Credential"] = key;
				headers["X-MMOS-Timestamp"] = timestamp;
				headers["X-MMOS-Nonce"] = nonce;
				headers["X-MMOS-Signature"] = signature;

				return headers;
			}
			uint64_t Authentication::timeSinceEpochMillisec() {
				using namespace std::chrono;
				return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			};
			std::string Authentication::CreateHmac(std::string key, std::string msg) {
				unsigned char hash[32];

				HMAC_CTX hmac;
				HMAC_CTX_init(&hmac);
				HMAC_Init_ex(&hmac, &key[0], key.length(), EVP_sha256(), NULL);
				HMAC_Update(&hmac, (unsigned char*)&msg[0], msg.length());
				unsigned int len = 32;
				HMAC_Final(&hmac, hash, &len);
				HMAC_CTX_cleanup(&hmac);

				std::stringstream ss;
				ss << std::hex << std::setfill('0');
				for (unsigned int i = 0; i < len; i++)
				{
					ss << std::hex << std::setw(2) << (unsigned int)hash[i];
				}

				return (ss.str());
			}
			;
		}
	}
}