@echo off
gcc client.c -o client -Lcurl/lib -Icurl/include -lcurl 