/*
 * @Description:                    演讲管理类
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-07 19:57:06
 * @LastEditTime: 2024-10-14 22:02:41
 */

#pragma once
#include "Speaker.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <deque>
#include <algorithm>
#include <functional> // sort(v.begin(), v.end(), greater<double>())
#include <numeric>    // accumulate()
using namespace std;

class SpeechManager
{
public:
    // 成员属性
    // 比赛选手 12人
    vector<int> v1;
    // 第一轮晋级 6人
    vector<int> v2;
    // 胜利的前3名
    vector<int> v3;
    // 存放选手编号及对应选手
    map<int, Speaker> m_speaker;
    // 记录比赛轮次
    int m_index;
    // 判断文件是否为空
    bool isFileEmpty;
    // 往届记录
    map<int, vector<string>> m_record; // <第几届, 每一届的记录>

    // 初始化成员属性
    void initSpeech();

    // 构造函数
    SpeechManager();

    // 展示菜单
    void showMenu();

    // 创建选手
    void createSpeaker();

    // 比赛流程控制
    void controlSpeech();

    // 抽签
    void speechDraw();

    // 开始比赛:
    void startSpeech();

    // 显示比赛分数
    void showScore();

    // 保存分数到文件
    void saveSpeechData();

    // 加载往届记录
    void loadRecord();

    // 查看往届记录
    void showRecord();

    // 清空比赛记录
    void clearRecord();

    // 退出比赛程序
    void exitSystem();

    // 析构函数
    ~SpeechManager();
};