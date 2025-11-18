#!/bin/bash
cd /var/www/webapp
port=8082
echo "🛑 Stopping any running instance..."
pkill -f "webapp --docroot" || true

echo "🔨 Rebuilding..."
g++ -std=c++17 -pthread -o webapp main.cpp \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lwthttp -lwt -lboost_system

if [ ! -f "webapp" ]; then
    echo "❌ Build failed!"
    exit 1
fi
chmod +x webapp

echo "🚀 Starting server..."
echo "📱 Access at: http://localhost:8{$port}"
echo "⏹️  Press Ctrl+C to stop"

./webapp --docroot . --http-address 0.0.0.0 --http-port $port