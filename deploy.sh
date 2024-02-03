#!/bin/bash
# deploy.sh: write a UF2 binary to a Raspberry Pi Pico (W) in BOOTSEL mode
# Probably needs root to work properly! (mount and cp commands)

mount_location=/mnt/pico # where the flash partition shall be mounted
                         # (no trailing slash, please)
binary=a0_bl.uf2 # the UF2 binary to send to the Pico

before=$(lsblk -o NAME) # get existing devices
read -n 1 -s -r -p "Plug the Pico in BOOTSEL mode. Press Enter when finished."
echo # runs when Enter is pressed
after=$(lsblk -o NAME) # get new device list

diff=$(diff <(printf "$before") <(printf "$after")) # find new/changed device
                                                    # (presumed to be the Pico)
dev_name=$(printf "$diff" | grep '^> └─' | cut -c 9-) # get name of the Pico

mount /dev/${dev_name} ${mount_location} # mount the Pico's flash partition
cp $binary ${mount_location} # copy over the UF2 binary

printf "\nDeployed.\n" # It works on my machine™, so no error handling