#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/tty.h>

#define MODULE_NAME "Leap Frog Psuedo Random Number Generator"
#define STACK 1024*64

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
/*writes LFprn into /proc/lfprng*/
int write_proc_lfprng(float psn)
{
  /*stub*/
  printk("Out: %f", psn);
  return 0;
}

/*spawns worker threads*/
int create_lfprng(int seed, pid_t pid)
{
  /*t = pid -> threadCount*/
  int t = 1
  int seed_array[t]
  void * stack = malloc(STACK)

  for (i = 0, i < t, i++)
  {
    seed_array[i] = seed
  }

  if (stack == 0) {
    perror("malloc: could not allocate stack");
    exit(1);
  }

  for(i = 0, i < t, i++)
  {  
    pid = clone(&threadFunction,
                 (char*) stack + STACK,
                 SIGCHLD | CLONE_FS | CLONE_FILES |\
		 CLONE_SIGHAND | CLONE_VM,
                 (void*)fd); 
 
    if (pid == -1) {
      perror("clone");
      exit(2);
    } 
 
  // Wait for the child thread to exit
  pid = waitpid(pid, 0, 0);
  if (pid == -1) {
    perror("waitpid");
    exit(3);
  } 

  free(stack)

}

/*worker thread function*/
void calculate_lfprng(int seed, int thread_count)
{

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

