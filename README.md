# LaunchDarkly Sample C Client-Side Application
We've built a simple console application that demonstrates how LaunchDarkly's SDK works. Below, you'll find the basic build procedure, but for more comprehensive instructions, you can visit your [Quickstart page](https://app.launchdarkly.com/quickstart#/). Use this as a starting point for integrating the c-client-sdk with your application.

## Build instructions
1. Copy your Mobile SDK key and feature flag key from your LaunchDarkly dashboard into `hello.c`
2. Download the latest SDK with `fetch.sh`, or `fetch.ps1`
3. Build for your particular platform with `build-linux.sh`, `build-mac.sh`, or `build-windows.ps1`
4. Run `./hello`
