/*
 *  hello-5.c - Demonstrates command line argument passing to a module.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Li Yilong");

static short int my_short = 1;
static int my_int = 420;
static long int my_long = 9999;
static char *my_string = "blah";
static int my_int_array[2] = { -1, -1 };
static int arr_argc;

/*
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits,
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */

module_param(my_short, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(my_short, "A short integer");
module_param(my_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(my_int, "An integer");
module_param(my_long, long, S_IRUSR);
MODULE_PARM_DESC(my_long, "A long integer");
module_param(my_string, charp, 0000);
MODULE_PARM_DESC(my_string, "A character string");

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array(my_int_array, int, &arr_argc, 0000);
MODULE_PARM_DESC(my_int_array, "An array of integers");

static int __init hello_5_init(void)
{
	int i;

	pr_info("Hello, world 5\n=============\n");
	pr_info("my_short is a short integer: %hd\n", my_short);
	pr_info("my_int is an integer: %d\n", my_int);
	pr_info("my_long is a long integer: %ld\n", my_long);
	pr_info("my_string is a string: %s\n", my_string);

	for (i = 0; i < sizeof(my_int_array) / sizeof(int); i++)
		pr_info("my_int_array[%d] = %d\n", i, my_int_array[i]);
	pr_info("got %d arguments for my_intArray.\n", arr_argc);
	return 0;
}

static void __exit hello_5_exit(void)
{
	pr_info("Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);

