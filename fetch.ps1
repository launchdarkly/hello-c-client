# script from https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/
$latestRelease = Invoke-WebRequest https://github.com/account/project/releases/latest -Headers @{"Accept"="application/json"}
$json = $latestRelease.Content | ConvertFrom-Json
$latestVersion = $json.tag_name
$url = "https://github.com/account/project/releases/download/$latestVersion/myArtifact.zip"
Invoke-WebRequest -Uri $url
Expand-Archive -Path artifacts\windows-vs-64bit-dynamic.zip -DestinationPath .
