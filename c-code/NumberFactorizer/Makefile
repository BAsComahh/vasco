# Makefile 示例

# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -g

# 目标可执行文件
TARGET = my_program

# 源文件和对象文件
SRCS = main.c PrimeFactorizer.c
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 目标可执行文件的生成规则
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 源文件到对象文件的转换规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件
clean:
	rm -f $(OBJS) $(TARGET)

# 运行程序的规则
run: $(TARGET)
	./$(TARGET)
