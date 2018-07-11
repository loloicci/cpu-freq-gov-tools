##########################
 自作 governor の作成方法
##########################
この sample-governor では governor の linux への登録方法を記述します．

******
 範囲
******
このドキュメントでは kernel module としての governor の作成方法のみに
重点を当てて記述します．
そのため，governor によって異なる，Dynamic な frequency
変更の方法の解説などは．
そちらについての詳細は https://github.com/loloiccl/linux に当てたコメントを
参照してください．
ondemand, conservative 系の Dynamic govornor については ondemand のコメントを，
schedutil については schedutil のコメントを参照してください．

**********************************
 governor の kernel module の作成
**********************************
goveror を kernel module として作成する場合は
一つの governor ごとに一つの kernel module を作成することになります．

また，ここでは kernel の source に自作した module の source を追加し，
kernel で ``make``, ``make modules_install`` を行う方法で kernel module を
install します．
それ以外の方法で module を作成する場合は適宜読み替えなどを行ってください．

*****************
 sample_governor
*****************
独自の governor を作成するサンプルです．
ここでは powersave と同じものを mypowersave として作成する手順を解説します．

build 方法
==========
Makefile 及び cpufreq_powersave2.c を kernel のソース中の driver/cpufreq 下
にコピーしてください．
その後 kernel 中で ``make``, ``make modules_install`` すると
kernel module として cpufreq_powersave2 がインストールされます．
reboot や modprobe でこれを読み込むと，governor mypowersave が使用できるように
なります．

Makefile
========
Makefile では，module を追加したディレクトリの Makefile に
``obj-m += <追加したモジュール>.o`` を追加します．

cpufreq_powersave2.c
====================
governor である powersave と同じものを mypowersave という名前に変更した
governor です．
以下ではコード内の governor の作成に特有の部分の解説を行います．

struct cpufreq_governor
-----------------------
governor の本体となります．
``cpufreq.h`` で定義されています．
module 内ではこの構造体を定義し，それを governor として登録することで
governor の追加を行います．

今回は powersave のものから ``.name`` のみを mypowersave に変更したもの
としています．
**この名前に数字を使用すると何故か governor として指定できません．**

static int __init XXX
---------------------
module_init にわたす module 読み込み時の動作を定義する関数です．
この中で ``cpufreq_registar_governor`` によって governor として登録する
構造体を指定します．

static void __exit XXX
----------------------
module_init にわたす module のアンロード時動作を定義する関数です．
この中で ``cpufreq_unregistar_governor`` によって削除する govornor の
構造体を指定します．

MODULE_LICENSE
--------------
コードの依存関係の関係上，GPL を指定する必要があります．

module_init
-----------
module 読み込み時の動作です．
``static int __init`` として定義したものを指定します．

module_exit
-----------
module アンロード時の動作です．
``static void __exit`` として定義したものを指定します．
