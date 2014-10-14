### Pakete

    # wifi firmware for intel 
    PACKAGES=firmware-iwlwifi #u.a. iwl4965 f. T61
    # networking
    PACKAGES=$PACKAGES wpasupplicant ifenslave-2.6 tcpdump vpnc vpnc-scripts
    #miredo
    # workspace
    PACKAGES=$PACKAGES tmux git cups lyx
    # multimedia
    #pulseaudio libao4 paprefs libpulse-mainloop-glib0 pulseaudio-module-jack
    #pulseaudio-module-x11 gstreamer0.10-pulseaudio pulseaudio-utils libasound2-plugins
    #paman pulseaudio-module-gconf libgconfmm-2.6-1c2 libglademm-2.4-1c2a
    #pulseaudio-esound-compat libpulse0 libpulse-dev pulseaudio-module-bluetooth pulseaudio-module-zeroconf
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

### Nutzer in sudoers einfügen

    su
    adduser ${USERNAME} sudo
    
### UUID identifizieren

    sudo blkid -o list -w /dev/null
### Network

    sudo chmod 600 /etc/network/interfaces 
    sudo chmod 600 /etc/wpa_supplicant/wpa_supplicant.conf

### WLAN Treiber einbinden

    lspci
    modprobe iwl4965

### Network Manager deaktivieren

    sudo /etc/init.d/network-manager stop
    sudo update-rc.d network-manager remove
    sudo /etc/init.d/networking stop
    sudo /etc/init.d/networking start

### set links from home to containers

