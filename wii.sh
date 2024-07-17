if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "Please run as root"
    exit
fi

rm -r ./Build

mkdir ./Build
mkdir ./Build/build
mkdir ./Build/source
mkdir ./Build/data

export PATH=/opt/devkitpro/tools/bin/:$PATH

git clone https://github.com/GRRLIB/GRRLIB.git

cd ./GRRLIB/GRRLIB

export DEVKITPPC=/opt/devkitpro/devkitPPC
export DEVKITPRO=/opt/devkitpro
sudo -E make clean all install

cd ../../

cp ./Makefiles/makefile.wii ./Build/Makefile

python3 -m pip install pywavefront
python3 sourceGen.py wii

cd ./Build

make
