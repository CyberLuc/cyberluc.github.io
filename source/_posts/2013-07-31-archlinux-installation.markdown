---
layout: post
title: "Archlinux安装小记"
date: 2013-07-31 10:07
comments: true
keywords: Archlinux
categories: [Archlinux]
tags: [Archlinux]
---

不知不觉已经使用了Archlinux好几个月的时间了，期间也记录了一些安装使用中遇到的问题，最近又把arch重新装了一遍，这里把整理后的安装记录发上来。

Arch的安装过程是全命令行的，连Debian那样的字符模拟图形界面也不会提供，不过安装过程还是相当简单的。

<!-- more -->

我是从Debian下转到Archlinux，手头正好有一个不用的U盘，于是便按照ArchWiki的说明将U盘写入archlinux的iso镜像。用`syslinux`的那个方法我试了，但是记得没用，以后哪天再去研究一下吧。

`lsblk`找到u盘的设备名，比如我的是`/dev/sdb`

注意这个方法是会格式化u盘数据的！

{% codeblock 写入USB %}
# dd bs=4M if=/home/twtwtw/Downloads/archlinux-2013.07.01-dual.iso of=/dev/sdb
{% endcodeblock %}

然后重启开始安装Archlinux。

### 1.分区
使用cfdisk可以很方便的给磁盘分区，我给arch划出了大约200个G，分别划分了/boot 200M，/ 90G，/home 140G，swap 8G。

### 2.格式化
对磁盘进行格式化，可以使用如下的命令，将其中的x替换为对应的磁盘符号
{% codeblock 格式化 %}
# mkfs.ext4 /dev/sdx                 //格式化为ext4
# mkswap /dev/sdx && swapon /dev/sdx //格式化swap并挂载
{% endcodeblock %}

### 3.挂载
接下来开始挂载分区，此时挂载分区一是为了正常安装系统，二是为了生成fstab，这个文件记录了磁盘挂载的信息，开机后按照文件内容会自动挂载。这里可以把Windos系统的NTFS分区也给挂载上，不过记得后面要装`ntfs-3g`，否则开机会报错。
{% codeblock 挂载 %}
# mount /dev/sdx /mnt <!-- 测试 -->
# mkdir /mnt/{boot,var,home}
# mount /dev/sd{9,10} /mnt/{boot,home}
{% endcodeblock %}

### 4.调整网络，修改Pacman源
{% codeblock 调整网络，修改Pacman源 %}
// dhcpcd、wifi-menu、ifconfig、iwconfig均可使用，我直接连接路由，arch已经自动dhcp
# vi /etc/pacman.d/mirrorlist //找到其中的China标记的项，去掉注释
{% endcodeblock %}
这些是China的源加在网上找的一些据说不错的源:
{% codeblock /etc/pacman.d/mirrorlist %}
Server = http://mirrors.163.com/archlinux/$repo/os/$arch
Server = http://mirror.hust.edu.cn/archlinux/$repo/os/$arch
Server = http://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch
Server = http://mirrors.stuhome.net/archlinux/$repo/os/$arch
Server = http://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch
Server = http://mirrors.neusoft.edu.cn/archlinux/$repo/os/$arch
Server = http://lug.mtu.edu/archlinux/$repo/os/$arch
Server = http://mirror.umd.edu/archlinux/$repo/os/$arch
Server = http://mirrors.liquidweb.com/archlinux/$repo/os/$arch
Server = http://cosmos.cites.illinois.edu/pub/archlinux/$repo/os/$arch
{% endcodeblock %}
### 5.安装系统基本组件和grub-bios
{% codeblock 安装系统基本组件 %}
# pacstrap /mnt base base-devel grub-bios
{% endcodeblock %}

### 6.生成fstab
`-p`这里表示生成以设备名为标识的fstab，比如/dev/sda等
`-U`标记可以生成UUID为标识的fstab
{% codeblock 生成fstab lang:bash %}
# genfstab -p /mnt >> /mnt/etc/fstab
{% endcodeblock %}
然后就等待慢慢下载安装吧。

### 7.切换到安装好的系统
{% codeblock 切换到安装好的系统 %}
# arch-chroot /mnt
{% endcodeblock %}

### 8.设置主机名
主机名写在文件`/etc/hostname`里边，写入就好。
{% codeblock 设置主机名 %}
# echo Cryo-Nyx > /etc/hostname
{% endcodeblock %}

### 9.修改locale
我想要系统仍旧以英文显示各种提示，所以这里仅仅修改`LC_CTYPE`为`zh_CN.UTF-8`。
{% codeblock 修改locale %}
# vi /etc/locale.conf    //添加LANG=en_US.UTF-8，LC_CTYPE=zh_CN.UTF-8
# vi /etc/locale.gen     //取消需要的locale前注释
# locale-gen
{% endcodeblock %}

