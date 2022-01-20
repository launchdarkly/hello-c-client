clang -target x86_64-apple-darwin21.1.0 -o hello hello.c lib/libldclientapi.a -I include -lcurl -lpthread -lm -framework CoreFoundation -framework IOKit
