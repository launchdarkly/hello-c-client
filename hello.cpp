#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <launchdarkly/api.hpp>

// Set MOBILE_KEY to your LaunchDarkly mobile key.
#define MOBILE_KEY ""

// Set FEATURE_FLAG_KEY to the feature flag key you want to evaluate.
#define FEATURE_FLAG_KEY "my-boolean-flag"
#define USER_KEY "example-user-key"
#define USER_NAME "Sandy"

#define INIT_TIMEOUT_MILLISECONDS 3000

int main(int argc, const char* argv[]) {
    const char *mobile_key = argc > 1 ? argv[1] : MOBILE_KEY;
    const char *feature_flag_key = argc > 2 ? argv[2] : FEATURE_FLAG_KEY;
    const char *user_key = argc > 3 ? argv[3] : USER_KEY;
    const char *user_name = argc > 4 ? argv[4] : USER_NAME;


    if (!strlen(mobile_key)) {
        printf("*** Please edit hello.cpp to set MOBILE_KEY to your LaunchDarkly mobile key first or pass it as the first argument\n\n");
        return 1;
    }

    LDConfig *config;
    LDClientCPP *client;
    LDUser *user;

    LDConfigureGlobalLogger(LD_LOG_INFO, LDBasicLogger);

    config = LDConfigNew(mobile_key);

    // Set up the user properties. This user should appear on your LaunchDarkly users dashboard
    // soon after you run the demo.
    user = LDUserNew(user_key);
    LDUserSetName(user, user_name);

    client = LDClientCPP::Init(config, user, INIT_TIMEOUT_MILLISECONDS);

    if(client->isInitialized()) {
        printf("*** SDK successfully initialized!\n\n");
    } else {
        printf("*** SDK failed to initialize\n\n");
        return 1;
    }

    LDBoolean flag_value = client->boolVariation(feature_flag_key, false);

    printf("*** Feature flag '%s' is %s for this user\n\n",
        feature_flag_key, flag_value ? "true" : "false");

    // Here we ensure that the SDK shuts down cleanly and has a chance to deliver analytics
    // events to LaunchDarkly before the program exits. If analytics events are not delivered,
    // the user properties and flag usage statistics will not appear on your dashboard. In a
    // normal long-running application, the SDK would continue running and events would be
    // delivered automatically in the background.
    client->close();

    return 0;
}
