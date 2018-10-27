#include "unistd.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"

#include "ldapi.h"

#define YOUR_MOBILE_SDK_KEY "<put your mobile sdk key here>"
#define YOUR_FEATURE_KEY "<put your feature key here>"

void on_signal(int signum) {
   // tear down the client
   LDClientClose(LDClientGet());
   exit(0);
}

int main() {
    LDConfig *config = LDConfigNew(YOUR_MOBILE_SDK_KEY);
    char* key = "bob@example.com";
    LDUser *user = LDUserNew(key);
    LDClient *client = LDClientInit(config, user);

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
