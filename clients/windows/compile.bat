@echo off
gcc client.c -o client -I../curl/include -L../curl/lib -lcurl
pause