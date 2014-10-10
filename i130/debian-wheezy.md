### Pakete

    #wifi firmware for intel 
    PACKAGES=firmware-iwlwifi
    #networking
    PACKAGES=$PACKAGES miredo vpnc vpnc-scripts
    #workspace
    PACKAGES=$PACKAGES tmux
    #multimedia
    #pulseaudio libao4 paprefs libpulse-mainloop-glib0 pulseaudio-module-jack
    #pulseaudio-module-x11 gstreamer0.10-pulseaudio pulseaudio-utils libasound2-plugins
    #paman pulseaudio-module-gconf libgconfmm-2.6-1c2 libglademm-2.4-1c2a
    #pulseaudio-esound-compat libpulse0 libpulse-dev pulseaudio-module-bluetooth pulseaudio-module-zeroconf
    #maybe purge everything with 'alsa'
    PACKAGES=$PACKAGES mplayer2 pulseaudio vlc pavucontrol pavumeter
    #communication
    PACKAGES=$PACKAGES enigmail
    #non-free einbeziehen
    sudo cat 'deb http://http.debian.net/debian/ wheezy main non-free' >> /etc/apt/sources.list
    #pakete ziehen
    apt-get update
    apt-get install ${PACKAGES}
    #activate wifi
    sudo modprobe iwlwifi

### Nutzer in sudoers einfügen

    su
    adduser ${USERNAME} sudo
    
### UUID identifizieren

    sudo blkid -o list -w /dev/null
    
