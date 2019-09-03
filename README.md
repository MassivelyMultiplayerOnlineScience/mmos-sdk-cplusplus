
[Site](http://mmos.ch/) |
[Developer Portal](https://devportal.mmos.ch/) |
[Twitter](https://twitter.com/the_mmos) |

# MMOS SDK - C++ edition

The MMOS SDK gives easy access to the MMOS API by providing an abstraction layer and encapsulating the authentication modules.

## Installation

* copy the contents of the MMOS.SDK folder into your project directory
* make sure OpenSSL, cpprestsdk and boost-algorithm includes and libraries are available for your building environment (we recommend using vcpkg for Visual Studio users)


## Usage example

In a standard Visual Studio C++ project you can use the syntax below.

Make sure your includes point to the correct file location.

```c++
#include "../MMOS.SDK/Api.h"

Api::ApiConfig Config = {
	"key",
	"secret",
	"game",
	"protocol",
	"host",
	"port",
	Api::ApiVersion::V2
};
   
Api api = Api::Api(Config);

web::json::value body;

web::json::value projects;
projects[0] = web::json::value(U("unige-exoplanet"));
body[U("projects")] = projects;

web::json::value player;
player[U("accountCode")] = web::json::value(U("accountcode"));
body[U("player")] = player;

web::json::value response = api.V2->players->CreateTask("playerCode", body);

```

## Using the MMOS SDK inside unreal

Due to the particularities of the Unreal Engine we've released a specific version of the SDK to be used inside Unreal Engine 4.
Please see the [repository](https://github.com/MassivelyMultiplayerOnlineScience/mmos-sdk-unreal) for more details.


## Documentation


API blueprint is available in compiled [html](doc/blueprint/mmos-api-public.html) and [apib](doc/blueprint/mmos-api-public.apib) format.


## Running automated tests

Presently the MMOS SDK automated tests use the MMOS Developer Portal. The MMOS Developer Portal helps developers understand how the MMOS API works through a set of publicly available test projects. Registration is publicly available at (https://devportal.mmos.ch/).

In order to run the tests, first you'll need to creare an account on the MMOS Developer Portal. Please note that the test rely on specific projects to be avaliable for the game, which is presently the Exoplanet research project by the University of Geneva. So first you'll need to add the Unige Exoplanet project to your available projects on the Developer Portal.

Please note that this may change in the future and thus you may need to update to the latest version of the SDK and follow the up-to-date instructions to be able to run the automated tests.

Once the account is created, there are three environment variables that need to be set in order to be able to run the tests:
* MMOS_SDK_TEST_API_KEY - The MMOS API Key
* MMOS_SDK_TEST_API_SECRET - The MMOS API Secret
* MMOS_SDK_TEST_GAME - The game id that is generated from your email address

Windows example:
```bat
$ SET MMOS_SDK_TEST_API_KEY=key
$ SET MMOS_SDK_TEST_API_SECRET=secret
$ SET MMOS_SDK_TEST_GAME=game
```

Linux example:
```shell
$ export MMOS_SDK_TEST_API_KEY=key
$ export MMOS_SDK_TEST_API_SECRET=secret
$ export MMOS_SDK_TEST_GAME=game
```

After setting the following environment variables you can run the the unit test inside Visual Studio, by switching to View -> Test. 

Please note that under MacOSX using Visual Studio you'll have to call the following commands (replacing with your personal values) in order for Visual Studio to see your environment variables (VS restart is needed):
```
launchctl setenv MMOS_SDK_TEST_API_KEY key
launchctl setenv MMOS_SDK_TEST_API_SECRET secret
launchctl setenv MMOS_SDK_TEST_GAME game
```
When you are done with testing you can remove these environment variables with the following commands:
```
launchctl unsetenv MMOS_SDK_TEST_API_KEY
launchctl unsetenv MMOS_SDK_TEST_API_SECRET
launchctl unsetenv MMOS_SDK_TEST_GAME
```

## Authentication

Please see the [authentication docs](api-hmac-authentication.md) for details.

## Acknowledgments

The GAPARS project has received funding from the European Union’s Horizon 2020 research and innovation programme under grant agreement Nr 732703

![EU flag](https://github.com/MassivelyMultiplayerOnlineScience/mmos-sdk-csharp/raw/master/MMOS.SDK/doc/logo/eu.jpg)