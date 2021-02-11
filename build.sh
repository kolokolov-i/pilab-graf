g++ -Wall src/*.cpp src/ipf/*.cpp src/gui/*.cpp src/lab/*.cpp -o main -mwindows `pkg-config gtkmm-3.0 --cflags --libs`
./main.exe