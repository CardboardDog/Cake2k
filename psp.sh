#!/bin/bash
source logger.sh

Title

Info

Log "Target - PSP"
Log "\$PSPDEV - $PSPDEV"

Step Preparation

Log "Checking for PSPSDK:"
if [ -d ./SDKS/pspdev ]
then
    Healthy "PSPSDK found";
else
    Error "PSPSDK not found."
    exit 1;
fi
Log "Setting \$PSPDEV:"
export PSPDEV="$PWD/SDKS/pspdev/"
if [ "$PSPDEV" = "$PWD/SDKS/pspdev/" ]
then
    Healthy "\$PSPDEV set"
else
    Error "Could not set $PSPDEV";
    exit 1;
fi
if [[ ":$PATH:" == *"$PSPDEV/bin:"* ]]
then
    Warn "Set \$PATH skipped"
else
    Log "Setting \$PATH";
    export PATH="$PSPDEV/bin:$PATH"
    Healthy "\$PATH was set"
fi
if [ -d ./Build/ ]
then
    Warn "Create ./Build/ skipped";
    Log "Cleaning ./Build/";
    rm -r ./Build/*;
else
    mkdir "./Build/";
    Healthy "Created ./Build/";
fi
{
    cp "./Makefiles/makefile.psp" "./Build/Makefile"
} || {
    Error "Could not copy PSP makefile";
    exit 1;
}

Step "Generating Source"

{
    python3 sourceGen.py
} || {
    exit 1
}

Step "Generating assets"

if [ -d ./SDKS/image ]
then
    Healthy "Image Magick SDK found"
    Log "Changing magick to executable"
    chmod +x ./SDKS/image/magick
    Healthy "Magick mode changed to executable"
else
    exit 1
fi
{
    python3 assetGen.py psp
} || {
    exit 1
}

echo "$PATH" > .pathsave

Step Compiling

cd ./Build/
make