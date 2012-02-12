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

Misc
----

In `read_proc_lfprng` (the callback for when a user reads), the if block gets
executed as long as thread_count is not set (-1), and that's where the number
generation should go, since its only executed once. There's no check currently
if there are not enough numbers, but that should be quite easy to check for.

In `write_proc_lfprng` the user input is converted to an integer and
`user_seed` is set to that.
