/*
 * @Description:                    演讲管理类
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-07 19:57:11
 * @LastEditTime: 2024-10-14 18:24:53
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
    this->m_record.clear();
}

// 构造函数
SpeechManager::SpeechManager()
{
    // 初始化属性
    this->initSpeech();
    // 创建选手
    this->createSpeaker();
    // 加载往届记录
    this->loadRecord();
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
    int n = nameSeed.length();  // 选手人数
    for (int i = 0; i < n; i++) // 若用nameSeed.length()返回的是 std::string::size_type 类型，这通常是一个无符号整数（unsigned），而这里i是int
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

// 比赛流程控制
void SpeechManager::controlSpeech()
{
    // 第一轮比赛
    // 抽签
    this->speechDraw();
    // 比赛
    this->startSpeech();
    // 显示晋级结果
    this->showScore();

    // 第二轮比赛
    this->m_index++;
    // 抽签
    this->speechDraw();
    // 比赛
    this->startSpeech();
    // 显示最终结果
    this->showScore();

    // 保存分数到文件中
    this->saveSpeechData();

    // 重置比赛，初始化属性      比赛结束数据没有实时更新，需要在比赛结束后将所有数据重置
    this->initSpeech();
    // 创建选手
    this->createSpeaker();
    // 加载往届记录
    this->loadRecord();

    cout << "本次比赛圆满结束!" << endl;
    system("pause");
    system("cls");
}

// 抽签
void SpeechManager::speechDraw()
{
    cout << "第 " << this->m_index << " 轮比赛: " << endl;
    cout << "抽签后选手演讲顺序如下: " << endl;
    if (this->m_index == 1)
    {
        // 第一轮比赛
        random_shuffle(v1.begin(), v1.end()); // 打乱顺序
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    else
    {
        // 第二轮比赛
        random_shuffle(v2.begin(), v2.end()); // 打乱顺序
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
    cout << endl;
    // system("pause");
}

// 开始比赛
void SpeechManager::startSpeech()
{
    cout << "第 " << this->m_index << " 轮比赛正式开始: " << endl
         << endl;

    // 准备临时容器存放小组成绩
    multimap<double, int, greater<double>> groupScore; // <分数，选手编号，从大到小>
    int num = 0;                                       // 人员个数: 6人一组
    vector<int> v;                                     // 当前比赛选手

    if (this->m_index == 1)
        v = v1;
    else
        v = v2;

    // 遍历所有选手进行比赛
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        num++;
        // 评委打分
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f; // 60 ~ 100
            // cout << score << ' ';
            d.push_back(score);
        }
        // cout << endl;
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front(); // 去掉最高最低分
        d.pop_back();
        // 累加总分
        double sum = accumulate(d.begin(), d.end(), 0.0f); // 0.0f 为起始累加值
        // 平均分
        double avg = sum / (double)d.size(); // 浮点 / 整型 == 整型
        // cout << "Player's ID: " << *it << "\tPlay's name: " << this->m_speaker[*it].m_name << "\tPlay's avg_score: " << avg << endl;
        // 将平均分放入map容器
        this->m_speaker[*it].m_score[this->m_index - 1] = avg;
        // 将打分数据放入临时小组容器中
        groupScore.insert(make_pair(avg, *it));
        if (num % 6 == 0)
        {
            cout << "第 " << num / 6 << " 小组比赛名次如下: " << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
                cout << "Player's ID: " << it->second << "\tPlay's name: " << this->m_speaker[it->second].m_name << "\tPlay's avg_score: " << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;

            // 取走前3名去下一轮
            int cnt = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && cnt < 3; it++, cnt++)
            {
                // 如果这是第1轮，则取走进入第2轮，否则进入决赛
                if (this->m_index == 1)
                    v2.push_back((*it).second);
                else
                    v3.push_back((*it).second);
            }
            groupScore.clear(); // 比赛结束，清空容器
        }
    }
    cout << endl;
    cout << "第 " << this->m_index << " 轮比赛结束！" << endl;
    cout << endl;
}

// 显示比赛分数
void SpeechManager::showScore()
{
    cout << "第 " << this->m_index << " 轮晋级选手成绩如下: " << endl;
    vector<int> v;
    if (this->m_index == 1)
        v = v2;
    else
        v = v3;
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << "Player's ID: " << *it << "\tPlay's name: " << this->m_speaker[*it].m_name << "\tPlay's avg_score: " << this->m_speaker[*it].m_score[this->m_index - 1] << endl;
    cout << endl;
    system("pause");
    system("cls");
}

// 保存分数到文件
void SpeechManager::saveSpeechData()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app); // 用输出并追加的方式打开（写文件）
    // 将每个人的数据写入文件
    for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
        ofs << *it << "," << m_speaker[*it].m_score[1] << ",";

    ofs << endl;

    ofs.close(); // 关闭文件
    cout << "数据已成功保存至文件!" << endl;
    this->isFileEmpty = false; // 文件有数据了
}

// 加载往届记录
void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in);
    if (!ifs.is_open())
    {
        this->isFileEmpty = true;
        cout << "文件不存在! " << endl;
        ifs.close();
        return;
    }

    // 文件清空的情况
    char ch;
    ifs >> ch;     // 读取开头字符
    if (ifs.eof()) // 读到的是文件结尾
    {
        cout << "文件为空! " << endl;
        this->isFileEmpty = true;
        ifs.close();
        return;
    }

    // 文件不为空的情况
    this->isFileEmpty = false;
    ifs.putback(ch); // 把刚刚读走的字符放回去
    int index = 1;   // 第几届记录
    string data;
    while (ifs >> data) // 将文件中的数据一行一行读到data中
    {
        // 例: 10002,86.675,10009,81.3,10007,78.55
        int pos = -1;     // 查找 , 位置
        int startPos = 0; // 查找的起始位置
        vector<string> v; // 存放6个string字符串数据
        while (true)
        {
            pos = data.find(",", startPos);
            if (pos == -1)
                break;
            string temp = data.substr(startPos, pos - startPos);
            // cout << temp << endl;
            v.push_back(temp);
            startPos = pos + 1;
        }
        this->m_record.insert(make_pair(index++, v));
    }
    ifs.close();
}

// 查看往届记录
void SpeechManager::showRecord()
{
    if (this->isFileEmpty)
        cout << "文件不存在或文件为空! " << endl;
    else
    {
        int n = this->m_record.size();
        cout << "record size: " << n << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << "第 " << i << " 届  "
                 << "冠军ID: " << this->m_record[i][0] << "\t得分: " << this->m_record[i][1] << "\t"
                 << "亚军ID: " << this->m_record[i][2] << "\t得分: " << this->m_record[i][3] << "\t"
                 << "季军ID: " << this->m_record[i][4] << "\t得分: " << this->m_record[i][5] << endl
                 << endl;
        }
    }

    system("pause");
    system("cls");
}

// 清空比赛记录
void SpeechManager::clearRecord()
{
    cout << "确认清空所有数据?('y' or 'n'): ";
    char select;
    cin >> select;
    if (select == 'y')
    {
        ofstream ofs("speech.csv", ios::trunc); // trunc: 如果文件存在则删除文件并重新创建
        ofs.close();
        // 初始化属性
        this->initSpeech();
        this->createSpeaker();
        this->loadRecord();

        cout << "清空成功!" << endl;
    } 
    system("pause");
    system("cls");
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
