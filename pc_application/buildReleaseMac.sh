make clean
make -B BUILD=release ARCH=64

mkdir -p switas_mac.app/Contents/MacOS
rm switas_mac.app/Contents/MacOS/switas
cp bin/switas switas_mac.app/Contents/MacOS
strip -s switas_mac.app/Contents/MacOS/switas

cp switas_settings.json switas_mac.app/Contents
cp switas_recent.json switas_mac.app/Contents

rm -rf switas_mac.app/Contents/share
mkdir -p switas_mac.app/Contents/share
find share -name '*.png' -o -name '*.jpg' | xargs /usr/local/opt/coreutils/libexec/gnubin/cp --parents -t switas_mac.app/Contents

# Install dylibbundler for this
dylibbundler -od -b -x switas_mac.app/Contents/MacOS/switas -d switas_mac.app/Contents/libs/

rm switas-mac-64bit.zip
zip -r switas-mac-64bit.app.zip switas_mac.app