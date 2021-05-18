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

#include "cgic.h"

int cgiMain(void)
{
	// 使用MIME头信息″Content-type: text/html\n\n″来输出HTML源代码给Web服务器。
	// 请注意任何MIME头信息后必须有一个空行。一旦发送这个MIME头信息给Web服务器后,Web浏览器将认为随后的文本输出为HTML源代码
	printf("Content-type: text/html\n\n");
	char username[40] = {};
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
	printf("用户名:%s\n\n",username);
	printf("密码:%s\n\n",password);
    printf("确认密码:%s\n\n",password2);

	return 0;
}