#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

FILE=$1

# Check if the file exists
if [ ! -f "$FILE" ]; then
  echo "Error: File '$FILE' not found!"
  exit 1
fi

# Infinite loop to display the file
while true; do
  clear  # Clear the screen
  cat "$FILE"  # Display the file content
  sleep 0.1  # 100 ms delay
done

