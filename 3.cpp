#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

struct position
{
    int x;
    int y;
    void operator=(const position pos)
    {
        x=pos.x;
        y=pos.y;
    }
};

bool init(int, int, char***);//初始化迷宫地图
char** getMaze(int, int);//生成迷宫
void findPath(vector<position> &, char**, int, int);//找到迷宫出路
void display(vector<position> &, char**, int, int);//显示答案

int main()
{
    int row,col;
    char **maze;
    vector<position> path;
    
    while(1)//生成用户相对满意的迷宫
    {
        cout<<"请输入迷宫的行数（r）和列数（c）(行数或列数不得大于2147483647，按ctrl+c退出本程序）):";
        cin>>row>>col;//输入迷宫的长和宽
        if(!(row&&col)) cout<<"行数或列数必须为正整数！"<<endl;
        else if(init(row,col, &maze)) break;
    }
    
    findPath(path, maze, row, col);
    display(path, maze, row, col);
    
    return 0;
}

bool init(int row, int col, char ***maze)
{
    int flag;
    *maze=getMaze(row,col);
    cout<<"是否重新生成地图（可再次输入行和列）？(输入数字1重新生成地图，数字0使用当前地图)：";
    cin>>flag;
    while(!(flag==0||flag==1))
    {
        cout<<"您输入的数字不合法，请重新输入！"<<endl;
        cin>>flag;
    }
    if(flag) return false;
    return true;
}

char** getMaze(int r,int c)//返回存取迷宫的二维指针
{
    char **maze;              //定义二维指针存取迷宫
    maze=new char *[r+2];  //申请长度等于行数加2的二级指针，方便建立迷宫边界
    for(int i= 0;i<r+2;i++)  //申请每个二维指针的空间
    {
        maze[i]=new char[c+2];
    }
    for(int i=0;i<r+2;i++)
        for(int j=0;j<c+2;j++)
            maze[i][j]='#';
    
    srand((unsigned)time(NULL));//随机数种子
    
    int runX=1, runY=1;
    maze[1][1]='0';
    maze[r][c]='0';
    if(r==1&&c==1) cout<<"请注意，该迷宫没有游戏性！"<<endl;
    else if(r==1)
        for(int i=2;i<=c;i++)
            maze[r][i]='0';
    else if(c==1)
        for(int i=2;i<=r;i++)
            maze[i][c]='0';
    else
    {
        while(maze[r-2][c]!='0'&&maze[r][c-2]!='0'&&maze[r-1][c-1]!='0')
        {
            int flag=0;
            int L=0,R=0,U=0,D=0;
            int num=rand();
            
            //随机砸墙，生成道路
            if(num%4==0&&runX!=1)//左
            {
                runX--;
                L=1;
            }
            else if(num%4==1&&runX!=r)//右
            {
                runX++;
                R=1;
            }
            else if(num%4==2&&runY!=1)//上
            {
                runY--;
                U=1;
            }
            else if(num%4==3&&runY!=c)//下
            {
                runY++;
                D=1;
            }
            if((maze[runX][runY-1]=='0'&&maze[runX+1][runY-1]=='0'&&maze[runX+1][runY]=='0')
               ||(maze[runX][runY+1]=='0'&&maze[runX+1][runY+1]=='0'&&maze[runX+1][runY]=='0')
               ||(maze[runX][runY-1]=='0'&&maze[runX-1][runY-1]=='0'&&maze[runX-1][runY]=='0')
               ||(maze[runX][runY+1]=='0'&&maze[runX-1][runY+1]=='0'&&maze[runX-1][runY]=='0'))
                flag=1;//不出现正方形互通单元格
            
            if(flag)
            {
                if(L) runX++;
                else if(R) runX--;
                else if(U) runY++;
                else if(D) runY--;
                continue;
            }
            maze[runX][runY]='0';
        }
    
    //打通通往终点的路
    if(maze[r][c-2]=='0') maze[r][c-1]='0';
    else if(maze[r-2][c]=='0') maze[r-1][c]='0';
    else if(rand()%2) maze[r][c-1]='0';
    else maze[r-1][c]='0';
    }
    
    cout<<"\n迷宫地图（左上角坐标定义为(1,1)作为起点，右下角坐标(r,c)为终点）：\n"<<endl;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
            cout<<maze[i][j]<<"\t";
        cout<<endl;
        cout<<"\n";
    }
    
    return maze;              //返回存贮迷宫的二维指针maze
};

void findPath(vector<position> &path, char **maze, int r, int c)
{
    char **pathMaze=maze;
    //初始位置
    position pos;
    pos.x=1;
    pos.y=1;
    path.push_back(pos);
    
    while(!(pos.x==r&&pos.y==c))
    {
        //向四个方向查找是否有通路，有则移动，并将本位置设为禁入点
        if(pathMaze[pos.x+1][pos.y]=='0')
        {
            pathMaze[pos.x][pos.y]='!';
            (pos.x)++;
            path.push_back(pos);
        }
        else if(pathMaze[pos.x][pos.y+1]=='0')
        {
            pathMaze[pos.x][pos.y]='!';
            (pos.y)++;
            path.push_back(pos);
        }
        else if(pathMaze[pos.x-1][pos.y]=='0')
        {
            pathMaze[pos.x][pos.y]='!';
            (pos.x)--;
            path.push_back(pos);
        }
        else if(pathMaze[pos.x][pos.y-1]=='0')
        {
            pathMaze[pos.x][pos.y]='!';
            (pos.y)--;
            path.push_back(pos);
        }
        //死路，原路返回
        else
        {
            pathMaze[pos.x][pos.y]='!';
            path.pop_back();
            //cout<<path.back().x<<" "<<path.back().y<<" p"<<endl;
            pos=path.back();
        }
    }
}

void display(vector<position> &path, char** maze, int r, int c)
{
    maze[1][1]='X';//起始点必定为解谜路径
    cout<<"\n迷宫路径：\n"<<endl;
    cout<<"<"<<path[0].x<<","<<path[0].y<<">";
    for(int i=1;i<path.size();i++)
    {
        maze[path[i].x][path[i].y]='X';//显示路径
        cout<<" ---> "<<"<"<<path[i].x<<","<<path[i].y<<">";
    }
    cout<<"\n";
    cout<<"\n解谜地图：\n"<<endl;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            if(maze[i][j]=='!') maze[i][j]='0';//地图复原
            cout<<maze[i][j]<<"\t";
        }
        cout<<"\n"<<endl;
    }
}
