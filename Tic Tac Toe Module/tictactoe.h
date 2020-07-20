#pragma once
#include <linux/kernel.h>
#include <linux/fs.h>

#define MODULE_NAME "tictactoe"

#define _MOD421_PRINTK(once, level, fmt, ...)do {printk##once(KERN_##level "[" MODULE_NAME "]" fmt, ##__VA_ARGS__);} while(0)

#define LOG_INFO(format, ...) _MOD421_PRINTK(, INFO, format, ##__VA_ARGS__)

#define LOG_WARN(format, ...) _MOD421_PRINTK(, WARN, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) _MOD421_PRINTK(, ERR, format, ##__VA_ARGS__)


int checkWinStates(char playerLetter);
int pieceInBoard(char letter, char x, char y);
int tictactoe_open(struct inode *pinode, struct file *pfile);
ssize_t tictactoe_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t tictactoe_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);
int tictactoe_release(struct inode *pinode, struct file *pfile);