### 10.设置时区与硬件时钟
这一步设置本地时区
{% codeblock 设置本地时区 %}
# ln -s /usr/share/zoneinfo/Asia/Chongqing /etc/localtime
# hwclock --systohc --utc
{% endcodeblock %}

### 11.设置键盘布局
这一步可以在tty下进行键盘布局的设置，比如交换CapsLock和Escape，方便VIM操作
{% codeblock 设置TTY下键盘布局 %}
# cd /usr/share/kbd/keymaps/i386/qwerty/
# cp us.map.gz twtwtw.map.gz
# gunzip twtwwt.map.gz
# vi twtwtw.map.gz
//找到CapsLock和Escape的键位，互换其值
# vi /etc/vconsole.conf  //添加`KEYMAP=twtwtw`
{% endcodeblock %}

### 12.创建引导linux内核的初始环境
`-p`是preset的意思，也就是以预设的linux配置文件生成。

如果是intel集显的话，可以在`/etc/mkinitcpio.conf`的`MODULE`里边添加`i915`打开KMS。

详情参照这里[ArchWiki: Intel Grapchis](https://wiki.archlinux.org/index.php/Intel_Graphics)。
{% codeblock 创建引导linux内核的初始环境 %}
# vi /etc/mkinitcpio.conf //在MODULES里添加i915
# mkinitcpio -p linux
{% endcodeblock %}

### 13.安装grub到/dev/sda上并生成初始配置
{% codeblock 安装grub %}
# grub-install /dev/sda  //将grub安装到sda上
# cp /usr/share/locale/en\@quot\LC_MESSAGES /boot/grub/locale/en.mo //不然开机加载grub时会提示en.mo not found
# pacman -S os-prober    //如果还装有Win系统的话
# grub-mkconfig -o /boot/grub/grub.cfg
{% endcodeblock %}

### 14.添加用户
{% codeblock 添加用户 %}
#useradd -d /home/twtwtw -m twtwtw
#usermod -G audio,video,wheel,users,games,optical,storage,lp twtwtw //将用户添加到xxxx各个组
{% endcodeblock %}

### 14.修改初始密码
{% codeblock 修改初始密码 %}
# passwd //修改root密码
# passwd twtwtw //修改用户密码
{% endcodeblock %}

## 15.安装基本系统软件
安装系统一些基本的软件，这些base包并没有提供。

Archlinux使用ip和netctl工具来进行网络管理，不过以前用惯了ifconfig，这里也一起装上吧。

`net-tools`提供了`ifconfig`工具
`wireless_tools`提供了`iwconfig`和`iwlist`
{% codeblock 安装基本系统软件 %}
# pacman -S sudo gksu vim net-tools wireless_tools  dialog wpa_supplicant dhcpcd ntfs-3
{% endcodeblock %}
然后visudo，把自己的用户加上管理员权限

### 15.安装桌面环境
我使用的是`Awesome`这款wm，并没有使用dm。
{% codeblock 安装桌面环境 %}
# pacman -S xorg-{server,server-utils,utils,xinit} xterm xf86-video-intel mesa alsa-utils feh awesome vicious xcompmgr
{% endcodeblock %}

### 16.安装完成
安装完成，重启进入系统。
{% codeblock 安装完成 %}
# exit
# umount -a
# reboot
{% endcodeblock %}

### 17.xinitrc
修改`.xinitrc`，添加`exec awesome`
```bash 我的.xinitrc
#!/bin/zsh
numlockx
xbacklight -set 0
#setxkbmap -option ctrl:nocaps
exec awesome
```

### 关于字体
有几个字体是必下，比如community里的`wqy-microhei`，`wqy-zenhei`，还有aur里的`ttf-dejavusans-yuanti`，以及`ttf-droid-sans`,`ttf-microsoft-yahei`也可以装上，都是很不错的字体。
{% codeblock 字体 %}
# pacman -S xorg-font-{util,utils,100dpi,75dpi,alias}
{% endcodeblock %}

### 常用软件
```text 常用软件
firefox //不解释
rdesktop //远程桌面
banshee //听歌还不错，不过ncmpcpp作为字符下的也还可以
mplayer
smplayer
chmsee
foxitreader //比evince好用
gthumb //不错的看图软件
bc //命令行下的计算器
emacs
xbacklight //可以设置笔记本的亮度，对于无法保存亮度的笔记本来说很方便
numlockx //自动打开小键盘
ibus,ibus-sunpinyin //挺不错的，个人觉得比ibus好用
```

已经安装了好久了，当时也没记录多详细，就这些内容了。

系统配置上的问题，以后想起来了再发吧。
