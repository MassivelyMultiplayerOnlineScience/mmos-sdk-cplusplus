#ifndef API_H_
#define API_H_

#include <cpprest/http_client.h>
#include "V2/Classifications.h"
#include "V2/Players.h"
#include "IAuthentication.h"
#include "V2/Authentication.h"
#include <string>
#include <vector>

namespace MMOS {
	namespace SDK {
		class Api {
		public:
			enum class ApiVersion { V2 = 2 };
			struct ApiV2 {
				V2::Players* players;
				V2::Classifications* classifications;
				IAuthentication* authentication;
				ApiV2(Api* api);
				~ApiV2();
			};
			struct ApiConfig {
				std::string Key;
				std::string Secret;
				std::string Game;
				std::string Protocol;
				std::string Host;
				std::string Port;
				ApiVersion Version;
			};
			
			const ApiVersion CURRENT_VERSION = ApiVersion::V2;
			const std::string DEFAULT_PROTOCOL = "https";
			const int DEFAULT_PORT = 443;

			Api(ApiConfig config);
			~Api();
			web::json::value Info();
			web::json::value Call(std::string path, std::string method, web::json::value body, std::vector<int> expectedStatusCodes);
			std::string GetGame();
			ApiV2* V2;
		private:
			ApiConfig Config;
			std::string Game;
			IAuthentication* Authentication;
			web::http::client::http_client* client;
			web::json::value HandleResponse(pplx::task<web::http::http_response> response, std::vector<int> expectedStatusCodes);
		};
	}
}

#endif