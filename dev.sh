#!/bin/bash
cd /var/www/cppWebApp
port=8085

echo "🛑 Stopping any running instance..."
pkill -f "webapp --docroot" || true

echo "🔨 Building with CMake..."
# Create build directory if it doesn't exist
mkdir -p build
cd build

# Always clean the CMake cache when switching between systems
echo "🧹 Cleaning CMake cache..."
rm -f CMakeCache.txt

# Configure with CMake
cmake ..

# Build
make -j4

if [ ! -f "webapp" ]; then
    echo "❌ Build failed!"
    exit 1
fi

cd ..
chmod +x build/webapp

echo "🚀 Starting server..."
echo "📱 Access at: http://localhost:${port}"
echo "⏹️  Press Ctrl+C to stop"

build/webapp --docroot . --http-address 0.0.0.0 --http-port $port