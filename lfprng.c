#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define MODULE_NAME "Leap Frog Psuedo Random Number Generator"

int init_module(void)
{
  struct proc_dir_entry* proc_file;
  proc_file = create_proc_entry("lfprng", 0755, NULL);
  return 0;
}
void cleanup_module()
{
  remove_proc_entry("lfprng", NULL);
}

