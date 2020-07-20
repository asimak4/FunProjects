#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>

#include "chess.h"
#define DRIVER_AUTHOR "Alex Simak"
#define DRIVER_DESC "Main Tic-Tac-Toe"

static dev_t device_number;
static struct cdev the_cdev;
static struct class* the_class = NULL;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = chess_read,
    .write = chess_write,
    .open = chess_open,
    .release = chess_release
};

static char *perm(struct device *dev, umode_t *mode){
    if(!mode){
        return NULL;
    }
    *mode = 0666;
    return NULL;
}

static int __init chess_start(void){
    LOG_INFO("Module Loaded.\n");

    // Show under "cat /proc/devices"
    if(alloc_chrdev_region(&device_number, 0, 1, MODULE_NAME"_proc") < 0){
        // error
        goto r_return;
    }

    // ls /sys/class
    the_class = class_create(THIS_MODULE, MODULE_NAME"_sys");
    the_class->devnode = perm;
    if(the_class == NULL){
        goto r_class;
    }

    if(device_create(the_class, NULL, device_number, NULL, MODULE_NAME) == NULL){
        goto r_device;
    }

    cdev_init(&the_cdev, &fops);
    if(cdev_add(&the_cdev,device_number, 1) < 0){
        goto r_cdev;
    }

    return 0;
r_cdev:
    device_destroy(the_class,device_number);
    cdev_del(&the_cdev);

r_device:
    class_destroy(the_class);

r_class:
    unregister_chrdev_region(device_number,1);

r_return:
    return -1;
};


static void __exit chess_exit(void){
    LOG_INFO("Module Unloaded.\n");

    device_destroy(the_class, device_number);
    cdev_del(&the_cdev);
    class_destroy(the_class);
    unregister_chrdev_region(device_number,1);
    
};

module_init(chess_start);
module_exit(chess_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("Chess");
