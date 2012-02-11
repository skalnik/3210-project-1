#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/tty.h>
#include <linux/vmalloc.h>
#include <linux/syscalls.h>
#include <linux/sys.h>
#include <linux/signal.h>



#define MODULE_NAME "Leap Frog Psuedo Random Number Generator"
#define STACK 1024*64

static struct proc_dir_entry *proc_file;

struct thread_data{
  int seed,i,a,b,c;
};

/* Called when someone attempts to read a psuedo random number /proc/lfprng */
int read_proc_lfprng(char *buffer,
                     char **buffer_location,
                     off_t offset,
                     int buffer_length,
                     int *eof,
                     void* data) {
  printk("/proc/lfprng was accessed!\nProcess ID:%ld\n", (long)current->pid);
  return 0;
}
/*writes LFprn into /proc/lfprng*/
int write_proc_lfprng(float psn)
{
  /*stub*/
  printk("Out: %f", psn);
  return 0;
}

 /*worker thread function*/
void calculate_lfprng(void* thread_seed)
{
  struct thread_data *my_seed;
  my_seed = (struct thread_data *) thread_seed;
  printk("this is a thread %i",my_seed->a);
}

/*spawns worker threads*/
void create_lfprng(int seed, pid_t pid)
{
  /*t = pid -> threadCount*/
  int t = 1;
  int seed_array[t];
  struct task_struct *ts;

  int i = 0;
   /*not real values*/
  int a = 2; 
  int b = 0;
  int c = 8;
  struct thread_data array[t]; 
  struct thread_data* input;  
  for (i= 0; i < t; i++)
  {
    seed_array[i] = (seed * (( a^i ) % c));
  }

  for (i = 0;i < t; i++)
  {  
    int num = seed_array[i];
    array[i].seed = num;
    array[i].i = i;
    array[i].a = a;
    array[i].b = b;
    array[i].c = c;
    input = &array[i];
    ts = kthread_run(calculate_lfprng, (void*) input, "caclfprn"); 
 
    if (pid == -1)
    {
      printk("kthread_run");
    } 
  }
    
  // Wait for the child thread to exit
    pid = sys_waitpid(pid, 0, 0);

    if (pid == -1) {
      printk("waitpid");
    } 
}




int init_module(void)
{
  proc_file = create_proc_entry("lfprng", 0755, NULL);

  proc_file->owner = THIS_MODULE;
  proc_file->read_proc = read_proc_lfprng;

  return 0;
}
void cleanup_module(void) 
{
  remove_proc_entry("lfprng", NULL);
}


		
