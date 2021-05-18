// 操作系统：CentOS7
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sqlite3.h>

#include "cgic.h"

int cgiMain(void)
{
	// 使用MIME头信息″Content-type: text/html\n\n″来输出HTML源代码给Web服务器。
	// 请注意任何MIME头信息后必须有一个空行。一旦发送这个MIME头信息给Web服务器后,Web浏览器将认为随后的文本输出为HTML源代码
	printf("Content-type: text/html\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	char username[21] = {};
	char password[40] = {};
    char password2[40] = {};
	//回显信息到HTML网页cgiHeaderContentType("text/html");

	if (cgiFormString("username", username, sizeof(username)) != cgiFormSuccess)
	{
		fprintf(stderr, "cgiFormString function username failed");
		//exit(-1);
	}
	// password gateway server_ip dns subnet_mask dhcp error
	if (cgiFormString("password", password, sizeof(password)) != cgiFormSuccess)
	{
		fprintf(stderr, "cgiFormString function password failed");
		//exit(-1);
	}
    if (cgiFormString("password2", password2, sizeof(password2)) != cgiFormSuccess)
	{
		fprintf(stderr, "cgiFormString function password2 failed");
		//exit(-1);
	}
	
	printf("用户名:%s\n\n", username);
	printf("密码:%s\n\n", password);
    printf("确认密码:%s\n\n", password2);

	if(0 != strncmp(password, password2, 40))
	{
		printf("<script>alert(\"密码与确认密码不一致，请重新输入！\")</script>\n\n");
		return -1;
	}

	// 定义sqlite3数据库连接对象db
	sqlite3 *db = NULL;
	int result = 0;
	// 用于存储SQL语句执行后返回的错误信息
	char *errmsg = NULL;
	// 定义char型二维数组,用于存放select语句执行后的结果
	char **dbResult = NULL;
	// 用于存储查询到数据的行列数
	int nRow = 0, nColumn = 0;
	int i = 0;

	// 打开数据库连接对象
	result = sqlite3_open("/var/www/cgi-bin/test.db", &db);
	if (result != SQLITE_OK)
	{
		printf("<script>alert(\"数据库打开失败\");</script>");
		return -1;
	}

	// 数据库操作代码
	// 开始查询，传入的 dbResult 已经是 char **，这里又加了一个 & 取地址符，传递进去的就成了 char ***
	// 用于存储SQL语句
	char sql_str[1024] = {};
	snprintf(sql_str, 400, "select username,password from user");
	result = sqlite3_get_table(db, sql_str, &dbResult, &nRow, &nColumn, &errmsg);
	// 查询成功
	if (SQLITE_OK == result)
	{
		for (; i < nRow; i++)
		{
			if (strncmp(username, dbResult[nColumn + 2 * i], 20) == 0)
			{
				printf("<script>alert(\"用户名已存在，请更换用户名！\")</script>\n\n");
				break;
			}
			else if (i == nRow - 1)
			{
				snprintf(sql_str, 400, "insert into user values(\"%s\", \"%s\")", username, password);
				result = sqlite3_exec(db, sql_str, 0, 0, &errmsg);
				if (SQLITE_OK != result)
				{
					printf("<script>alert(\"注册失败！\");</script>");
					sqlite3_free_table(dbResult);
					// 关闭数据库
					sqlite3_close(db);
					return -1;
				}
				printf("<script>alert(\"注册成功！\");</script>\n\n");
				printf("<meta http-equiv=Refresh content=1;URL=../login2.html>\n\n");
			}
		}
	}
	else
	{
		printf("<script>alert(\"查询数据失败\");</script>");
		return -1;
	}

	// 到这里，不论数据库查询是否成功，都释放 char** 查询结果，使用 sqlite 提供的功能来释放
	sqlite3_free_table(dbResult);

	// 关闭数据库
	sqlite3_close(db);

	return 0;
}