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
#include <asm/uaccess.h>

#define MODULE_NAME "Leap Frog Psuedo Random Number Generator"
#define STACK 1024*64
#define SEED_BUFFER_MAX 512

extern struct task_struct *find_task_by_pid(pid_t nr);
static struct proc_dir_entry *proc_file;
static unsigned int thread_count = -1;
static int rngs[5] = {1, 2, 3, 4, 5};
static int *rngs_ptr = rngs;
static unsigned int seed_buffer_size = 0;
static char seed_buffer[SEED_BUFFER_MAX];
int user_seed;

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
  int ret;

  if(thread_count == -1)
  {
    struct task_struct *task;
    atomic_t signal_count;

    pid_t current_pid = current->pid;
    printk("/proc/lfprng was accessed!\nProcess ID:%ld\n", (long)current_pid);

    task = find_task_by_pid(current_pid);
    signal_count = task->signal->count;
    thread_count = atomic_read(&signal_count);
    printk("Process has %i threads\n", thread_count);

    /* Generate Numbers */
  }

  if(offset > 0)
  {
    *eof = 1;
    ret = 0;
  }
  else
  {
    ret = sprintf(buffer, "%d", *rngs_ptr);
    rngs_ptr++;
  }

  return ret;
}


/* Called when someone attempts to write a seed to /proc/lfprng */
int write_proc_lfprng(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
  char **endp;
  seed_buffer_size = count;
  if(seed_buffer_size > SEED_BUFFER_MAX)
  {
    seed_buffer_size = SEED_BUFFER_MAX;
  }

  copy_from_user(seed_buffer, buffer, seed_buffer_size);

  user_seed = simple_strtol(seed_buffer, endp, 10);
  printk("Seed: %i\n", user_seed);

  return seed_buffer_size;
}

 /*worker thread function*/
void calculate_lfprng(void* thread_seed)
{
  struct thread_data *my_seed;
  my_seed = (struct thread_data *) thread_seed;

  while(1)
  {
  
    if(kthread_should_stop())
    {
      break;
    }
    else
    {
      printk("this is a thread %i",my_seed->a);
    }
 
  }
}

/*spawns worker threads*/
void create_lfprng(int seed, pid_t pid)
{
  /*t = pid -> threadCount*/
  int t = 1;
  int output_size = 256;
  int seed_array[t];
  struct task_struct *ts;
  int lfprn_array[output_size];
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
  for(i=0;i<output_size;i++)
  {
    lfprn_array[i] = array[i%t].seed;
  }
  kthread_stop(ts);
  
}




int init_module(void)
{
  proc_file = create_proc_entry("lfprng", 0766, NULL);

  proc_file->owner = THIS_MODULE;
  proc_file->read_proc = read_proc_lfprng;
  proc_file->write_proc = write_proc_lfprng;

  return 0;
}
void cleanup_module(void) 
{
  remove_proc_entry("lfprng", NULL);
}


		
