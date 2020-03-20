#!/bin/bash

echo "Counting warnings and errors"

out=`make re -j 2>&1`

warns=$(echo "$out" | grep "warning:" | wc -l)
errors=$(echo "$out" | grep "error:" | wc -l)
total=$(( $warns + $errors ))

echo "{\"errors\": $errors, \"warnings\": $warns, \"total\": $total}" > badge.json
