#ifndef CLASSIFICATIONS_H_
#define CLASSIFICATIONS_H_

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
			class Classifications {
				private:
					Api* api;
				public:
					Classifications(Api* api);
					~Classifications();
					web::json::value Create(web::json::value body);
			};
		}
	}
}

#endif