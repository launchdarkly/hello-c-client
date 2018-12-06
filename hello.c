#include "unistd.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"

#include "ldapi.h"

#define YOUR_MOBILE_SDK_KEY "<put your mobile sdk key here>"
#define YOUR_FEATURE_KEY "<put your feature key here>"

void logger(const char *s) {
    printf("LD: %s\n", s);
}

void on_signal(int signum) {
    // tear down the client
    LDClientClose(LDClientGet());
    exit(0);
}

int main() {
    LDSetLogFunction(LD_LOG_INFO, logger);

    LDConfig *config = LDConfigNew(YOUR_MOBILE_SDK_KEY);
    char* key = "bob@example.com";
    LDUser *user = LDUserNew(key);
    // wait up to 3 seconds to connect
    LDClient *client = LDClientInit(config, user, 3000);

    signal(SIGINT, on_signal);

    // disable output buffering
    setbuf(stdout, NULL);

    while (1) {
        int show_feature = LDBoolVariation(client, YOUR_FEATURE_KEY, false);

        if (show_feature) {
            // application code to show the feature
            printf("Showing your feature to %s\n", key);
        } else {
            // the code to run if the feature is off
            printf("Not showing your feature to %s\n", key);
        }

        sleep(1);
    }
}
