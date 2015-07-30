#!/usr/bin/env sh

cd ..

# Install Root
wget http://www-ekp.physik.uni-karlsruhe.de/~sieber/root_5.34.07-1_amd64.deb || exit 1
sudo dpkg -i root_5.34.07-1_amd64.deb || exit 1
echo "/usr/local/lib" | sudo tee -a /etc/ld.so.conf
echo "/usr/local/lib/root" | sudo tee -a /etc/ld.so.conf
sudo ldconfig || exit 1

# Install Kappa
git clone -b development https://github.com/KappaAnalysis/Kappa.git || exit 1
make -C Kappa/DataFormats/test || exit 1
