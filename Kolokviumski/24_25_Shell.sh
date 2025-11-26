#!/bin/bash
files=$(find . -type f -name "*.crypto")
rm -f ./all.crypto

for f in $files
do
    if grep -wE "BTC|Doge|EOS|ETH|XPM" "$f"; then
      cat "$f" >> all.crypto
    fi
done
