1: http://forums.linuxmint.com/viewtopic.php?f=197&t=71159
2: http://www.stura.htw-dresden.de/members/PaulRiegel/os/lmde/log

sudo -s
apt-get update
apt-get install lvm2 squashfs-tools
apt-get install cryptsetup
gdisk -l /dev/sda
cryptsetup luksFormat /dev/sda2
cryptsetup luksOpen /dev/sda2 harddisk
VOLUME=/dev/mapper/harddisk
pvcreate $VOLUME
vgcreate volumes $VOLUME
lvcreate -L 20G -n swap volumes
mkswap /dev/mapper/volumes-swap 
lvcreate -n lmde -L 1000G volumes
#error message used to fill disk with the number in paranteses
lvcreate -n lmde -l 70440 volumes
swapon /dev/volumes/swap
mkfs -t ext4 -L root -j /dev/volumes/lmde
#sudo cryptsetup -c aes-xts-plain64 -s 512 luksFormat /dev/sda2
mount /dev/volumes/lmde /mnt
mkdir /mnt/boot
mount /dev/sda1 /mnt/boot
