#!/bin/bash

# Check if no arguments are provided
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <argument1> <argument2> ..."
    exit 1
fi

# Display the provided arguments
echo "Provided arguments:"
for arg in "$@"; do
    echo "$arg"
done