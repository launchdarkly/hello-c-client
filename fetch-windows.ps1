# script from https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/
$ProgressPreference = "SilentlyContinue"  # prevents console errors from CircleCI host
$latestRelease = Invoke-WebRequest https://github.com/launchdarkly/c-client-sdk/releases/latest -Headers @{"Accept"="application/json"}
$json = $latestRelease.Content | ConvertFrom-Json
$latestVersion = $json.tag_name
$url = "https://github.com/launchdarkly/c-client-sdk/releases/download/$latestVersion/windows-vs-64bit-dynamic-release.zip"
Invoke-WebRequest -Uri $url -Outfile windows-vs-64bit-dynamic.zip
Expand-Archive -Path windows-vs-64bit-dynamic.zip -DestinationPath .
cp lib/ldclientapi.dll .
