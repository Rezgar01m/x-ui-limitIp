#!/bin/bash

while true; do
    read -p "Do you want to run the command ./main? (y/n): " choice

    if [[ $choice == "y" || $choice == "Y" ]]; then
        nohup ./main > output.log
    elif [[ $choice == "stop main" ]]; then
        echo "Program stopped."
        break
    else
        echo "Invalid input. Please try again."
    fi
done
