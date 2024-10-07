/*
 * @Description:
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-07 14:46:33
 * @LastEditTime: 2024-10-07 22:27:43
 */

/*
比赛规则
学校举行一场演讲比赛，共有12个人参加。比赛共两轮，第一轮为汰赛，第二轮为决赛。
每名选手都有对应的编号，如10001~10012

比赛方式: 分组比赛，每组6个人;
第一轮分为两个小组，整体按照选手编号进行抽签后顺序演讲，
十个评委分别给每名选手打分，去除最高分和最低分，求的平均分为本轮选手的成绩
当小组演讲完后，淘汰组内排名最后的三个选手，前三名晋级，进入下一轮的比赛。
第二轮为决赛，前三名胜出
每轮比赛过后需要显示晋级选手的信息

程序功能
开始演讲比赛:完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
查看往届记录:查看之前比赛前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
清空比赛记录:将文件中数据清空
退出比赛程序:可以退出当前程序

比赛流程分析:
抽签 → 开始演讲比賽 → 显示第-轮比賽结果 →
插签 → 开始演讲比賽 → 显示前三名结果 → 保存分数
*/

#include "speechManager.h"
#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, char *argv[])
{
    // 在Windows系统中，控制台默认使用的是系统本地编码（通常是GBK或GB2312），而源代码是使用UTF-8编码保存的，这会导致在控制台输出时出现乱码
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8

    SpeechManager sm; // 创建对象

    int choice = -1;
    while (true)
    {
        // 展示菜单
        sm.showMenu();

        // 测试代码
        for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
            cout << "Player's ID: " << it->first << "\tPlay's name: " << it->second.m_name << "\tPlay's score: " << it->second.m_score[0] << endl;

        cout << endl
             << "Please input your choice:  ";
        cin >> choice;
        switch (choice)
        {
        case 0: // 退出比赛程序
            sm.exitSystem();
            return 0;
        case 1: // 开始演讲比赛
            break;
        case 2: // 查看往届记录
            break;
        case 3: // 清空比赛记录
            break;
        default:
            system("cls"); // windows系统的清屏  Unix-like系统(如Linux或macOS)是system("clear");
            break;
        }
    }

    return 0;
}
