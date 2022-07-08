Turn into super user
```
sudo su
```
## Prerequisite
```
apt update
apt install wget
apt install wget vim ccache build-essential
```
## Download and Extract WebP
Download
```
wget https://storage.googleapis.com/downloads.webmproject.org/releases/webp/libwebp-1.2.2.tar.gz
```
Extract
```
tar xzf libwebp-1.2.2.tar.gz
```
Get into the directory
```
cd libwebp-1.2.2
```
## Configure
```
./configure
```
Make Ccache as default
```
export PATH="/usr/lib/ccache:$PATH"
```
> use this command before every compilation
