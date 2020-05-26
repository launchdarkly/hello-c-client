#include <stdbool.h>
#include <stdio.h>

#include "ldapi.h"
#include "uthash.h"

#define YOUR_MOBILE_SDK_KEY "<put your mobile sdk key here>"
#define YOUR_FEATURE_KEY "<put your feature key here>"
 
void logger(const char *s) {
    printf("LD: %s\n", s);
}

int main() {
    LDSetLogFunction(LD_LOG_INFO, logger);
 
    LDConfig *config = LDConfigNew(YOUR_MOBILE_SDK_KEY);
    const char* key = "bob@example.com";
    LDUser *user = LDUserNew(key);
 
    // wait up to 3 seconds to connect
    LDClient *client = LDClient::Init(config, user, 3000);
 
    int show_feature = client->boolVariation(YOUR_FEATURE_KEY, false);

	client->close();
	
	
    if (show_feature) {
        // application code to show the feature
        printf("Showing your feature to %s\n", key);
    } else {
        // the code to run if the feature is off
        printf("Not showing your feature to %s\n", key);
    }
 
    return 0;
}