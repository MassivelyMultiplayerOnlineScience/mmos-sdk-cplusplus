#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <string>
#include <cpprest/http_client.h>

namespace MMOS {
	namespace SDK {
		class Api; //forward declaration
	}
}

namespace MMOS {
	namespace SDK {
		namespace V2 {
			class Players {
				private:
					Api* api;
				public:
					Players(Api* api);
					~Players();
					web::json::value Get(std::string playerCode, std::string project);
					web::json::value CreateTask(std::string playerCode, web::json::value body);
			};
		}
	}
}

#endif