######################################
 Odroid xu3 上で kernel を build する
######################################

**********************************
 Odroid に Ubuntu を install する
**********************************

micro SD カードにイメージを作成
===============================
https://wiki.odroid.com/odroid-xu4/os_images/linux/ubuntu/ubuntu

から ubuntu-[version]-mate-odroid-xu3-XXX.img を入手する．
この image を適当な方法で micro SD カードに焼くとインストール完了．

設定ファイルとファイル構造
--------------------------
boot.ini などについて追記します．

root のパーティションの拡張
===========================
カーネルを build するためには，上記の image の root のパーティション
は容量が小さいため，resize してやる必要がある．

https://forum.odroid.com/viewtopic.php?f=52&t=2948

の方法が紹介されていたが，私は fdisk は別の端末の Ubuntu で micro SD 上の
パーティションをリサイズする方法をとった．

fdisk で XXXXp2 を，空き容量をすべて使用するようにリサイズすれば良い．

その後，この micro SD で odroid を起動し，
`resize2fs /dev/mmcblk0p2` を実行する．

以上でパーティションが拡張される．

*****************
 kernel の build
*****************

ダウンロード
============
kernel.org のカーネルは設定ファイルなどの都合からか build できない．
そのため，

https://github.com/hardkernel/linux

から branch odroidxu4-4.14.y などの kernel を clone してくる．

Build と Install
================
https://wiki.odroid.com/odroid-xu4/software/building_kernel の
4.14.y に従って行う．

```
$ make odroidxu4_defconfig
$ make -j8
$ sudo make modules_install
$ sudo cp -f arch/arm/boot/zImage /media/boot
$ sudo cp -f arch/arm/boot/dts/exynos5422-odroidxu3.dtb /media/boot
$ sudo cp -f arch/arm/boot/dts/exynos5422-odroidxu4.dtb /media/boot
$ sudo cp -f arch/arm/boot/dts/exynos5422-odroidxu3-lite.dtb /media/boot
$ sync
```

```
$ sudo cp .config /boot/config-`make kernelrelease`
$ sudo update-initramfs -c -k `make kernelrelease`
$ sudo mkimage -A arm -O linux -T ramdisk -C none -a 0 -e 0 -n uInitrd -d /boot/initrd.img-`make kernelrelease` /boot/uInitrd-`make kernelrelease`
$ sudo cp /boot/uInitrd-`make kernelrelease` /media/boot/uInitrd
$ sudo sync
$ sudo reboot
```
