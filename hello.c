#include <stdbool.h>
#include <stdio.h>

#include <launchdarkly/api.h>

#define YOUR_MOBILE_SDK_KEY "<put your mobile sdk key here>"
#define YOUR_FEATURE_KEY "<put your feature key here>"

int main() {
    LDConfigureGlobalLogger(LD_LOG_INFO, LDBasicLogger);

    struct LDConfig *config = LDConfigNew(YOUR_MOBILE_SDK_KEY);
    char* key = "bob@example.com";
    struct LDUser *user = LDUserNew(key);
    // wait up to 3 seconds to connect
    struct LDClient *client = LDClientInit(config, user, 3000);

    LDBoolean show_feature = LDBoolVariation(client, YOUR_FEATURE_KEY, false);

    if (show_feature) {
        // application code to show the feature
        printf("Showing your feature to %s\n", key);
    } else {
        // the code to run if the feature is off
        printf("Not showing your feature to %s\n", key);
    }

    LDClientClose(client);

    return 0;
}
