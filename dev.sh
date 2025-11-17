#!/bin/bash
cd /var/www/webapp

echo "🛑 Stopping any running instance..."
pkill -f "webapp --docroot" || true

echo "🔨 Rebuilding..."
g++ -std=c++17 -pthread -o webapp main.cpp MemoryMonitor.cpp \
    -I/usr/local/include \
    -L/usr/local/lib \
    -lwthttp -lwt -lboost_system

if [ ! -f "webapp" ]; then
    echo "❌ Build failed!"
    exit 1
fi

chmod +x webapp

echo "🚀 Starting server..."
echo "📱 Access at: http://localhost:8081"
echo "⏹️  Press Ctrl+C to stop"

./webapp --docroot . --http-address 0.0.0.0 --http-port 8080