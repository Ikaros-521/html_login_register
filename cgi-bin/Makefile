# 添加所有的.c文件
SRCS = $(wildcard ./*.c) 

# 指定 头文件目录
#INCLUDES = -I ./inc

# 指定库目录 
LIB = -lpthread -lsqlite3

# 指定库路径
LIB_PATH = /usr/lib64/mysql/

TOOL = cgic.c

# 指定编译器
CC = gcc
# 指定编译选项（可选）
CFLAGS = -g -Wall -O2


# 
INPUT1 = login.o
INPUT2 = register.o
INPUT3 = login2.o
INPUT4 = register2.o

INPUTLIST=$(INPUT1) $(INPUT2) $(INPUT3) $(INPUT4)

# 编译目标列表
OUTPUT1 = login.cgi
OUTPUT2 = register.cgi
OUTPUT3 = login2.cgi
OUTPUT4 = register2.cgi

# ...
OUTPUTLIST=$(OUTPUT1) $(OUTPUT2) $(OUTPUT3) $(OUTPUT4)

# 将 所有的目标作为一个列表，便于make clean
all : $(OUTPUTLIST)

# 编译目标1
$(OUTPUT1) : $(INPUT1)
	@$(CC) $^ $(TOOL) -o $@ $(LIB)
$(OUTPUT2) : $(INPUT2)
	@$(CC) $^ $(TOOL) -o $@ $(LIB)
$(OUTPUT3) : $(INPUT3)
	@$(CC) $^ $(TOOL) -o $@ $(LIB)
$(OUTPUT4) : $(INPUT4)
	@$(CC) $^ $(TOOL) -o $@ $(LIB)

%.o : %.c
	@$(CC) -c $(CFLAGS) $<

clean:
	@rm $(OUTPUTLIST)

rm:
	@rm $(INPUTLIST)
