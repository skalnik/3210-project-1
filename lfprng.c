#define __KERNEL__
#define MODULE

#include <linux/module.h>
#include <linux/proc_fs.h>

int init_module()
{
  proc_file = create_proc_entry("lfprng", "666", proc_root);
  return 0;
}
void cleanup_module()
{
  proc_file = remove_proc_entry("lfprng", proc_root);
}
