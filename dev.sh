#!/bin/bash
cd /var/www/cppWebApp
port=8081

echo "🛑 Stopping any running instance..."
pkill -f "webapp --docroot" || true

echo "🔨 Building with CMake..."
# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake (only if needed)
if [ ! -f "Makefile" ]; then
    cmake ..
fi

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