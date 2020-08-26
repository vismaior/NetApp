rm -rf build
mkdir build
cd build
cmake ..
make
./NetApp -c -p 555 -i 127.0.0.1 -t task
