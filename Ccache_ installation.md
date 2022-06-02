## Turn into super user
```
sudo su
```
## Get Update to your system
```
apt update
```
## To get able to download
```
apt install wget
```
## Install neccessay tools (vim, ccache, build-essential(gcc,c++))
```
apt install wget vim ccache build-essential
```
## Download WebP
```
wget https://storage.googleapis.com/downloads.webmproject.org/releases/webp/libwebp-1.2.2.tar.gz
```
## Extract the downloaded file
```
tar xzf libwebp-1.2.2.tar.gz
```
## Get into the directory
```
cd libwebp-1.2.2
```
## Configure
```
./configure
```
## Make Ccache as default
```
export PATH="/usr/lib/ccache:$PATH"
```

