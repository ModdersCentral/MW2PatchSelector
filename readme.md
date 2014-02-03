i saw links where deleted for this so i have decided to repost it. (this isn't my work)

=========

Made By: 
EmersonS35

Help From:

DarkHacker

EvilSperm


Installation
============
PSL1GHTv2: 'ppu.mk' is now called 'ppu_rules' and the files have been changed. so will not work

PSL1GHTv1: it should work OK  if you have DEADRSX





place these into your $HOME/.bashrc file


export PS3DEV=/usr/local/ps3dev
export PATH=$PS3DEV/bin:$PS3DEV/ppu/bin:$PS3DEV/spu/bin:$PATH


or


echo 'export PS3DEV=/usr/local/ps3dev' >> ~/.bashrc
echo 'export PSL1GHT=$PS3DEV/libpsl1ght' >> ~/.bashrc
echo 'export PATH="$PATH:$PS3DEV/bin:$PS3DEV/ppu/bin:$PS3DEV/spu/bin"' >> ~/.bashrc
. ~/.bashrc
