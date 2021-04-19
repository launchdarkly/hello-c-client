#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <launchdarkly/api.h>

// Set MOBILE_KEY to your LaunchDarkly mobile key.
#define MOBILE_KEY ""

// Set FEATURE_FLAG_KEY to the feature flag key you want to evaluate.
#define FEATURE_FLAG_KEY "my-boolean-flag"

#define INIT_TIMEOUT_MILLISECONDS 3000

int main() {    
    if (!strlen(MOBILE_KEY)) {
        printf("*** Please edit hello.c to set MOBILE_KEY to your LaunchDarkly mobile key first\n\n");
        return 1;
    }

    struct LDConfig *config;
    struct LDClient *client;
    struct LDUser *user;

    LDConfigureGlobalLogger(LD_LOG_INFO, LDBasicLogger);

    config = LDConfigNew(MOBILE_KEY);

    // Set up the user properties. This user should appear on your LaunchDarkly users dashboard
    // soon after you run the demo.
    user = LDUserNew("example-user-key");
    LDUserSetName(user, "Sandy");

    client = LDClientInit(config, user, INIT_TIMEOUT_MILLISECONDS);

    if (LDClientIsInitialized(client)) {
        printf("*** SDK successfully initialized!\n\n");
    } else {
        printf("*** SDK failed to initialize\n\n");
        return 1;
    }

    LDBoolean flag_value = LDBoolVariation(client, FEATURE_FLAG_KEY, false);

    printf("*** Feature flag '%s' is %s for this user\n\n",
        FEATURE_FLAG_KEY, flag_value ? "true" : "false");

    // Here we ensure that the SDK shuts down cleanly and has a chance to deliver analytics
    // events to LaunchDarkly before the program exits. If analytics events are not delivered,
    // the user properties and flag usage statistics will not appear on your dashboard. In a
    // normal long-running application, the SDK would continue running and events would be
    // delivered automatically in the background.
    LDClientClose(client);

    return 0;
}
