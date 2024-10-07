/*
 * @Description:                    演讲管理类
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-07 19:57:11
 * @LastEditTime: 2024-10-07 22:27:12
 */

#include "speechManager.h"

// 初始化成员属性
void SpeechManager::initSpeech()
{
    // 容器都置空
    this->v1.clear();
    this->v2.clear();
    this->v3.clear();
    this->m_speaker.clear();
    this->m_index = 1;
}

// 构造函数
SpeechManager::SpeechManager()
{
    // 初始化属性
    this->initSpeech();
    // 创建选手
    this->createSpeaker();
}

// 展示菜单
void SpeechManager::showMenu()
{
    cout << "***************************************" << endl;
    cout << "*********** 欢迎参加演讲比赛 **********" << endl;
    cout << "***********  1.开始演讲比赛 ***********" << endl;
    cout << "***********  2.查看往届记录 ***********" << endl;
    cout << "***********  3.清空比赛记录 ***********" << endl;
    cout << "***********  0.退出比赛程序 ***********" << endl;
    cout << "***************************************" << endl;
}

// 创建选手
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    int n = nameSeed.length();   // 选手人数
    for (int i = 0; i < n; i++)  // 若用nameSeed.length()返回的是 std::string::size_type 类型，这通常是一个无符号整数（unsigned），而这里i是int
    {
        string name = "选手";
        name += nameSeed[i];

        Speaker speaker;
        // 选手姓名
        speaker.m_name = name;
        // 选手初始分数为0
        speaker.m_score[0] = 0;
        speaker.m_score[1] = 0;
        // 12名选手编号
        this->v1.push_back(i + 10001);
        // 选手编号及对应选手
        this->m_speaker.insert(make_pair(i + 10001, speaker));
    }
}

// 退出比赛程序
void SpeechManager::exitSystem()
{
    cout << "Successfully exited the system! Welcome to use next time" << endl;
    exit(0);
}

// 析构函数
SpeechManager::~SpeechManager()
{
}
