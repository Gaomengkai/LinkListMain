// LinkListMain.cpp : Defines the entry point for the application.
//

#include "LinkListMain.h"

#define PRINT_STATUS	printStatus(st, op);
#define t_sleep(x)		std::this_thread::sleep_for(std::chrono::milliseconds((x)));
#define CHK_EXT if(!L){puts("[NONE]\t线性表不存在！");break;}

using namespace std;

int main()
{
	SetConsoleTitle("来自Asuna Gao, 链表管理，ver0.00");
	printMenu();

	int			op = 1;
	status		st = OK;
	LinkList	L = NULL;
	int			i = 0;
	ElemType	pre;
	ElemType	next;
	ElemType	e;

	char		fileName[1000];
	char		listName[1000];
	memset(fileName, 0, sizeof(fileName));
	memset(listName, 0, sizeof(listName));

	while (op) {
		cout << "\n您的选项：";
		cin >> op;
		switch (op)
		{
		case 0:
			puts("谢谢使用。我去玩咯~");
			t_sleep(1500);
			// 这是附加功能 (> = <)
			return 0;
		case 1:
			st = InitList(L);
			PRINT_STATUS;
			break;
		case 2:
			st = DestroyList(L);
			PRINT_STATUS;
			break;
		case 3:
			st = ClearList(L);
			PRINT_STATUS;
			break;
		case 4:
			st = ListEmpty(L);
			if (st == INFEASIBLE) {
				puts("线性表不存在！");
			}
			else {
				if (st)puts("[EMPTY]\t线性表是空的。");
				else puts("[NON_EMPTY]\t线性表非空。");
			}
			break;
		case 5:
			st = ListLength(L);
			if (st == INFEASIBLE)puts("[NONE]\t线性表不存在！");
			else printf("线性表的长度是：%d\n", st);
			t_sleep(800);
			break;
		case 6:
			CHK_EXT
			puts("获取线性表的第i个元素，请输入i:");
			cin >> i;
			st = GetElem(L, i, e);
			PRINT_STATUS;
			if (st == OK) {
				cout << "第 " << i << "个元素是 " << e << endl;
				t_sleep(800);
			}
			break;
		case 7:
			CHK_EXT
			puts("查找元素e，请输入您要查找的元素：");
			cin >> e;
			st = LocateElem(L, e);
			PRINT_STATUS;
			if (st == OK) {
				cout << "您要查找的元素的位置是" << st << endl;
				t_sleep(800);
			}
			break;
		case 8:
			CHK_EXT
			puts("您正在查找e的前驱，现在请输入e");
			cin >> e;
			st = PriorElem(L, e, pre);
			PRINT_STATUS;
			if (st == OK) {
				cout << e << "的前驱是" << pre << endl;
				t_sleep(800);
			}
			break;
		case 9:
			CHK_EXT
			puts("您正在查找e的后继，现在请输入e");
			cin >> e;
			st = NextElem(L, e, pre);
			PRINT_STATUS;
			if (st == OK) {
				cout << e << "的后继是" << pre << endl;
				t_sleep(800);
			}
			break;
		case 10:
			CHK_EXT
			puts("您正在尝试将e插入到表中第i个元素之前");
			printf("现在请您输入e:");
			cin >> e;
			printf("\n现在请您输入i:");
			cin >> i;
			st = ListInsert(L, i, e);
			PRINT_STATUS;
			break;
		case 11:
			CHK_EXT
			puts("您正在尝试删除表中第i个元素。");
			printf("现在，请您输入i:");
			cin >> i;
			st = ListDelete(L, i, e);
			PRINT_STATUS;
			if (st == OK) {
				cout << "您删除了" << e << endl;
				t_sleep(800);
			}
			break;
		case 12:
			CHK_EXT
			st = ListTraverse(L);
			PRINT_STATUS;
			break;
		case 13:
			CHK_EXT
			puts("输入文件名：");
			cin >> fileName;
			st = SaveList(L, fileName);
			PRINT_STATUS;
			break;
		case 14:
			puts("输入文件名：");
			cin >> fileName;
			st = LoadList(L, fileName);
			PRINT_STATUS;
			break;
		default:
			puts("您惊扰了 Witch");
			// puts("您输入了一个不太合理的数字哦~");
			puts("请重新输入");
			break;
		}
		t_sleep(600);
		printMenu();
	}
	return 0;
}

void printMenu() {
	puts("\n\n\n       欢迎使用这个链表系统。");
	puts("==================================");
	puts("      输入数字来进行活动");
	puts("==================================");
	puts("0. 退了");
	puts("1. 创建一个默认链表");
	puts("2. 销毁这个默认链表");
	puts("3. 清空这个默认链表");
	puts("4. 链表是不是空的？");
	puts("5. 求链表的长度");
	puts("6. 获取链表中指定位置的元素");
	puts("7. 查找某个元素的位置");
	puts("8. 获取某个元素的前驱元素");
	puts("9. 获取某个元素的后继元素");
	puts("10插入一个元素");
	puts("11删除一个元素");
	puts("12遍历链表");
	puts("13从文件读取线性表");
	puts("14向文件写入线性表");
}

void printStatus(int st, int op) {
	if (st == INFEASIBLE) {
		switch (op)
		{
		case 1:
		case 14:
			puts("[CONFLICT] 线性表已经存在了哦~");
			break;
		default:
			puts("[NONE]\t线性表不存在！");
			break;
		}
	}
	else if (st == OK) {
		puts("[OK]\t操作成功！");
	}
	else if (st == FILEERROR) {
		puts("[FILE] 文件操作失败！");
	}
	else if (st == ERROR) {
		switch (op) {
		case 1:
			puts("[ERROR]\t分配内存错误！");
			break;
		case 6:
			puts("[ERROR]\t输入的i不合法！");
			break;
		case 7:
			puts("[NONE]\t查找的元素不存在！");
			break;
		case 8:
			puts("[NONE]\t查找的元素没有前驱或者元素不合法！");
			break;
		case 10:
			puts("[INDEXERROR]\t插入的位置不合法！");
			break;
		case 11:
			puts("[INDEXERROR]\t要删除的位置不合法！");
			break;
		default:
			puts("[ERROR]\t[UNEXPECTED]\t未经处理的异常！");
			break;
		}
		return;
	}
}