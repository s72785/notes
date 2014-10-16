### Pakete

    # networking
    # wifi firmware for intel 
    #PACKAGES=firmware-iwlwifi #u.a. iwl4965 f. T61
    # wifi firmware for x230
    #PACKAGES=firmware-linux-nonfree firmware-realtek
    PACKAGES=$PACKAGES wpasupplicant ifenslave-2.6 tcpdump vpnc vpnc-scripts curl
    #miredo
    # workspace
    PACKAGES=$PACKAGES tmux #terminal multiplexer
    PACKAGES=$PACKAGES git  #version control system
    # printers
    PACKAGES=$PACKAGES cups #printer management
    #PACKAGES=$PACKAGES hplip hplip-cups #hp deskjet printers, some laserjet
    #PACKAGES=$PACKAGES sane #scanning with hp deskjet aio devices
    PACKAGES=$PACKAGES lyx  #tex system, easy to use
    PACKAGES=$PACKAGES geany doc-base #geany editor
    #
    # make, xstl tools (c3d2-web etc.)
    PACKAGES=$PACKAGES make libxml2-utils xsltproc
    # multimedia
    #pulseaudio libao4 paprefs libpulse-mainloop-glib0 pulseaudio-module-jack
    #pulseaudio-module-x11 gstreamer0.10-pulseaudio pulseaudio-utils libasound2-plugins
    #paman pulseaudio-module-gconf libgconfmm-2.6-1c2 libglademm-2.4-1c2a
    #pulseaudio-esound-compat libpulse0 libpulse-dev pulseaudio-module-bluetooth
    #pulseaudio-module-zeroconf
    # maybe purge everything with 'alsa' - didnt need that for now
    PACKAGES=$PACKAGES mplayer2 pulseaudio vlc pavucontrol pavumeter
    # communication
    PACKAGES=$PACKAGES enigmail transmission psi-plus
    # things not needed anyhow 
    NOPACKAGES=evolution libjudydebian1
    # non-free for wifi drivers
    sudo cat 'deb http://http.debian.net/debian/ wheezy main non-free' >> /etc/apt/sources.list
    # finally pull packages
    sudo apt-get update
    sudo apt-get remove ${NOPACKAGES}
    sudo apt-get upgrade
    sudo apt-get install ${PACKAGES}

### ext. Software

    dropbox
    truecrypt
    gchqconfig # hqprint, nw-bonding
    htwtools
    htwconfig
    wpa_subblicant.conf
    #x230 wifi for rtl8192ce incl. rtl8188ce
    # read: 
    #      http://crunchbang.org/forums/viewtopic.php?id=19790
    #      http://forums.debian.net/viewtopic.php?t=84245
    # download http://www.realtek.com.tw/downloads/downloadsView.aspx?Langid=1&PNid=21&PFid=48&Level=5&Conn=4&DownTypeID=3&GetDown=false&Downloads=true#2722
    #tar -xf linux_mac80211_0012.0207.2013.tar.bz2 
    #sudo mv rtl_92ce_92se_92de_8723ae_88ee_linux_mac80211_0012.0207.2013/* /lib/firmware/rtlwifi/
    #sudo modprobe rtl8192ce

### Nutzer in sudoers einfügen

    su
    visudo
    #adduser ${USERNAME} sudo
    
### UUID identifizieren

    sudo blkid -o list -w /dev/null
    
### Network

    # interfaces
    auto lo
    iface lo inet loopback
    
    auto wlan0
    iface wlan0 inet dhcp
        wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf
    #    bond-master bond0
    #    bond-primary eth0
    #    bond-mode active-backup

    allow-hotplug eth0
    iface eth0 inet dhcp
    #    bond-master bond0
    #    bond-primary eth0
    #    bond-mode active-backup

    # Define master
    #auto bond0
    #iface bond0 inet dhcp
    #    bond-slaves none
    #    bond-primary eth0
    #    bond-mode active-backup
    #    bond-miimon 100

    # /interfaces

    sudo chmod 600 /etc/network/interfaces 
    sudo chmod 600 /etc/wpa_supplicant/wpa_supplicant.conf

### Network Manager deaktivieren

    sudo /etc/init.d/network-manager stop
    sudo update-rc.d network-manager remove
    sudo /etc/init.d/networking stop
    sudo /etc/init.d/networking start
    #sudo /etc/init.d/networking restart

### WLAN Treiber einbinden

    lspci
    dmesg|grep -i firmware
    iwconfig
    # for t61
    #modprobe iwl4965 
    # for c230
    #modprobe rtl8192ce 
    dhcp wlan0

### Drucker einrichten

* [HP AIO Geräte](https://help.ubuntu.com/community/HpAllInOne#Setup)

### set links from home to containers

