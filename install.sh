#!/bin/bash

#*******************************************************************************************#
#*----- Auteur :        Aubertin Emmanuel               | For: Lord Quixard             ****#
#*----- Description :   Lord Quixard installer                                          ****#
#*******************************************************************************************#

PROGNAME=$(basename $0)
RELEASE="Revision 1.0"
AUTHOR="(c) 2024 Aubertin Emmanuel"
DEBUG=0


print_release() {
    echo "$RELEASE $AUTHOR"
}

print_usage() {
        echo ""
        echo "$PROGNAME"
        echo ""
        echo "Usage: $PROGNAME | [-h | --help] | [-v | --version] | [-d | --debug]"
        echo ""
        echo "          -h  Aide"
        echo "          -v  Version"
        echo "          -d  Debug"
        echo ""
}

print_help() {
        print_release $PROGNAME $RELEASE
        echo ""
        print_usage
        echo ""
        echo ""
                exit 0
}

while [ $# -gt 0 ]; do
    case "$1" in
        -h | --help)
            print_help
            exit 
            ;;
        -v | --version)
                print_release
                exit 
                ;;
        -d | --debug)
                DEBUG=1
                ;;
        *)  echo "Argument inconnu: $1"
            print_usage
            ;;
        esac
shift
done

# Detect operating system
OS=$(uname -s)

colored_echo() {
    local color_code="$1"
    local text="$2"
    case "$OS" in
        Darwin)
            # macOS uses \033 instead of \e for color codes
            echo -e "\033[${color_code}${text}\033[0m"
            ;;
        *)
            # Linux and other systems
            echo -e "\e[${color_code}${text}\e[0m"
            ;;
    esac
}


function ask_yes_or_no() {
    echo -n "[yes/no] : "
    read -r YESNO
    if [[ $YESNO =~ [yY] ]]; then
        return 0
    fi
    return 1
}

install_dependencies() {
    colored_echo "32m--------|" "Installing Dependencies |--------"
    
    # Detect operating system
    OS=$(uname -s)
    case "$OS" in
        Darwin)
            # macOS
            echo "Detected macOS. Installing dependencies using brew..."
            if ! command -v brew &> /dev/null
            then
                echo "Homebrew not found. Installing Homebrew..."
                /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
            fi
            brew install sdl2 sdl2_mixer sdl2_ttf sdl2_image make
            ;;
        Linux)
            # Distinguish between Debian-based Linux and CentOS
            if [ -f /etc/debian_version ]; then
                # Debian-based system
                echo "Detected Debian-based Linux. Installing dependencies using apt..."
                sudo apt-get update
                sudo apt-get install -y libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev clang make
            elif [ -f /etc/centos-release ]; then
                # CentOS system
                echo "Detected CentOS. Installing dependencies using yum or dnf..."
                if command -v dnf &> /dev/null; then
                    sudo dnf install -y SDL2 SDL2_mixer SDL2_ttf SDL2_image clang make
                else
                    sudo yum install -y SDL2 SDL2_mixer SDL2_ttf SDL2_image clang make
                fi
            else
                echo "Unsupported Linux distribution"
                exit 1
            fi
            ;;
        *)
            echo "Unsupported operating system: $OS"
            exit 1
            ;;
    esac
}


install_dependencies

if [ -d "/opt/lord_quixard" ]; then
    sudo rm -rf /opt/lord_quixard
fi

if grep -qEi "(Microsoft|WSL)" /proc/version &> /dev/null ; then
    echo "Detected WSL environment."
    export XDG_RUNTIME_DIR=/tmp/runtime-$(whoami)
    mkdir -p $XDG_RUNTIME_DIR
    chmod 0700 $XDG_RUNTIME_DIR
fi

# Downloading all file
colored_echo "32m--------|" "Downloading Lord Quixard |--------"
git clone https://github.com/emmanuel-aubertin/QuixoCPP.git lord-quixard

colored_echo "32m--------|" "Installing Lord Quixard |--------"

LORD_QUIXARD_DIR="lord-quixard"
DEST_DIR="/opt/lord_quixard"

echo "Copying static files to $DEST_DIR"
sudo mv "$LORD_QUIXARD_DIR/" "$DEST_DIR/"
rm -rf lord-quixard
echo "Copying static files to $DEST_DIR"
sudo mv "$LORD_QUIXARD_DIR/" "$DEST_DIR/"
rm -rf lord-quixard

if cd $DEST_DIR && git pull && make; then
    sudo mv $DEST_DIR/Quixo /usr/local/bin/Quixo
    sudo chmod +x /usr/local/bin/Quixo

    colored_echo "32m" "Installation complete."

    colored_echo "1;32m" "*************************************************"
    colored_echo "1;33m" "*        🎉 Now you can enjoy Quixo! 🎉         *"
    colored_echo "1;32m" "*************************************************"
    colored_echo "1;34m" "Just type 'Quixo' to start the game."
    colored_echo "1;32m" "Happy Gaming! 😊"
else
    colored_echo "1;31m" "Error during installation. Please check the errors above."
fi