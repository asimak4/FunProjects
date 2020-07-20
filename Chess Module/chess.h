#pragma once
#include <linux/kernel.h>
#include <linux/fs.h>

#define MODULE_NAME "chess"

#define _MOD421_PRINTK(once, level, fmt, ...)do {printk##once(KERN_##level "[" MODULE_NAME "]" fmt, ##__VA_ARGS__);} while(0)

#define LOG_INFO(format, ...) _MOD421_PRINTK(, INFO, format, ##__VA_ARGS__)

#define LOG_WARN(format, ...) _MOD421_PRINTK(, WARN, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) _MOD421_PRINTK(, ERR, format, ##__VA_ARGS__)


char* changePiece(char color,char piece);
int isCheck(char color, char *board[8][8]);
int compChar(char a, char b);
int validMove(char color, char piece, int movingToX,int movingToY, int startingX, int startingY,char *board[8][8]);
int convertLetterToNum(char letter);
int chess_open(struct inode *pinode, struct file *pfile);
ssize_t chess_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t chess_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);
int chess_release(struct inode *pinode, struct file *pfile);

