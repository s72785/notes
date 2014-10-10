### Pakete

    PACKAGES=firmware-iwlwifi miredo mplayer2 pulseaudio tmux vpnc vpnc-scripts enigmail
    apt-get update
    a pt-get install ${PACKAGES}

### Nutzer in sudoers einfügen

    su
    adduser ${USERNAME} sudo
    
### UUID identifizieren

    sudo blkid -o list -w /dev/null
    
