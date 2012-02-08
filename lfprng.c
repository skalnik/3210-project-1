#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/tty.h>

#define MODULE_NAME "Leap Frog Psuedo Random Number Generator"

static struct proc_dir_entry *proc_file;

/* Called when someone attempts to read a psuedo random number /proc/lfprng */
int read_proc_lfprng(char *buffer,
                     char **buffer_location,
                     off_t offset,
                     int buffer_length,
                     int *eof,
                     void* data) {
  printk("PID is:%ld", (long)current->pid);
  return 0;
}

int init_module(void)
{
  proc_file = create_proc_entry("lfprng", 0755, NULL);

  proc_file->owner = THIS_MODULE;
  proc_file->read_proc = read_proc_lfprng;

  return 0;
}
void cleanup_module()
{
  remove_proc_entry("lfprng", NULL);
}

