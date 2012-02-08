3210 Project 1
==============

Leap Frog random number generator kernel module!

Install Module
--------------

On factor-3210:

    make
    scp lfprng.ko factor007:~

On factor007

    sudo su
    insmod lfprng.ko

Remove Module
-------------

    rmmod lfprng
