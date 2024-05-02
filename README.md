# Dependencies
## Eigen3
```bash
sudo apt -y install libeigen3-dev
```
## fmt 
```bash
git clone https://github.com/fmtlib/fmt.git fmt
mkdir -p ./fmt/build
cd ./fmt/build
cmake -DBUILD_SHARED_LIBS=TRUE ../
make -j4
sudo make install
```

# Structure

# Usage